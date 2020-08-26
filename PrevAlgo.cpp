//System Includes and Libraries
#include <iostream>
#include <map>
#include <stdexcept>
#include <list>
#include <vector>
#include <math.h>
#include <string>
#include <iterator>
#include <algorithm>

//Local includes
#include "PrevAlgo.hpp"

void modelSelectionDriver(std::vector<double> lossVals){
    //Verification of input, does not run the funciton if it fails. 
    try{
        verifyInputVec(lossVals);
    }
    catch(std::logic_error error){
        std::cout << error.what();
        return;
    }
    //Passed validation, initialize our path. 
    std::map<double, Model> path;
    std::vector<double>::iterator currentModel = lossVals.begin();
    //This corresponds to index i in the paper. The largest selected model from the previous iteration. 
    std::map<double, Model>::iterator largestSelectedModel;
    //Corresponds to N in paper. Total number of models with unique loss vals that decrease. 
    int numberModels = lossVals.size();
    Model firstModel = Model(1, *currentModel);
    int indexModelSize = 2;
    //Initialization of the path and iterators.
    path.insert(std::pair<double, Model>(INFINITY, firstModel));
    largestSelectedModel = path.begin();

    //Main loop for Algorithm 1
    

}

//Breakpoint computation method 
double findBreakpoint(Model firstModel, Model secondModel){
   double newBreakpoint = (secondModel.loss - firstModel.loss) / (firstModel.modelSize - secondModel.modelSize);
   if(newBreakpoint < 0){
      throw std::logic_error("[ ERROR ] Breakpoint computed between Modelsize: " + std::to_string(firstModel.modelSize) + "and Modelsize: "+ std::to_string(secondModel.modelSize) 
                        + "is less than zero, and is therefore invalid.");
   }
   return newBreakpoint;
}

void verifyInputVec(std::vector<double> input){
    std::vector<double>::iterator currentModel = input.begin();
    while(std::next(currentModel) != input.end()){
        if(*currentModel <= *std::next(currentModel)){
            throw std::logic_error("[ ERROR ] LOSS IS NOT DECREASING IN INPUT\n");
        }
        currentModel = std::next(currentModel);
    }
}
int main(){
    std::cout<< "Testing old algorithm\n";
    std::vector<double> errorVec = {8.0, 9.0, 21321.0};
    modelSelectionDriver(errorVec);
    //Middle panel of Fig 1
    std::vector<double> testVector1 = {7.0, 3.0, 0};
    modelSelectionDriver(testVector1);
    //Right panel of Fig 1
    std::vector<double> testVector2 = {7.0, 4.0, 2.0};
    modelSelectionDriver(testVector2);
}