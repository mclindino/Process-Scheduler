#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
#define Quantum 2

class Processo
{
    public:
    	Processo();
        Processo(int tChegada, int tDuracao, int Memoria, int Prioridade);

        int tChegada;
        int tDuracao;
        int Memoria;
        int Prioridade;
        int tProcessado;
        int tRestante;
        int tPrioridade;
        int tSlice;
        int numaCPU;
        int prioridadePrimaria;
        int lancamento;
        bool controleLancamento;
};

bool zerado(vector<Processo> v0,  vector<Processo> v1,  vector<Processo> v2,  vector<Processo> v3,  vector<Processo> v4);
Processo Ciclo(Processo atual, int time, int CPU);
bool compInicio(Processo a, Processo b);
vector <Processo> LeArquivo(const char *arq, int prioridade);
void printa(vector<Processo> p);