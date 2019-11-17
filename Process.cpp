#include "Process.h"

void Process::setParameters(int arrival, int duration, int memory, int priority)
{
    this->arrival = arrival;
    this->duration = duration;
    this->memory = memory;
    this->priority = priority;
}

int Process::getArrival()           {   return arrival; }
int Process::getDuration()          {   return arrival; }
int Process::getMemory()            {   return arrival; }
int Process::getPriority()          {   return arrival; }
