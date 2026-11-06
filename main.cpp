#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

// prototype method
float euclidean_distance(vector<float>&, vector<float>&);
float dot_product(vector<float>&, vector<float>&);
float euclidean_distance(vector<float>&, const vector<float>&); // Overloaded (If overloaded is the word for it)
float cosine_similarity(vector<float>&, vector<float>&);
float scaler_projection(vector<float>&, vector<float>&);
vector<float> vector_projection(vector<float>&, vector<float>&);

int main(){
    vector<float> X1 = {2.0f, 4.0f, 6.0f};
    vector<float> X2 = {5.0f, 8.0f, 10.0f};
    // Compute Distance
    cout << "Euclidean Distance is: " << euclidean_distance(X1, X2) << endl;
    
    // Dot product
    cout << "Dot Product is: " << dot_product(X1, X2) << endl; 

    // cosine similarity
    cout << "Cosine Similarity " << cosine_similarity(X1, X2) << endl;

    // vector projection
    cout << "Vector X1 projects: " << scaler_projection(X1, X2) << " onto X2" << endl;

    vector<float> proj = vector_projection(X1, X2);

    for(size_t i=0; i<proj.size(); i++)
        cout << proj[i] << " ";
    cout << endl; // blank line for spacing on the console
    
    return 0;
}



float euclidean_distance(vector<float>& X1, vector<float>& X2){
    float distance = 0.0f;
    if(X1.size() != X2.size()){
         throw runtime_error("Cant do distance on two different size vectors");   
    }

    for(int i=0; i<X1.size(); i++){
        float temp_dist = X1[i] - X2[i];
        distance += temp_dist * temp_dist; // Removed calling pow overhead
    }
  
    // after summing up all the distances square root the distance
    distance = sqrt(distance);
    return distance;
}

float euclidean_distance(vector<float>& X1, const vector<float>& X2){
    float distance = 0.0f;
    if(X1.size() != X2.size()){
         throw runtime_error("Cant do distance on two different size vectors");   
    }

    for(int i=0; i<X1.size(); i++){
        float temp_dist = X1[i] - X2[i];
        distance += temp_dist * temp_dist; // Removed calling pow overhead
    }
  
    // after summing up all the distances square root the distance
    distance = sqrt(distance);
    return distance;
}

float dot_product(vector<float>& X1, vector<float>& X2){
    float dprod = 0.0f;
    if(X1.size() != X2.size()){
        throw runtime_error("Cant do distance on two different size vectors");   
    }
    for(size_t i=0; i<X1.size(); i++){
        dprod += X1[i] * X2[i];
    }
    return dprod;
}

float cosine_similarity(vector<float>& X1, vector<float>& X2){
    if(X1.size() != X2.size()){
        throw runtime_error("Cant do distance on two different size vectors");   
    }

    const vector<float> dummy(X1.size(), 0.0f);
    float magnitude1 =  euclidean_distance(X1, dummy);
    float magnitude2 = euclidean_distance(X2, dummy); 
    float dot_prod = dot_product(X1, X2);
    
    if(magnitude1 == 0.0f || magnitude2 == 0.0f)
        throw runtime_error("Can not do division by 0");

    float cosine_sim = (dot_prod)/(magnitude1 * magnitude2);
    return cosine_sim;
}

/*
    * Vector Projection
    * This lets us know how much of vector X projects onto vector Y
    * Operation:
        - Compute Dot Product of X1 and X2
        - Divide by magnitude of X2
*/
float scaler_projection(vector<float>& X1, vector<float>& X2){
    if(X1.size() != X2.size()){
        throw runtime_error("Cant do distance on two different size vectors");   
    } 

    // Dot product of X1 and X2
    float dot_prod =   dot_product(X1, X2);
    const vector<float> dummy(X1.size(), 0.0f);
    float mag_x2 = euclidean_distance(X2, dummy); 

    if(mag_x2 == 0.0f)
        throw runtime_error("Cant divide by 0");
    float scaler_proj = dot_prod/mag_x2;
    return scaler_proj;
}

vector<float> vector_projection(vector<float>& X1, vector<float>& X2){
    if(X1.size() != X2.size()){
        throw runtime_error("Cant do distance on two different size vectors");   
    } 
    vector<float> projection(X2.size(), 0.0f);
    vector<float> dummy(X2.size(), 0.0f);

    float dot_prod = dot_product(X1, X2);
    float magnitude_x2 = euclidean_distance(X2, dummy);

    if(magnitude_x2 == 0.0f)
        throw runtime_error("Cant do division by 0");

     magnitude_x2 *= magnitude_x2; // Square magnitude (I asked in the prompt we square it... so I assume yes)
    float quotient = dot_prod/magnitude_x2;

    cout << "Quotient: " << quotient << endl;
    
    // Loop through and compute the projection
    for(size_t i=0; i<X2.size(); i++){
        projection[i] = quotient * X2[i];
    }
    return projection;
}
