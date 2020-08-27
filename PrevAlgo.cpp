//System Includes and Libraries
#include <iostream>
#include <map>
#include <stdexcept>
#include <vector>
#include <math.h>
#include <string>
#include <iterator>

//Local includes
#include "PrevAlgo.hpp"

std::map<double,Model> modelSelectionDriver(std::vector<double> lossVals){
    //Verification of input, lossvalues must decrease in line with segment counts increasing. 
    try{
        verifyInputVec(lossVals);
    }
    catch(std::logic_error error){
        std::cout << error.what();
        return std::map<double,Model>();
    }
    //Passed validation, initialize our path. 
    std::map<double, Model> path;
    //Current position in the loss vec.
    std::vector<double>::iterator currentModelLoss = lossVals.begin();
    //This corresponds to index i in the paper. The largest selected model from the previous iteration. 
    std::map<double, Model>::iterator largestSelectedModel;
    //Corresponds to N in paper. Total number of models with unique loss vals that decrease. 
    int numberModels = lossVals.size();
    Model firstModel = Model(1, *currentModelLoss);
    //Variable to represent the true size of the current model. 
    int currentModelSize = 2;
    //Initialization of the path and iterators.
    path.insert(std::pair<double, Model>(INFINITY, firstModel));
    largestSelectedModel = path.begin();
    //Increment to the next loss value. 
    currentModelLoss = std::next(currentModelLoss);
    //Algorithm 1 loop
    for(currentModelSize = 2; currentModelSize <= numberModels; currentModelSize++){
        std::cout << "[ITERATION WITH SIZE: " << currentModelSize << "]\n";
        Model currentModel = Model(currentModelSize,*currentModelLoss);
        double candidateBreakpoint = findBreakpoint(largestSelectedModel->second, currentModel);
        std::cout << "Candidate Breakpoint between " << currentModelSize << " and " << largestSelectedModel->second.modelSize << " : " 
                    << candidateBreakpoint << " Prev largest breakpoint: " << largestSelectedModel->first << "\n";
        //Represents the solve subroutine, algo 2. 
        while(candidateBreakpoint >= largestSelectedModel->first){
            std::cout << "While condition is true! " << candidateBreakpoint << " >= " << largestSelectedModel->second.modelSize << " \n";
            auto temp = largestSelectedModel;
            largestSelectedModel = next(largestSelectedModel); //This gets us nowhere with prev because the largest model is the smallest key.
            path.erase(temp);
            candidateBreakpoint = findBreakpoint(largestSelectedModel->second, currentModel);    
        }
        //Once we find a place, insert the current model.
        path.insert(std::pair<double,Model>(candidateBreakpoint, currentModel));
        largestSelectedModel = path.begin();
        currentModelLoss = std::next(currentModelLoss);
    }
    //Return the final path we found.
    displayMap(path); 
    return path;
}

//Breakpoint computation method 
double findBreakpoint(Model firstModel, Model secondModel){
   std::cout << "Finding breakpoint with model size: " << firstModel.modelSize <<  " and " << secondModel.modelSize 
                << " with loss values: " << firstModel.loss << " and " <<secondModel.loss <<" \n";
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

//DISPLAY METHODS
void displayMap(std::map<double,Model> penaltyModelMap) {
  std::cout <<  "\nCurrent Map Display\n" << "#######################\n";
  std::cout << "Penalty          ModelSize\n"; 
  for (std::map<double,Model>::iterator it=penaltyModelMap.begin(); it!=penaltyModelMap.end(); ++it) 
      std::cout << it->first << "      =>           " << it->second.modelSize << '\n';
   std::cout << " \n";
 }

int main(){
    //std::vector<double> errorVec = {8.0, 9.0, 21321.0};
    //modelSelectionDriver(errorVec);
    //Left panel
    std::cout << "\n[LEFT PANEL]\n";
    std::vector<double> testVectorLeft = {7.0, 4.0};
    modelSelectionDriver(testVectorLeft);
    //Middle panel of Fig 1
    std::cout << "\n[MIDDLE PANEL]\n";
    std::vector<double> testVectorMiddle = {7.0, 4.0, 0};
    modelSelectionDriver(testVectorMiddle);
    //Right panel of Fig 1
    std::cout << "\n[RIGHT PANEL]\n";
    std::vector<double> testVectorRight = {7.0, 4.0, 2.0};
    modelSelectionDriver(testVectorRight);
}