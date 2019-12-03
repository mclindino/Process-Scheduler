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
};
