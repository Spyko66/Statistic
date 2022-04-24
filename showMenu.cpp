#include<iostream>    
using std::cout;
using std::cin;
using std::endl;

#include "ArrayNumbers.h"

int showMenu(){
    int selectedOption;

    cout<<"What do you want to do?\n\n";
    cout<<"1)  Show dominium, range and the processed data"<<endl<<"2) Show measures of central tendency (mean, median and mode)"<<endl<<"3) Both\n";
    cin>>selectedOption;
    
    return selectedOption;
}