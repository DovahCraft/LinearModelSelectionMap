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

#include "PrevAlgo.hpp"

//Input is an array of decreasing loss values in real numbers s.t. L[1]=loss with one model > L[2] > ... > L[N]
void insert(){
}

void modelSelectionDriver(std::vector<double> lossVals){
    try{
        verifyInputVec(lossVals);
    }
    catch(std::logic_error error){
        std::cout << error.what();
        std::cout << *lossVals.begin() << " caused an error.\n";
        return;
    }
    std::cout << *lossVals.begin() << " passed validation.\n";
    std::map<double, Model> path;
    std::vector<double>::iterator currentModel = lossVals.begin();
    Model firstModel = Model(1, *currentModel);
    std::cout << "Running algorithm\n";
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