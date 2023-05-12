#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "functions.h"

int runProg(char *filename);

void main(int argc, char *argv[])
{
	int i = 1;
	int res = 1;
	FILE *errorFile;
	if (argc < 1)
	{
		errorFile = fopen("errorFile.as", "w+");
		fprintf(errorFile, "there are no files\n");
	}
	else
	{
		while(argv[i] != NULL)
		{
			res = runProg(argv[i]);
			if(res == 0)
			{
				printf("there was a problam with the file (%s) , check %s.err for explantion\n",argv[i],argv[i]);
			}
			i++;
		}
	}
	printf("-------------------the program was finshed--------------\n");
}

int runProg(char *filename)
{
	int IC = 100;
	int DC = 0;
	int numOfErr =0;
	int lineNum = 0;
	int temp = 0;/*the temp will tell us if there was any errors in the first or second pass*/
	int numwords;/*will tell us the number of words in total*/
	int numdata;/*will tell us the number of data we inserted */
	int tnw =0;/*stand for total number of words*/
	FILE *errorFile ;
	char tempname[maxVsize];
	FILE *filePointer;
	line_s *headL = NULL;
	datal *headD = NULL;
	label *headS = NULL;
	word *headW = NULL;
	entry *headE = NULL;
	strcpy(tempname , filename);
	filePointer = fopen(filename, "r");
	strtok(tempname,".");
	if(filePointer == NULL)
	{
		printf("there was a problam opening the file \n");
		return 0;
	}
	else
	{
		headL=readtext(&lineNum, filePointer, tempname, &numOfErr ); /*reading the text file and setting it into a list with the needed flag to continue*/
		fclose(filePointer);
		if(numOfErr > 0)
		{
			if(errorFile == NULL)
			{
		
				errorFile = fopen("errorFile.as", "w+");
			}
			fprintf(errorFile, "there was %d number of problams after the first pass", numOfErr);
			numOfErr++;
			return 0;
		}
		else
		{
			temp = firstpass(headL, &headD, &headS, &headW , &headE, tempname, &numOfErr,&IC, &DC);		
			if (temp == 0)
			{
				if(errorFile == NULL)
				{
			
					errorFile = fopen("errorFile.as", "w+");
				}
				fprintf(errorFile, "there was %d number of problams after the first pass\n", numOfErr);
				numOfErr++;
				return 0;
			}
			else /* if temp == 1 */
			{
				temp = secondpass(headL, headD, headS, headW , &numOfErr ,&IC, tempname);
				if (temp == 1)/* that meens we finshed with both pass and there were no errors*/
				{
					numwords = numOFwords(headW);
					numdata = addData(headW, headD);
					tnw = numwords + numdata;
					addentry(headE, headS, filename);
					addextern(headL, headW, filename);
					addBase64(headW, filename, numwords, numdata);
				}
		
			}
		}
	}
	freeLineNode(headL);
	freeLabelNode(headS);
	freeEntryNode(headE);
	freeWordNode(headW,tnw);
	freeDataNode(headD);
	return 1;
}
