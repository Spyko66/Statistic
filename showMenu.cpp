#include<iostream>    
using std::cout;
using std::cin;
using std::endl;

#include "ArrayNumbers.h"

int showMenu(){
   
    int selectedOption;

    cout<<"What do you want to do?\n\n";
    cout<<"1)  Show dominium, range and the processed data"<<endl<<"2) Show medidas de tendencia central(mediana, media y moda)"<<endl<<"3) All the previous ones\n";
    cin>>selectedOption;
    
    return selectedOption;
}