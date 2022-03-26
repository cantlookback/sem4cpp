#include <iostream>
#include "Neural.h"
using namespace std;

int main() {
    NeuralNetwork net{ 2 };
    net.setWeights();
    vector<double> data = { 2, 2, 2 };
    //net.feedForward(&data);
    
    vector<vector<double>> viborka = {{1, -3}}; 
    vector<double> ans = {1};
    net.train(&viborka, &ans);
    net.print();


    return 0;
}