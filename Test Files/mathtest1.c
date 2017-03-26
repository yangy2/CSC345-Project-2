#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* getfield(char*line)
{
	int arraysize;
	int columns = 0;

	char* tok;
	for(tok = strtok(line, ","); tok && &tok; tok = strtok(NULL, ",\n"))
	{
	//	printf("%s\n", tok);
		columns++;
	}

	arraysize = columns;
	char* tokenarray[arraysize];
	printf("Array size is %ld\n", sizeof(tokenarray)/sizeof(tokenarray[0]));
/*
	for(tok = strtok(line, ","); tok&& &tok; tok = strtok(NULL, ",\n"))
	{
		tokenarray[x] = tok;
		printf("%s\n", tokenarray[x]);
		x++;
	}

	for(int i = 0; i<arraysize; i++)
		printf("%s\n", tokenarray[i]);
*/
}

int main()
{	
	int rows = 0;

	FILE* stream = fopen("./analcatdata/lawsuit.csv", "r");
	char line[1024];
	while(fgets(line, 1024, stream))
	{
		char* tmp = strdup(line);
		getfield(tmp);
		free(tmp);

		rows++;
	}
	printf("Number of Rows: %d\n", rows);
}

