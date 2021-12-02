#include <stdlib.h>
#include <stdio.h>
#include "processus.h"

void Fifo(int nb, process *proc)
{

	int i;
	int j;
	process permut;

	//tri
	for (i = 0; i < nb + 1; i++)
		for (j = i + 1; j < nb; j++)
		{
			if (proc[i].Ta > proc[j].Ta)
			{
				permut = proc[i];
				proc[i] = proc[j];
				proc[j] = permut;
			}
		}

	printf("\n");
	/*Afficher l'ordonnancement appliqué*/
	printf("Ordonnancement FIFO\n");
	printf("\n");
	/*Afficher la date d'arrivee, le temps d'execution et la priorité de chaque processus*/
	printf("Processus\t Ta\t Te\t Pr\n");
	for (i = 0; i < nb; i++)
	{
		printf("P%s\t\t %dms \t %dms\t %d\n", proc[i].nomProcessus, proc[i].Ta, proc[i].Te, proc[i].Pr);
	}
	printf("\n");
	/*afficher lA DATE DE FIN D'EXECUTION DE CHAQUE  processuss*/
	printf("****date de debut et de fin d'execution des %d processus****\n", nb);
	printf("\n");
	printf("Processus\t Tdeb\t Tfin\n");

	/*Calcul*/
	proc[0].temfin = proc[0].Te + proc[0].Ta;
	proc[0].temAttente = 0;
	proc[0].temdeb = proc[0].Ta;

	printf("P%s\t\t %dms --> %dms\t\n", proc[0].nomProcessus, proc[0].temdeb, proc[0].temfin);
	for (i = 1; i < nb; i++)
	{
		if (proc[i].Ta >= proc[i - 1].temfin)
		{
			proc[i].temfin = proc[i].Te + proc[i].Ta;
			proc[i].temAttente = 0;
			proc[i].temdeb = proc[i].Ta;
		}
		else
		{
			proc[i].temdeb = proc[i - 1].temfin;
			proc[i].temfin = proc[i].temdeb + proc[i].Te;
		}

		printf("P%s\t\t %dms --> %dms\t\n", proc[i].nomProcessus, proc[i].temdeb, proc[i].temfin);
	}
	printf("\n");
}
