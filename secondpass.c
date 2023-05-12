#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "functions.h"


int secondpass(line_s *headL, datal *headD, label *headS, word *headW, int *numOfErr, int *IC,char *filename )
{
	int stage;
	FILE *errorFile;
	line_s * currline;
	word *wow; /*the wow stand for work on word so we wont write temp */
	int run = 0;
	int lineNum;
	char tempname[maxVsize];
	strcpy(tempname,filename);
	strcat(tempname,".err");
	enum {stage2,stage4, stage5, stage7} stages;
	stage = stage2;
	while (currline != NULL)
	{
		switch (stage)
		{
			case stage2:
			{
				if (run == 0)/*first time we do the second pass on the file*/
				{
					currline = headL;
				}
				else
				{
					currline = currline->next;
				
				}
				stage = stage4;
				break;
			}
			case stage4:
			{
				if (currline->insFlag == D || currline->insFlag == S || currline->insFlag == Ex)
				{
					stage = stage2;
				
				}
				else
				{
					stage = stage5;
				}
				break;
			}
			case stage5:
			{
				if (currline->insFlag == En)
				{
					stage = stage2;
				}
				else
				{
					stage = stage7;
					
				}
				break;
			}
			case stage7:
			{
				wow = findCurrWord(headW, currline->lineNum);
				if (wow == NULL)
				{
					lineNum = currline->lineNum;
					if(errorFile == NULL)
					{
						errorFile = fopen(tempname, "w+");
					}
					fprintf(errorFile, "where was a problam with creating the 12 bits words\n");
					*numOfErr = *numOfErr + 1;
				}
				wow->subword = Csubword(wow, currline,headS);
				stage = stage2;
				break;
			}
			
		}
	run++;
	}
	if (*numOfErr > 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
