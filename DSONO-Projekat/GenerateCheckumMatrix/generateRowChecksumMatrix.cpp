#include<vector>
#include<iostream>

std::vector<int> generateRowChecksumMatrix(std::vector<int> matrix, int dim){
    matrix = std::vector<int>();

    for(int i = 1;i <= dim*dim;i++)
        matrix.push_back(i);
    matrix.resize((dim+1)*(dim+1));

    int cnt = 0;
    for(int i = 0;i < matrix.size()/(dim+1);i++){
        for(int j = 0;j < matrix.size()/(dim+1);j++){
            if(cnt == dim){
                int p = 0;
                for(int k = i;k < i+1;k++){
                    for(int l = j-dim;l < dim;l++){
                        p += matrix[k*(dim+1)+l];
                    }
                }
                matrix.insert(matrix.begin()+(i*(dim+1)+j), p);
            }
            //std::cout << to_string(matrix[i*(dim+1)+j]) + " ";
            cnt++;
        }
        cnt = 0;
        //std::cout << std::endl;
    }

    matrix.resize((dim+1)*(dim+1));

    return matrix;
}

std::vector<int> generateColumnChecksumMatrix(std::vector<int> matrix, int dim){
    /*for(int i = 0;i < matrix.size()/(dim+1);i++){
        for(int j = 0;j < matrix.size()/(dim+1);j++){

        }
    }*/

    int p = 0;
    int cnt = 0;
    for(int i = 0;i < dim+1;i++){
        for(int j = 0;j < dim;j++){
            p += matrix[cnt];
            cnt += dim+1;
        }
        matrix.insert(matrix.begin()+(dim*(dim+1))+i, p);
        cnt = 0;
        cnt += i+1;
        p = 0;
    }

    matrix.resize((dim+1)*(dim+1));

    return matrix;
}