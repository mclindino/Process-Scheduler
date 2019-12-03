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
        int      CPU;
    public:
        void    setParameters(int arrival, int duration, int memory, int priority, int CPU);
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
        int*                 current;
    public:
        void                setListProcess(Process* process, int nProcess);
        void                setSlice(int slice);
        Process             getCurrentProcess(int current_CPU);
        bool                sliceEdge(int clock, int current_CPU, int* memory);
        void                setPriority(int priority);
        int                 getPriority();
        int                 getLength();
        void                setLength(int length);
        Process*            getListProcess();
        void                setCurrent(int nCPUs);
};  

class multiLine
{
    private:
        roundRobin*  multilines;
    public:
        void            ajustProcess(Process* process, int nProcess, int nCPUs);
        void            freeMultilines();
        roundRobin*     getMultilines();
};

int* readParameters(string parameters);
void printAllProcess(multiLine m);
void printOneLineOfProcess(roundRobin line, int clock, int nCPUs);
int verifyListProcess(Process* r, int length, int clock, int current_process, int** memory, int current_cpu);
int zeros(Process* r, int length, int** memory);
int  processesFinder(Process* p, int length, int CPU);