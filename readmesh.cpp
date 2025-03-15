#include "readmesh.h"
#include <fstream>
#include <sstream>
#include <iostream>

// グローバル変数の定義
std::vector<std::vector<double>> poses;//無くてもいいのでは
std::vector<std::vector<int>> triangles;

void loadPoses(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error: " << filename << " を開けませんでした。" << std::endl;
        return;
    }

    std::getline(file, line); // ヘッダーをスキップ
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::vector<double> point(2);
        std::string x_str, y_str;

        if (std::getline(ss, x_str, ',') && std::getline(ss, y_str, ',')) {
            point[0] = std::stod(x_str);
            point[1] = std::stod(y_str);
            poses.push_back(point);
        } else {
            std::cerr << "Error: 無効な行形式: " << line << std::endl;
        }
    }
}

void loadTriangles(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error: " << filename << " を開けませんでした。" << std::endl;
        return;
    }

    std::getline(file, line); // ヘッダーをスキップ
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::vector<int> triangle(3);
        std::string v1_str, v2_str, v3_str;

        if (std::getline(ss, v1_str, ',') &&
            std::getline(ss, v2_str, ',') &&
            std::getline(ss, v3_str, ',')) {
            triangle[0] = std::stoi(v1_str);
            triangle[1] = std::stoi(v2_str);
            triangle[2] = std::stoi(v3_str);
            triangles.push_back(triangle);
        } else {
            std::cerr << "Error: 無効な行形式: " << line << std::endl;
        }
    }
}
