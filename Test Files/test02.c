#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** argv[1000];
int x = 0;
const char* getfield(char*line)
{
	char* tok;
	for(tok = strtok(line, ","); tok && &tok; tok = strtok(NULL, ",\n"))
	{
		printf("%s\n", tok);
	}
}

int main()
{	
	FILE* stream = fopen("./analcatdata/lawsuit.csv", "r");
	char line[1024];
	while(fgets(line, 1024, stream))
	{
		char* tmp = strdup(line);
		getfield(tmp);
		free(tmp);
	}

}

