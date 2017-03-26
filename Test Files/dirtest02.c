#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Parse the .csv file
const char* getfield(char*line)
{
	char* tok;
	for(tok = strtok(line, ","); tok && &tok; tok = strtok(NULL, ",\n"))
	{
		printf("%s\n", tok);
	}
}

void main(void)
{
	DIR *d;
	struct dirent *dir;
	d = opendir("analcatdata");

	char file[50], dest[50]; //name of file and directory

	if(d)
	{
		while((dir = readdir(d)) != NULL)
		{
			strcpy(file, dir->d_name);
			strcpy(dest, "./analcatdata/");

			//Check if filename is .csv type
			//looks at last letter to see if 'v'
			if(file[strlen(file)-1] == 'v')
			{
				strcat(dest, file); //concatenate filename to directory
				printf("%s\n", dest);

				FILE* stream = fopen(dest, "r"); //open file in directory
				char line[1024];
				while(fgets(line, 1024, stream))
				{
					char* tmp = strdup(line);
					getfield(tmp);
					free(tmp);
				}

			}
		}
		closedir(d);
	}
}
