#include<iostream>      
using std::cout;
using std::cin;
using std::endl;

#include "ArrayNumbers.h"

int main(){
    int numElements, selectedOption;
    bool frstCondition=true, scndCondition=false;

    cout<<"Enter the size of the sample:  \n";
    cin>>numElements;

    ArrayNumbers SampleData=ArrayNumbers(numElements);
    SampleData.setRawData();
    SampleData.bubbleSort();
    SampleData.findFrequencyDistribution();
    SampleData.findBoundaries();
    SampleData.findClassMark();

    selectedOption=showMenu();
    switch(selectedOption){
        case 1:
            SampleData.findRelativeAndCumulativeFr();
            SampleData.showProcessedData(frstCondition, scndCondition);
        break;

        case 2:
            SampleData.calculateMeanMedianMode();
            SampleData.showProcessedData(scndCondition,frstCondition);
            
        break;

        case 3:
            SampleData.findRelativeAndCumulativeFr();
            SampleData.calculateMeanMedianMode();
            SampleData.showProcessedData(frstCondition,frstCondition);

        break;

        default:
        cout<<"Invalid option\n";
        break;
    }
}