#include "my_matrix.h"
#include <iostream>

int main(int argc,char *argv[])
{
    MyMatrix<int> matrix(2,3);
    matrix(1,2) = 2;
    MyMatrix<int> matrix1(2,2);
    matrix += matrix1; 
    std::cout << matrix << std::endl
              << matrix1 << std::endl;

    matrix =  matrix.Transpose();
    std::cout << matrix << std::endl;
    return 0;
}
