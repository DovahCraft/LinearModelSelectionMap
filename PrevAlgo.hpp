#pragma once
#include <list>
#include <map>
#include <vector>
#include <iostream>
#include <string>

struct Model {
    //Create a model if it has valid modelSize and loss values given. 
    Model(int inputSize, double inputLoss) : modelSize(inputSize), loss(loss) {
        if(inputSize >= 0 && inputLoss >= 0){
            modelSize = inputSize;
            loss = inputLoss;
        }
        else{
            throw std::out_of_range("[ ERROR ] Cannot create model with negative size or loss values! Provided model_size = " 
            + std::to_string(inputSize) + ", loss = " + std::to_string(inputLoss) + "\n");
        }
    }
    //Number of segments (k-value)
    int modelSize = 0;
    //Loss associated with the given model 
    double loss = 0.0;
};

//Algorithm 1: Returns a Path struct with the selected models. 
std::map<double, Model> computePath(std::vector<double> lossVals);
//Algorithm 2: Decides what breakpoints/models to remove and/or keep and returns them to Algorithm 1.
void solver();
//Helper method to insert to store things? Might not be necessary. 
void insert(std::vector<double> lossVals);

