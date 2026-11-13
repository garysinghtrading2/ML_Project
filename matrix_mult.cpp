#include<iostream>
#include<vector>
using namespace std;

bool CanPerformMatrixMult(vector<vector<float>>& a, vector<vector<float>>& b){
    if(!a.empty() && !b.empty()){
        return a[0].size() == b.size();
    }
    return false;
}

vector<vector<float>> MatrixMult(vector<vector<float>>& a, vector<vector<float>>& b){
    // check do our dimensions match
    vector<vector<float>> answer(a.size());

    for(size_t i=0; i<a.size(); i++){
        vector<int> temp(a.size(), 0);
        for(size_t j=0; j<a.size(); j++){
            int value = 0;
            for(size_t k=0; k<b.size(); k++){
                value += a[i][k] * b[k][j];
            }
            temp[j] = value;
        } 
        answer[i] = temp;
    }
    return answer; 
}

int main(){
    vector<vector<int>> a = {
        {1,3,-2},
        {4,0,5}
    };

    vector<vector<int>> b = {
        {2,-1},
        {0,4},
        {3,1}
    };   


    return 0;
}