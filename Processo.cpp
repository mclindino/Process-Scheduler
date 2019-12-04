#include "Processo.h"

Processo::Processo()
{
	this->tChegada = 0;                 //Slice que comecara a processar
    this->tDuracao = 0;                 //Duracao do processo
    this->Memoria = 0;                  //Memoria necessaria
    this->Prioridade = 0;               //Prioridade
    this->tProcessado = 0;              //Variavel para o controle do tempo de processamento
    this->tRestante = 0;                //Variavel para o controle de quanto tempo falta acabar o processo
    this->tPrioridade = 0;              //Variavel para o controle de troca de prioridade
    this->tSlice = 0;                   //Ultimo slice que o processo foi executado
    this->numaCPU = 0;                  //ID da CPU que esta processando
    this->prioridadePrimaria = 0;       //Controle da troca de prioridade
    this->lancamento = 0;               //Qual slice comecou a ser processado
    this->controleLancamento = false;   //Controle para a variavel lancamento
}
Processo::Processo(int tChegada, int tDuracao, int Memoria, int Prioridade)
{
    this->tChegada = tChegada;
    this->tDuracao = tDuracao;
    this->Memoria = Memoria;
    this->Prioridade = Prioridade;
    this->tRestante = tDuracao - tProcessado;
    this->tProcessado = 0;
    this->tPrioridade = 0;
    this->tSlice = 0;
    this->numaCPU = 0;
    this->prioridadePrimaria = Prioridade;
    this->lancamento = 0;
    this->controleLancamento = false;
};

//Controla se todos os processos ja foram executados, retornando verdadeiro caso nao tenha mais processos
bool zerado(vector<Processo> v0,  vector<Processo> v1,  vector<Processo> v2,  vector<Processo> v3,  vector<Processo> v4)
{
    if((v0.size() + v1.size() + v2.size() + v3.size() + v4.size()) == 0)     {     return true;    }
    else                                                                     {     return false;   }
}

//Chamada a cada slice. Atualiza os valores do processo atual
Processo Ciclo(Processo atual, int time, int CPU)
{
    //Atualiza o tempo processado
    atual.tProcessado = atual.tProcessado + Quantum;

    //Atualiza o tempo para a troca de prioridade
    atual.tPrioridade = atual.tPrioridade + Quantum;

    //Atualiza o tempo restante para terminar o processo
    atual.tRestante = atual.tDuracao - atual.tProcessado;
    
    //Define o slice que o processo foi lancado
    if(!atual.controleLancamento)
    {
        atual.lancamento = time;
        atual.controleLancamento = true;
    }

    //Atualiza o ultimo slice que foi executado
    atual.tSlice = time;

    //Define qual CPU esta executando o processo atual
    atual.numaCPU = CPU;

    //Caso for necessario trocar de prioridade
    if(atual.tPrioridade >= 10)
    {
        if((atual.Prioridade > 0) && (atual.prioridadePrimaria != 4))
        {
            //Diminui prioridade
            atual.Prioridade++;
            atual.tPrioridade = 0;
        }
        else if((atual.Prioridade == 4) && (atual.prioridadePrimaria != 4))
        {
            //Aumenta prioridade
            atual.Prioridade--;
            atual.tPrioridade = 0;
        }
    }

    //Retorna processo atual
    return atual;
}

//Utilizada para organizar os vetores de prioridades
bool compInicio(Processo a, Processo b)
{
    return (a.tChegada < b.tChegada);
}

//Le o arquivo e aloca os processos nos determinandos vetores
vector <Processo> LeArquivo(const char *arq, int prioridade)
{
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

//Printa um vetor de escolha (deBug)
void printa(vector<Processo> p)
{
    for(int i = 0; i < p.size(); i++)
    {
        cout << p[i].tChegada << '-'
             << p[i].tDuracao << '-'
             << p[i].tSlice << '-'
             << p[i].numaCPU << endl;
    }
}