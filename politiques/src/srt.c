#include <stdlib.h>
#include <stdio.h>
#include "processus.h"

void Srt(int nb, process *proc)
{

    int i, j, current_time = 0;
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
    printf("****Ordonnancement SRT****\n");
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
    printf("****Date de debut et de fin d'execution des %d processus****\n", nb);
    printf("\n");
    printf("\t ");
    printf("Processus\t Tdeb\t Tfin\n");
    printf("\n");

    /*Calcul*/

    int Te_total = 0;

    int Min_Te_restant;

    int k = 0;

    int *Te_restant = (int *)malloc(sizeof(int) * nb);

    int *count = (int *)malloc(sizeof(int) * nb);

    for (i = 0; i < nb; i++)
    {
        count[i] = 0;

        Te_restant[i] = proc[i].Te;

        Te_total += proc[i].Te;
    }

    while (current_time < Te_total)
    {

        Min_Te_restant = 999;

        if (current_time <= proc[nb - 1].Ta)
        {

            for (i = 0; i < nb; i++)
            {

                if ((proc[i].termine == 0) && (proc[i].Ta <= current_time) && (Min_Te_restant > Te_restant[i]))
                {
                    Min_Te_restant = Te_restant[i];

                    k = i;
                }
            }
            printf("\t ");
            printf("P%d\t\t %dms --> %dms\t\n", proc[0].idProcessus, proc[0].Ta, proc[0].Te - Te_restant[0]);
        }

        else
        {

            for (i = 0; i < nb; i++)
            {

                if ((proc[i].termine == 0) && (Min_Te_restant > Te_restant[i]))
                {
                    Min_Te_restant = Te_restant[i];

                    k = i;
                }
            }
        }

        if (count[k] == 0)
        {
            count[k]++;
        }

        Te_restant[k]--;

        current_time++;

        if (Te_restant[k] == 0)
        {
            proc[k].termine = 1;

            proc[k].temAttente = current_time - proc[k].Te - proc[k].Ta;

            proc[k].temfin = current_time;
            printf("\t ");
            printf("P%d\t\t %dms --> %dms\t\n", proc[k].idProcessus, proc[k].Ta + proc[k].temAttente, proc[k].temfin);
        }
    }

    free(count);
    free(Te_restant);
}

int main(int argc, char *argv[])
{
    process *proc;
    int nb = 0;
    extraction(&proc, argv[1]);
    nb = Nombre_processus(argv[1]);

    Srt(nb, proc);
}