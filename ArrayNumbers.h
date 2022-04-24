#ifndef ARRAYNUMBERS_H
#define ARRAYNUMBERS_H
class ArrayNumbers{
    public:
        ArrayNumbers(int);
        void setRawData(void);
        void bubbleSort(void);
        void findFrequencyDistribution(void);
        void findBoundaries(void);
        void findClassMark(void);
        void findRelativeAndCumulativeFr(void);
        void showDomainAndRange(void);
        void calculateMeanMedianMode(void);
        void showProcessedData(bool,bool);
        
    private:
        int nElements,nClasses,*frDistribution,*C;
        float *element,domainBottom,domainTop,range,**intervals,**boundaries,*X,*relativeFr,*cumulativeFr,*relativeCuFr, mean,median,mode;
};

int showMenu();
#endif