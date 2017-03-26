#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int outputfile = 0;

void main(void)
{
	time_t begin = time(NULL);

	DIR *d;
	struct dirent *dir;
	d = opendir("analcatdata");

	char file[50], dest[50]; //name of file and directory

	//Task 1 Variables
	int filecount = 0;
	int maxindex = 20000; //size of array of words
	char *filearray[84]; //array of file names
	int result[84]; //array of unique words
	char *words[maxindex]; //array of words
	int windex = 0; //index for array of words
	
	for(int i = 0; i<maxindex; i++)
		words[i] = ","; //fill array with dummy values

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
				printf("%s\n", filearray[filecount]);
				
				int rows = 0;
				int columns = 0;
				int uniqueword = 0;
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
							words[windex] = tok; //store strings in array
							windex++;
						}

						x++;
					//	printf("%s\n", tok);
						
					}
					free(tmp);
					if(columns == 0)
						columns = x;	
					rows++; //count lines in stream
				}
//				printf("%d, %d\n", rows, columns);
//				printf("Number of data points: %d\n", columns*rows);
				
				for(int outer = 1; outer < maxindex; outer++)
				{
					int isunique = 1;
					for(int inner = 0; isunique && inner < outer; inner++)
					{
						if(words[inner] == words[outer])
								isunique = 0; //duplicate word found
					}
					if(isunique)
						uniqueword++;
				}
				result[filecount] = uniqueword;
//				uniqueword = 0;
				filecount++;
//				break;
			}
//		printf("%d\n", filecount);
		}


		closedir(d);

		//print();

		//Print report to console
		if(outputfile == 0)
		{
			printf("=== T1 completed ===\n");
			printf("=== T1 report start ===\n");
			for(int i = 0; i<84; i++)
			{
				printf("T1 RESULT: File %s: Total number of unique words = %d\n", filearray[i], result[i]);
			}
			printf("T1 RESULT: Total elapsed time: %ld seconds\n", time(NULL)-begin);
			printf("=== T1 report end ===\n");
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
			fflush(output);
//			fseek(output, position, 0);

			fprintf(output, "=== T1 completed ===\n");
			fprintf(output, "=== T1 report start ===\n");
			for(int i = 0; i<84; i++)
			{
				fflush(output);
				fprintf(output, "T1 RESULT: File %s: Total number of unique words = %d%%\n", filearray[i], result[i]);
				fflush(output);
			}
			fprintf(output, "T1 RESULT: Total elapsed time: %ld seconds\n", time(NULL)-begin);
			fprintf(output, "=== T1 report end ===\n");
			fprintf(output, "\n");

//			position = ftell(output);
//			fclose(output);
		}
//		sem_post(&sem); //unlock

	}
}
