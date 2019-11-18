#include <iostream>
#include <sstream>
using namespace std;

class Process
{
    private:
       int      arrival;
       int      duration;
       int      memory;
       int      priority;
    
    public:
        void    setParameters(int arrival, int duration, int memory, int priority);
        void    modifyDuration();
        int     getArrival();
        int     getDuration();
        int     getMemory();
        int     getPriority();
};

class roundRobin
{
    private:
        Process*    process;
        Process     current = process[0];
        int         count = 0;
        int         slice;
        int         priority;
    public:
        void        setSlice(int slice);
        void        setProcess(Process* process);
        void        slideEdge(int clock);
        int         setPriority(int priority);
        int         getPriority();
};  

int* readParameters(string parameters);