#include<algorithm>
#include<cmath>
#include<vector>

std::vector<double> squared_distances(const std::vector<std::vector<double>>& Historical, const std::vector<double>& curPoint){
    if(Historical[0].size() == 0 || Historical.size() == 0){
      throw throw invalid_argument("Cant perform distance calculations on empty historical data");
    }
    std::vector<double> distances(Historical.size(), 0.0);
    for(size_t i=0; i<Historical.size(); i++){
        double dist = 0.0;
        for(size_t j=0; j<Historical[0].size(); j++){
            double difference = (Historical[i][j]) - curPoint[j];
            dist += difference * difference;
        }
        distances[i] = dist;
    }
    return distances;
}

std::vector<double> GaussianKernel(std::vector<double>& SquareDist, const double p, double h=1.0){
  if(h <= 0.0){
    throw invalid_argument("h cant be 0 or less");
  }
    std::vector<double> k_weights(SquareDist.size(), 0.0);
    double normalization_factor = 
      1.0/(std::pow((2.0 * M_PI),(p/2.0)) * std::pow(h, p));

    double dist_contribution_normalizer = 2.0 * (h*h);

    for(size_t i=0; i<SquareDist.size(); i++){
        k_weights[i]= normalization_factor * std::exp(-(SquareDist[i])/dist_contribution_normalizer);
    }
    return k_weights;
}

double average(const std::vector<double>& k_weights){
  if(k_weights.size() == 0){
    throw invalid_argument("No weights provided, cant continue with operation");
  }
  double avg = 0.0;
  for(size_t i=0; i<k_weights.size(); i++){
    avg += k_weights[i];
  }
  avg = (avg/static_cast<double>(k_weights.size()));
  return avg;
}

std::vector<double> get_all_historical_densities(std::vector<std::vector<double>>& Historical, double h = 1.0) {
    std::vector<double> densities(Historical.size(), 0.0);
    
    for(size_t i = 0; i < Historical.size(); i++) {
        // 1. Treat the i-th historical row as your current query point
        std::vector<double> curPoint = Historical[i];
        
        // 2. Compute squared distances to all historical points
        std::vector<double> dists = squared_distances(Historical, curPoint);
        
        // 3. Convert distances to Gaussian kernel weights
        std::vector<double> weights = GaussianKernel(dists, h);
        
        // 4. Sum up the weights to get the total density score for this point
        double total_density = 0.0;
        for(size_t k = 0; k < weights.size(); k++) {
            // Note: If k == i, the distance is 0.0 and weight is 1.0 (self-match). 
            // Standard KDE includes this, but you can skip it if you want leave-one-out density.
            total_density += weights[k];
        }
        
        densities[i] = total_density;
    }
    
    return densities;
}

double get_point_density(std::vector<std::vector<double>>& Historical, std::vector<double>& curPoint, double h = 1.0) {
    // 1. Get squared distances
    std::vector<double> dists = squared_distances(Historical, curPoint);
    
    // 2. Turn distances into kernel weights
    std::vector<double> weights = GaussianKernel(dists, h);
    
    // 3. Sum the weights for your final relative density score
    double density_score = 0.0;
    for (double w : weights) {
        density_score += w;
    }

    std::vector<double> all_densities = get_all_historical_densities(Historical, h);
    
    // 5. Sort historical densities so we can rank our point
    std::sort(all_densities.begin(), all_densities.end());

    // 6. Count how many historical densities are strictly less than our score
    int count_less = 0;
    for (double hist_score : all_densities) {
        if (hist_score < density_score) {
            count_less++;
        }
    }

    // 7. Return the percentile (0.0 to 1.0, or multiply by 100.0 for 0-100 scale)
    double percentile = (static_cast<double>(count_less) / all_densities.size()) * 100.0;
    
    return percentile;
    
    //return density_score;
}



