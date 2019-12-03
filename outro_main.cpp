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
    if(v0.size() && v1.size() && v2.size() && v3.size() && v4.size()) {     return true;    }
    else                                                              {     return false;   }
}

Processo Ciclo(Processo atual, int time)
{
    atual.tProcessado = atual.tProcessado + Quantum;
    atual.tPrioridade = atual.tPrioridade + Quantum;

    atual.tSlice = time;
    if(atual.tPrioridade >= 10)
    {
        if((atual.Prioridade > 0) && (atual.Prioridade < 4))
        {
            atual.Prioridade++;
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

int main()
{
    int memoria_disponivel = 1000;
    //Processo atual();

    vector <Processo> prioridade_0 = LeArquivo("arquivo.txt", 0);
    vector <Processo> prioridade_1 = LeArquivo("arquivo.txt", 1);
    vector <Processo> prioridade_2 = LeArquivo("arquivo.txt", 2);
    vector <Processo> prioridade_3 = LeArquivo("arquivo.txt", 3);
    vector <Processo> prioridade_4 = LeArquivo("arquivo.txt", 4);

    vector <Processo> processados;

    sort(prioridade_0.begin(), prioridade_0.end(), compInicio);
    sort(prioridade_1.begin(), prioridade_1.end(), compInicio);
    sort(prioridade_2.begin(), prioridade_2.end(), compInicio);
    sort(prioridade_3.begin(), prioridade_3.end(), compInicio);
    sort(prioridade_4.begin(), prioridade_4.end(), compInicio);

    for(int time = 0; time < 10000; time = time + Quantum)
    {
        if(zerado(prioridade_0, prioridade_1, prioridade_2, prioridade_3, prioridade_4)) break;
        if(prioridade_0.size() != 0)
        {
            for(int i = 0; i < prioridade_0.size(); i++)
            {
                if(prioridade_0[i].tChegada <= time)
                {
                    if(prioridade_0[i].Memoria <= memoria_disponivel)
                    {
                        memoria_disponivel = memoria_disponivel - prioridade_0[i].Memoria;

                        prioridade_0.push_back(Ciclo(prioridade_0[i], time));
                        prioridade_0.erase(prioridade_0.begin());

                        memoria_disponivel = memoria_disponivel + prioridade_0.back().Memoria;

                        if(prioridade_0.back().tRestante <= 0)
                        {
                            processados.push_back(prioridade_0.back());
                            prioridade_0.erase(prioridade_0.begin());
                        }

                        break;
                    }
                }
            }
        }

        if(prioridade_1.size() != 0)
        {
            for(int i = 0; i < prioridade_1.size(); i++)
            {
                if(prioridade_1[i].tChegada <= time)
                {
                    if(prioridade_1[i].Memoria <= memoria_disponivel)
                    {
                        memoria_disponivel = memoria_disponivel - prioridade_1[i].Memoria;

                        prioridade_1.push_back(Ciclo(prioridade_1[i], time));
                        prioridade_1.erase(prioridade_1.begin());

                        memoria_disponivel = memoria_disponivel + prioridade_1.back().Memoria;

                        if(prioridade_1.back().tRestante <= 0)
                        {
                            processados.push_back(prioridade_1.back());
                            prioridade_1.erase(prioridade_1.begin());
                        }
                        else if(prioridade_1.back().Prioridade != 1)
                        {
                            prioridade_2.push_back(prioridade_1.back());
                            prioridade_1.erase(prioridade_1.begin());
                        }

                        break;
                    }
                }
            }
        }

        if(prioridade_2.size() != 0)
        {
            for(int i = 0; i < prioridade_2.size(); i++)
            {
                if(prioridade_2[i].tChegada <= time)
                {
                    if(prioridade_2[i].Memoria <= memoria_disponivel)
                    {
                        memoria_disponivel = memoria_disponivel - prioridade_2[i].Memoria;

                        prioridade_2.push_back(Ciclo(prioridade_2[i], time));
                        prioridade_2.erase(prioridade_2.begin());

                        memoria_disponivel = memoria_disponivel + prioridade_2.back().Memoria;

                        if(prioridade_2.back().tRestante <= 0)
                        {
                            processados.push_back(prioridade_2.back());
                            prioridade_2.erase(prioridade_2.begin());
                        }
                        else if(prioridade_2.back().Prioridade != 2)
                        {
                            prioridade_3.push_back(prioridade_2.back());
                            prioridade_2.erase(prioridade_2.begin());
                        }

                        break;
                    }
                }
            }
        }

        if(prioridade_3.size() != 0)
        {
            for(int i = 0; i < prioridade_3.size(); i++)
            {
                if(prioridade_3[i].tChegada <= time)
                {
                    if(prioridade_3[i].Memoria <= memoria_disponivel)
                    {
                        memoria_disponivel = memoria_disponivel - prioridade_3[i].Memoria;

                        prioridade_3.push_back(Ciclo(prioridade_3[i], time));
                        prioridade_3.erase(prioridade_3.begin());

                        memoria_disponivel = memoria_disponivel + prioridade_3.back().Memoria;

                        if(prioridade_3.back().tRestante <= 0)
                        {
                            processados.push_back(prioridade_3.back());
                            prioridade_3.erase(prioridade_3.begin());
                        }
                        else if(prioridade_3.back().Prioridade != 3)
                        {
                            prioridade_4.push_back(prioridade_3.back());
                            prioridade_3.erase(prioridade_3.begin());
                        }

                        break;
                    }
                }
            }
        }

        if(prioridade_4.size() != 0)
        {
            for(int i = 0; i < prioridade_4.size(); i++)
            {
                if(prioridade_4[i].tChegada <= time)
                {
                    if(prioridade_4[i].Memoria <= memoria_disponivel)
                    {
                        memoria_disponivel = memoria_disponivel - prioridade_4[i].Memoria;

                        prioridade_4.push_back(Ciclo(prioridade_3[i], time));
                        prioridade_4.erase(prioridade_4.begin());

                        memoria_disponivel = memoria_disponivel + prioridade_4.back().Memoria;

                        if(prioridade_4.back().tRestante <= 0)
                        {
                            processados.push_back(prioridade_4.back());
                            prioridade_4.erase(prioridade_4.begin());
                        }
                        // else if(prioridade_4.back().prioridade != 4)
                        // {
                        //     prioridade_4.push_back(prioridade_3.back());
                        //     prioridade_3.pop_back();
                        // }

                        break;
                    }
                }
            }
        }
    }    //RR(r);
}
