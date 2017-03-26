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

	//Task 2 Variables
	int filecount = 0;
	char *filearray[84]; //array of file names
	double maxresult[84]; //array of max numbers
	double minresult[84]; //array of min numbers
	double avgresult[84]; //array of average numbers
	double varresult[84]; //array of variance

	double max = 0;
	double min = 0;
	double sum = 0;
	int maxindex = 200000;
	int currentindex = 0;
	double datapoints[maxindex];
	for(int i=0; i<maxindex; i++)
		datapoints[i] = 0;


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
				
				char *ep;

//				FILE* stream = fopen(dest, "r"); //open file in directory
				FILE* stream = fopen("./analcatdata/floridashark.csv", "r");
				char line[1024];
				while(fgets(line, 1024, stream))
				{
					char* tmp = strdup(line);
					int x = 0;
					char* tok;
					int uniqueword = 0;
					for(tok = strtok(tmp, ","); tok && &tok; tok = strtok(NULL, ",\n"))
					{
						double num = strtol(tok, &ep, 10);
						if(tok != ep) //if its not a string
						{
							//find max 
							if(max == 0)
								max = atof(tok);
							else
							{
								if(max < atof(tok))
									max = atof(tok);
							}

							//find min
							if(min == 0)
								min = atof(tok);
							else
							{
								if(min > atof(tok))
									min = atof(tok);
							}
							
							//Record number to calculate variance later
							datapoints[currentindex] = atof(tok);
							currentindex++;

							sum = sum + atof(tok);
							
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
				maxresult[filecount] = max;
				minresult[filecount] = min;
				avgresult[filecount] = sum/(columns*rows);

				for(int i=0; i<currentindex; i++)
				{
					datapoints[i] = (datapoints[i]-avgresult[filecount])*(datapoints[i]-avgresult[filecount]);
					varresult[filecount] = varresult[filecount] + datapoints[i];
				}
				varresult[filecount] = varresult[filecount]/(columns*rows);
printf("%.2f\n", varresult[filecount]);
				filecount++;
				break;
			}
//		printf("%d\n", filecount);
		}


		closedir(d);

		//print();

/*		//Print report to console
		if(outputfile == 0)
		{
			printf("=== T2 completed ===\n");
			printf("=== T2 report start ===\n");
			for(int i = 0; i<84; i++)
			{
				printf("T2 RESULT: File %s: Max = %.2f, Min = %.2f, Avg = %.2f, Var = %.2f\n", filearray[i], maxresult[i], minresult[i], avgresult[i], varresult[i]);
			}
			printf("T2 RESULT: Total elapsed time: %ld seconds\n", time(NULL)-begin);
			printf("=== T2 report end ===\n");
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

			fprintf(output, "=== T2 completed ===\n");
			fprintf(output, "=== T2 report start ===\n");
			for(int i = 0; i<84; i++)
			{
				fflush(output);
				fprintf(output, "T2 RESULT: File %s: Max = %.2f, Min = %.2f, Avg = %.2f, Var = %.2f\n", filearray[i], maxresult[i], minresult[i], avgresult[i], varresult[i]);
				fflush(output);
			}
			fprintf(output, "T2 RESULT: Total elapsed time: %ld seconds\n", time(NULL)-begin);
			fprintf(output, "=== T2 report end ===\n");
			fprintf(output, "\n");

//			position = ftell(output);
//			fclose(output);
		}*/
//		sem_post(&sem); //unlock

	}
}
