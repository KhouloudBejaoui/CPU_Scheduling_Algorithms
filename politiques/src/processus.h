#ifndef PROCESSUS_DOT_H    
#define PROCESSUS_DOT_H    

	typedef struct process
	{
		char nomProcessus[50];
		int Ta;
		int Te;
		int Pr;
		int temAttente;
		int temfin;
		int temdeb;
        int termine;
	} process;

void Fifo(int nb, process *proc);
void RR(int nb, process *proc);
void Sjf(int nb, process *proc);

#endif 
