#include <iostream>
using namespace std;

class Process
{
    private:
       int arrival;
       int duration;
       int memory;
       int priority;
    
    public:
        void setParameters(int arrival, int duration, int memory, int priority);
        int getArrival();
        int getDuration();
        int getMemory();
        int getPriority();
};
