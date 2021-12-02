#include <stdlib.h>
#include <stdio.h>
#include "processus.h"

void Sjf(int nb, process *proc)
{

	int i;
	int j;
	int curr_time = 0;
	int min = 0;
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
	printf("Ordonnancement SJF\n");
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

	/* Calculate the time of the first running process */
	proc[0].termine = 1;
	proc[0].temfin = proc[0].Te + proc[0].Ta;
	proc[0].temAttente = 0;

	curr_time = proc[0].temfin;
	// Increase the current time by the termine process time
	printf("P%s\t\t %dms --> %dms\t\n", proc[0].nomProcessus, proc[0].Ta, proc[0].temfin);
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
				min = j;
				// Initialize the min variable
				break;
				// escape loop
			}
		}

		/* Repeat the number of processes -1 */
		for (j = 1; j < nb; j++)
		{
			/* Search for processes with minimum working time */
			if ((proc[j].termine == 0) && (proc[j].Ta <= curr_time) && (proc[j].Te < proc[min].Te))
			{
				min = j;
				// update the minimum working process
			}
		}

		proc[min].temAttente = curr_time - proc[min].Ta;
		// Calculate the waiting time of the process to run
		proc[min].termine = 1;
		// change the execution process completion state

		curr_time += proc[min].Te;
		// Incremented by the execution time of the current time process

		proc[min].temfin = curr_time;
		// Calculate process return time
		printf("P%s\t\t %dms --> %dms\t\n", proc[min].nomProcessus, proc[min].Ta + proc[min].temAttente, proc[min].temfin);
	}
}
