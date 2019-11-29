#include "Units.h"


int main(int argc, char* argv[])
{	
    //Informaçoes do Simulador
    int nCPUs = (int) atoi(argv[1]);
    int memory = (int) atoi(argv[2]);
    char* fileName = argv[3];

    //Retira dados do arquivo
    Process* process = NULL;    
    ifstream processFile(fileName);
    int* parameters;
    int nProcess = 0;
    string line;
    while( getline(processFile, line) )
    {
        parameters = readParameters(line);
        nProcess++;

        process = (Process*) realloc(process, nProcess * sizeof(Process));
        process[nProcess - 1].setParameters(parameters[0], parameters[1], 
                                            parameters[2], parameters[3], 10000);
        //cout << process[nProcess-1].getMemory() << endl;
    }

    //Instancia e ajusta todos os processos na multifila
    multiLine lista;
    lista.ajustProcess(process, nProcess);
    printAllProcess(lista);
    //Tempo limite para processar todos os Processos (Variavel i)
    for(int slice = 0; slice < 200000; slice++)
    {
        for(int cpuID = 0; cpuID < nCPUs; cpuID++)
        {
            if(lista.getMultilines()[0].sliceEdge(slice, cpuID))
            {
                printOneLineOfProcess(lista.getMultilines()[0], slice);
            }
            
            else if(lista.getMultilines()[1].sliceEdge(slice, cpuID))
            {
                printOneLineOfProcess(lista.getMultilines()[1], slice);
            }

            else if(lista.getMultilines()[2].sliceEdge(slice, cpuID))
            {
                printOneLineOfProcess(lista.getMultilines()[2], slice);
            }
            else if(lista.getMultilines()[3].sliceEdge(slice, cpuID))
            {
                printOneLineOfProcess(lista.getMultilines()[3], slice);
            }
            else if(lista.getMultilines()[4].sliceEdge(slice, cpuID))
            {
                printOneLineOfProcess(lista.getMultilines()[4], slice);
            }
            else
            {
                cout << "Acabou os processos..." << endl;
                exit(1);
            }
        }
        //lista.getMultilines()[0].sliceEdge(i);
        
        printAllProcess(lista);
        sleep(1);
    }
    free(parameters);
    free(process);
    processFile.close();
}