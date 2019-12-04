#include "Processo.h"

int main(int argc, char* argv[])
{
    //Retira informacao para o simulador
    int memoria_disponivel = (int) atoi(argv[2]);
    int memoria_maxima = memoria_disponivel;
    int time = 0;
    int nCPUs = (int) atoi(argv[1]);
    bool CPU_processou = false;

    //Le o arquivo e distribui para os vetores com diferentes prioridades (MULTIFILAS)
    vector <Processo> prioridade_0 = LeArquivo(argv[3], 0);
    vector <Processo> prioridade_1 = LeArquivo(argv[3], 1);
    vector <Processo> prioridade_2 = LeArquivo(argv[3], 2);
    vector <Processo> prioridade_3 = LeArquivo(argv[3], 3);
    vector <Processo> prioridade_4 = LeArquivo(argv[3], 4);

    //Vetor final com todos os processos ja executados e suas estatisticas
    vector <Processo> processados;

    //Organiza os vetores por ordem de chegada
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
        //Loop para quantos CPUs irao processar por slice
        for(int CPU = 1; CPU <= nCPUs; CPU++)
        {
            CPU_processou = false;

            //Caso tenha processos na prioridade e a CPU atual ainda nao executou nenhum...
            if((prioridade_0.size() != 0) && !CPU_processou)
            {
                //Realiza uma busca para qual o proximo processo disponivel 
                for(int i = 0; i < prioridade_0.size(); i++)
                {
                    if(prioridade_0[i].Memoria > memoria_maxima)
                        prioridade_0.erase(prioridade_0.begin() + i);

                    //Verifica o tempo de chegada
                    if(prioridade_0[i].tChegada <= time)
                    {
                        //Verifica memoria disponivel
                        if(prioridade_0[i].Memoria <= memoria_disponivel)
                        {
                            //Verifica se nenhuma CPU o alocou
                            if (prioridade_0[i].numaCPU == 0)
                            {
                                CPU_processou = true;

                                //Aloca memoria 
                                memoria_disponivel = memoria_disponivel - prioridade_0[i].Memoria;

                                //Executa o processo e o coloca no fim da fila
                                prioridade_0.push_back(Ciclo(prioridade_0[i], time, CPU));
                                prioridade_0.erase(prioridade_0.begin() + i);

                                memoria_disponivel = memoria_disponivel + prioridade_0.back().Memoria;

                                //Caso o processo acabou, coloca ele no vetor processados e o retira da fila atual
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

            //A logica acima se repete para cada prioridade, com a distincao de havera a troca de prioridade entre eles 
            if((prioridade_1.size() != 0) && !CPU_processou)
            {
                for(int i = 0; i < prioridade_1.size(); i++)
                {
                    if(prioridade_1[i].Memoria > memoria_maxima)
                        prioridade_1.erase(prioridade_1.begin() + i);

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
                    if(prioridade_2[i].Memoria > memoria_maxima)
                        prioridade_2.erase(prioridade_2.begin() + i);

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
                    if(prioridade_3[i].Memoria > memoria_maxima)
                        prioridade_3.erase(prioridade_3.begin() + i);
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
                    if(prioridade_4[i].Memoria > memoria_maxima)
                        prioridade_4.erase(prioridade_4.begin() + i);
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

        //Zera a CPU para que no proximo slice, outro processador poder executar o processo
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
    
    //Estatisticas finais
    for(int i = 0; i < processados.size(); i++)
    {   cout << "Chegada: " << processados[i].tChegada << "\tLancamento: " << processados[i].lancamento << "\tDuracao Projetada: " << processados[i].tDuracao << "\tDuracao Observada: " << (processados[i].tSlice + Quantum) << endl;    }
}