#include "Units.h"
void Process::setParameters(int arrival, int duration, int memory, int priority, int CPU)
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
void Process::setCPU(int CPU)        {   this->CPU = CPU;    }
int  Process::getCPU()               {   return CPU;      	 }
//int  Process::getLose_priority()     {   return lose_priority;}
//void Process::setLose_priority(int x) { this->lose_priority = x; }

void  roundRobin::setPriority(int priority)                {   this->priority = priority;  		}
int  roundRobin::getPriority()                             {   return priority;            		}
void roundRobin::setSlice(int slice)                       {   this->slice = slice;        		}
Process* roundRobin::getListProcess()			   		   {   return list_process;				}
void roundRobin::setCurrent(int nCPUs)                     {   this->current = (int *) malloc(nCPUs * sizeof(int));    }
Process  roundRobin::getCurrentProcess(int current_CPU)
{   
    // int available_process = verifyListProcess(this->list_process, this->length);
    // if(available_process != 404)
    // {
    //     current[current_CPU] = available_process;
        
    // }
    return list_process[current[current_CPU]];              
}
bool roundRobin::sliceEdge(int clock, int current_CPU, int* memory)
{
    if(!zeros(this->list_process, this->length, &memory))
    {
        if((clock % slice) == 0)
        {
            //Processol disponivel
            current[current_CPU] = verifyListProcess(this->list_process,this->length, clock, current[current_CPU], &memory, current_CPU);
            //cout << "PROCESSO ATUAL: " << current[current_CPU] << endl;
            if(current[current_CPU] != 404)
            {
                //current[current_CPU] = available_process;
                //Pode ser processado?
                if(list_process[current[current_CPU]].getArrival() <= clock)
                {
                    list_process[current[current_CPU]].setCPU(current_CPU);
                    list_process[current[current_CPU]].modifyDuration();
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else {   return false;  }
        }
        else
        {
            if(list_process[current[current_CPU]].getArrival() <= clock)
            {
                if(list_process[current[current_CPU]].getDuration() != 0)
                {
                list_process[current[current_CPU]].modifyDuration();
                return true;  
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
                
        }
    }
    else
    {
        return false;
    }
    
    
    // borda de clock
    //     processo_disponivel {true, false}
    // nao é borda de clock
    //     processo_atual {true, false caso acabou!}
}  

int  roundRobin::getLength()										{	return this->length; 		}
void roundRobin::setLength(int length)								{	this->length = length;		}
void roundRobin::setListProcess(Process* process, int nProcess)
{
	list_process = (Process*) malloc(nProcess * sizeof(Process));
	for(int i = 0; i < nProcess; i++)
	{
		list_process[i].setParameters(process[i].getArrival(), process[i].getDuration(),
									  process[i].getMemory(), process[i].getPriority(), process[i].getCPU());
	}
    first = list_process[0].getArrival();
}

void  multiLine::freeMultilines()                                   {   free(this->multilines);     }
roundRobin*  multiLine::getMultilines()								{	return this->multilines;	}					
void  multiLine::ajustProcess(Process* process, int nProcess, int nCPUs)
{

	this->multilines = (roundRobin*) malloc(5 * sizeof(roundRobin));
	Process* prioritys = NULL;
	int size = 0;

	for(int priority = 0; priority < 5; priority++)
	{
	    for(int i = 0; i < nProcess; i++)
	    {
	    	if(process[i].getPriority() == priority)
	    	{
	    		size++;
	    		prioritys = (Process*) realloc(prioritys, size * sizeof(Process));
	    		prioritys[size-1].setParameters(process[i].getArrival(), process[i].getDuration(), process[i].getMemory(), process[i].getPriority(), process[i].getCPU());
	    		//cout << "Prioridade: " << priority << "\tProcess: " << prioritys[size-1].getDuration() << endl;
	    	}
	    }
	    this->multilines[priority].setListProcess(prioritys, size);
        this->multilines[priority].setLength(size);
        this->multilines[priority].setSlice(2);
        this->multilines[priority].setCurrent(nCPUs);
	    size = 0;
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
								   << m.getMultilines()[i].getListProcess()[j].getMemory() << '-'
								   << m.getMultilines()[i].getListProcess()[j].getCPU() << endl;
		}
	}
	cout << "--------------------------------------------------" << endl;
}

void printOneLineOfProcess(roundRobin line, int clock, int current_cpu)
{
    cout << "--------------------------------------------------" << endl;
    cout << "slice: " << clock << endl;
    for(int i = 0; i < line.getLength(); i++)
    {
        cout << "\tProcesso: " << line.getListProcess()[i].getArrival() << "-"
                                << line.getListProcess()[i].getDuration() << "-"
                                << line.getListProcess()[i].getMemory() << "-"
                                << line.getListProcess()[i].getPriority() << "-"
                                << line.getListProcess()[i].getCPU() << endl;
    }   

    cout << "\n\tProcesso Atual: " << line.getCurrentProcess(current_cpu).getArrival() << "-"
                                    << line.getCurrentProcess(current_cpu).getDuration() << "-"
                                    << line.getCurrentProcess(current_cpu).getMemory() << "-"
                                    << line.getCurrentProcess(current_cpu).getPriority() << "-"
                                    << line.getCurrentProcess(current_cpu).getCPU() << endl;
    cout << "--------------------------------------------------" << endl;
}

int verifyListProcess(Process* r, int length, int clock, int current_process, int** memory, int current_cpu)
{	
    //cout << "CURRENT: " << current_process << endl;
    //cout << "CURRENT CPU: " << current_cpu << endl;
    //cout << "Length: " << length << endl;
    for(int i = current_process; i < length; i++)
    {
        if(r[i].getDuration() != 0)
        {
            if(r[i].getCPU() == 10000)
            {
                if(r[i].getArrival() <= clock)
                {
                    if(current_process != i)
                    {
                        if((*(*memory) - r[i].getMemory() + r[current_process].getMemory()) > 0)
                        {
                            r[current_process].setCPU(10000);
                            //cout << "MEMORIA 1: " << *(*memory) << endl;
                            *(*memory) = *(*memory) - r[i].getMemory() + r[current_process].getMemory();
                            return i;
                        }
                    }
                    else
                    {
                      if((*(*memory) - r[i].getMemory()) > 0)
                        {
                            r[current_process].setCPU(10000);
                            //cout << "entra AQUI" << endl;
                            *(*memory) = *(*memory) - r[i].getMemory();
                            return i;
                        }  
                    }
                }
            }
        }
   	}
    
    if(current_process != 404)
    {
        for(int j = 0; j < current_process; j++)
        {
        //cout << "PROCESSO:" << current_process << "ATUALIDADE:" << j << endl;
        if(r[j].getDuration() != 0)
            {
                if(r[j].getCPU() == 10000)
                {
                    if(r[j].getArrival() <= clock)
                    {
                        if(( *(*memory) - r[j].getMemory() + r[current_process].getMemory()) > 0)
                        {
                            r[current_process].setCPU(10000);
                            *(*memory) = *(*memory) - r[j].getMemory() + r[current_process].getMemory();
                            //cout << "NAO AKI" << endl;
                            return j;
                        }
                    }
                }
            } 
        }
    }
    else
    {
        for(int j = 0; j < length; j++)
        {
        //cout << "PROCESSO:" << current_process << "ATUALIDADE:" << j << endl;
        if(r[j].getDuration() != 0)
            {
                if(r[j].getCPU() == 10000)
                {
                    if(r[j].getArrival() <= clock)
                    {
                        if(( *(*memory) - r[j].getMemory() + r[current_process].getMemory()) > 0)
                        {
                            r[current_process].setCPU(10000);
                            *(*memory) = *(*memory) - r[j].getMemory() + r[current_process].getMemory();
                            //cout << "NAO AKI" << endl;
                            return j;
                        }
                    }
                }
            } 
        }
    }
    

    if((r[current_process].getDuration() != 0) && (r[current_process].getCPU() == current_cpu))
    {
        //cout << "ZUEIA" << endl;
        return current_process;
    }
   	else
    {
        //cout << current_process << endl;
        r[current_process].setCPU(10000);
        return 404;
    }
}

int zeros(Process* r, int length, int** memory)
{
    //bool verify = true;
    for(int i = 0; i < length; i++)
    {
        if(r[i].getDuration() != 0 )
        {
            //verify = false;
            return false;
        }
        else
        {
            if((r[i].getCPU() != 10000) && (i != 0))
            {
                r[i].setCPU(10000);
                *(*memory) = *(*memory) + r[i].getMemory();
            }
        }
        
    }
    
    // if(verify)
    // {
    //     for(int i = 0; i < length; i++)
    //     {
    //         if(r[i].getCPU() != 10000)
    //         {
    //             r[i].setCPU(10000);
    //             *(*memory) = *(*memory) + r[i].getMemory();
    //         }
    //     }
    // }
    
    return true;
}
int  processesFinder(Process* p, int length, int CPU) 
{
    for(int process_search = 0; process_search < length; process_search++)
    {
    	if((p[process_search].getCPU() == CPU) && (p[process_search].getDuration() != 0)) return process_search;
    }
    return 404; 
}



// Pvoid verifyPriority(multiLine r, int nProcess) //, Process p)
// {
//     int size = 0;
//     Process* p = (Process *) malloc(sizeof(Process));
//     for(int priority = 0; priority < 5; priority++)
// 	{
// 	    for(int j = 0; j < nProcess; j++)
// 	    {
//             p.setParameters(r.getMultilines()[priority].getListProcess()[j];
//             if((p.getPriority() >= 1) && p.getPriority() != 4)
//             {
//                 if(p.getLose_priority() >= 10)
//                 {
//                     Process* aux;
//                     for(int i = 0; i < r[p.getPriority() + 1].getLength(); i++)
//                     {
//                         size++;
//                         aux = (Process*) realloc(aux, size * sizeof(Process));
//                         aux[size-1].setParameters(r[p.getPriority() + 1].getListProcess()[i].getArrival(), r[p.getPriority() + 1].getListProcess()[i].getDuration(), r[p.getPriority() + 1].getListProcess()[i].getMemory(), r[p.getPriority() + 1].getListProcess()[i].getPriority(), r[p.getPriority() + 1].getListProcess()[i].getCPU());
//                         //cout << "Prioridade: " << priority << "\tProcess: " << prioritys[size-1].getDuration() << endl;
//                     }
                    
//                     aux = (Process*) realloc(aux, (size+1) * sizeof(Process));
//                     aux[size-1].setParameters(p.getArrival(), p.getDuration(), p.getMemory(), p.getPriority(), p.getCPU());
//                     r.getMultilines()[p.getPriority() + 1].setListProcess(aux, size);
//                 }
//             }
// 	    }
// 	}
// }