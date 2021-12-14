#include <stdlib.h>
#include <stdio.h>
#include "processus.h"

void RR(int nb, process *proc)
{

  int i, j, curr_time = 0, q, Te_totale = 0;
  process permut, *procAffichage;
  procAffichage = (process *)malloc(sizeof(process) * nb); //tab dynamique

  int *Te_restant = (int *)malloc(sizeof(int) * nb);
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

  printf("   Donner le quantum : ");
  scanf("%d", &q);
  printf("\n");
  /*Afficher l'ordonnancement appliqué*/
  printf("****Ordonnancement RR avec quantum égale à %d****\n", q);
  printf("\n");
  /*Afficher la date d'arrivee, le temps d'execution et la priorité de chaque processus*/
  printf("\t");
  printf("Processus\t Ta\t Te\t Pr\n");
  printf("\n");
  for (i = 0; i < nb; i++)
  {
    printf("\t");
    printf("P%d\t\t %dms \t %dms\t %d\n", proc[i].idProcessus, proc[i].Ta, proc[i].Te, proc[i].Pr);
  }
  printf("\n");
  /*afficher lA DATE DE FIN D'EXECUTION DE CHAQUE  processuss*/
  printf("****Date de debut et de fin d'execution des %d processus****\n", nb);
  printf("\n");
  printf("\t");
  printf("Processus\t Tdeb\t Tfin\n");
  printf("\n");
  //calcul
  for (i = 0; i < nb; i++)
  {
    Te_restant[i] = proc[i].Te;
    Te_totale += proc[i].Te;
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
          procAffichage[i].idProcessus = proc[i].idProcessus;
          procAffichage[i].Ta = proc[i].Ta;
          procAffichage[i].Te = proc[i].Te;
          procAffichage[i].temfin = proc[i].temfin;
          printf("\t");
          printf("P%d\t\t %dms --> %dms\t\n", proc[i].idProcessus, curr_time - q, curr_time);
        }

        else //bch ykaml
        {
          curr_time += Te_restant[i];
          proc[i].temAttente = curr_time - proc[i].Te;
          procAffichage[i].idProcessus = proc[i].idProcessus;
          procAffichage[i].Ta = proc[i].Ta;
          procAffichage[i].Te = proc[i].Te;
          procAffichage[i].temfin = proc[i].temfin;
          printf("\t");
          printf("P%d\t\t %dms --> %dms\t\n", proc[i].idProcessus, curr_time - Te_restant[i], curr_time);
          Te_restant[i] = 0;
        }
      }
    }

    if (termine == 1)
      break;
  }
  //diagramme de gantt
  printf("\n");
  printf("****Diagramme de GANTT****\n");
  printf("\n");
  printf("\t");

  /* barre superieur */
  for (i = 0; i < nb; i++)
  {
    Te_restant[i] = procAffichage[i].Te;
  }
  while (1)
  {
    int termine = 1;

    for (i = 0; i < nb; i++)
    {
      if (Te_restant[i] > 0)
      {
        termine = 0;

        if (Te_restant[i] < q)
        {
          printf(" ");
          for (j = 0; j < Te_restant[i]; j++)
            printf("--");
        }

        else
        {
          printf(" ");
          for (j = 0; j <= q; j++)
            printf("--");
        }

        if (Te_restant[i] > q)
        {
          curr_time += q;
          Te_restant[i] -= q;
        }

        else
        {
          curr_time += Te_restant[i];
          procAffichage[i].temAttente = curr_time - procAffichage[i].Te;
          Te_restant[i] = 0;
        }
      }
    }

    if (termine == 1)
      break;
  }

  printf(" \n\t");

  /* imprimer id processus */
  for (i = 0; i < nb; i++)
  {
    Te_restant[i] = procAffichage[i].Te;
  }

  while (1)
  {
    int termine = 1;

    for (i = 0; i < nb; i++)
    {
      if (Te_restant[i] > 0)
      {
        termine = 0;

        if (Te_restant[i] < q)
        {
          printf("|");

          if (Te_restant[i] != 1)
          {
            for (j = 0; j <= Te_restant[i] / 2; j++)
              printf(" ");

            printf("P%d", procAffichage[i].idProcessus);

            for (j = 0; j <= Te_restant[i] / 2; j++)
              printf(" ");
          }

          else
            printf("P%d", procAffichage[i].idProcessus);
        }

        else
        {
          printf("|");

          for (j = 0; j < q; j++)
            printf(" ");

          printf("P%d", procAffichage[i].idProcessus);

          for (j = 0; j < q; j++)
            printf(" ");
        }

        if (Te_restant[i] > q)
        {
          curr_time += q;
          Te_restant[i] -= q;
        }

        else
        {
          curr_time += Te_restant[i];
          procAffichage[i].temAttente = curr_time - procAffichage[i].Te;
          Te_restant[i] = 0;
        }
      }
    }

    if (termine == 1)
      break;
  }

  printf("|\n\t");

  for (i = 0; i < nb; i++)
  {
    Te_restant[i] = procAffichage[i].Te;
  }

  /* imprime la barre du bas*/
  while (1)
  {
    int termine = 1;

    for (i = 0; i < nb; i++)
    {
      if (Te_restant[i] > 0)
      {
        termine = 0;

        if (Te_restant[i] < q)
        {
          printf(" ");
          for (j = 0; j < Te_restant[i]; j++)
            printf("--");
        }

        else
        {
          printf(" ");
          for (j = 0; j <= q; j++)
            printf("--");
        }

        if (Te_restant[i] > q)
        {
          curr_time += q;
          Te_restant[i] -= q;
        }

        else
        {
          curr_time += Te_restant[i];
          procAffichage[i].temAttente = curr_time - procAffichage[i].Te;
          Te_restant[i] = 0;
        }
      }
    }

    if (termine == 1)
      break;
  }

  printf("\n\t");

  for (i = 0; i < nb; i++)
    Te_restant[i] = procAffichage[i].Te;

  curr_time = 0;

  /* temps */
  while (1)
  {
    int termine = 1;

    for (i = 0; i < nb; i++)
    {
      if (Te_restant[i] > 0)
      {
        termine = 0;

        if (Te_restant[i] < q)
        {
          printf("%-2d", curr_time);

          for (j = 0; j < Te_restant[i] - 1; j++)
            printf("  ");

          printf(" ");
        }

        else
        {
          printf("%-2d", curr_time);

          for (j = 0; j < q; j++)
            printf("  ");

          printf(" ");
        }

        if (Te_restant[i] > q)
        {
          curr_time += q;
          Te_restant[i] -= q;
        }

        else
        {
          curr_time += Te_restant[i];
          procAffichage[i].temAttente = curr_time - procAffichage[i].Te;
          Te_restant[i] = 0;
        }
      }
    }

    if (termine == 1)
      break;
  }

  printf("%-3d\n", Te_totale);

  printf("\n");

  free(Te_restant);
}

int main(int argc, char *argv[])
{
  process *proc;
  int nb = 0;
  extraction(&proc, argv[1]);
  nb = Nombre_processus(argv[1]);

  RR(nb, proc);
}
