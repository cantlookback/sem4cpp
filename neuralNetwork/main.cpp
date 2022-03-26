#include <iostream>
#include "Neural.h"
using namespace std;

int main() {
    NeuralNetwork net{ 3 };
    net.setWeights();
    vector<double> data = { 2, 2, 2 };
    net.feedForward(&data);
    net.print();


    return 0;
}