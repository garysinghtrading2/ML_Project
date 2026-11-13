#include<iostream>
#include<vector>
#include "matrix_rotation.h"
#include "vector_operations.h"
using namespace std;

bool CanPerformMatrixMult(const vector<vector<float>>& a, const vector<vector<float>>& b){
    if(!a.empty() && !b.empty()){
        return a[0].size() == b.size();
    }
    return false;
}

vector<vector<float>> MatrixMult(const vector<vector<float>>& a, const vector<vector<float>>& b){
    // check do our dimensions match
    if(!CanPerformMatrixMult(a, b)){
      throw invalid_argument("Matrix Dimensions do not match for multiplication");
    }
    size_t rowsA = a.size();
    size_t colsA = a[0].size();
    size_t colsB = b[0].size();

    vector<vector<float>> answer(rowsA, vector<float>(colsB, 0.0f)); // Declare a 2-D vector

    for(size_t i=0; i<rowsA; i++){
        for(size_t j=0; j<colsB; j++){
            float value = 0.0f;
            for(size_t k=0; k<colsA; k++){
                value += a[i][k] * b[k][j];
            }
            answer[i][j] = value;
        }
    }
    return answer; 
}

int main(){
    vector<vector<float>> a = {
        {2.0f, 5.0f},
        {40.f, 8.0f},
        {6.0f, 10.0f}
    };

    vector<vector<float>> b = {
        {7.0f,8.0f},
        {9.0f,10.0f},
        {11.0f,12.0f}
    }; 

    //vector<vector<float>> mat = MatrixMult(a,b);

    vector<float> x1 = {-1.0f, 0.0f, 1.0f};
    vector<float> x2 = {-2.33f, -0.333f, 2.667f};

    // dot product:
    cout << dot_product(x1, x2) << endl; 
    return 0;
}