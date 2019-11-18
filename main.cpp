#include "Units.h"
#include <fstream>

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
                                            parameters[2], parameters[3]);
    }

    
    //Libera memória
    free(parameters);
    free(process);
    processFile.close();
}