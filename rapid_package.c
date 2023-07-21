
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>


#ifndef MAX 
	#define MAX 300
	typedef struct var{
		char 
			first_dir[MAX],
			package_dir[MAX],
			file[MAX];
	}MyVar;
#else
	#error
#endif


int main(int argc, char *argv[]){
	setlocale(LC_CTYPE, " ");
	time_t tempo;
	time(&tempo);

	MyVar 
		content 	= {.first_dir = "", .package_dir = ""},
		content2 	= {.file = ""};


	printf("inserire nome directory principale: ");
	fgets(content.first_dir, MAX, stdin); // carattere finale \n

	content.first_dir[strcspn(content.first_dir, "\n")] = '\0'; // tolgo il \n causato dall'fgets

	//directory main
	if(mkdir(content.first_dir, 0777) == -1){
		perror("Errore nella creazione della directory main ):\n");
		return EXIT_FAILURE;
	}

	//changelog.txt
	strcat(content.file, content.first_dir);

	FILE *changelog = fopen(strcat(content.file, "/changelog.txt"), "w");
	if(changelog == NULL){
		perror("errore nell'apertura file changelog");
		return EXIT_SUCCESS;
	}
	fprintf(changelog, "#changelog\n\n");
	fprintf(changelog, "##versione [1.0.1] - %s\n\n", ctime(&tempo)); // tempo locale
	fprintf(changelog, "###added\n\n");
	fprintf(changelog, "-");
	fclose(changelog);
	printf("creazione del file changelog: successo\n");

	//README.MD
	strcat(content2.file, content.first_dir);

	FILE *readme = fopen(strcat(content2.file, "/README.md"), "w");
	if(readme == NULL){
		perror("errore nella creazione del README.md");
		return EXIT_FAILURE;
	}
	fprintf(readme, "# TITOLO\n\n");
	fprintf(readme, "## Descrizione\n\n");
	fprintf(readme, "## Errori del programma\n\n");
	fprintf(readme, "##Requisiti\n\n");
	fprintf(readme, "##Esecuzione\n\n");
	fprintf(readme, "##Tags\n\n");
	fprintf(readme, "#Author\n\n");
	fclose(readme);
	printf("creazione del file README.md: successo\n");

	//package
	strcat(content.package_dir, content.first_dir);
	strcat(content.package_dir, "/package");
	if(mkdir(content.package_dir, 0777) == -1){
		perror("errore nella creazione della cartella package");
		return EXIT_FAILURE;
	}
	printf("creazione della cartella package: successo\n");

	// FILE PYTHON
	strcat(content.package_dir, "/main.py");
	FILE *python = fopen(content.package_dir, "w");
	if(python == NULL){
		perror("errore nell'apertura file python");
		return EXIT_FAILURE;
	}
	fprintf(python, "import sys\nimport os\nimport time\nimport math\n\n"); // libreria standard python
	fprintf(python, "''' INTESTAZIONE \n consegna:\n\n\nauthor: <name>\ndata: %s'''", ctime(&tempo));
	fprintf(python, "\nif __name__ == '__main__':\n"); // FUNZIONE MAIN DEL FILE PYTHON
	fprintf(python, "\tprint('hello world')");
	fclose(python);
	
	printf("creazione del file main.py: successo\n");
	
	printf("\n\n|__fine programma__|\n");
	return EXIT_SUCCESS;
}

