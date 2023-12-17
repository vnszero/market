#include "fileHandler.h"
#include <stdio.h>

int save(char filePath[], char text[]) {
	FILE* f = fopen(filePath, "a");
	if (f == NULL) {
		printf("Erro ao abrir arquivo!");
		return 0;
	}	
	fprintf(f, "%s", text);
	fclose(f);
	return 1;
}

int clear(char filePath[]) {
	return (!remove(filePath) == 0);
}