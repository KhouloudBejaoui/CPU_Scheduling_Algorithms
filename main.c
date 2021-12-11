#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include "./politiques/src/processus.h"

int main(int argc, char *argv[])
{
	struct dirent *dir;
	DIR *d = opendir("./politiques/build");

	//liste dynamique
	char **tab = NULL;
	int k = 0;
	int i = 1;
	tab = malloc(10 * sizeof(char *));

	if (d)
	{
    printf("\t+-----------------------+\n");
    printf("\t|\t  Menu\t\t|\n");
    printf("\t+-----------------------+\n");
	printf("\t|\t\t\t|\n");
		while ((dir = readdir(d)) != NULL)
		{
			if (strstr(dir->d_name, ".") == NULL)
			{
				printf("\t\t%d", i);
				printf("-%s\n", dir->d_name);
				i++;
				tab[k] = dir->d_name;
				k++;
				printf("\t|\t\t\t|\n");
			}
		}
		closedir(d);
    printf("\t+-----------------------+\n");
	}

	//choisir à partir du clavier
	int cl;
	printf("\n");
	printf("   Choisir une politique : ");
	scanf("%d", &cl);

	const char *path = "./politiques/build/";
	char commande[100];
	strcpy(commande, path);

	if ((cl >= 1) && (cl <= k))
	{
		strcat(commande, tab[cl - 1]);
	}
	else
	{
		strcat(commande, tab[0]);
	}

	strcat(commande, " ");
	strcat(commande, argv[1]);
	system(commande);
}
