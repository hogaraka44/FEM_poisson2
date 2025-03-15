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



//�g��W���s��̕\���֐�
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

//�����W���s��̕\���֐�
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
//���E����
case�ɂ���Ċ�{���E����(�����Ȃ�)���㏑�����Ă��玩�R���E����(�@����������)�𑫂����킹��
*/
void Lbcon1(std::vector<std::vector<double>>& mat){
    //��{���E����
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


//�ꎟ���̏ꍇ
/*1~n�܂�lmat�𑫂�*/
int main(){
    
    //���E�̐ݒ�
    bconExt();
    
    int k = triangles.size();
    int m = poses.size();
    std::vector<std::vector<double>> matA(m, std::vector<double>(m + 1));
    for(int i=0;i<k;i++){
        //9�ɂȂ�
        /*
        1 (0,25):[k] = triangles[i][0]] :[n][3]
        0.3 =  b[1] : [k]
        */
       //matA[triangeles[�_�̏ꏊ(tri�ōl����)][�_�̏ꏊ(tri�ōl����)]]
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

    //�ʐς�������
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

    //�E��
    Rhs(matA);

    //�o��
    //printf("input\n");
    //out(matA);

    //�K�E�X�W�����_��
    gaussJordan(matA);

    //�o��
    //printf("out\n");
    //out(matA);

    
    std::cout << "���ƌ덷�̊���" << std::endl;
    int ins = interNum.size();
    int as =  matA.size();

    for(int i = 0;i<ins;i++){
        double s = AnaU(poses[interNum[i]]);
        double ms = matA[interNum[i]][as];
        //std::cout  << poses[interNum[i]][0]  << " , " << poses[interNum[i]][1] << ")�Ő^�̒l " <<
        // s << "\n���l�� " << matA[interNum[i]][as];// 
        std::cout <<  poses[interNum[i]][0]  << " , " << poses[interNum[i]][1] << ")"  << 
        ms << "," << s << "," << ( ms -s) << "," << ( ms -s)/s << std::endl;
    }    


}




/*
g++ -o ex mesh1.cpp gauss.cpp rhs.cpp readmesh.cpp

Ctrl+Shift+L -> cmake build 
./ex
*/