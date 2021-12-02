#include <stdlib.h>
#include <stdio.h>
#include "processus.h"

void RR(int nb, process *proc)
{

  int i, j;
  int curr_time = 0;
  int q ;
  int *Te_restant = (int *)malloc(sizeof(int) * nb);
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

  printf("donner le quantum : \n");
  scanf("%d",&q);
  printf("\n");
  /*Afficher l'ordonnancement appliqué*/
  printf("Ordonnancement RR\n");
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

  //calcul
  for (i = 0; i < nb; i++)
  {
    Te_restant[i] = proc[i].Te;
  }

  while (1)
  {
    int termine = 1; //indique si les processus ont terminé ou non

    for (i = 0; i < nb; i++)
    {
      if ((Te_restant[i] > 0) && (proc[i].Ta <= curr_time))
      {
        termine = 0;

        if (Te_restant[i] > q) // mezl makmlch
        {
          curr_time += q;
          Te_restant[i] -= q;
          printf("P%s\t\t %dms --> %dms\t\n", proc[i].nomProcessus, curr_time - q, curr_time);
        }

        else //bch ykaml
        {
          curr_time += Te_restant[i];
          proc[i].temAttente = curr_time - proc[i].Te;

          printf("P%s\t\t %dms --> %dms\t\n", proc[i].nomProcessus, curr_time - Te_restant[i], curr_time);
          Te_restant[i] = 0;
        }
      }
    }

    if (termine == 1)
      break;
  }

  free(Te_restant);
}
