#include<vector>
#include<algorithm>
using namespace std;

vector<vector<float>> rotate_90(vector<vector<float>>& grid){
  size_t n=grid.size();
  // transpose
  for(size_t i=0; i<n; i++){
    for(size_t j=i+1; j<n; j++){
      swap(grid[i][j], grid[j][i]);
    }
  }
  // reverse
  for(size_t i=0; i<n; i++){
    reverse(grid[i].begin(), grid[i].end());
  }
  return grid;
}

vector<vector<float>> Matrix_rotation(vector<vector<float>>& grid){

  size_t rows = grid.size();
  size_t cols = grid[0].size();

  /*
  * Ignoring square rotation for now
  if(rows == cols){
    // square matrix
    return rotate_90(grid);
  } 
  */

  // else rectangular matrix a NxM matrix will be MxN
  vector<vector<float>> result(cols, vector<float>(rows, 0.0f));// new matrix of size MxN

  for(size_t i=0; i<rows; i++){
    for(size_t j=0; j<cols; j++){
      result[j][i] = grid[i][j];
    }
  }
  
  return result;

}