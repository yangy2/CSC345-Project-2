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

	//Task 3 Variables
	int r_min = 0;
	int r_max = 0;
	int r_total = 0;
	int c_min = 0;
	int c_max = 0; 
	int c_total = 0;
	int filecount = 0;

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
//				printf("%s\n", dest);
			
				int rows = 0;
				int columns = 0;

				FILE* stream = fopen(dest, "r"); //open file in directory
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
					if(columns == 0)
						columns = x;	
					rows++; //count lines in stream
				}
	
//				printf("Number of Rows: %d\n", rows);
//				printf("Number of Columns: %d\n", columns);

				//Find min # of rows
				if(r_min == 0)
					r_min = rows;
				else
				{
					if(r_min > rows)
						r_min = rows;
				}

				//Find max # of rows
				if(r_max == 0)
					r_max = rows;
				else
				{
					if(r_max < rows)
						r_max = rows;
				}

				//Find min # of columns
				if(c_min == 0)
					c_min = columns;
				else
				{
					if(c_min > columns)
						c_min = columns;
				}

				//Find max # of columns
				if(c_max == 0)
					c_max = columns;
				else
				{
					if(c_max < columns)
						c_max = columns;
				}

				//Find avg # of rows/columns
				r_total = r_total + rows;
				c_total = c_total + columns;
				filecount++;
				
			}
		}

		closedir(d);

		//Print report to console
		if(outputfile == 0)
		{
			printf("=== T3 completed ===\n");
			printf("=== T3 report start ===\n");
			printf("T3 RESULT: Rows: Max = %d, Min = %d, Avg = %d\n", r_max, r_min, r_total/filecount);
			printf("T3 RESULT: Cols: Max = %d, Min = %d, Avg = %d\n", c_max, c_min, c_total/filecount);
			printf("T3 RESULT: Total elapsed time: %ld seconds\n", time(NULL)-begin);
			printf("=== T3 report end ===\n");
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

			fprintf(output, "=== T3 completed ===\n");
			fprintf(output, "=== T3 report start ===\n");
			fprintf(output, "T3 RESULT: Rows: Max = %d, Min = %d, Avg = %d\n", r_max, r_min, r_total/filecount);
			fprintf(output, "T3 RESULT: Cols: Max = %d, Min = %d, Avg = %d\n", c_max, c_min, c_total/filecount);
			fprintf(output, "T3 RESULT: Total elapsed time: %ld seconds\n", time(NULL)-begin);
			fprintf(output, "=== T3 report end ===\n");
		}
	}
}
