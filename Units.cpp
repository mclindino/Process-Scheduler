#include "Units.h"

void Process::setParameters(int arrival, int duration, int memory, int priority)
{
    this->arrival = arrival;
    this->duration = duration;
    this->memory = memory;
    this->priority = priority;
}
void Process::modifyDuration()       {   this->duration--;   }
void Process::modifyPriority()       {   this->priority--;   }
int  Process::getArrival()           {   return arrival;     }
int  Process::getDuration()          {   return duration;    }
int  Process::getMemory()            {   return memory;      }
int  Process::getPriority()          {   return priority;    }

int  roundRobin::setPriority(int priority)                 {   this->priority = priority;  }
int  roundRobin::getPriority()                             {   return priority;            }
void roundRobin::setSlice(int slice)                       {   this->slice = slice;        }
void roundRobin::setListProcess(vector<Process> process)   {   this->process = process;    }
void roundRobin::slideEdge(int clock)
{
    //Verifica se precisa executar o processo
    while (current[0].getDuration() == 0)
    {
        current++;
    }

    //Observa se está no slice para poder processar 
    if (current[0].getArrival() >= clock)
    {
        //Verifica se precisa realizar a troca de contexto
        if( ((slice % clock) == 0) && (clock != 0) )
        {
            //Verifica se o proximo processo já pode ser executado 
            if(current[1].getArrival() >= clock)
            {
                current++;
                current[0].modifyDuration();
                
                //Verifica se o vetor acabou
                if ( current[1].getMemory() == 0 )
                {
                    current = process.begin();
                }
                else
                {          
                    current++;
                }
            }
        }
        else
        {
            current[0].modifyDuration();
        }
    }   
}
vector<Process> roundRobin::setLines(Process individual_process, int priority)
{
    this->priority = priority;
    return process.push_back(individual_process);
}

void  multiLine::ajustProcess(Process* process, int nProcess)
{    
    for(int i = 0; i < nProcess; i++)
    {
        switch(process[i].getPriority())
        {
            case 0:
                lines.push_back(line.setLines(process[i]), 0);
            break;
            case 1:
                lines.push_back(line.setLines(process[i]), 1);
            break;
            case 2:
                lines.push_back(line.setLines(process[i]), 2);
            break;
            case 3:
                lines.push_back(line.setLines(process[i]), 3);
            break;
            case 4:
                lines.push_back(line.setLines(process[i]), 4);
            break;
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
