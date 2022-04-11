#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

//Neural network class
class NeuralNetwork {
public:
    //Construcor. setting layers, weights and values vectors.
    NeuralNetwork(int m_layers);

    //Function to view network internals
    void print();

    //Activation funcion
    double sigm(double arg);

    //Derivative of sigm
    double sigm_deriv(double arg);

    //Feed forward function
    void feedForward(vector<double>* data);

    //Setting base weights
    void setWeights();

    //Function to calculate "Mean Square Error"
    double MSE(vector<double> Ytrue);

    //Training function
    void train(vector<vector<double>>* data, vector<double>* answers);

private:
    //* layers, neurons
    pair<int, vector<int>> network;
    //* Weights of axons
    vector<vector<double>> weights;
    //* Values of neurons in each layer
    vector<vector<double>> values;
};

#endif