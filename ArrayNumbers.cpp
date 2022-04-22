#include<iostream>
using std::cout;
using std::cin;
using std::endl;

#include<stdlib.h>
#include<cmath>

#include<iomanip>
using std::setw;
using std::setprecision;

#include "ArrayNumbers.h"

ArrayNumbers::ArrayNumbers(int numberElements){                     //ARCHIVO CLASE.CPP
    nElements=numberElements;
}

void ArrayNumbers::setRawData(void){

    element=new float[nElements];

    for(int i=0;i<nElements;i++)
    {
        cout<<"Enter the number "<<(i+1)<<": \n";
        cin>>*(element+i);
    }
}

void ArrayNumbers::bubbleSort(void){
    float aux;

    for(int i=0;i<nElements;i++){
        for(int j=0;j<nElements-1;j++){
            if(*(element+j)>*(element+j+1)){
                aux=*(element+j);
                *(element+j)=*(element+j+1);
                *(element+j+1)=aux;
            }
        }
    }
}

void ArrayNumbers::findFrequencyDistribution(void){
    float cAux;
    
    domainBottom=(*element);
    domainTop=*(element+nElements-1);
    range=domainTop-domainBottom;

    showDomainAndRange();

    cout<<"How many classes do you want?    ";
    cin>>nClasses;
    
    frDistribution=new int[nClasses];
    C=new int[nClasses];
    intervals=new float*[nClasses];

    for(int i=0;i<nClasses;i++)
        intervals[i]=new float[2];

    for(int i=0;i<nClasses;i++)
        *(frDistribution+i)=0;

    cAux=range/nClasses;
    
    for(int i=0;i<nClasses;i++)
        (*(C+i))=round(cAux);

    *(*(intervals)+1)=(domainBottom+(*(C))-1);
    *(*(intervals))=(domainBottom);
     
    for(int i=1;i<nClasses;i++){
        for(int j=0;j<2;j++){
            if(j==0)
                (*(*(intervals+i)+j))=*(*(intervals))+((*(C+i))*i);
            else
                (*(*(intervals+i)+j))=*(*(intervals)+1)+((*(C+i))*i);
        }
    }

    if((*(*(intervals+nClasses-1)+1))<domainTop){
        (*(C+nClasses-1))=(*(C+nClasses-1))+(domainTop-(*(*(intervals+nClasses-1)+1)));
        *(*(intervals+nClasses-1)+1)=domainTop;
    }

    if((*(*(intervals+nClasses-1)+1))>domainTop){
        (*(C+nClasses-1))=(*(C+nClasses-1))-((*(*(intervals+nClasses-1)+1))-domainTop);
        *(*(intervals+nClasses-1)+1)=domainTop;
    }

    for(int i=0;i<nClasses;i++){
        for(int j=0;j<2;j++){
            for(int k=0;k<nElements;k++){
                if(j==0){
                    if((*(element+k))>=(*(*(intervals+i)))&&(*(element+k))<=(*(*(intervals+i)+1)))
                        (*(frDistribution+i))++;
                }
            }
        }
    }

}

void ArrayNumbers::findBoundaries(void){

    float variation;
    boundaries=new float*[nClasses];

    for(int i=0;i<nClasses;i++)
        boundaries[i]=new float[2];

    for(int i=1;i<nClasses;i++){
        *(*(boundaries+i-1)+1)=(*(*(intervals+i))+*(*(intervals+i-1)+1))/2;
        *(*(boundaries+i))=*(*(boundaries+i-1)+1);
    }

    variation=*(*(boundaries)+1)-*(*(intervals)+1);
    *(*(boundaries))=(*(*(intervals)))-variation;
    *(*(boundaries+nClasses-1)+1)=(*(*(intervals+nClasses-1)+1))+variation;
}

void ArrayNumbers::findClassMark(void){

    X=new float[nClasses];

    for(int i=0;i<nClasses;i++)
        *(X+i)=((*(*(intervals+i)))+(*(*(intervals+i)+1)))/2;
}

void ArrayNumbers::findRelativeAndCumulativeFr(void){
    relativeFr=new float[nClasses];
    cumulativeFr=new float[nClasses];
    relativeAcFr=new float[nClasses];

    for(int i=0;i<nClasses;i++)
        (*(relativeFr+i))=(*(frDistribution+i))*100/nElements;

    *(cumulativeFr)=*(relativeAcFr)=0;

    for(int i=1;i<nClasses;i++){
        *(cumulativeFr+i)=(*(cumulativeFr+i))+(*(frDistribution+i-1));
        *(relativeAcFr+i)=(*(cumulativeFr+i))*100/nElements;
    }

}

void ArrayNumbers::calculateMeanMedianMode(void){
    float *fx,sumfx=0,halfNElements=nElements/2,aux=(*(frDistribution));
    int medianClass,*sumFr,modClass=0,deltaOne,deltaTwo;
    fx=new float[nClasses];
    sumFr=new int[nClasses];
    

    for(int i=0;i<nClasses;i++){                    //Mean
        (*(fx+i))=(*(frDistribution+i))*(*(X+i));
        sumfx=sumfx+(*(fx+i));
    }

    mean=sumfx/nElements;

    (*(sumFr))=(*(frDistribution));                 //Median

    for(int i=1;i<nClasses;i++){
        (*(sumFr+i))=(*(sumFr+i-1))+(*(frDistribution+i));
        if((halfNElements>0)&&(halfNElements<=(*(sumFr))))
            medianClass=0;
        else if((halfNElements>(*(sumFr+i-1)))&&(halfNElements<=(*(sumFr+i))))
            medianClass=i;
    }

    if(medianClass==0){
        (*(sumFr))=0;
        median=(*(*(boundaries+medianClass)))+((halfNElements-(*(sumFr)))/(*(frDistribution+medianClass)))*(*(C+medianClass));
    }
    else{
        median=(*(*(boundaries+medianClass)))+((halfNElements-(*(sumFr+medianClass-1)))/(*(frDistribution+medianClass)))*(*(C+medianClass));
    }   
    
    for(int i=0;i<nClasses;i++){                    //Mode
        if((*(frDistribution+i))>aux){
            aux=*((frDistribution+i));
            modClass=i;
        }
    }

    deltaOne=(*(frDistribution+modClass))-(*(frDistribution+modClass-1));
    deltaTwo=(*(frDistribution+modClass))-(*(frDistribution+modClass+1));

    mode=(*(*(boundaries+modClass)))+(deltaOne/(deltaOne+deltaTwo))*(*(C+modClass));

    delete[] fx;
    delete[] sumFr;

}

void ArrayNumbers::showProcessedData(bool condition, bool conditionTwo){

    int counter=0,lessThan=domainBottom;

    if(condition){

        cout<<"Please open the fullscreen mode for a better visualization\n";

        for(int i=0;i<=((2*nClasses)+1);i++){
            if((i%2)==0)
                cout<<setw(92)<<"----------------------------------------------------------------------------------------\n";
            else if(i==1)
                cout<<setw(12)<<"INTERVALS"<<setw(15)<<"FREQ DISTR"<<setw(15)<<"BOUNDARIES"<<setw(15)<<"AMPLITUD"<<setw(15)<<"CLASS MARK"<<setw(15)<<"REL FREQ"<<setw(15)<<"LESS THAN"<<setw(15)<<"CUMUL FREQ"<<setw(20)<<"REL CUMUL FREQ\n";
            else{
                cout<<setw(10)<<setprecision(2)<<*(*(intervals+counter))<<"-"<<setprecision(2)<<*(*(intervals+counter)+1)<<setw(13)<<*(frDistribution+counter)<<setw(13)<<setprecision(2)<<*(*(boundaries+counter))<<"-"<<setprecision(2)<<*(*(boundaries+counter)+1)<<setw(13)<<*(C+counter)<<setw(13)<<*(X+counter)<<setw(13)<<*(relativeFr+counter)<<setw(13)<<lessThan<<setw(13)<<*(cumulativeFr+counter)<<setw(16)<<*(relativeAcFr+counter)<<endl;
                counter++;
                lessThan=lessThan+(*(frDistribution+counter));
            }
        
        cout<<endl<<endl;
            
        }
    }

    if(conditionTwo){
        cout<<"MEAN=    "<<mean<<"\n\nMEDIAN=   "<<median<<"\n\nMODE=   "<<mode<<endl;
    }

    delete[] element;
    delete[] frDistribution;
    delete[] C;
    for(int i=0;i<nClasses;i++)
        delete[] intervals[i];
    delete[] intervals;
    for(int i=0;i<nClasses;i++)
        delete[] boundaries[i];
    delete[] boundaries;
    delete[] X;
    delete[] relativeFr;
    delete[] cumulativeFr;
    delete[] relativeAcFr;
}

void ArrayNumbers::showDomainAndRange(){
    cout<<"The dominium is  "<<domainBottom<<"-"<<domainTop<<endl;
    cout<<"The range is "<<range<<endl;
}