#include <iostream>
#include "readmesh.h"
#include "bconExt.h"


std::vector<int> gamma1Num;
std::vector<int> gamma2Num;
std::vector<int> interNum;

//‹«ŠE‚ğì‚éŠÖ”@
void bconExt(){

    //std::vector<std::vector <bool>> fieldNum;
   
    //tri.csv‚ğæ‚è‚Ş
    loadPoses("poses.csv");
    loadTriangles("triangles.csv");//poses,triangles‚ªg‚¦‚é‚æ‚¤‚É
    
    int pnum = poses.size();
    //int tnum = triangles.size();


    for(int i=0;i<pnum;i++){
        double x = poses[i][0]; 
        double y = poses[i][1]; 
        if(x == 0 || x==1 || y== 0 || y == 1){
            gamma1Num.push_back(i);
        }
      
        else{
            interNum.push_back(i);
        }
    }
    int n = gamma1Num.size();
    for(int i = 0;i<n;i++){
        std::cout << gamma1Num[i] << " ";
    }
    std::cout  << std::endl;


    int n2 = interNum.size();
    for(int i = 0;i<n2;i++){
        std::cout << interNum[i] << " ";
    }
    std::cout  << std::endl;
    
}

/*
int main(){
    bconExt();
    return 0;
}
*/
