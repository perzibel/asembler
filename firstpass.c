#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "functions.h"


int firstpass(line_s *headL , datal **headD ,label **headS, word **headW ,entry **headE,char *filename,int *numOfErr , int *IC ,int *DC)
{
	int L = 0;
	line_s *current;
	label *currL = (*headS);
	label *tempL;
	datal *currD = (*headD);
	datal *tempD;
	word *currW = (*headW);
	word *tempW;
	entry *firstE = (*headE);
	entry *nextE;
	FILE *errorFile;
	char tempname[maxVsize];
	int action;
	int runs = 0;
	strcpy(tempname,filename);
	strcat(tempname,".err");
	enum {
		stage2, stage5, stage6, stage7, stage8,
		stage9, stage11, stage12, stage13, stage14, stage16,
		stage17, stage18
	} stages;
	int islab;
	
	int stage = stage2;
	while (current != NULL)
	{
		
		switch (stage)
		{
			case stage2:
			{
				if (runs == 0)//first time we do the first pass on the file
				{
					current = headL;
					
				
				}
				else
				{
					current = current->next;
				}
				if ((current == NULL)&&(runs > 0))
				{
					
					stage = stage16;
				
				}
				else
				{
					stage = stage5;
					
				}
				break;
			
			}
			case stage5:
			{
				if ((current->insFlag) == D || (current->insFlag) == S)
				{
					stage = stage6;
				}
				else
				{
					stage = stage8;
				}
				break;
			}
			case stage6:
			{
				if (current->labFlag == Yflag)
				{
					islab=checkLab(current->labName, currL );
					if (islab == 0)
					{
						if(errorFile == NULL)
						{
							errorFile = fopen(tempname, "w+");
						}
						fprintf(errorFile, "the label (%s) was defined twice\n", current->labName);
						*numOfErr = *numOfErr + 1;
					}
					else if(islab == 1)
					{
						if(currL  == NULL)
						{
							
							currL  = (label*)malloc(sizeof(label));
							if ((current->insFlag) == D)
							{
								currL  = pushL(current,DC,Dflag);
							}
							else if ((current->insFlag) == S)
							{
								currL  = pushL(current,DC,Sflag);
							}
						}
						else
						{
							tempL = currL ;
							while(tempL->next !=NULL)
							{
								tempL = tempL->next;
							}
							
							if ((current->insFlag) == D)
							{
								tempL->next  = pushL(current,DC,Dflag);

							}
							else if ((current->insFlag) == S)
							{
								tempL->next  = pushL(current,DC,Sflag);
								*DC = *DC + 1;
							}
						}
					}
					else
					{
						if(errorFile == NULL)
						{
							errorFile = fopen(tempname, "w+");
						}
						fprintf(errorFile, "you tried to use a save name (%s)for a label in line %d\n",current->labName,current->lineNum);
						*numOfErr = *numOfErr + 1;
					}
				
				}
				stage = stage7;
				break;
			
			}
			case stage7:
			{
				if (current->insFlag == D)//if the instraction is data
				{
					if(currD == NULL)
					{
						currD = (datal*)malloc(sizeof(datal));
						currD = pushD(DC, typeI, current->line );
					}
					else
					{
						
						tempD = currD;
						while(tempD->next !=NULL)
						{
							tempD = tempD->next;
						}
						tempD->next= pushD(DC, typeI, current->line);
					}
					
					
				}
				else if (current->insFlag == S)//if the instraction is string
				{
					
					if(currD == NULL)
					{
						currD = (datal*)malloc(sizeof(datal));
						currD = pushD(DC, typeS, current->line );
					}
					else
					{
						tempD = currD;
						while(tempD->next !=NULL)
						{
							tempD = tempD->next;
						}
						tempD->next= pushD(DC, typeS, current->line);
						
					}
				}
				stage = stage2;
				break;
			
			}
			case stage8:
			{
				if (current->insFlag == Ex)//if the instraction is extern
				{
					stage = stage9;
				}
				else if(current->insFlag == En)//if the instraction is entry
				{
					if(currL == NULL)
					{
						firstE = (entry*)malloc(sizeof(entry));
						firstE = pushE(current,DC,ENflag);
					}
					else
					{
						nextE = firstE;
						while(nextE->next !=NULL)
						{
							nextE = nextE->next;
						}
						nextE->next = (entry*)malloc(sizeof(entry));
						nextE->next= pushE(current,DC,ENflag);
					}
					stage = stage2;
				}
				else
				{
					stage = stage11;
				}
				break;
			}
			case stage9:
			{
					islab = checkLab(current->line, currL);
					
					if (islab == 0)
					{
						
						if(errorFile == NULL)
						{
							errorFile = fopen(tempname, "w+");
						}
						fprintf(errorFile, "there are two diffrent labels with the same name -> (%s)\n", current->labName);
						*numOfErr = *numOfErr + 1;
					}
					else if(islab == 1)
					{
						if(currL == NULL)
						{
							currL = (label*)malloc(sizeof(label));
							currL = pushL(current,DC,EXflag);
							*DC = *DC + 1;
						}
						else
						{
							tempL = currL;
							while(tempL->next !=NULL)
							{
								tempL = tempL->next;
							}
							tempL->next = (label*)malloc(sizeof(label));
							tempL->next= pushL(current,DC,EXflag);
							*DC = *DC + 1;
						}

					}
					else
					{
						if(errorFile == NULL)
						{
							errorFile = fopen(tempname, "w+");
						}
						fprintf(errorFile, "you tried to use a save name (%s)for a label in line %d\n",current->labName,current->lineNum);
						*numOfErr = *numOfErr + 1;
					}
				stage = stage2;
				break;
			}
			case stage11:
			{
				if (current->labFlag == Yflag)
				{
					islab = checkLab(current->labName, currL);
					if (islab == 0)
					{
						if(errorFile == NULL)
						{
							errorFile = fopen(tempname, "w+");
						}
						fprintf(errorFile, "there was %d number of problams in the first pass\n", *numOfErr);
						*numOfErr = *numOfErr + 1;
					}
					else if(islab == 1)
					{
						if(currL == NULL)
						{
							currL = (label*)malloc(sizeof(label));
							currL = pushL(current,IC,ICflag);
						}
						else
						{
							tempL = currL;
							while(tempL->next !=NULL)
							{
								tempL =tempL->next;
							}
							tempL->next = (label*)malloc(sizeof(label));
							tempL->next= pushL(current,IC,ICflag);
						}

					}
					else
					{
						if(errorFile == NULL)
						{
							errorFile = fopen(tempname, "w+");
						}
						fprintf(errorFile, "you tried to use a save name (%s)for a label in line %d\n",current->labName,current->lineNum);
						*numOfErr = *numOfErr + 1;
					}
				}
				stage = stage12;
				break;
			}
			case stage12:
			{
				action = checkact(current->line);
				if (action == -1)
				{
					if(errorFile == NULL)
					{
						errorFile = fopen(tempname, "w+");
					}
					fprintf(errorFile, "the commend name that was enter in line %d was not correct\n",current->lineNum);
					*numOfErr = *numOfErr + 1;
				}
				stage = stage13;
				break;
			}
			case stage13:
			{
				if(currW == NULL)
				{
					currW = malloc(sizeof(word));
					currW = pushW(&L, current->line,action,numOfErr,current->lineNum, errorFile,filename);
				}
				else
				{	
					tempW = currW;
					while (tempW->next != NULL)
					{
						tempW = tempW->next;
					}
					tempW->next = pushW(&L, current->line,action,numOfErr,current->lineNum, errorFile,filename);
				}
				stage = stage14;
				break;
			
			}
			case stage14:
			{
				*IC = *IC + L;
				L = 0;
				stage = stage2;
				break;
			
			}
			
		}


		
	
	runs++;
	}
	while(1)
	{
		switch (stage)
		{
			case stage16:
			{
				if (*numOfErr > 0)
				{
					if(errorFile == NULL)
					{
						errorFile = fopen(tempname, "w+");
					}
					fprintf(errorFile,"numOfErr -> %d \n",*numOfErr);
					return Nflag;
				}
			
				stage = stage17;
				break;
		
			}
			case stage17:
			{
				updateS(currL,currD,IC);
				stage = stage18;
				break;
			}
			case stage18:
			{
				(*headS) = currL;
				(*headD) = currD;
				(*headW) = currW;
				(*headE) = firstE;
				return Yflag;
			}
		}
	}
}
