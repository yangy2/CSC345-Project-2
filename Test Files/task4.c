#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int outputfile = 1;

void main(void)
{
	time_t begin = time(NULL);

	DIR *d;
	struct dirent *dir;
	d = opendir("analcatdata");

	char file[50], dest[50]; //name of file and directory

	//Task 4 Variables
	int filecount = 0;
	char *filearray[84];
	int result[84];
	
	if(d)
	{
		while((dir = readdir(d)) != NULL)
		{
			strcpy(file, dir->d_name);
			strcpy(dest, "./analcatdata/"); //directory name files saved in

			//Check if filename is .csv type
			//looks at last letter to see if 'v'
			if(file[strlen(file)-1] == 'v')
			{
				strcat(dest, file); //concatenate filename to directory
//				printf("%s\n", file);
				filearray[filecount] = dir->d_name;
//				printf("%s\n", filearray[filecount]);
				
				int rows = 0;
				int columns = 0;
				int nonzero = 0;
				char *ep;

				FILE* stream = fopen(dest, "r"); //open file in directory
//				FILE* stream = fopen("./analcatdata/anscombe.csv", "r");
				char line[1024];
				while(fgets(line, 1024, stream))
				{
					char* tmp = strdup(line);
					int x = 0;
					char* tok;
					for(tok = strtok(tmp, ","); tok && &tok; tok = strtok(NULL, ",\n"))
					{
						double num = strtol(tok, &ep, 10);
						if(tok == ep)
						{
						//	printf("String\n");
							nonzero++;
						}
						else if(num != 0)
						{
						//	printf("Non-zero number\n");
							nonzero++;
						}
						else if(tok[1] == '.')
						{
							int j = 0;
							int notzero = 0;
							//check if it is a decimal of zeroes
							while(j<strlen(tok))
							{
								if(tok[j] != 0 || tok[j] != '.')
								{	
								//	printf("%s\n", tok);
									notzero = 1;
								}
								j++;
							}
							if(notzero = 1)
								nonzero++;
						}

						x++;
						//printf("%s\n", tok);
						
					}
					free(tmp);
					if(columns == 0)
						columns = x;	
					rows++; //count lines in stream
				}
//				printf("%d, %d\n", rows, columns);
//				printf("Number of zeroes: %d\n", columns*rows-nonzero);
//				printf("Number of data points: %d\n", columns*rows);
//				printf("zeroes: %d\n", 100*(columns*rows-nonzero)/(columns*rows));
				result[filecount] = (100*(columns*rows-nonzero)/(columns*rows));

				filecount++;
//				break;
			}
//		printf("%d\n", filecount);
		}

		closedir(d);

		//Print report to console
		if(outputfile == 0)
		{
			printf("=== T4 completed ===\n");
			printf("=== T4 report start ===\n");
			for(int i = 0; i<84; i++)
			{
				printf("T4 RESULT: File %s: Ratio = %d%%\n", filearray[i], result[i]);
			}
			printf("T4 RESULT: Total elapsed time: %ld seconds\n", time(NULL)-begin);
			printf("=== T4 report end ===\n");
		}

		//Print report to .txt file
		if(outputfile == 1)
		{
			FILE *output = fopen("output.txt", "w");
			if (output == NULL)
			{
				printf("Error\n");
				exit(1);
			}

			fprintf(output, "=== T4 completed ===\n");
			fprintf(output, "=== T4 report start ===\n");
			for(int i = 0; i<84; i++)
			{
				fprintf(output, "T4 RESULT: File %s: Ratio = %d%%\n", filearray[i], result[i]);
			}
			fprintf(output, "T4 RESULT: Total elapsed time: %ld seconds\n", time(NULL)-begin);
			fprintf(output, "=== T4 report end ===\n");
		}
	}
}
