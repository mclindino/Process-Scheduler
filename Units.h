#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <unistd.h>

using namespace std;

class Process
{
    private:
        int      arrival;
        int      duration;
        int      memory;
        int      priority;
        int*     CPU;
    public:
        void    setParameters(int arrival, int duration, int memory, int priority, int* CPU);
        void    modifyDuration();
        void    modifyPriority();
        int     getArrival();
        int     getDuration();
        int     getMemory();
        int     getPriority();
        int     getCPU();
        void    setCPU(int CPU);
};

class roundRobin
{
    private:
        Process*             list_process;
        int                  first;
        int                  slice; 
        int                  priority;
        int                  length;
        bool                 loop_indector = false;
    public:
        int                 current = 0;
        void                setListProcess(Process* process, int nProcess);
        void                setSlice(int slice);
        Process             getCurrentProcess();
        bool                sliceEdge(int clock, int CPU);
        int                 setPriority(int priority);
        int                 getPriority();
        int                 getLength();
        void                setLength(int length);
        Process*            getListProcess();
};  

class multiLine
{
    private:
        roundRobin*  multilines;
    public:
        void            ajustProcess(Process* process, int nProcess);
        void            freeMultilines();
        roundRobin*     getMultilines();
};

int* readParameters(string parameters);
void printAllProcess(multiLine m);
void printOneLineOfProcess(roundRobin line, int clock);
void passProcess(Process p1, Process p2);
bool verifyZeros(Process* r, int length);