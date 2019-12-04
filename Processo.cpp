#include "Processo.h"

Processo::Processo()
{
	this->tChegada = 0;//Tempo que leva pra ele ser processado
    this->tDuracao = 0;//Tempo que leva para ele come�ar a ser processado
    this->Memoria = 0;//Round Robin
    this->Prioridade = 0;
    this->tProcessado = 0;
    this->tRestante = 0;
    this->tPrioridade = 0;
    this->tSlice = 0;
    this->numaCPU = 0;
    this-> prioridadePrimaria = 0;
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
};

