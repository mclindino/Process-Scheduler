#include "Process.h"
#include <fstream>

int main(int argc, char* argv[])
{
    //Informaçoes do Simulador
    int nCPUs = (int) atoi(argv[1]);
    int memory = (int) atoi(argv[2]);
    char* fileName = argv[3];

    //Retira dados do arquivo
    //int arrival, duration, memoryProcess, priority;
    ifstream processFile(fileName);
    string parameters;
    while( getline(processFile, parameters) )
    {
    }
    processFile.close();
}