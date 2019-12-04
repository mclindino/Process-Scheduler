#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "Processo.h"

#define Quantum 2

using namespace std;

bool zerado(vector<Processo> v0,  vector<Processo> v1,  vector<Processo> v2,  vector<Processo> v3,  vector<Processo> v4)
{
    if((v0.size() + v1.size() + v2.size() + v3.size() + v4.size()) == 0)     {     return true;    }
    else                                                                     {     return false;   }
}

void limpaCPUs(vector<Processo> v0)
{
    for(int i = 0; i < v0.size(); i++)
    {
        if(v0[i].numaCPU != 0)
        {
            v0[i].numaCPU = 0;
        }
    }
}
Processo Ciclo(Processo atual, int time, int CPU)
{
    atual.tProcessado = atual.tProcessado + Quantum;
    atual.tPrioridade = atual.tPrioridade + Quantum;
    atual.tRestante = atual.tDuracao - atual.tProcessado;
    atual.tSlice = time;
    atual.numaCPU = CPU;

    if(atual.tPrioridade >= 10)
    {
        if((atual.Prioridade > 0) && (atual.prioridadePrimaria != 4))
        {
            atual.Prioridade++;
            atual.tPrioridade = 0;
        }
        else if((atual.Prioridade == 4) && (atual.prioridadePrimaria != 4))
        {
            atual.Prioridade--;
            atual.tPrioridade = 0;
        }
    }

    return atual;
}

bool compInicio(Processo a, Processo b){
    return (a.tChegada < b.tChegada);
}

vector <Processo> LeArquivo(const char *arq, int prioridade){
    ifstream arquivo;
    arquivo.open(arq, ios::in);
    int tChegada, tDuracao, Memoria, Prioridade;

    vector <Processo> a;

    while(arquivo.good()){
        arquivo >> tChegada >> tDuracao >> Memoria >> Prioridade;
        if(Prioridade == prioridade)
        {
            Processo aux(tChegada, tDuracao, Memoria, Prioridade);
            a.push_back(aux);
        }

    }
    arquivo.close();
    return a;
}

void printa(vector<Processo> p)
{
    for(int i = 0; i < p.size(); i++)
    {
        cout << p[i].tChegada << '-'
             << p[i].tDuracao << '-'
             << p[i].tSlice << endl;
    }
}

int main()
{
    int memoria_disponivel = 1000;
    int time = 0;
    int nCPUs = 2;
    bool CPU_processou = false;
    //Processo atual();

    vector <Processo> prioridade_0 = LeArquivo("processParameters.txt", 0);
    vector <Processo> prioridade_1 = LeArquivo("processParameters.txt", 1);
    vector <Processo> prioridade_2 = LeArquivo("processParameters.txt", 2);
    vector <Processo> prioridade_3 = LeArquivo("processParameters.txt", 3);
    vector <Processo> prioridade_4 = LeArquivo("processParameters.txt", 4);

    vector <Processo> processados;

    sort(prioridade_0.begin(), prioridade_0.end(), compInicio);
    sort(prioridade_1.begin(), prioridade_1.end(), compInicio);
    sort(prioridade_2.begin(), prioridade_2.end(), compInicio);
    sort(prioridade_3.begin(), prioridade_3.end(), compInicio);
    sort(prioridade_4.begin(), prioridade_4.end(), compInicio);

    cout << "--------------------------------------------------" << endl;
    cout << "PROCESSOS A SEREM EXECUTADOS: " << endl;
    printa(prioridade_0);
    printa(prioridade_1);
    printa(prioridade_2);
    printa(prioridade_3);
    printa(prioridade_4);
    cout << "--------------------------------------------------" << endl;

    while(!zerado(prioridade_0, prioridade_1, prioridade_2, prioridade_3, prioridade_4))
    {
        for(int CPU = 1; CPU <= nCPUs; CPU++)
        {
            CPU_processou = false;
            if((prioridade_0.size() != 0) && !CPU_processou)
            {
                for(int i = 0; i < prioridade_0.size(); i++)
                {
                    if(prioridade_0[i].tChegada <= time)
                    {
                        if(prioridade_0[i].Memoria <= memoria_disponivel)
                        {
                            if (prioridade_0[i].numaCPU == 0)
                            {
                                CPU_processou = true;
                                memoria_disponivel = memoria_disponivel - prioridade_0[i].Memoria;

                                prioridade_0.push_back(Ciclo(prioridade_0[i], time, CPU));
                                prioridade_0.erase(prioridade_0.begin() + i);

                                memoria_disponivel = memoria_disponivel + prioridade_0.back().Memoria;

                                if(prioridade_0.back().tRestante <= 0)
                                {
                                    processados.push_back(prioridade_0.back());
                                    prioridade_0.erase(prioridade_0.begin() + (prioridade_0.size()));
                                }

                                break;
                            }
                        }
                    }
                }
            }
            if((prioridade_1.size() != 0) && !CPU_processou)
            {
                for(int i = 0; i < prioridade_1.size(); i++)
                {
                    if(prioridade_1[i].tChegada <= time)
                    {
                        if(prioridade_1[i].Memoria <= memoria_disponivel)
                        {
                            if(prioridade_1[i].numaCPU == 0)
                            {
                                CPU_processou = true;
                                memoria_disponivel = memoria_disponivel - prioridade_1[i].Memoria;

                                prioridade_1.push_back(Ciclo(prioridade_1[i], time, CPU));
                                prioridade_1.erase(prioridade_1.begin() + i);

                                memoria_disponivel = memoria_disponivel + prioridade_1.back().Memoria;

                                if(prioridade_1.back().tRestante <= 0)
                                {
                                    processados.push_back(prioridade_1.back());
                                    prioridade_1.erase(prioridade_1.begin() + prioridade_1.size());
                                }
                                else if(prioridade_1.back().Prioridade != 1)
                                {
                                    prioridade_2.push_back(prioridade_1.back());
                                    prioridade_1.erase(prioridade_1.begin() + prioridade_1.size());
                                }

                                break;
                            }
                        }
                    }
                }
            }

            if((prioridade_2.size() != 0) && !CPU_processou)
            {
                for(int i = 0; i < prioridade_2.size(); i++)
                {
                    if(prioridade_2[i].tChegada <= time)
                    {
                        if(prioridade_2[i].Memoria <= memoria_disponivel)
                        {
                            if(prioridade_2[i].numaCPU == 0)
                            {
                                CPU_processou = true;
                                memoria_disponivel = memoria_disponivel - prioridade_2[i].Memoria;

                                prioridade_2.push_back(Ciclo(prioridade_2[i], time, CPU));
                                prioridade_2.erase(prioridade_2.begin() + i);

                                memoria_disponivel = memoria_disponivel + prioridade_2.back().Memoria;

                                if(prioridade_2.back().tRestante <= 0)
                                {
                                    processados.push_back(prioridade_2.back());
                                    prioridade_2.erase(prioridade_2.begin() + prioridade_2.size());
                                }
                                else if(prioridade_2.back().Prioridade != 2)
                                {
                                    prioridade_3.push_back(prioridade_2.back());
                                    prioridade_2.erase(prioridade_2.begin() + prioridade_2.size());
                                }

                                break;
                            }
                        }
                    }
                }
            }

            if((prioridade_3.size() != 0)&& !CPU_processou)
            {
                for(int i = 0; i < prioridade_3.size(); i++)
                {
                    if(prioridade_3[i].tChegada <= time)
                    {
                        if(prioridade_3[i].Memoria <= memoria_disponivel)
                        {
                            if(prioridade_3[i].numaCPU == 0)
                            {
                                CPU_processou = true;
                                memoria_disponivel = memoria_disponivel - prioridade_3[i].Memoria;

                                prioridade_3.push_back(Ciclo(prioridade_3[i], time, CPU));
                                prioridade_3.erase(prioridade_3.begin() + i);

                                memoria_disponivel = memoria_disponivel + prioridade_3.back().Memoria;

                                if(prioridade_3.back().tRestante <= 0)
                                {
                                    processados.push_back(prioridade_3.back());
                                    prioridade_3.erase(prioridade_3.begin() + prioridade_3.size());
                                }
                                else if(prioridade_3.back().Prioridade != 3)
                                {
                                    prioridade_4.push_back(prioridade_3.back());
                                    prioridade_3.erase(prioridade_3.begin() + prioridade_3.size());
                                }

                                break;
                            }
                        }
                    }
                }
            }

            if((prioridade_4.size() != 0)&& !CPU_processou)
            {
                for(int i = 0; i < prioridade_4.size(); i++)
                {
                    if(prioridade_4[i].tChegada <= time)
                    {
                        if(prioridade_4[i].Memoria <= memoria_disponivel)
                        {
                            if(prioridade_4[i].numaCPU == 0)
                            {
                                CPU_processou = true;
                                memoria_disponivel = memoria_disponivel - prioridade_4[i].Memoria;

                                prioridade_4.push_back(Ciclo(prioridade_3[i], time, CPU));
                                prioridade_4.erase(prioridade_4.begin() + i);

                                memoria_disponivel = memoria_disponivel + prioridade_4.back().Memoria;

                                if(prioridade_4.back().tRestante <= 0)
                                {
                                    processados.push_back(prioridade_4.back());
                                    prioridade_4.erase(prioridade_4.begin() + prioridade_4.size());
                                }
                                else if(prioridade_4.back().Prioridade != 4)
                                {
                                    prioridade_3.push_back(prioridade_4.back());
                                    prioridade_4.erase(prioridade_4.begin() + prioridade_4.size());
                                }

                                break;
                            }
                        }
                    }
                }
            }
        }
        for(int k = 0; k < prioridade_0.size(); k++)
        {
            if(prioridade_0[k].numaCPU != 0) prioridade_0[k].numaCPU = 0;
        }
        for(int k = 0; k < prioridade_1.size(); k++)
        {
            if(prioridade_1[k].numaCPU != 0) prioridade_1[k].numaCPU = 0;
        }
        for(int k = 0; k < prioridade_2.size(); k++)
        {
            if(prioridade_2[k].numaCPU != 0) prioridade_2[k].numaCPU = 0;
        }
        for(int k = 0; k < prioridade_3.size(); k++)
        {
            if(prioridade_3[k].numaCPU != 0) prioridade_3[k].numaCPU = 0;
        }
        for(int k = 0; k < prioridade_4.size(); k++)
        {
            if(prioridade_4[k].numaCPU != 0) prioridade_4[k].numaCPU = 0;
        }

        time = time + Quantum;
    }
    printa(processados);
}
