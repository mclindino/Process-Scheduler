#include <iostream>
#include <sstream>
#include <vector>

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
        void    modifyPriority();
        int     getArrival();
        int     getDuration();
        int     getMemory();
        int     getPriority();
};

class roundRobin
{
    private:
        vector<Process>             process;
        vector<Process>::iterator   current = process.begin();
        int                         slice;
        int                         priority;
    public:
        void        setListProcess(vector<Process> process);
        void        setSlice(int slice);
        void        slideEdge(int clock);
        int         setPriority(int priority);
        int         getPriority();
};  

class multiLine
{
    private:
        vector<roundRobin>  lines;
    public:
        void        ajustProcess(Process* process, int nProcess);
};
int* readParameters(string parameters);