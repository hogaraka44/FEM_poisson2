//right
#include <iostream>
#include <vector>
#include "readmesh.h"
#include "math.h"
#include "bconExt.h"

#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
//std::vector<std::vector<double>> mat;


double f(std::vector<double>& posv){
    //double j =  0; //収束確認済み 1
    double j = sin(M_PI *posv[0]) * sin(M_PI *posv[1]);
    //std::cout <<"f(" << "x=" << posv[0]<< "y= " << posv[1] << ")= " << j  << std::endl; 
    return  j;
}

double u(std::vector<double>& posv){
    double j =  .001; 
    //double j =  10*pow(posv[0],3) + 10*pow(posv[1],3)  + 1;
    /*if(posv[1] == 1){
        j =  posv[0] * (1 - posv[0]);
    }*/ //収束確認済み 1
    
    return  j;
}


double AnaU(std::vector<double>& posv){
    double sum = 0.0;
    /*for (int n = 1; n <= 15; n += 2) { // nを1,3,5,...,15と繰り返す
        double term = sin(n * M_PI * posv[0]) * sinh(n * M_PI * posv[1]) / (n * n * n * sinh(n * M_PI));
        sum += term;
    }
    sum  = (8 / pow(M_PI, 3)) * sum    
    */ //収束確認済み 1
    sum = 1 / (2 * pow(M_PI,2)) * sin(M_PI *posv[0]) * sin(M_PI *posv[1]) + .001; //-1倍ずれてる

    return sum; 
}

void Rbcon1(std::vector<std::vector<double>>& mat){
    int m = mat.size();
    int n = gamma1Num.size();

    for(int i = 0;i<n;i++){
        mat[gamma1Num[i]][m] = u(poses[gamma1Num[i]]);
    }    
}

void Rhs(std::vector<std::vector<double>>& mat1 ){


    //int k = triangles.size();

    int n = mat1.size();
    std::vector<std::vector<double>> rmat(n, std::vector<double>(n));
    printf("size %d\n",n);
    /*2 1
      1 2*/
    //int m = poses.size();//n ==m
    int k = triangles.size();

    for(int i=0;i<k;i++){
        //printf("num is %d\n",i);

        for(int j=0;j<3;j++){
            for(int l=0;l<3;l++){
                if(j==l){
                    rmat[triangles[i][j]][triangles[i][l]]  += 2 ;
                }
                else{
                    rmat[triangles[i][j]][triangles[i][l]]  += 1 ;
                }
            }

        }

    }

    for (int i = 0; i < n; i++)
    {
        for(int j =0;j<n;j++){
            mat1[i][n] += rmat[i][j] * f(poses[j]);
        }
    }
    


   

    //correct
    std::cout << "area = " <<  pow((1/ (double)(sqrt(n)-1) ),2)/2.0 <<std::endl;
    for(int i = 0;i<n;i++){
        mat1[i][n] *= pow((1/ (double)(sqrt(n)-1) ),2) / 2.0 /12.0;  
    }


    //?o??
/*
    printf("??????????mat1\n");
    for(int i=0;i<m;i++){
        for(int j=0;j<m+1;j++){
            std::cout << mat1[i][j] <<" ";
        }
        std::cout  << std::endl;
    }
*/

    Rbcon1(mat1);
    printf("右辺\n");
    for(int i=0;i<n;i++){
        //for(int j=0;j<m+1;j++){
        std::cout << mat1[i][n] << std::endl;
        //}
        //std::cout  << std::endl;
    }

    

  
}

