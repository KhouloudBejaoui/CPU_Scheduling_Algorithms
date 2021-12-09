#ifndef PROCESSUS_DOT_H    
#define PROCESSUS_DOT_H    

	typedef struct process
	{
		int idProcessus;
		int Ta;
		int Te;
		int Pr;
		int temAttente;
		int temfin;
		int temdeb;
        int termine;
	} process;

int Nombre_processus(char *algo){
	char c;
	int nb = 0; //nbre de processus dans le fichier 
	FILE *fichier = NULL;
	char path[50] ="../../";
	strcat(path,algo);
	fichier = fopen(path, "r+");

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
	}
  else
	{
		printf("Impossible d'ouvrir le fichier de configuration");
	}
	return nb;
}


void extraction(process **proc,char *algo){
	int i = 0;
	char c;
	int nb = Nombre_processus(algo); //nbre de processus dans le fichier 
	FILE *fichier = NULL;
	char path[50] ="../../";
	strcat(path,algo);
	fichier = fopen(path, "r+");
	*proc = (process *)malloc(sizeof(process) * nb); //tab dynamique

	if (fichier != NULL)
	{

		do
		{
			c = fgetc(fichier);
			if (c == 'p')
			{
				fscanf(fichier, "%d %d %d  %d", &(*(*proc+i)).idProcessus, &(*(*proc+i)).Ta, &(*(*proc+i)).Te, &(*(*proc+i)).Pr); //lire les 				données à partir du fichier conf
				i++;
			}

		} while (fgetc(fichier) != EOF);
	}
}	

int main(int argc, char *argv[]);

#endif 
