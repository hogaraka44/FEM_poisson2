#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

#include<stdio.h>
#include <iostream>
#include <math.h>


#include "gauss.h"
#include "rhs.h"
#include "readmesh.h"
#include "areaCoor.h"
#include "bconExt.h"



//拡大係数行列の表示関数
void out(std::vector<std::vector<double>>& matA ){
    int n  = matA.size();
    for(int i=0;i<n;i++){
        for(int j=0;j<n+1;j++){
            if(j != n){ std::cout << matA[i][j] <<" ";}
            else {std::cout << matA[i][j]   <<" ";}
        }
        std::cout  << std::endl;
    }
}

//正方係数行列の表示関数
void out2(std::vector<std::vector<double>>& matA ){
    int n  = matA.size();
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            std::cout << matA[i][j] <<" ";
        }
        std::cout  << std::endl;
    }
}

/*
//境界条件
caseによって基本境界条件(微分なし)を上書きしてから自然境界条件(法線方向微分)を足し合わせる
*/
void Lbcon1(std::vector<std::vector<double>>& mat){
    //基本境界条件
    int m = mat.size();
    int n = gamma1Num.size();
    for(int i = 0;i<n;i++){
        //if(i != 4){
        for(int j = 0;j <m;j++){
            mat[gamma1Num[i]][j] = 0;
        }
        mat[gamma1Num[i]][gamma1Num[i]] = 1;
        //} 
    }    
}


//一次元の場合
/*1~nまでlmatを足す*/
int main(){
    
    //境界の設定
    bconExt();
    
    int k = triangles.size();
    int m = poses.size();
    std::vector<std::vector<double>> matA(m, std::vector<double>(m + 1));
    for(int i=0;i<k;i++){
        //9個になる
        /*
        1 (0,25):[k] = triangles[i][0]] :[n][3]
        0.3 =  b[1] : [k]
        */
       //matA[triangeles[点の場所(triで考える)][点の場所(triで考える)]]
       //matA[[k][k]], k = triangles[i][0]]
       //matA[[k][l]], l = triangles[i][1]]
       //matA[[k][m]], m = triangles[i][2]]
        std::vector<std::vector<double>> matpos = {poses[triangles[i][0]],poses[triangles[i][1]],poses[triangles[i][2]]};

        for(int j =0;j<3;j++){
            matA[triangles[i][0]][triangles[i][j]] += CoorB(matpos,0) * CoorB(matpos,j) + CoorC(matpos,0) * CoorC(matpos,j);
            matA[triangles[i][1]][triangles[i][j]] += CoorB(matpos,1) * CoorB(matpos,j) + CoorC(matpos,1) * CoorC(matpos,j);
            matA[triangles[i][2]][triangles[i][j]] += CoorB(matpos,2) * CoorB(matpos,j) + CoorC(matpos,2) * CoorC(matpos,j);
        }

    }

    //面積をかける
    for(int i=0;i<m;i++){
        for(int j = 0;j<m;j++){
            //matA[i][j]  *= 1/2.0 *pow((1/ (sqrt(m)-1) ),2);    
            matA[i][j]  *= area;    //delta correct
        }
    }

    //std::cout << "matA" <<std::endl;
    //out(matA);

    Lbcon1(matA);
    //std::cout << " Lbcon & matA" <<std::endl;
    //out(matA);

    //右辺
    Rhs(matA);

    //出力
    //printf("input\n");
    //out(matA);

    //ガウスジョルダン
    gaussJordan(matA);

    //出力
    //printf("out\n");
    //out(matA);

    
    std::cout << "差と誤差の割合" << std::endl;
    int ins = interNum.size();
    int as =  matA.size();

    for(int i = 0;i<ins;i++){
        double s = AnaU(poses[interNum[i]]);
        double ms = matA[interNum[i]][as];
        //std::cout  << poses[interNum[i]][0]  << " , " << poses[interNum[i]][1] << ")で真の値 " <<
        // s << "\n数値解 " << matA[interNum[i]][as];// 
        std::cout <<  poses[interNum[i]][0]  << " , " << poses[interNum[i]][1] << ")"  << 
        ms << "," << s << "," << ( ms -s) << "," << ( ms -s)/s << std::endl;
    }    


}




/*
g++ -o ex mesh1.cpp gauss.cpp rhs.cpp readmesh.cpp

Ctrl+Shift+L -> cmake build 
./ex
*/