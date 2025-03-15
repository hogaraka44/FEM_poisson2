#include <iostream>
#include <vector>


// ガウス・ジョルダン法を実行する関数
//n, n+1行列
void gaussJordan(std::vector<std::vector<double>>& matrix) {
    int n = matrix.size();
    std::cout << "size " << n <<std::endl;
    for (int i = 0; i < n; i++) {
        // 対角成分を1にする
        double diag = matrix[i][i];
        for (int j = 0; j < n + 1; j++) {
            matrix[i][j] /= diag;
        }

        // 他の行から現在の列を消去する
        for (int k = 0; k < n; k++) {
            if (k != i) {
                double factor = matrix[k][i];
                for (int j = 0; j < n + 1; j++) {
                    matrix[k][j] -= factor * matrix[i][j];
                }
            }
        }
    }
}



