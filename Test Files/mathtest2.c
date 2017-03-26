#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{	
	int rows = 0; 
	int columns = 0;

	FILE* stream = fopen("./analcatdata/AIDS.csv", "r");
	char line[1024];
	while(fgets(line, 1024, stream))
	{
		char* tmp = strdup(line);
		int x = 0;
		char* tok;
		for(tok = strtok(tmp, ","); tok && &tok; tok = strtok(NULL, ",\n"))
		{
			x++; //count columns in line
		}
		free(tmp);
		columns = x;
		rows++; //count lines in stream
	}
	
	printf("Number of Rows: %d\n", rows);
	printf("Number of Columns: %d\n", columns);
}

