#include "csv_parser.h"

CsvParser::CsvParser(const std::string& filePath) : filePath(filePath) {}

/*
 * CSVパーサーの概要
 *
 * このクラスは、指定されたCSVファイルを読み込むための機能を提供します。
 * 各行を解析し、内容を2次元ベクターとして返します。
 */
std::vector<std::vector<std::string>> CsvParser::Read() {
    //ファイルを開きます
    std::ifstream file(filePath);
    //データを格納するベクター
    std::vector<std::vector<std::string>> data;
    //行を格納するための変数
    std::string line;

    //最初の行をスキップ
    std::getline(file, line);

    //行を1つずつ読み込み
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string item;
        std::vector<std::string> row;

        while (std::getline(ss, item, ',')) {
            row.push_back(item);
        }
        data.push_back(row);
    }
    return data;
}