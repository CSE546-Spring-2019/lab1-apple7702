#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
	// check the input arguments
	if (argc!=4)
	{
		printf ("Please fill in input name, pattern and output name\n");
		exit(1);
	}


	FILE *inputFile=NULL;
	FILE *outputFile=NULL;
	char *pattern=argv[2];
	long size=0;
	int count=0;

	
	
	// try to open input file, exit if fail
	if ((inputFile=fopen(argv[1],"rb"))==NULL)
	{
		printf("Fail to open input file.\n");
		exit(1);
	}



	// try to open input file, exit if fail
	if ((outputFile=fopen(argv[3],"wb+"))==NULL)
	{
		printf("Fail to open output file.\n");
		exit(1);
	}



	// read and count the input file
	fseek(inputFile,0,SEEK_SET);  //move to beginning of file
	int cellSize=strlen(pattern);   //get the length of pattern


	int flag=1;  //to record if two string match
	char compare[cellSize];
	// printf ("%s\n", pattern);

	// read same size as pattern every time until reach the end
	while(fread(compare, sizeof(char), cellSize, inputFile)==cellSize){
		// printf ("%s\n", compare);

		flag=1;
		for (int i = 0; i < cellSize; ++i)
		{
			if (compare[i]!=pattern[i])
			{
				flag=0;
				break;
			}
		}

		if(flag){
			count++;
		}
		
		// set start to next char
		fseek(inputFile,-(cellSize-1)*sizeof(char),SEEK_CUR);
	}

	fseek(inputFile, 0, SEEK_END);
	size=ftell(inputFile);

	printf ("Size of file is %ld\n", size);
	printf ("Number of matches = %d\n", count);
	


	// write to file
	fseek(outputFile, 0, SEEK_SET);
	fprintf(outputFile, "Size of file is %ld\n", size);
	fprintf(outputFile, "Number of matches = %d\n", count);




	fclose(inputFile);
	fclose(outputFile);


	return 0;

	
}