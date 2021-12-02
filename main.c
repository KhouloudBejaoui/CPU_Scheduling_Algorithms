#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include "./politiques/src/processus.h"


int main(int argc, char *argv[])
{
	process *proc;
	int i = 0;
	char c;
	int nb = 0; //nbre de processus dans le fichier
	FILE *fichier = NULL;
	fichier = fopen(argv[1], "r+");

	struct dirent *dir;
	DIR *d = opendir("./politiques/src");

	if (fichier != NULL)
	{

		do
		{
			c = fgetc(fichier);
			if (c == '#' || c == '\n')
				continue; //sauter les commentaires

			else if (c == 'p')
			{
				nb++;
			}

		} while (fgetc(fichier) != EOF);
		//printf("%d", nb);
		proc = (process *)malloc(sizeof(process) * nb); //tab dynamique
		fichier = fopen("conf-file", "r+");
		do
		{
			c = fgetc(fichier);
			if (c == 'p')
			{
				fscanf(fichier, "%s %d %d  %d", proc[i].nomProcessus, &proc[i].Ta, &proc[i].Te, &proc[i].Pr); //lire les 				données à partir du fichier conf
				i++;
			}

		} while (fgetc(fichier) != EOF);

		//liste dynamique

		//char **tab = NULL;
		//tab = malloc(10 * sizeof(char *));
		//int k = 0;
		if (d)
		{
			printf("Menu: \n");
			while ((dir = readdir(d)) != NULL)
			{
				if (strstr(dir->d_name, ".") == NULL)
				{
					printf("-%s\n", dir->d_name);

					/*tab[k] = (dir->d_name);
					printf("-%s\n", tab[k]);
					k++;*/
				}
			}
			closedir(d);
		}

		//choisir à partir du clavier
		int cl;
		printf("\n");
		printf("choisir une politique");
		scanf("%d", &cl);
		
		switch (cl)
		{
		case 1:
			Fifo(nb, proc);
			break;

		case 2:
			RR(nb, proc);
			break;
		case 3:
			Sjf(nb, proc);
			break;

		default:
			Fifo(nb, proc);
			printf("fifo");
		}
	}
	else
	{
		printf("Impossible d'ouvrir le fichier de configuration");
	}
}