#include "Neural.h"

NeuralNetwork::NeuralNetwork(int m_layers) {
    network.first = m_layers;
    weights.resize(m_layers - 1);
    values.resize(m_layers);

    cout << "Enter the number of neurons on each layer: " << endl;
    //Setting the number of neurons on each layer
    for (unsigned i = 0; i <= weights.size(); i++) {
        cout << "Layer " << i + 1 << ">>>";
        int neur = 0;
        cin >> neur;
        network.second.push_back(neur);
        values[i].resize(neur);
    }
    //Seting the number of weights on each layer
    for (int i = 0; i < m_layers - 1; i++) {
        weights[i].resize(network.second[i] * network.second[i + 1]);
    }

    for (auto l : weights) {
        for (auto w : l) {
            w = 0;
        }
    }
    for (auto l : values) {
        for (auto v : l) {
            v = 0;
        }
    }
}

void NeuralNetwork::print(){
    cout << "   NUMBER OF LAYERS    " << endl;
        cout << network.first << endl;
        cout << "   NUMBER OF NEURONS IN EACH LAYER    " << endl;  
        for (auto neur : network.second) {
            cout << neur << "   ";
        }
        cout << endl << "   NUMBER OF WEIGHT LAYERS    " << endl;
        cout << weights.size() << endl;
        cout << "   ALL WEIGHTS    " << endl;
        for (auto l : weights) {
            for (auto w : l) {
                cout << w << "  ";
            }
            cout << endl;
        }
        cout << "   VALS    " << endl;
        for (auto layer : values) {
            for (auto val : layer) {
                cout << val << "    ";
            }
            cout << endl;
        }
        cout << "   D_X     " << endl;
        for (auto d : d_X){
            for (auto dd : d){
                cout << dd << " ";
            }
            cout << endl;
        }

}

double NeuralNetwork::sigm(double arg){
    return 1 / (1 + exp(-arg));
}

double NeuralNetwork::sigm_deriv(double arg){
    double fx = sigm(arg);
    return fx * (1 - fx);
}

void NeuralNetwork::feedForward(vector<double> *data){
    //Copy data to input layer
    values[0] = *data;
    //!For each layer, starting with i = 1
    //!For each neuron from the i layer and beyond
    //!For each neuron from i-1 layer
    //!Value of current neuron = SUM of previous layer neurons * appropriate weight
    //!Then using activation function on our value
    for (int i = 1; i < network.first; i++) {
        for (int j = 0; j < network.second[i]; j++) {
            for (int k = 0; k < network.second[i - 1]; k++) {
                values[i][j] += values[i - 1][k] * weights[i - 1][k * network.second[i] + j];
            }
            values[i][j] = sigm(values[i][j]);
        }
    }
}

void NeuralNetwork::setWeights() {
    for (unsigned i = 0; i < weights.size(); i++) {
        for (unsigned j = 0; j < weights[i].size(); j++) {
            weights[i][j] = 1;//(static_cast<double>(rand()) / RAND_MAX) * 5;
        }
    }
}

double NeuralNetwork::MSE(vector<double> *Ypred, vector<double> *Ytrue){
    double mse = 0;
    for (int i = 0; i < Ypred->size(); i++){
        mse += pow((*Ytrue)[i] - (*Ypred)[i], 2);
    }
    mse /= Ypred->size();
    return mse;
}


//TODO: It's working, but smth wrong, need to fix.
void NeuralNetwork::train(vector<vector<double>> *data, vector<double> *answers){
    double trainRate = 0.1;
    unsigned epochs = 1000;
    for (unsigned epoc = 0; epoc < epochs; epoc++){
        cout << epoc;
        for (unsigned jija = 0; jija < data->size(); jija++){
            feedForward(&(*data)[jija]);
            
            d_X.resize(network.first);

            for (int i = 0; i < d_X.size(); i++){
                d_X[i].resize(network.second[i]);
            }

            for (int i = 0; i < d_X.size(); i++){
                for (int j = 0; j < d_X[i].size(); j++){
                    d_X[i][j] = 0;
                }
            }

            for (int i = 0; i < d_X[network.first - 1].size(); i++){
                d_X[network.first - 1][i] = ((*answers)[i] - values[network.first - 1][i]) * sigm_deriv(values[network.first - 1][i]);
            }

            for (int i = network.first - 2; i >= 0 ; i--){
                for (int j = 0; j < d_X[i].size(); j++){
                    for (int k = 0; k < d_X[i + 1].size(); k++){
                        d_X[i][j] += d_X[i + 1][k] * weights[i][k * network.second[i + 1] + j];
                    }
                    d_X[i][j] *= sigm_deriv(values[i][j]);
                }
            }


        }
    }
}

