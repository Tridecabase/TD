#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "../Tools/csv_parser.h"
#include <Novice.h>
#include <unordered_map>
#include <string>
#include <thread>
#include <mutex>
#include <map>
#include <future>

class ResourceManager {
public:
    ResourceManager();
    ~ResourceManager();

    void LoadTextures(const std::string& sceneName);
    void UnloadTextures(const std::string& sceneName);
    void RegisterTexturesFromCSV(const std::string& csvFilePath);
    void Draw(int destX, int destY, const std::string& textureName, float scaleX, float scaleY, float angle, unsigned int color);
    void DrawAnimation(int destX, int destY, const std::string& baseTextureName, int currentFrame, float scaleX, float scaleY, float angle, unsigned int color);
    void DrawSpriteAnimation(int destX, int destY, int frameWidth, int frameHeight, const std::string& textureName, int currentFrame, float scaleX, float scaleY, float angle, unsigned int color);

private:
    //シーンのリソースを読み込む
    void LoadTexturesForScene(const std::string& sceneName);
    //シーンのリソースを解放する
    void UnloadTexturesForScene(const std::string& sceneName);

    //リソースを保存するマップ
    std::unordered_map<std::string, std::unordered_map<std::string, int>> textures;
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> texturePaths;
    std::mutex cacheMutex;

};

#endif