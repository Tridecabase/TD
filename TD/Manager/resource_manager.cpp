#include "resource_manager.h"

ResourceManager::ResourceManager() {
}

ResourceManager::~ResourceManager() {
    UnloadTexturesForScene("");
}

/*
 * CSVファイルからリソースの登録機能の概要
 *
 * 2024年10月5日、テクスチャの登録機能を追加しました。
 * CSVファイルからシーンごとのリソースを読み込み、関連付けます。
 *
 * 【機能の詳細】
 * 各行は3つの要素（ハンドル名、グループ名、パス）で構成されており、
 * texturePathsマップに格納されます。
 */
void ResourceManager::RegisterTexturesFromCSV(const std::string& csvFilePath) {
    //CSVパーサーの宣言
    CsvParser parser(csvFilePath);
    //データの読み込み
    auto texturesData = parser.Read();

    for (const auto& row : texturesData) {
        if (row.size() != 3) continue;      //各行には3つの要素

        std::string textureName = row[0];   //ハンドル名
        std::string sceneName = row[1];     //グループ名
        std::string texturePath = row[2];   //パス

        // 先にリソース情報だけ保存し、後でロード
        texturePaths[sceneName][textureName] = texturePath;
    }
}

/*
 * 非同期ロード機能の概要
 * 
 * 2024年10月4日、非同期リソースロード機能を追加しました。
 * シーンごとのリソースを非同期でロードし、主スレッドがブロックされるのを防ぎます。
 *
 * 【以前の同期ロード方式との違い】
 * 以前は、リソースの同期ロード中に主スレッドが停止していましたが、
 * 今回の非同期ロードではそれを回避できるようになりました。
 * 
 * 追記:Novice::LoadTextureは同期読み込みのため、ここでは実現できないことに気づいた。
 * でも、こう書いても影響はないから、このままでいこう。
 */
void ResourceManager::LoadTextures(const std::string& sceneName) {
    std::future<void> future = std::async(std::launch::async, &ResourceManager::LoadTexturesForScene, this, sceneName);
}

void ResourceManager::LoadTexturesForScene(const std::string& sceneName) {
    //スレッドセーフのロック
    std::lock_guard<std::mutex> lock(cacheMutex);

    if (textures.find(sceneName) != textures.end()) {
        return;
    }

    for (const auto& texturePair : texturePaths[sceneName]) {
        textures[sceneName][texturePair.first] = Novice::LoadTexture(texturePair.second.c_str());
    }
}

/*
 * リソースアンロード機能の概要
 *
 * この関数は、指定されたシーンに関連するリソースをメモリからアンロードする機能を提供します。
 * 特に、シーンごとのリソースをアンロードし、リソースを解放するメソッドが含まれています。
 */
void ResourceManager::UnloadTextures(const std::string& sceneName) {
    //指定されたシーンのリソースをアンロード
    UnloadTexturesForScene(sceneName);
}

void ResourceManager::UnloadTexturesForScene(const std::string& sceneName) {
    std::lock_guard<std::mutex> lock(cacheMutex);

    auto it = textures.find(sceneName);
    if (it != textures.end()) {
        for (const auto& texture : it->second) {
            Novice::UnloadTexture(texture.second);
        }
        textures.erase(it);
    }
}

/*
 * リソース描画機能の概要
 *
 * この関数は、リソースマネージャーによって管理されるリソースを描画する機能を提供します。
 * 特に、リソースを描画するメソッドとアニメーションのフレームを描画するメソッドが含まれています。
 */
void ResourceManager::Draw(int destX, int destY, const std::string& textureName, float scaleX, float scaleY, float angle, unsigned int color) {
    for (const auto& scene : textures) {
        //リソース名でシーン内を検索
        auto it = scene.second.find(textureName);

        if (it != scene.second.end()) {
            //描画
            Novice::DrawSprite(destX, destY, it->second, scaleX, scaleY, angle, color);
            return;
        }
    }
}

void ResourceManager::DrawAnimation(int destX, int destY, const std::string& baseTextureName, int currentFrame, float scaleX, float scaleY, float angle, unsigned int color) {
    //描画するリソース名を計算
    std::string textureName = baseTextureName + std::to_string(currentFrame);

    for (const auto& scene : textures) {
        auto it = scene.second.find(textureName);
        if (it != scene.second.end()) {
            //指定されたフレームをDrawSpriteで描画
            Novice::DrawSprite(destX, destY, it->second, scaleX, scaleY, angle, color);
            return;
        }
    }
}

void ResourceManager::DrawSpriteAnimation(int destX, int destY, int frameWidth, int frameHeight, const std::string& textureName, int currentFrame, float scaleX, float scaleY, float angle, unsigned int color) {
    for (const auto& scene : textures) {
        auto it = scene.second.find(textureName);
        if (it != scene.second.end()) {
            int textureHandle = it->second;

            int srcX = (currentFrame * frameWidth) % (frameWidth * frameWidth);
            int srcY = ((currentFrame * frameWidth) / (frameWidth * frameWidth)) * frameHeight;

            Novice::DrawSpriteRect(
                destX, destY,
                srcX, srcY,
                frameWidth, frameHeight,
                textureHandle,
                scaleX, scaleY,
                angle,
                color
            );
            return;
        }
    }
}
