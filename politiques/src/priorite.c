#include <stdlib.h>
#include <stdio.h>
#include "processus.h"

void priorite(int nb, process *proc)
{

	int i, j, curr_time = 0, rotation = 0, max = 0;

	process permut, *procAffichage;
	procAffichage = (process *)malloc(sizeof(process) * nb); //tab dynamique

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
	printf("****Ordonnancement priorité****\n");
	printf("\n");
	/*Afficher la date d'arrivee, le temps d'execution et la priorité de chaque processus*/
	printf("\t ");
	printf("Processus\t Ta\t Te\t Pr\n");
	printf("\n");
	for (i = 0; i < nb; i++)
	{
		printf("\t ");
		printf("P%d\t\t %dms \t %dms\t %d\n", proc[i].idProcessus, proc[i].Ta, proc[i].Te, proc[i].Pr);
	}
	printf("\n");
	/*afficher lA DATE DE FIN D'EXECUTION DE CHAQUE  processuss*/
	printf("****date de debut et de fin d'execution des %d processus****\n", nb);
	printf("\n");
	printf("\t ");
	printf("Processus\t Tdeb\t Tfin\n");
	printf("\n");

	/*Calcul*/

	/* Calculate the time of the first running process */
	proc[0].termine = 1;
	proc[0].temfin = proc[0].Te + proc[0].Ta;
	proc[0].temAttente = 0;

	curr_time = proc[0].temfin;
	// Increase the current time by the termine process time
	printf("\t ");
	printf("P%d\t\t %dms --> %dms\t\n", proc[0].idProcessus, proc[0].Ta, proc[0].temfin);
	procAffichage[0].idProcessus = proc[0].idProcessus;
	procAffichage[0].Ta = proc[0].Ta;
	procAffichage[0].Te = proc[0].Te;
	procAffichage[0].temfin = proc[0].temfin;
	/* Repeat the number of processes -1 */
	for (i = 1; i < nb; i++)
	{
		/* Repeat the number of processes -1 */
		for (j = 1; j < nb; j++)
		{
			/* If the process has already been termine */
			if (proc[j].termine == 1)
				continue;
			// go to next loop

			/* If the process has not yet termine */
			else
			{
				max = j;
				// Initialize the min variable
				break;
				// escape loop
			}
		}

		/* Repeat the number of processes -1 */
		for (j = 1; j < nb; j++)
		{
			/* Search for processes with maximum priority*/
			if ((proc[j].termine == 0) && (proc[j].Ta <= curr_time) && (proc[j].Pr > proc[max].Pr))
			{
				max = j;
				// update the maximum working process
			}
		}

		proc[max].temAttente = curr_time - proc[max].Ta;
		// Calculate the waiting time of the process to run
		proc[max].termine = 1;
		// change the execution process completion state

		curr_time += proc[max].Te;
		// Incremented by the execution time of the current time process

		proc[max].temfin = curr_time;
		// Calculate process return time
		printf("\t ");
		printf("P%d\t\t %dms --> %dms\t\n", proc[max].idProcessus, proc[max].Ta + proc[max].temAttente, proc[max].temfin);
		procAffichage[i].idProcessus = proc[max].idProcessus;
		procAffichage[i].Ta = proc[max].Ta;
		procAffichage[i].Te = proc[max].Te;
		procAffichage[i].temfin = proc[max].temfin;
	}
	printf("\n");
	printf("****Diagramme de GANTT****\n");
	printf("\n");
	printf("\t ");

	for (i = 0; i < nb; i++)
	{
		for (j = 0; j < procAffichage[i].Te; j++)
			printf("--");

		printf(" ");
	}

	printf("\n\t|");

	for (i = 0; i < nb; i++)
	{
		for (j = 0; j < procAffichage[i].Te - 1; j++)
			printf(" ");

		printf("P%d", procAffichage[i].idProcessus);

		for (j = 0; j < procAffichage[i].Te - 1; j++)
			printf(" ");

		printf("|");
	}

	printf("\n\t ");

	for (i = 0; i < nb; i++)
	{
		for (j = 0; j < procAffichage[i].Te; j++)
			printf("--");

		printf(" ");
	}

	printf("\n\t");

	printf("%d", procAffichage[0].Ta);

	for (i = 0; i < nb; i++)
	{
		rotation += procAffichage[i].Te - procAffichage[i].Ta;
		for (j = 0; j < procAffichage[i].Te; j++)
			printf("  ");
		if (rotation > 8)
			printf("\b");
		printf("%d", procAffichage[i].temfin);
	}
	printf("\n");
}
int main(int argc, char *argv[])
{
	process *proc;
	int nb = 0;
	extraction(&proc, argv[1]);
	nb = Nombre_processus(argv[1]);

	priorite(nb, proc);
}