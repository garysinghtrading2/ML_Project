#include<iostream>
#include<vector>
#include "matrix_rotation.h"
#include "vector_operations.h"
#include "kde.h"
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
    vector<vector<double>> Historical_Data = {
        {1.0, 2.0},
        {1.5, 2.5},
        {2.0, 2.0},
        {5.0, 6.0},
        {5.5, 5.5}
    };

    vector<vector<float>> b = {
        {2,0, 2.5},
    }; 

    //vector<vector<float>> mat = MatrixMult(a,b);

    vector<double> x1 = {2.0, 2.5};

    double pct_ = get_point_density(Historical_Data, x1, 1.0);
    if(pct_ < 20.0){ cout << "Potential Anomaly" << endl;}
    

    
    return 0;
}
