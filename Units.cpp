#include "Units.h"

void Process::setParameters(int arrival, int duration, int memory, int priority, int* CPU)
{
    this->arrival   = arrival;
    this->duration  = duration;
    this->memory    = memory;
    this->priority  = priority;
    this->CPU       = CPU;
}
void Process::modifyDuration()       {   this->duration--;   }
void Process::modifyPriority()       {   this->priority--;   }
int  Process::getArrival()           {   return arrival;     }
int  Process::getDuration()          {   return duration;    }
int  Process::getMemory()            {   return memory;      }
int  Process::getPriority()          {   return priority;    }
void Process::setCPU(int CPU)        {   this->CPU = &CPU;   }
int  Process::getCPU()               {   return *(CPU);      }

int  roundRobin::setPriority(int priority)                 {   this->priority = priority;  		}
int  roundRobin::getPriority()                             {   return priority;            		}
void roundRobin::setSlice(int slice)                       {   this->slice = slice;        		}
Process* roundRobin::getListProcess()			   		   {   return list_process;				}
Process  roundRobin::getCurrentProcess()                   {   return list_process[current];    }
bool roundRobin::sliceEdge(int clock, int CPU)
{
    if(verifyZeros(this->list_process, this->length))
    {
        return false;
    }

    // if(list_process[current].getDuration() == 0)
    // {
    //     if(current == 0) { passProcess(list_process[0],list_process[length - 1]); }
    //     else             { passProcess(list_process[current],list_process[current-1]);}
    //     length--;
    // }
    //Verifica se precisa executar o processo
    while (list_process[current].getDuration() == 0)
    {
        current++;
    }
    //Verifica se o processo ja nao esta em uma CPU
    // while(list_process[current].getCPU() != NULL)
    // {
    //     current++;
    // }
    // list_process[current].setCPU(&CPU);
    //Observa se está no slice para poder processar
    if (list_process[current].getArrival() <= clock)
    {
        //Verifica se precisa realizar a troca de contexto

        if( ((clock % slice) == 0) && (clock != first) )
        {
            //Verifica se o tem mais processos
            if(current == (length-1))
            {
                current = 0;
                while (list_process[current].getDuration() == 0)
                {
                    current++;
                }
                list_process[current].modifyDuration();
            } 
            else
            {
                //Verifica se o proximo processo já pode ser executado 
                if(list_process[current + 1].getArrival() <= clock)
                {
                    current++;
                    list_process[current].modifyDuration();
                }else
                {
                    list_process[current].modifyDuration();
                }
            }
        }
        else
        {
            list_process[current].modifyDuration();
        }
    }
    return true;   
}

int  roundRobin::getLength()										{	return this->length; 		}
void roundRobin::setLength(int length)								{	this->length = length;		}
void roundRobin::setListProcess(Process* process, int nProcess)
{
	list_process = (Process*) malloc(nProcess * sizeof(Process));
	for(int i = 0; i < nProcess; i++)
	{
		list_process[i].setParameters(process[i].getArrival(), process[i].getDuration(),
									  process[i].getMemory(), process[i].getPriority(), NULL);
	}
    first = list_process[0].getArrival();
}

void  multiLine::freeMultilines()                                   {   free(this->multilines);     }
roundRobin*  multiLine::getMultilines()								{	return this->multilines;	}					
void  multiLine::ajustProcess(Process* process, int nProcess)
{

	this->multilines = (roundRobin*) malloc(5 * sizeof(roundRobin));
	Process* prioritys = NULL;
	int length = 0;

	for(int priority = 0; priority < 5; priority++)
	{
	    for(int i = 0; i < nProcess; i++)
	    {
	    	if(process[i].getPriority() == priority)
	    	{
	    		length++;
	    		prioritys = (Process*) realloc(prioritys, length * sizeof(Process));
	    		prioritys[length-1].setParameters(process[i].getArrival(), process[i].getDuration(), process[i].getMemory(), process[i].getPriority(), NULL);
	    	}
	    }
	    this->multilines[priority].setListProcess(prioritys, length);
	    this->multilines[priority].setLength(length);
        this->multilines[priority].setSlice(2);
        this->multilines[priority].current = 0;
	    length = 0;
	}

	free(prioritys);
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

void printAllProcess(multiLine m)
{
	int nProcess;
	cout << "--------------------------------------------------" << endl;
	cout << "Processos Lidos:	(Chegada/Duracao/Memoria)   \n" << endl;
	for(int i = 0; i < 5; i++)
	{
		cout << "Prioridade: " << i << endl;
        nProcess = m.getMultilines()[i].getLength();
        for(int j = 0; j < nProcess; j++)
		{
			cout << "\tProcesso: " << m.getMultilines()[i].getListProcess()[j].getArrival() << '-' 
								   << m.getMultilines()[i].getListProcess()[j].getDuration() << '-'
								   << m.getMultilines()[i].getListProcess()[j].getMemory() << endl;
		}
	}
	cout << "--------------------------------------------------" << endl;
}

void printOneLineOfProcess(roundRobin line, int clock)
{
    cout << "--------------------------------------------------" << endl;
    cout << "slice: " << clock << endl;
    for(int i = 0; i < line.getLength(); i++)
    {
        cout << "\tProcesso: " << line.getListProcess()[i].getArrival() << "-"
                                << line.getListProcess()[i].getDuration() << "-"
                                << line.getListProcess()[i].getMemory() << "-"
                                << line.getListProcess()[i].getPriority() << endl;
    }   

    cout << "\n\tProcesso Atual: " << line.getCurrentProcess().getArrival() << "-"
                                    << line.getCurrentProcess().getDuration() << "-"
                                    << line.getCurrentProcess().getMemory() << "-"
                                    << line.getCurrentProcess().getPriority() << endl;
    cout << "--------------------------------------------------" << endl;
}

void passProcess(Process p1, Process p2)
{    p1.setParameters(p2.getArrival(), p2.getDuration(), p2.getMemory(), p2.getPriority(), NULL); 
     p1.setCPU(p2.getCPU());}

bool verifyZeros(Process* r, int length)
{
    int zero = 0;
    for(int i = 0; i < length; i++)
    {
        if(r[i].getDuration() == 0)
        {
            zero++;
        }
    }

    if(zero == (length))
    {
        return true;
    }
    else
    {
        return false;
    }
}