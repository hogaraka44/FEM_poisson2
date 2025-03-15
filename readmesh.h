#ifndef REAMMESH_H
#define REAMMESH_H

#include <vector>
#include <string>

// グローバル変数の宣言
extern std::vector<std::vector<double>> poses;
extern std::vector<std::vector<int>> triangles;

void loadPoses(const std::string& filename);
void loadTriangles(const std::string& filename);

#endif // REAMMESH_H
