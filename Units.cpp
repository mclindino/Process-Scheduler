#include "Units.h"

void Process::setParameters(int arrival, int duration, int memory, int priority)
{
    this->arrival = arrival;
    this->duration = duration;
    this->memory = memory;
    this->priority = priority;
}
void Process::modifyDuration()      {   this->duration--;   }
int Process::getArrival()           {   return arrival;     }
int Process::getDuration()          {   return duration;    }
int Process::getMemory()            {   return memory;      }
int Process::getPriority()          {   return priority;    }

void roundRobin::setSlice(int slice)            {   this->slice = slice;        }
void roundRobin::setProcess(Process* process)   {   this->process = process;    }
int  roundRobin::setPriority(int priority)      {   this->priority = priority;  }
int  roundRobin::getPriority()                  {   return priority;            }
void roundRobin::slideEdge(int clock)
{
    if (this->current.getArrival() >= clock)
    {
        if( ((slice % clock) == 0) && (clock != 0) )
        {
            if(this->process[count + 1].getArrival() >= clock)
            {
                this->current = this->process[count + 1];
                count++;
            }
        }
        else
        {
            this->current.modifyDuration();
        }
    }
    
}

int* readParameters(string parameters)
{
    string aux = "";
    int count = 0;
    int* values;
    values = (int*) malloc(4 * sizeof(int));

    for (int i = 0; i < parameters.size(); i++)
    {
        if (parameters[i] == ',')
        {
            stringstream geek(aux);
            geek >> values[count];
            aux = "";
            count++;
            continue;
        }
        else
        {
            aux = aux + parameters[i];
        } 
    }

    stringstream geek(aux);
    geek >> values[count];

    return values; 
}