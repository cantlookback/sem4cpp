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
    
}

void NeuralNetwork::print() {
    cout << "----------------------------\n   NUMBER OF LAYERS\n|";
    cout << network.first;
    cout << "|\n----------------------------\n   NUMBER OF NEURONS IN EACH LAYER\n|";
    for (auto neur : network.second) {
        cout << neur << '|';
    }
    cout << "\n----------------------------\n   NUMBER OF WEIGHT LAYERS\n|";
    cout << weights.size();
    cout << "|\n----------------------------\n   ALL WEIGHTS\n|";
    for (auto l : weights) {
        for (auto w : l) {
            cout << w << '|';
        }
        cout << "\n|";
    }
    cout << "----------------------------\n   VALS\n|";
    for (auto layer : values) {
        for (auto val : layer) {
            cout << val << '|';
        }
        cout << "\n|";
    }
}

double NeuralNetwork::sigm(double arg) {
    return 1 / (1 + exp(-arg));
}

double NeuralNetwork::sigm_deriv(double arg) {
    return arg * (1 - arg);
}

void NeuralNetwork::feedForward(vector<double>* data) {
    //Copy data to input layer
    for (int i = 0; i < values.size(); i++){
        for (int j = 0; j < values[i].size(); j++){
            values[i][j] = 0;
        }
    }
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
            weights[i][j] = (static_cast<double>(rand()) / RAND_MAX) * 5;
        }
    }
}

double NeuralNetwork::MSE(vector<double>* Ypred, vector<double>* Ytrue) {
    double mse = 0;
    for (unsigned i = 0; i < Ypred->size(); i++) {
        mse += pow((*Ytrue)[i] - (*Ypred)[i], 2);
    }
    mse /= Ypred->size();
    return mse;
}


//TODO: It's working, but smth wrong, need to fix.
void NeuralNetwork::train(vector<vector<double>>* data, vector<double>* answers) {
    double trainRate = 0.01;
    double alpha = 0.3;
    unsigned epochs = 100000;
    for (unsigned epoc = 0; epoc < epochs; epoc++) {
        //cout << epoc;
        for (unsigned jija = 0; jija < data->size(); jija++) {
            feedForward(&(*data)[jija]);
            
            //*d_X
            vector<vector<double>> d_X;
            //* GRADs
            vector<vector<double>> GRADs;
            d_X.resize(network.first);
            GRADs.resize(network.first - 1);

            for (unsigned i = 0; i < d_X.size(); i++) {
                d_X[i].resize(network.second[i]);
            }
            for (int i = 0; i < network.first - 1; i++) {
                GRADs[i].resize(network.second[i] * network.second[i + 1]);
            }


            for (unsigned i = 0; i < d_X[network.first - 1].size(); i++) {
                d_X[network.first - 1][i] = ((*answers)[i] - values[network.first - 1][i]) * sigm_deriv(values[network.first - 1][i]);
            }

            for (int i = network.first - 2; i >= 0; i--) {
                for (unsigned j = 0; j < d_X[i].size(); j++) {
                    for (unsigned k = 0; k < d_X[i + 1].size(); k++) {
                        d_X[i][j] += d_X[i + 1][k] * weights[i][k * (network.second[i + 1] - 1) + j];
                    }
                    d_X[i][j] *= sigm_deriv(values[i][j]);
                }
            }
            
            for (unsigned i = 0; i < GRADs.size(); i++) {
                for (unsigned j = 0; j < GRADs[i].size(); j++) {
                    GRADs[i][j] = values[i][j % values[i].size()] * d_X[i + 1][int(j / values[i].size())];
                }
            }
/*
            cout << "----------------------------\n   d_X   \n|";
            for (auto Gs : d_X){
                for (auto g : Gs){
                    cout << g << '|';
                }
                cout << "\n|";
            }

            cout << "----------------------------\n   GRADS   \n|";
            for (auto Gs : GRADs){
                for (auto g : Gs){
                    cout << g << '|';
                }
                cout << "\n|";
            }
*/
            //G{0,0} = v{0,0} * d{1,0}
            //G{0,1} = v{0,1} * d{1,0}
            //G{0,2} = v{0,0} * d{1,1}
            //G{0,3} = v{0,1} * d{1,1}
            //G{0,4} = v{0,0} * d{1,2}
            //G{0,5} = v{0,1} * d{1,2}
            //G{1,0} = v{1,0} * d{2,0}
            //G{1,1} = v{1,1} * d{2,0}
            //G{1,2} = v{1,2} * d{2,0}
        
            vector<vector<double>> dW;
            dW.resize(weights.size());
            for (int i = 0; i < dW.size(); i++){
                dW[i].resize(weights[i].size());
            }

            for (int i = 0; i < dW.size(); i++){
                for (int j = 0; j < dW[i].size(); j++){
                    dW[i][j] = trainRate * GRADs[i][j] + alpha * dW[i][j];
                }
            }

            for (int i = 0; i < weights.size(); i++){
                for (int j = 0; j < weights[i].size(); j++){
                    weights[i][j] += dW[i][j];
                }
            }
        }
    }
}
