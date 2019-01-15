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



	//initiallize the size read every time
	int readSize=10000;
	int flag=1;
	char compare[readSize]; //store stream to buffer

	while((readSize=fread(compare,1,readSize,inputFile))>=cellSize){

		for (int i = 0; i+cellSize<=readSize; ++i)
		{
			/* code */
			if (compare[i]==pattern[0])
			{
				flag=1;
				for (int j = 0; j < cellSize; ++j)
				{
					if (compare[i+j]!=pattern[j])
					{
						flag=0;
						break;
					}
				}

				if(flag){
					count++;
				}
				
			}
		}
		fseek(inputFile,1-cellSize,SEEK_CUR);

	}


	fseek(inputFile, 0, SEEK_END);
	size=(long)ftell(inputFile);

	printf ("Size of file is %ld\n", size);
	printf ("Number of matches = %d\n", count);
	


	// write to file
	// fseek(outputFile, 0, SEEK_SET);
	fprintf(outputFile, "Size of file is %ld\n", size);
	fprintf(outputFile, "Number of matches = %d\n", count);




	fclose(inputFile);
	fclose(outputFile);


	return 0;

	
}
