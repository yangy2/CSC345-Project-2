#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

int outputfile = 0; /* 0 for console, 1 for .txt file */
sem_t sem; /* lock */
double totaltime = 0; /* execution time for all tasks */
FILE *output;

void print()
{
	sem_wait(&sem); /* lock */
	printf("Printing...\n");
}

void* task1(void* param);
void* task2(void* param);
void* task3(void* param);
void* task4(void* param);

int main(int argc, char** argv)
{
	sem_init(&sem, 0, 1);

	/* Set up threads */
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
	struct sched_param schedparam;

	pthread_t tid1;
	pthread_t tid2;
	pthread_t tid3;
	pthread_t tid4;
	
	if(strcmp(argv[1], "single") == 0)
	{
	//	printf("Hello\n");
		if(atoi(argv[2]) == 1)
		{
			pthread_create(&tid1, 0, task1, NULL);
			pthread_join(tid1, NULL);
		}
		else if(atoi(argv[2]) == 2)
		{
			pthread_create(&tid2, 0, task2, NULL);
			pthread_join(tid2, NULL);
		}
		else if(atoi(argv[2]) == 3)
		{
			pthread_create(&tid3, 0, task3, NULL);
			pthread_join(tid3, NULL);
		}
		else if(atoi(argv[2]) == 4)
		{
			pthread_create(&tid4, 0, task4, NULL);
			pthread_join(tid4, NULL);
		}
		else
			printf("Command not recognized\n");
	}

	else if(strcmp(argv[1], "RR") == 0)
	{
		printf("Do RR algorithm\n");
		pthread_attr_setschedpolicy(&attr, SCHED_RR);
		schedparam.sched_priority = 10;
		pthread_attr_setschedparam(&attr, &schedparam);
		pthread_create(&tid1, &attr, task1, NULL);
		pthread_create(&tid2, &attr, task2, NULL);
		pthread_create(&tid3, &attr, task3, NULL);
		pthread_create(&tid4, &attr, task4, NULL);

		pthread_join(tid1, NULL);
		pthread_join(tid2, NULL);
		pthread_join(tid3, NULL);
		pthread_join(tid4, NULL);

	}
	
	else if(strcmp(argv[1], "FIFO") == 0)
	{
		printf("Do FIFO algorithm\n");
		pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
		schedparam.sched_priority = 10;
		pthread_attr_setschedparam(&attr, &schedparam);
		pthread_create(&tid1, &attr, task1, NULL);
		pthread_create(&tid2, &attr, task2, NULL);
		pthread_create(&tid3, &attr, task3, NULL);
		pthread_create(&tid4, &attr, task4, NULL);
		
		pthread_join(tid1, NULL);
		pthread_join(tid2, NULL);
		pthread_join(tid3, NULL);
		pthread_join(tid4, NULL);
	}


	else if(strcmp(argv[1], "priority") == 0)
	{
		pthread_attr_setschedpolicy(&attr, SCHED_FIFO);

		if(atoi(argv[2]) == 1)
		{
			if(strcmp(argv[3], "low") == 0)
			{
				printf("Task 1 deprioritized\n");

				schedparam.sched_priority = 3;
				pthread_attr_setschedparam(&attr, &schedparam);
				pthread_create(&tid1, &attr, task1, NULL);
			}
			else if(strcmp(argv[3], "high") == 0)
			{
				printf("Task 1 prioritized\n");
				schedparam.sched_priority = 90;
				pthread_attr_setschedparam(&attr, &schedparam);
				pthread_create(&tid1, &attr, task1, NULL);
			}
			schedparam.sched_priority = 50;
			pthread_attr_setschedparam(&attr, &schedparam);

			pthread_create(&tid2, &attr, task2, NULL);
			pthread_create(&tid3, &attr, task3, NULL);
			pthread_create(&tid4, &attr, task4, NULL);
	
			pthread_join(tid1, NULL);
			pthread_join(tid2, NULL);
			pthread_join(tid3, NULL);
			pthread_join(tid4, NULL);
		}
		if(atoi(argv[2]) == 2)
		{
			if(strcmp(argv[3], "low") == 0)
			{
				printf("Task 2 deprioritized\n");
				schedparam.sched_priority = 3;
				pthread_attr_setschedparam(&attr, &schedparam);
				pthread_create(&tid2, &attr, task2, NULL);
			}
			else if(strcmp(argv[3], "high") == 0)
			{
				printf("Task 2 prioritized\n");
				schedparam.sched_priority = 90;
				pthread_attr_setschedparam(&attr, &schedparam);
				pthread_create(&tid2, &attr, task2, NULL);
			}
			schedparam.sched_priority = 50;
			pthread_attr_setschedparam(&attr, &schedparam);

			pthread_create(&tid1, &attr, task1, NULL);
			pthread_create(&tid3, &attr, task3, NULL);
			pthread_create(&tid4, &attr, task4, NULL);
	
			pthread_join(tid1, NULL);
			pthread_join(tid2, NULL);
			pthread_join(tid3, NULL);
			pthread_join(tid4, NULL);
		}
		if(atoi(argv[2]) == 3)
		{
			if(strcmp(argv[3], "low") == 0)
			{
				printf("Task 3 deprioritized\n");
				schedparam.sched_priority = 3;
				pthread_attr_setschedparam(&attr, &schedparam);
				pthread_create(&tid3, &attr, task3, NULL);
			}
			else if(strcmp(argv[3], "high") == 0)
			{
				printf("Task 3 prioritized\n");
				schedparam.sched_priority = 90;
				pthread_attr_setschedparam(&attr, &schedparam);
				pthread_create(&tid3, &attr, task3, NULL);
			}
			schedparam.sched_priority = 50;
			pthread_attr_setschedparam(&attr, &schedparam);

			pthread_create(&tid2, &attr, task2, NULL);
			pthread_create(&tid1, &attr, task1, NULL);
			pthread_create(&tid4, &attr, task4, NULL);
	
			pthread_join(tid1, NULL);
			pthread_join(tid2, NULL);
			pthread_join(tid3, NULL);
			pthread_join(tid4, NULL);
		}
		if(atoi(argv[2]) == 4)
		{
			if(strcmp(argv[3], "low") == 0)
			{
				printf("Task 4 deprioritized\n");
				schedparam.sched_priority = 3;
				pthread_attr_setschedparam(&attr, &schedparam);
				pthread_create(&tid4, &attr, task4, NULL);
			}
			else if(strcmp(argv[3], "high") == 0)
			{
				printf("Task 4 prioritized\n");
				schedparam.sched_priority = 90;
				pthread_attr_setschedparam(&attr, &schedparam);
				pthread_create(&tid4, &attr, task4, NULL);
			}
			schedparam.sched_priority = 50;
			pthread_attr_setschedparam(&attr, &schedparam);

			pthread_create(&tid2, &attr, task2, NULL);
			pthread_create(&tid3, &attr, task3, NULL);
			pthread_create(&tid1, &attr, task1, NULL);
	
			pthread_join(tid1, NULL);
			pthread_join(tid2, NULL);
			pthread_join(tid3, NULL);
			pthread_join(tid4, NULL);
		}
	}

	else if(strcmp(argv[1], "file") == 0)
	{
		outputfile = 1;

		output = fopen("output.txt", "w");
		if (output == NULL)
		{
			printf("Error\n");
			exit(1);
		}

		pthread_create(&tid1, 0, task1, NULL);
		pthread_create(&tid2, 0, task2, NULL);
		pthread_create(&tid3, 0, task3, NULL);
		pthread_create(&tid4, 0, task4, NULL);

		pthread_join(tid1, NULL);
		pthread_join(tid2, NULL);
		pthread_join(tid3, NULL);
		pthread_join(tid4, NULL);

		fprintf(output, "=== All Task Completed ===\n");
		fprintf(output, "=== All Task report start ===\n");
		fprintf(output, "RESULT: Total elapsed time: %.4f seconds\n", totaltime);
		fprintf(output, "=== All Task report end ===\n");
	}
	else
		printf("Error\n");

	if(outputfile == 0)
	{
		printf("=== All Task Completed ===\n");
		printf("=== All Task report start ===\n");
		printf("RESULT: Total elapsed time: %.4f seconds\n", totaltime);
		printf("=== All Task report end ===\n");
	}

	sem_destroy(&sem);

}

void* task1(void* param)
{
	clock_t begin = clock();

	DIR *d;
	struct dirent *dir;
	d = opendir("analcatdata");

	char file[50], dest[50]; /* name of file and directory */

	/* Task 1 Variables */
	int filecount = 0; /* tracks number of files */
	int maxindex = 20000; /* size of array of words */
	char *filearray[84]; /* array of file names */
	int result[84]; /* array of unique words */
	char *words[maxindex]; /* array of words */
	int windex = 0; /* index for array of words */
	
	for(int i = 0; i<maxindex; i++)
		words[i] = ","; /* fill array with dummy values */

	if(d)
	{
		while((dir = readdir(d)) != NULL)
		{
			strcpy(file, dir->d_name);
			strcpy(dest, "./analcatdata/"); /* directory name files saved in */

			/* Check if filename is .csv type
			   looks at last letter to see if 'v' */
			if(file[strlen(file)-1] == 'v')
			{
				strcat(dest, file); /* concatenate filename to directory */
//				printf("%s\n", file);
				filearray[filecount] = dir->d_name;
//				printf("%s\n", filearray[filecount]);
				
				int rows = 0;
				int columns = 0;
				
				char *ep; /* pointer for type conversions */

				FILE* stream = fopen(dest, "r"); /* open file in directory */
//				FILE* stream = fopen("./analcatdata/anscombe.csv", "r");
				char line[1024];
				while(fgets(line, 1024, stream))
				{
					char* tmp = strdup(line);
					int x = 0; /* a counter */
					char* tok;
					int uniqueword = 0;
					for(tok = strtok(tmp, ","); tok && &tok; tok = strtok(NULL, ",\n"))
					{
						double num = strtol(tok, &ep, 10);
						if(tok == ep)
						{
						//	printf("String\n");
							words[windex] = tok; /* store strings in array */
							windex++;
						}
						int isunique = 1;
						x++;
						for(int outer = 1; outer < windex; outer++)
						{
							
							for(int inner = 0; isunique && inner < outer; inner++)
							{
								if(words[inner] == words[outer])
								{
									//printf("%s\n", words[inner]);
									isunique = 0; /* duplicate word found */
								}
							}
							if(isunique)
								uniqueword++;
						}
					//	printf("%s\n", tok);
							
					}
					free(tmp);
					if(columns == 0)
						columns = x;	
					rows++; /* count lines in stream */

					result[filecount] = uniqueword/4;
				}
//				printf("%d, %d\n", rows, columns);
//				printf("Number of data points: %d\n", columns*rows);
				

				
//				uniqueword = 0;
				filecount++;
//				break;
			}
//		printf("%d\n", filecount);
		}


		closedir(d);

		print();

		/* Print report to console */
		if(outputfile == 0)
		{
			printf("=== T1 completed ===\n");
			printf("=== T1 report start ===\n");
			for(int i = 0; i<84; i++)
			{
				printf("T1 RESULT: File %s: Total number of unique words = %d\n", filearray[i], result[i]);
			}
			printf("T1 RESULT: Total elapsed time: %.4f seconds\n", (double)(clock()-begin)/CLOCKS_PER_SEC);
			totaltime = totaltime + (double)(clock()-begin)/CLOCKS_PER_SEC;
			printf("=== T1 report end ===\n");
		}

		/* Print report to .txt file */
		if(outputfile == 1)
		{

			fprintf(output, "=== T1 completed ===\n");
			fprintf(output, "=== T1 report start ===\n");
			for(int i = 0; i<84; i++)
			{
				fprintf(output, "T1 RESULT: File %s: Total number of unique words = %d%%\n", filearray[i], result[i]);
			}
			fprintf(output, "T1 RESULT: Total elapsed time: %.4f seconds\n", (double)(clock()-begin)/CLOCKS_PER_SEC);
			totaltime = totaltime + (double)(clock()-begin)/CLOCKS_PER_SEC;
			fprintf(output, "=== T1 report end ===\n");
			fprintf(output, "\n");
		}
		sem_post(&sem); /* unlock */

	}
}

void* task2(void* param)
{
	clock_t begin = clock();

	DIR *d;
	struct dirent *dir;
	d = opendir("analcatdata");

	char file[50], dest[50]; /* name of file and directory */

	/* Task 2 Variables */
	int filecount = 0; /* track number of files */
	char *filearray[84]; /* array of file names */
	double maxresult[84]; /* array of max numbers */
	double minresult[84]; /* array of min numbers */
	double avgresult[84]; /* array of average numbers */
	double varresult[84]; /* array of variance */
	int maxindex = 200000;
	double datapoints[maxindex];


	if(d)
	{
		while((dir = readdir(d)) != NULL)
		{
			strcpy(file, dir->d_name);
			strcpy(dest, "./analcatdata/"); /* directory name files saved in */

			/* Check if filename is .csv type
			   looks at last letter to see if 'v' */
			if(file[strlen(file)-1] == 'v')
			{
				strcat(dest, file); /* concatenate filename to directory */
//				printf("%s\n", file);
				filearray[filecount] = dir->d_name;
//				printf("%s\n", filearray[filecount]);
				
				int rows = 0;
				int columns = 0;
				double max = 0;
				double min = 0;
				double sum = 0;
				int currentindex = 0;
				for(int i=0; i<maxindex; i++)
					datapoints[i] = 0;
				
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
						if(tok != ep) /* if its not a string */
						{
							/* find max */
							if(max == 0)
								max = atof(tok);
							else
							{
								if(max < atof(tok))
									max = atof(tok);
							}

							/* find min */
							if(min == 0)
								min = atof(tok);
							else
							{
								if(min > atof(tok))
									min = atof(tok);
							}
							
							/* Record number to calculate variance later */
							datapoints[currentindex] = atof(tok);
							currentindex++;

							sum = sum + atof(tok);
							
						}
						x++;
							
					}
					free(tmp);
					if(columns == 0)
						columns = x;	
					rows++; /* count lines in stream */

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
				
//				uniqueword = 0;
				filecount++;
//				break;
			}
//		printf("%d\n", filecount);
		}


		closedir(d);

		print();

		/* Print report to console */
		if(outputfile == 0)
		{
			printf("=== T2 completed ===\n");
			printf("=== T2 report start ===\n");
			for(int i = 0; i<84; i++)
			{
				printf("T2 RESULT: File %s: Max = %.2f, Min = %.2f, Avg = %.2f, Var = %.2f\n", filearray[i], maxresult[i], minresult[i], avgresult[i], varresult[i]);
			}
			printf("T2 RESULT: Total elapsed time: %.4f seconds\n", (double)(clock()-begin)/CLOCKS_PER_SEC);
			totaltime = totaltime + (double)(clock()-begin)/CLOCKS_PER_SEC;
			printf("=== T2 report end ===\n");
		}

		/* Print report to .txt file */
		if(outputfile == 1)
		{


			fprintf(output, "=== T2 completed ===\n");
			fprintf(output, "=== T2 report start ===\n");
			for(int i = 0; i<84; i++)
			{
				fprintf(output, "T2 RESULT: File %s: Max = %.2f, Min = %.2f, Avg = %.2f, Var = %.2f\n", filearray[i], maxresult[i], minresult[i], avgresult[i], varresult[i]);
			}
			fprintf(output, "T2 RESULT: Total elapsed time: %.4f seconds\n", (double)(clock()-begin)/CLOCKS_PER_SEC);
			totaltime = totaltime + (double)(clock()-begin)/CLOCKS_PER_SEC;
			fprintf(output, "=== T2 report end ===\n");
			fprintf(output, "\n");
		}
		sem_post(&sem); /* unlock */

	}
}

void* task3(void* param)
{
	clock_t begin = clock();
	
	DIR *d;
	struct dirent *dir;
	d = opendir("analcatdata");

	char file[50], dest[50]; /* name of file and directory */

	/* Task 3 Variables */
	int r_min = 0;
	int r_max = 0;
	double r_total = 0;
	int c_min = 0;
	int c_max = 0; 
	double c_total = 0;
	int filecount = 0;

	if(d)
	{
		while((dir = readdir(d)) != NULL)
		{
			strcpy(file, dir->d_name);
			strcpy(dest, "./analcatdata/"); /* directory name files saved in */

			/* Check if filename is .csv type
			   looks at last letter to see if 'v' */
			if(file[strlen(file)-1] == 'v')
			{
				strcat(dest, file); /* concatenate filename to directory */
//				printf("%s\n", dest);
			
				int rows = 0;
				int columns = 0;

				FILE* stream = fopen(dest, "r"); /* open file in directory */
				char line[1024];
				while(fgets(line, 1024, stream))
				{
					char* tmp = strdup(line);
					int x = 0;
					char* tok;
					for(tok = strtok(tmp, ","); tok && &tok; tok = strtok(NULL, ",\n"))
					{
						x++; /* count columns in line */
					}
					free(tmp);
					if(columns == 0)
						columns = x;	
					rows++; /* count lines in stream */
				}
	
//				printf("Number of Rows: %d\n", rows);
//				printf("Number of Columns: %d\n", columns);

				/* Find min # of rows */
				if(r_min == 0)
					r_min = rows;
				else
				{
					if(r_min > rows)
						r_min = rows;
				}

				/* Find max # of rows */
				if(r_max == 0)
					r_max = rows;
				else
				{
					if(r_max < rows)
						r_max = rows;
				}

				/* Find min # of columns */
				if(c_min == 0)
					c_min = columns;
				else
				{
					if(c_min > columns)
						c_min = columns;
				}

				/* Find max # of columns */
				if(c_max == 0)
					c_max = columns;
				else
				{
					if(c_max < columns)
						c_max = columns;
				}

				/* Find avg # of rows/columns */
				r_total = r_total + rows;
				c_total = c_total + columns;
				filecount++;
				
			}
		}

		closedir(d);

		print();

		/* Print report to console */
		if(outputfile == 0)
		{
			printf("=== T3 completed ===\n");
			printf("=== T3 report start ===\n");
			printf("T3 RESULT: Rows: Max = %d, Min = %d, Avg = %.2f\n", r_max, r_min, r_total/filecount);
			printf("T3 RESULT: Cols: Max = %d, Min = %d, Avg = %.2f\n", c_max, c_min, c_total/filecount);
			printf("T3 RESULT: Total elapsed time: %.4f seconds\n", (double)(clock()-begin)/CLOCKS_PER_SEC);
			totaltime = totaltime + (double)(clock()-begin)/CLOCKS_PER_SEC;
			printf("=== T3 report end ===\n");
			printf("\n");
		}

		/* Print report to .txt file */
		if(outputfile == 1)
		{


			fprintf(output, "=== T3 completed ===\n");
			fprintf(output, "=== T3 report start ===\n");
			fprintf(output, "T3 RESULT: Rows: Max = %d, Min = %d, Avg = %.2f\n", r_max, r_min, r_total/filecount);
			fprintf(output, "T3 RESULT: Cols: Max = %d, Min = %d, Avg = %.2f\n", c_max, c_min, c_total/filecount);
			fprintf(output, "T3 RESULT: Total elapsed time: %.4f seconds\n", (double)(clock()-begin)/CLOCKS_PER_SEC);
			totaltime = totaltime + (double)(clock()-begin)/CLOCKS_PER_SEC;
			fprintf(output, "=== T3 report end ===\n");
			fprintf(output, "\n");
		}
		sem_post(&sem); /* unlock */
	}
}

void* task4(void* param)
{
	clock_t begin = clock();

	DIR *d;
	struct dirent *dir;
	d = opendir("analcatdata");

	char file[50], dest[50]; /* name of file and directory */

	/* Task 4 Variables */
	int filecount = 0;
	char *filearray[84];
	double result[84];
	
	if(d)
	{
		while((dir = readdir(d)) != NULL)
		{
			strcpy(file, dir->d_name);
			strcpy(dest, "./analcatdata/"); /* directory name files saved in */

			/* Check if filename is .csv type
			   looks at last letter to see if 'v' */
			if(file[strlen(file)-1] == 'v')
			{
				strcat(dest, file); /* concatenate filename to directory */
//				printf("%s\n", file);
				filearray[filecount] = dir->d_name;
//				printf("%s\n", filearray[filecount]);
				
				int rows = 0;
				int columns = 0;
				int nonzero = 0;
				char *ep;

				FILE* stream = fopen(dest, "r"); /* open file in directory */
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
							/* check if it is a decimal of zeroes */
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
					rows++; /* count lines in stream */
				}
//				printf("%d, %d\n", rows, columns);
//				printf("Number of zeroes: %d\n", columns*rows-nonzero);
//				printf("Number of data points: %d\n", columns*rows);
//				printf("zeroes: %d\n", 100*(columns*rows-nonzero)/(columns*rows));
				result[filecount] = ((double)(100*(columns*rows-nonzero))/(double)(columns*rows));

				filecount++;
//				break;
			}
//		printf("%d\n", filecount);
		}

		closedir(d);

		print();

		/* Print report to console */
		if(outputfile == 0)
		{
			printf("=== T4 completed ===\n");
			printf("=== T4 report start ===\n");
			for(int i = 0; i<84; i++)
			{
				printf("T4 RESULT: File %s: Ratio = %.2f%%\n", filearray[i], result[i]);
			}
			printf("T4 RESULT: Total elapsed time: %.4f seconds\n", (double)(clock()-begin)/CLOCKS_PER_SEC);
			totaltime = totaltime + (double)(clock()-begin)/CLOCKS_PER_SEC;
			printf("=== T4 report end ===\n");
			printf("\n");
		}

		/* Print report to .txt file */
		if(outputfile == 1)
		{

			fprintf(output, "=== T4 completed ===\n");
			fprintf(output, "=== T4 report start ===\n");
			for(int i = 0; i<84; i++)
			{
				fprintf(output, "T4 RESULT: File %s: Ratio = %.2f%%\n", filearray[i], result[i]);
			}
			fprintf(output, "T4 RESULT: Total elapsed time: %.4f seconds\n", (double)(clock()-begin)/CLOCKS_PER_SEC);
			totaltime = totaltime + (double)(clock()-begin)/CLOCKS_PER_SEC;
			fprintf(output, "=== T4 report end ===\n");
			fprintf(output, "\n");
		}
		sem_post(&sem); /* unlock */
	}
}


