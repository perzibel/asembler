#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "functions.h"




line_s *readtext(int *numLine, FILE *filePointer,char *filename, int *numOfErr)
{	
	line_s *head = NULL;
	line_s *current = head;
	line_s *next;
	char nextc;
	int lineIndex = 0;
	char com[maxLineSize];//for command
	char label[maxLabelSize + 3];
	int temp;
	char ins[8];
	FILE *errorFile;
	char tempname[maxVsize];
	int lineNum = 0;
	int i = 0;
	int test=0;
	int e =0;
	strcpy(tempname ,filename);
	strcat(tempname ,".err");
	enum opcom
	{
		start,
		comment,
		read,
		reset
	};
	
	int scr = start;//start,comment,read
	nextc = getc(filePointer);	
	while (nextc != EOF)
	{
		lineIndex = 0;
		blankLine = 0;
		temp = 0;
		i = 0;
		switch (scr)
		{	
			
			case start:
			{
				
				insFlag = 0;
				
				if (nextc == ';')
				{
					scr = comment;

				}
				else if (isspace(nextc))//do nothing if space
				{
					nextc = getc(filePointer);
				}
				else
				{
					
					scr = read;
					
				
				}
				break;
			
			
			}
			case read:
			{
				
				while (nextc != '\n')
				{
					
					if (nextc == ':')
					{
						strcpy(label , com);
						label[lineIndex] = '\0';
						lineIndex = 0;
						temp = strsize(label);
						if (temp > maxLabelSize)
						{
							if(errorFile == NULL)
							{
								errorFile = fopen(tempname, "w+");
							}
							fprintf(errorFile, "there was %d number of problams in read text", *numOfErr);
							*numOfErr++;
						}
						else
						{
							labFlag = Yflag;

						}
						strcpy(com, "");//so we could saperate the label name from the line
						nextc = getc(filePointer);
						if(isspace(nextc))
						{
							while (isspace(nextc))
							{
								nextc = getc(filePointer);
							}
						}
					}
					else if (nextc == '.')
					{
						nextc = getc(filePointer);
						while (!isspace(nextc))
						{
							
							ins[i] = nextc;
							nextc = getc(filePointer);
							i++;
						}
						ins[i] = '\0';
						insFlag = checkins(ins);
						
						if (insFlag == Z)
						{
							if(errorFile == NULL)
							{
								errorFile = fopen(tempname, "w+");
							}
							fprintf(errorFile, "there was %d number of problams in readtext", *numOfErr);
							*numOfErr++;
						}
						if(isspace(nextc))
						{
							while (isspace(nextc))
							{
								nextc = getc(filePointer);
							}
						}
					
					}
					else
					{
						
						com[lineIndex] = nextc;
						lineIndex++;
						nextc = getc(filePointer);				
					}
					
					
					
				}
				if(isNspace(nextc))
				{
					while (isNspace(nextc))
					{
						nextc = getc(filePointer);
						
					}
				}
				com[lineIndex ] = '\0';
				scr = reset;
				break;
			}
			case comment:
			{
				
				while ((nextc = getc(filePointer))!= '\n')
				{

				}
				scr = reset;
				blankLine = yBlank;
				break;
			
			}
			case reset:
			{
				
				if(head == NULL)
				{
					head= malloc(sizeof(line_s));
					head->lineNum = lineNum;
					if (insFlag != Z)
					{
						head->dsex = (char*)malloc(strlen(ins) + 1);
						strcpy(head->dsex , ins);
						head->insFlag = insFlag;
					
			
					}
					head->line = (char*)malloc(strlen(com) + 1);
					strcpy(head->line , com);
					if (labFlag == Yflag)
					{
			
						head->labFlag = labFlag;
						head->labName = (char*)malloc(strlen(label) + 1);
						strcpy(head->labName , label);
					}
					head->next = NULL;
					
					
				}
				else
				{
					current = head;	
					while(current->next != NULL)
					{
						current = current->next;
					}
					
					next= malloc(sizeof(line_s));
					next->lineNum = lineNum;
					if (insFlag != Z)
					{
						next->dsex = (char*)malloc(strlen(ins) + 1);
						strcpy(next->dsex , ins);
						next->insFlag = insFlag;
					
					}
					else
					{
						next->insFlag= Z;
					}
					next->line = (char*)malloc(strlen(com) + 1);
					strcpy(next->line , com);
					while(com[e] !='\0')
					{
						e++;
					}
					if (labFlag == Yflag)
					{
			
						next->labFlag = labFlag;
						next->labName = (char*)malloc(strlen(label) + 1);
						strcpy(next->labName , label);
					}
					else
					{
						next->labFlag = Nflag;
					}
					next->next = NULL;
					current->next = next;
				}
				++lineNum;
				insFlag = Z;
				strcpy(com, "");
				strcpy(ins, "");
				strcpy(label, "");
				scr = start;
				labFlag = Nflag;
				break;
			}
		}
		test++;
		
	}
	*numLine = lineNum;
	return head;
}


