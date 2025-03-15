//面積座標
#include <iostream>
#include <vector>

//b,c
double area;
double Delta(std::vector<std::vector<double>>& mat){
    //area = 1/2.0 * ((mat[0][1] - mat[0][0]) *(mat[1][2] - mat[1][0]) - (mat[0][2] - mat[0][0]) *(mat[1][1] - mat[1][0]) );
    area = 1/2.0 * ((mat[1][0] - mat[0][0]) *(mat[2][1] - mat[0][1]) - (mat[2][0] - mat[0][0]) *(mat[1][1] - mat[0][1]) );
    //std::cout <<"area= " << area <<std::endl;
    return area;
}


double CoorB(std::vector<std::vector<double>>& mat ,int i){
    //double sum = (mat[(i+1)%3][1] - mat[(i+2)%3][1])/(2.0 * Delta(mat));
    //std::cout <<"sum= " << sum <<std::endl;
    //mat[添え字][x or y or z] 
    return (mat[(i+1)%3][1] - mat[(i+2)%3][1])/(2.0 * Delta(mat));//delata correct
}

double CoorC(std::vector<std::vector<double>>& mat ,int i){
    //return (mat[(i+2)%3][0] - mat[(i+1)%3][0])/(2.0 * area);
    return (mat[(i+2)%3][0] - mat[(i+1)%3][0])/(2.0 * Delta(mat));//delata correct
}
