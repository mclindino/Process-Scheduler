#include "Units.h"

void Process::setParameters(int arrival, int duration, int memory, int priority)
{
    this->arrival = arrival;
    this->duration = duration;
    this->memory = memory;
    this->priority = priority;
}

int Process::getArrival()           {   return arrival; }
int Process::getDuration()          {   return duration; }
int Process::getMemory()            {   return memory; }
int Process::getPriority()          {   return priority; }

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