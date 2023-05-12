#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "functions.h"

int isNspace(unsigned char c);
/* this function get a string and check its size*/
int strsize(char *str)
{
	int size = 0;
	int i = 0;
	while (str[i] != '\0')
	{
		size++;
		i++;
	}
	return size;
}


/*this function check what instraction is given and return its value as int */
int checkins(char *ins) 
{
	char *instractionD = "data";
	char *instractionS = "string";
	char *instractionE = "entry";
	char *instractionX = "extern";
	int i;
	int size;
	int res;
	res = strcmp(ins , instractionD);
	
	if(res == 0)
	{	
		return D;
	}

	res = strcmp(ins , instractionS);
	
	if (res == 0)
	{
		return S;
	}

	res = strcmp(ins , instractionE);
	
	if (res == 0)
	{
		return En;
	}

	res = strcmp(ins , instractionX);
	
	if (res == 0)
	{
		return Ex;
	}

	return Z;
}

/* this function check if a given label is already stated*/
int checkLab(char *labName, label *headS) 
{
	label *current = headS;
	int i;
	char *labs[12];
	labs[0] = "data";
	labs[1] = "string";
	labs[2] = "extern";
	labs[3] = "entry";
	labs[4] = "r0";
	labs[5] = "r1";
	labs[6] = "r2";
	labs[7] = "r3";
	labs[8] = "r4";
	labs[9] = "r5";
	labs[10] = "r6";
	labs[11] = "r7";
	for(i = 0 ; i < 12 ; i++)
	{
		if(strcmp(labs[i],labName)==0)
		{
			return 2;
		}
	}
	if (headS == NULL) // if the list is empty
	{
		return 1;
	}
	else//if there are labels in the list
	{
		while (current != NULL)
		{
			if (strcmp(current->labelName, labName) == 0) // is there a label with the same name
			{
				return 0;
			}
			else
			{
				current = current->next;
			}

		}
		return 1;
	}
}

entry *pushE(line_s *current,int *addres,int type)
{
	entry *newL = NULL;
	entry *temp= NULL;
	entry *head = NULL;
	char nextc;
	char com[maxLineSize];
	char labName[maxLineSize];
	int length=0;
	int i = 0 ;
	int j = 0;
	int fon =0;
	newL = (entry*)malloc(sizeof(entry));
	newL->isE = Yflag;
	length = strlen(current->line);
	strcpy(com ,current->line);
	while(i < length)
	{
		nextc = com[i];
		if(isNspace(nextc))
		{
			while(isNspace(nextc))
			{
				i++;
				nextc = com[i];
			}
		}
		while((nextc != ',') && i < length )
		{		
			
			labName[j] = nextc;
			i++;
			j++;
			nextc = com[i];
			if(isNspace(nextc))
			{
				while(isNspace(nextc))
				{
					i++;
					nextc = com[i];
				}
			}
		}
		if(nextc == ',')/*then we have more then 1 varibel*/
		{
			newL->labelName = (char *)malloc(strlen(labName)+1);
			strcpy(newL->labelName , labName);
			newL->isE = Yflag;
			newL->type = type;
			if (fon == 0)
			{
				newL->next = NULL;
				head = newL;
				fon++;
				newL = newL->next;
				newL = (entry*)malloc(sizeof(entry));
				strcpy(labName,"");
				j = 0;
			}
			else
			{
				temp = head;
				while(temp->next != NULL)
				{
					temp = temp->next;
				}
				temp->next = newL;
				newL->next = NULL;
				temp = temp->next;
				newL = newL->next;;
				newL = (entry*)malloc(sizeof(entry));
				strcpy(labName,"");
				j = 0;
			}
		}
		labName[j] = '\0';
		
	}
	newL->labelName = (char *)malloc(strlen(labName)+1);
	strcpy(newL->labelName , labName);
	newL->isE = Yflag;
	newL->addres = 0;
	newL->type = type;
	newL->next = NULL;
	if (fon == first)
	{
		return newL;
	}
	else
	{
		temp = head;
		while(temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = newL;
		newL->next = NULL;
		temp = temp->next;
		newL = newL->next;
		strcpy(labName,"");
		free(newL);
		j = 0;
		return head;
	}

}
/* this funtion pushs a new label into the label list*/
label *pushL(line_s *current,int *addres,int type) 
{
	label *newL = NULL;
	label *temp= NULL;
	label *head = NULL;
	char nextc;
	char com[maxLineSize];
	char labName[maxLineSize];
	int length=0;
	int i = 0 ;
	int j = 0;
	int fon =0;
	newL = (label*)malloc(sizeof(label));
	if (current->insFlag == Ex)
	{
		newL->isE = Yflag;
		length = strlen(current->line);
		strcpy(com ,current->line);
		while(i < length)
		{
			nextc = com[i];
			while((nextc != ',') && i < length )
			{		
				labName[j] = nextc;
				j++;
				i++;
				nextc = com[i];
				if(isNspace(nextc))
				{
					while(isNspace(nextc))
					{
						i++;
						nextc = com[i];
					}
				}
			}
			if(nextc == ',')/*then we have more then 1 varibel*/
			{
				newL->labelName = (char *)malloc(strlen(labName)+1);
				strcpy(newL->labelName , labName);
				newL->isE = Yflag;
				newL->type = type;
				if (fon == 0)
				{
					newL->next = NULL;
					head = newL;
					fon++;
					newL = newL->next;
					newL = (label*)malloc(sizeof(label));
					strcpy(labName,"");
					j = 0;
				}
				else
				{
					temp = head;
					while(temp->next != NULL)
					{
						temp = temp->next;
					}
					temp->next = newL;
					newL->next = NULL;
					temp = temp->next;
					newL = newL->next;;
					newL = (label*)malloc(sizeof(label));
					strcpy(labName,"");
					j = 0;
				}
			}
			
		}
		newL->labelName = (char *)malloc(strlen(labName)+1);
		strcpy(newL->labelName , labName);
		newL->isE = Yflag;
		newL->addres = 0;
		newL->type = type;
		newL->next = NULL;
		if (fon == first)
		{
			return newL;
		}
		else
		{
			temp = head;
			while(temp->next != NULL)
			{
				temp = temp->next;
			}
			temp->next = newL;
			newL->next = NULL;
			temp = temp->next;
			newL = newL->next;
			strcpy(labName,"");
			j = 0;
			return head;
		}
		
	}
	else
	{
		newL->labelName = (char *)malloc(strlen(current->labName)+1);
		strcpy(newL->labelName , current->labName);
		newL->addres = *addres; /*we put the address here because the binery line of extern is all 0 there for we dont need the "real" address */
		newL->isE = Nflag;
		newL->type = type;
		newL->next = NULL;
		return newL;
	}
	
	
}

/*this function get a line without the simbol and instraction and push the data into the data list*/
datal *pushD(int *DC, int type, char *line )
{
	char *temp = (char*)malloc(sizeof(line));
	char curr[maxVsize];
	char curr2[maxVsize];
	char nextc;
	int value;
	int i = 0;/*index for curr */
	int t = 0;/*index for temp*/
	int j = 0;/*index for temp in for loop*/
	int h = 0;/*index for curr2*/
	int length ;
	int fon = 0;/*first or nextc*/
	int mtov =0;/* stand for more then one varible , and its perpas is so we could check if there are a few varibels the saparate*/
	int tempDC = 0;/*the tempDC is for us to count all the varibels and add them to DC at the end */
	datal *current =NULL;
	datal *tempD =NULL;
	datal *newL = NULL;
	strcpy(temp,line);
	nextc = temp[t];
	while (nextc != '\0')
	{
		if (type == typeI)
		{
			if (isNspace(nextc))
			{
				
				while (isNspace(nextc))
				{
					j++;
					nextc = temp[t];
				}
			}
			
			while (nextc != '\0')
			{
				if (isNspace(nextc))
				{
				
					while (isNspace(nextc))
					{
						i++;
						nextc = curr[i];
					}
				}
				if(nextc == ',')
				{
					mtov = 1;
				}
				curr[i] = nextc;
				i++;
				t++;
				nextc = temp[t];
			}
			
			curr[i] = '\0';
			if(mtov == 1)
			{
				length = strlen(curr);
				t = 0;
				nextc = temp[t];
				for(j = 0; j < length; j++)
				{
					if(nextc == ',')
					{
						newL = (datal*)malloc(sizeof(datal));
						curr2[h] ='\0';
						value = atoi(curr2);
						newL->DC = *DC;
						*DC = *DC + 1;
						newL->type = type;
						newL->value = (datat*)malloc(sizeof(datat));
						newL->value->x = value;
						newL->next = NULL;
						if (fon == 0)
						{
							current = newL;
							newL = newL->next;
							nextc = curr[j];
							strcpy(curr2,"");
							h = 0;
							fon =1;
						}
						else
						{
							tempD = current;
							while(tempD->next != NULL)
							{
								tempD = tempD->next;
							}
						
							tempD->next = newL;
							newL->next = NULL;
							tempD = tempD->next;
							newL = newL->next;
							strcpy(curr2,"");
							h = 0;
						}
					}
					else if (isNspace(nextc))
					{
					
						while (isNspace(nextc))
						{
							j++;
							nextc = curr[j];
						}
					}
					else
					{
						curr2[h] = nextc;
						h++;
					}
					t++;
					nextc = temp[t];
				}
			}
			newL = (datal*)malloc(sizeof(datal));
			if(mtov == 0)
			{	
				value = atoi(curr);
			}
			else
			{
				curr2[h] ='\0';
				value = atoi(curr2);
				tempD->next = newL;
			}
			newL->DC = *DC;
			*DC = *DC +1;
			newL->type = type;
			newL->value = (datat*)malloc(sizeof(datat));
			newL->value->x = value;
			newL->next = NULL;
		}
		else if (type == typeS)
		{
			
			if (nextc == '"')
			{
				t++;
				nextc = temp[t];
			}
			while ((nextc != '\0'))
			{
				
				curr[i] = nextc;
				tempDC++;
				i++;
				t++;
				nextc = temp[t];
				if (nextc == '"')
				{
					t++;
					nextc = temp[t];
				}
			}
			curr[i] = '0';/*add 0 so we could create a word for '\0'*/
			i++;
			curr[i] ='\0';
			newL = (datal*)malloc(sizeof(datal));
			newL->DC = *DC;
			*DC = *DC + tempDC ;
			newL->type = type;
			newL->value = (datat*)malloc(sizeof(datat));
			newL->value->ch = (char*)malloc(strlen(curr)+1);
			strcpy(newL->value->ch , curr);
			newL->next = NULL;
			return newL;	
		}
	}
	*DC = *DC + tempDC;
	if(mtov == 0)
	{
		return newL;
	}
	return current;
}

/*checkact is a function that check what action was called and return a number based on the table in the task*/
int checkact(char *line)
{
	char *action[16];
	action[0] = "mov";
	action[1] = "cmp";
	action[2] = "add";
	action[3] = "sub";
	action[4] = "not";
	action[5] = "clr";
	action[6] = "lea";
	action[7] = "inc";
	action[8] = "dec";
	action[9] = "jmp";
	action[10] = "bne";
	action[11] = "red";
	action[12] = "prn";
	action[13] = "jsr";
	action[14] = "rts";
	action[15] = "stop";
	
	char com[5];
	char nextc;
	int i = 0;
	int l = 0;
	int res =-1;
	int comlength=0;
	char linelength=0;
	char templine[maxLineSize];
	int Bskip=0;/*blank notes skip (space's )*/
	strcpy(templine,line);
	nextc = templine[l];
	if (isspace(nextc))
	{
		while (isspace(nextc))
		{
			l++;
			nextc = templine[l];
		}
	}
	while (!isspace(nextc))
	{
		com[i] = nextc;
		i++;
		l++;
		nextc = templine[l];
	}
	while (isspace(nextc))
	{
		l++;
		Bskip++;
		nextc = templine[l];
	}
	com[i] = '\0';
	comlength = strlen(com);
	linelength = strlen(line);
	strncpy(line ,(templine)+(comlength+Bskip),(linelength));/*now the line is just the varibels */
	line[(linelength)-(comlength+Bskip)]='\0';
	for (i = 0; i < actionSize; i++)
	{
		res = strcmp(com, action[i]);
		if (res == 0)
		{
			return i;
		}
	}
	return -1;
}

/*this function (instract opcode) is to set the opcode for a given word*/
void Iopcode(word *current, int instract)
{
	
	int i;
	for (i = fourth; i >=0; i--)
	{
		if ((instract & mask) == 0)
		{
			current->opcode[i] = 0;
			instract = instract >> 1;
		}
		else
		{
			current->opcode[i] = 1;
			instract = instract >> 1;
		}
	}
	
	
	
	
}

int isNumeric(const char *str) 
{
	char temp[maxVsize];
	int i =0;
	strcpy(temp,str);
	while(temp[i] != '\0')
	{
		if(temp[i] == '-')
		{
			
		}
		else if(temp[i] < '0' || temp[i] > '9')
		{
			return 1;
		}

		i++;
	}
	return 0;
}

/*pushW is a function to push into a list all the first words*/
word *pushW(int *L, char *line ,int instract,int *numOfErr,int lineNum, FILE *errorFile , char *filename)
{
	char nextc;
	char templine[maxLineSize];
	char com[maxVsize];
	char com2[maxVsize];
	word *temphead;
	word *current = NULL;
	int i = 0;
	int j = 0;
	int h = 0;/*index for com2*/
	int run=0;
	int l = 0 ;
	int length =0;
	int stateOrg = 0;
	int stateDes = 0;
	int error =0;
	char val[maxVsize];
	int vallength = (-1);
	int valnum;
	strcpy(templine ,line);
	length = strlen(templine);
	current = (word *)malloc(sizeof(word));
	nextc = templine[l];
	while (nextc != '\0')
	{
		if (isNspace(nextc))
		{
			while (isNspace(nextc))
			{
				l++;
				nextc = templine[l];
			}
		}
		if ((instract == 0) || (instract == 1) || (instract == 2) || (instract == 3) || (instract == 6))/*mov , cmp , add , sub or lea-> meeing there are 2 arguments*/
		{
			if (run == 0)
			{
				Iopcode(current, instract);
				
			}
			if (run >= 2)/*meeing there are too many values*/
			{
				
				if(errorFile == NULL)
				{
					strcat(filename,".err");
					errorFile = fopen(filename,"w+");
				}
				fprintf(errorFile, "there was too mant aruments in line %d", lineNum);
				*numOfErr = *numOfErr + 1;
			}
			while ((nextc != '\0'))
			{
				
				com[i] = nextc;
				i++;
				l++;
				nextc = templine[l];
				if (isNspace(nextc))
				{
					l++;
					nextc = templine[l];
				}
				if(nextc == ',') vallength = i;
			}
			com[i] = '\0';
			if(vallength == -1)
			{
				vallength = i;
			}
			nextc = templine[first];
			for(j=0 ; j < l ; j++)/*we set the while part to j < l because we know that templine[l] = '\0' after the first loop*/
			{
				nextc = templine[j];
				if (isNspace(nextc))
				{
					j++;
					nextc = templine[j];
				}
				if(nextc ==',')
				{
					com2[h] = '\0';
					if (isNumeric(com2) == 0)
					{
						current->org[first] = 0;
						current->org[second] = 0;
						current->org[third] = 1;
						stateOrg = 0;
					}
					else if (com2[first] == '@')/*if there is a register */
					{
						strncpy(val ,com2 + third,vallength-1);
						valnum = atoi(val);
						if ((valnum <= 7) && (valnum >=0))
						{
							current->org[first] = 1;
							current->org[second] = 0;
							current->org[third] = 1;
							stateOrg =1;
						}
						else
						{
							if(errorFile == NULL)
							{
								strcat(filename,".err");
								errorFile = fopen(filename,"w+");
							}
							fprintf(errorFile, "the register was of to large number in line %d", lineNum);
							*numOfErr = *numOfErr + 1;
						}
					}
					else
					{
						current->org[first] = 0;
						current->org[second] = 1;
						current->org[third] = 1;
						stateOrg = 2;
					}
					strcpy(com2,"");
					h = 0;
					run++;
				}
				else
				{
					com2[h] = nextc;
					h++;
				}
			}
			com2[h] = '\0';
			/* we create the orgin current in to loop and the destention after we finshed it*/
			if(isNumeric(com2)==0)
			{
				current->des[first] = 0;
				current->des[second] = 0;
				current->des[third] = 1;
				stateDes = 0;
			}
			else if(com2[first] == '@')
			{
				strncpy(val ,com2 + third,vallength-1);
				valnum = atoi(val);
				if ((valnum <= 7) && (valnum >=0))
				{
					
					current->des[first] = 1;
					current->des[second] = 0;
					current->des[third] = 1;
					stateDes = 1;
				
				}
				else
				{
					if(errorFile == NULL)
					{
						strcat(filename,".err");
						errorFile = fopen(filename,"w+");
					}
					fprintf(errorFile, "the register was of too large number in line %d", lineNum);
					*numOfErr = *numOfErr + 1;
				}
			}
			else
			{
				current->des[first] = 0;
				current->des[second] = 1;
				current->des[third] = 1;
				stateDes = 2;
			}
		nextc = '\0';
		}
		else if ((instract == 4) || (instract == 5) || (instract == 7) || (instract == 8) || (instract == 9) || (instract == 10) || (instract == 11) || (instract == 12) || (instract == 13))
		{
			
			if (run >= 1)/*meeing there are too many values , there should to be 1 value*/
			{
				if(errorFile == NULL)
				{
					strcat(filename,".err");
					errorFile = fopen(filename,"w+");
				}
				fprintf(errorFile, "there were two many arguments in line %d \n", lineNum);
				*numOfErr = *numOfErr +1;
			}
			
			nextc = templine[l];
			length = strlen(templine);
			while (nextc != '\0')
			{
				com[i] = nextc;
				i++;
				l++;
				nextc = templine[l];
				if (isNspace(nextc))
				{
					l++;
					nextc = templine[l];
				}
				if(nextc == ',')
				{
					error = 1;
				}
			}
			com[i] = '\0';
			if (run == 0)
			{
				Iopcode(current, instract);
			}
			current->org[first] = 0;
			current->org[second] = 0;
			current->org[third] = 0;
			stateOrg = 3;
			if (isNumeric(com) == 0)
			{
				current->des[first] = 0;
				current->des[second] = 0;
				current->des[third] = 1;
				stateDes = 0;

			}
			else if (com[first] == '@')/*if there is a register */
			{
				if ((com[third] <= 7)&&(com[third] >= 0))
				{

					current->des[first] = 1;
					current->des[second] = 0;
					current->des[third] = 1;
					stateDes = 1;
				}
				else
				{
					if(errorFile == NULL)
					{
						strcat(filename,".err");
						errorFile = fopen(filename,"w+");
					}
					fprintf(errorFile, "the register was of too large number in line %d", lineNum);
					*numOfErr = *numOfErr + 1;
				}
			}
			else
			{
				
				current->des[first] = 0;
				current->des[second] = 1;
				current->des[third] = 1;
				stateDes = 2;
			}
			
		}
		else if ((instract == 14) || (instract == 15))
		{
			Iopcode(current, instract);
			if(run > 0) /*there should be no values to those instract*/
			{
				if(errorFile == NULL)
				{
					strcat(filename,".err");
					errorFile = fopen(filename,"w+");
				}
				fprintf(errorFile, "there should be no values to those instract in line %d \n", lineNum);
				*numOfErr = *numOfErr + 1;
			}
			current->org[first] = 0;
			current->org[second] = 0;
			current->org[third] = 0;

			current->des[first] = 0;
			current->des[second] = 0;
			current->des[third] = 0;
			stateOrg = 3;
			stateDes = 3;
		}
		current->stateDes = stateDes;
		current->stateOrg = stateOrg;
		i = 0;
		l++;
		strcpy(com, "");
		run++;
		if (isNspace(templine[l]))/*so we could make sure there are no extra spaces and the next char is '\0'*/
		{
			while (isNspace(templine[l]))
			{
				l++;
			}
		}
		
	}
	/*after we are finshed with making the word we can set the other varibles */
	if((instract == 15) || (instract == 14))/*end case where the first char in the line is \0 */
	{
		Iopcode(current, instract);
		if(run > 0) /*there should be no values to those instract*/
		{
			if(errorFile == NULL)
			{
				strcat(filename,".err");
				errorFile = fopen(filename,"w+");
			}
			fprintf(errorFile, "there was %d number of problams after the first pass", *numOfErr);
			*numOfErr = *numOfErr + 1;
		}
		current->org[first] = 0;
		current->org[second] = 0;
		current->org[third] = 0;

		current->des[first] = 0;
		current->des[second] = 0;
		current->des[third] = 0;
		stateOrg = 3;
		stateDes = 3;
		
		current->stateDes = stateDes;
		current->stateOrg = stateOrg;
	}
	current->are[first] = 0;
	current->are[second] = 0;
	current->lineNum = lineNum;
	if ((instract == 0) || (instract == 1) || (instract == 2) || (instract == 3) || (instract == 6))
	{/*so we could check that the number of varibels was right*/
		if(run < 2)
		{
			if(errorFile == NULL)
			{
				strcat(filename,".err");
				errorFile = fopen(filename,"w+");
			}
			fprintf(errorFile, "there was a varible missing in line %d", lineNum);
			*numOfErr = *numOfErr + 1;
		}
	}
	else if((instract ==4)||(instract ==5)||(instract ==7)||(instract ==8)||(instract ==9)||(instract ==10)||(instract ==11)||(instract ==12)||(instract==13))
	{
		if(error == 1)
		{
			if(errorFile == NULL)
			{
				strcat(filename,".err");
				errorFile = fopen(filename,"w+");
			}
			fprintf(errorFile, "there was a varible missing in line %d", lineNum);
			*numOfErr = *numOfErr + 1;
		}
	}
	
	if ((stateDes == fourth) && (stateOrg == fourth))/* meening there are no destention and orgin arguments*/
	{
		*L = 0;
		current->con = 0;
	}
	else if ((stateDes == second) && (stateOrg == second))/* meening there are 2 registers then there are 2 lines*/
	{
		*L = 2;
		current->con = 1;
	}
	else if((stateDes == fourth) || (stateOrg == fourth))/* if one of the arguments is empty there are 2 lines*/
	{
		*L = 2;
		current->con = 1;
	}
	else/* if there are a destntion argument and a orgin argument there are 3 lines*/
	{
		*L =  3;
		current->con = 2;
	}
	
	current->next = NULL;
	return current;
}

/*this function is to find the first data node that has the same DC as a label*/
datal *findnextd(datal *head, int addres)
{
	datal *current = head;

	while (current != NULL)
	{
		if (current->DC == addres)
		{
			return current;
		}
		current = current->next;
	}
	return NULL;
}

/*this function is to update the addres and DC for the data list and the data type labels*/
void updateS(label *headS ,datal *headD ,int *IC)
{
	label *currs = headS;
	datal *currd = headD;
	
	while (currd != NULL)
	{
		currd->DC += *IC;
		currd = currd->next;
	}
	while (currs != NULL)
	{
		if ((currs->type == Dflag) || (currs->type == Sflag))
		{
			currs->addres += *IC;
		}
		currs = currs->next;
	}
}

/* the function findCurrWord is to find the word we need to work on based on the line number*/
word *findCurrWord(word *headW, int lineNum)
{
	word *current = headW;
	while (current != NULL)
	{
		if (current->lineNum == lineNum)
		{
			return current;
		}
		current = current->next;
	}
	return NULL;
}

/* hte function labelA is to find a labels addres and send in back so we could put her binery code into a subword*/
int labelA(label *headS, char *com)
{
	label *currl = headS;
	char labname[maxLineSeize] ;
	strcpy(labname,com);
	while (currl != NULL)
	{
		if (strcmp(currl->labelName, labname) == 0)
		{
			if (currl->isE == Yflag)
			{
				return 0;
			}
			return currl->addres;
		}
		currl = currl->next;

	}
	return -1;
}

/* this function (Csubword) is to create the subwords  */
subword *Csubword(word *currword, line_s *currline,label *headS)
{
	int con = currword->con;
	char templine[maxVsize];
	char com[maxVsize];
	char nextc;
	int i = 0;
	int l = 0;
	int j = fifth;
	int y = fifth;
	int fon = 0 ;
	int pass = 0;
	int temp =0;
	int value=0;
	int labAd =0;
	int negative = 0;
	int remember = 0;
	subword *firstW = NULL;
	subword *newS;
	strcpy(templine ,currline->line);
	nextc =templine[l];
	while (con > 0)
	{
		if (con == 1)/* that meens that there is 1 subword to deal with and its either 2 register or only a destnetion argument*/
		{
			con -= 1;/* we decrese con by 1 here so we could put in the new subword how many next subwords are they*/
			
			newS =(subword*)malloc(sizeof(subword));
			newS->con = con;
			if ((currword->stateDes == second) && (currword->stateOrg == second))/*if both are registers*/
			{
				while (pass < 2)
				{
					if(isNspace(nextc))
					{
						while(isNspace(nextc))
						{
							l++;
							nextc =templine[l];
						}
					}
					if(pass == 0)/*then we need to look for the first register*/
					{
						while (nextc != ',')
						{
							com[i] = nextc;
							i++;
							l++;
							nextc =templine[l];
						}
					}
					else if(pass == 1)/* then we need to look for the second register*/
					{
						while (nextc != '\0')
						{
							com[i] = nextc;
							i++;
							l++;
							nextc =templine[l];
						}

					}
					l++;
					nextc =templine[l];
					com[i] = '\0';
					value = com[third]- '0';
					if (pass == 0)/* than we need to take care of the first register*/
					{
						while (value != 0)
						{
							temp = value & mask;
							newS->bitL[j] = temp;
							value >>= 1;
							j--;
						}
						if (j >= 0)
						{
							while (j >= 0)
							{
								newS->bitL[j] = 0;
								j--;
							}
						}
					}
					else /* then we need to ttake care of the second register*/
					{
						while (value != 0)
						{
							temp = value & mask;
							newS->bitR[y] = temp;
							value >>= 1;
							y--;
						}
						if (y >= 0)
						{
							while (y >= 0)
							{
								newS->bitR[y] = 0;
								y--;
							}
						}
					}
					i = 0;
					pass++;
					strcpy(com,"");
				}
				newS->are[first] = 0;
				newS->are[second] = 0;
			}/* other wise we need to take care only of the destention argument*/
			else if (currword->stateDes == first)/*then theres a number*/
			{
				while (nextc != '\0')
				{
					if(isNspace(nextc))
					{
						while(isNspace(nextc))
						{
							l++;
							nextc =templine[l];
						}
					}
					com[i] = nextc;
					i++;
					l++;
					nextc =templine[l];
				}
				com[i] = '\0';
				value = atoi(com);
				newS->are[first] = 0;
				newS->are[second] = 0;
				if(value < 0)
				{
					value = value *(-1);/*to start the 2 completion*/
					negative = 1;
				}
				while (value != 0)
				{
					if (j < 0)
					{
						temp = value & mask;
						newS->bitL[y] = temp;
						value >>= 1;
						y--;
					}
					else
					{
						temp = value & mask;
						newS->bitR[j] = temp;
						value >>= 1;
						j--;
					}	
				}
				if (j >= 0)
				{
					while (j >= 0)
					{
						newS->bitR[j] = 0;
						j--;
					}
				}
				if (y >= 0)
				{
					while (y >= 0)
					{
						newS->bitL[y] = 0;
						y--;
					}
				}
				if(negative == 1)
				{
					j = fifth;
					y = fifth;
					while(j >= 0 || y >= 0)/*we transform every 0 to 1 and 1 to 0*/
					{
						if (j < 0)
						{
							if(newS->bitL[y] == 1)
							{
								newS->bitL[y] = 0;
							}
							else
							{
								newS->bitL[y] = 1;
							}
							y--;
						}
						else
						{
							if(newS->bitR[j] == 1)
							{
								newS->bitR[j] = 0;
							}
							else
							{
								newS->bitR[j] = 1;
							}
							j--;
						}
					}
					j = fourth;/*because we check the fifth place on our owen*/
					y = fifth;
					newS->bitR[fifth] += 1;
					if(newS->bitR[fifth] == 2)
					{
						
						newS->bitR[fifth] = 0;
						remember == 1;
					}
					while(remember != 0)
					{
						
						if(y < 0)/*we finshed with all the 12 bits*/
						{
							remember = 0;
						}
						else if (j < 0)
						{
							newS->bitL[y] += 1;
							if(newS->bitL[y] == 2)
							{
								newS->bitL[y] = 0;
								remember = 1;
							}
							else
							{
								remember = 0;
							}
							y--;
						}
						else if(j >= 0)
						{
							newS->bitR[j] += 1;
							if(newS->bitR[j] == 2)
							{
								newS->bitR[j] = 0;
								remember = 1;
							}
							else
							{
								remember = 0;
							}
							j--;
						}
						
					}
				}
			}
			else if (currword->stateDes == second)/* then theres a register*/
			{
				newS->are[first] = 0;
				newS->are[second] = 0;
				while (nextc != '\0')
				{
					if(isNspace(nextc))
					{
						while(isNspace(nextc))
						{
							l++;
							nextc =templine[l];
						}
					}
					com[i] = nextc;
					i++;
					l++;
					nextc =templine[l];
				}
				com[i] = '\0';
				value = com[third]-'0';
				while (value != 0)
				{
					temp = value & mask;
					newS->bitR[j] = temp;
					value >>= 1;
					j--;
				}
				if (j >= 0)
				{
					while (j >= 0)
					{
						newS->bitR[j] = 0;
						j--;
					}
				}
				if (y >= 0)
				{
					while (y >= 0)
					{
						newS->bitL[y] = 0;
						y--;
					}
				}
			}
			else if (currword->stateDes == third)/*there is a label*/
			{
				while (nextc != '\0')
				{
					if(isNspace(nextc))
					{
						while(isNspace(nextc))
						{
							l++;
							nextc =templine[l];
						}
					}
					com[i] = nextc;
					i++;
					l++;
					nextc =templine[l];
				}
				com[i] = '\0';
				labAd = labelA(headS, com);
				if (labAd == 0)/* meening the label is extern*/
				{
					newS->are[first] = 0;
					newS->are[second] = 1;
					if (j >= 0)
					{
						while (j >= 0)
						{
							newS->bitR[j] = 0;
							j--;
						}
					}
					if (y >= 0)
					{
						while (y >= 0)
						{
							newS->bitL[y] = 0;
							y--;
						}
					}
				}
				else if (labAd != (-1))
				{
					newS->are[first] = 1;
					newS->are[second] = 0;
					while (labAd != 0)
					{
						if (j < 0)
						{
							temp = labAd & mask;
							newS->bitL[y] = temp;
							labAd >>= 1;
							y--;
						}
						else
						{
							temp = labAd & mask;
							newS->bitR[j] = temp;
							labAd >>= 1;
							j--;
							
						}
					}
					if (j >= 0)
					{
						while (j >= 0)
						{
							newS->bitR[j] = 0;
							j--;
						}
					}
					if (y >= 0)
					{
						while (y >= 0)
						{
							newS->bitL[y] = 0;
							y--;
						}
					}
				}

			}
			if(fon == first)
			{
				firstW = newS;
				newS->next = NULL;
				newS = newS->next;
			}
			else
			{
				firstW->next = newS;
				newS->next = NULL;
				newS = newS->next;
			}
		}
		else if (con == 2)/* it meens that we have 2 subwords to deal with */
		{
			con -= 1;/* we decrese con by 1 here so we could put in the new subword how many next subwords are they*/
			newS =(subword*)malloc(sizeof(subword));
			newS->con = con;
			if (currword->stateOrg == first)/*then theres a number*/
			{
				while (nextc != ',')
				{
					
					com[i] = nextc;
					i++;
					l++;
					nextc =templine[l];
				}
				
				com[i] = '\0';
				value = atoi(com);
				newS->are[first] = 0;
				newS->are[second] = 0;
				if(value < 0)
				{
					value = value *(-1);/*to start the 2 comletion*/
					negative = 1;
				}
				while (value != 0)/*then we calaulate the number*/
				{
					if (j < 0)
					{
						temp = value & mask;
						newS->bitL[y] = temp;
						value >>= 1;
						y--;
					}
					else
					{
						temp = value & mask;
						newS->bitR[j] = temp;
						value >>= 1;
						j--;
					}
				}
				if (j >= 0)
				{
					while (j >= 0)
					{
						newS->bitR[j] = 0;
						j--;
					}
				}
				if (y >= 0)
				{
					while (y >= 0)
					{
						newS->bitL[y] = 0;
						y--;
					}
				}
				if(negative == 1)
				{
					j = fifth;
					y = fifth;
					while(j >= 0 || y >= 0)
					{
						if (j < 0)
						{
							if(newS->bitL[y] == 1)
							{
								newS->bitL[y] = 0;
							}
							else
							{
								newS->bitL[y] = 1;
							}
							y--;
						}
						else
						{
							if(newS->bitR[j] == 1)
							{
								newS->bitR[j] = 0;
							}
							else
							{
								newS->bitR[j] = 1;
							}
							j--;
						}
					}
					j = fourth;/*because we check the fifth place on our owen*/
					y = fifth;
					newS->bitR[fifth] += 1;
					if(newS->bitR[fifth] == 2)
					{
						newS->bitR[fifth] = 0;
						remember == 1;
					}
					while(remember != 0)
					{
						
						if(y < 0)/*we finshed with all the 12 bits*/
						{
							remember = 0;
						}
						else if (j < 0)
						{
							newS->bitL[y] += 1;
							if(newS->bitL[y] == 2)
							{
								newS->bitL[y] = 0;
								remember = 1;
							}
							else
							{
								remember = 0;
							}
							y--;
						}
						else if(j >= 0)
						{
							newS->bitR[j] += 1;
							if(newS->bitR[j] == 2)
							{
								newS->bitR[j] = 0;
								remember = 1;
							}
							else
							{
								remember = 0;
							}
							j--;
						}
						
					}
				}

			}
			else if (currword->stateOrg == second)/* then theres a register*/
			{
				newS->are[first] = 0;
				newS->are[second] = 0;
				
				while (nextc != ',')
				{
					com[i] = nextc;
					i++;
					l++;
					nextc =templine[l];
				}
				l++;
				nextc =templine[l];
				com[i] = '\0';
				value = com[third]-'0';
				y = fifth;
				j = fifth;
				while (value != 0)
				{
					temp = value & mask;
					newS->bitL[y] = temp;
					value >>= 1;
					y--;
				}
				if (j >= 0)
				{
					while (j >= 0)
					{
						newS->bitR[j] = 0;
						j--;
					}
				}
				if (y >= 0)
				{
					while (y >= 0)
					{
						newS->bitL[y] = 0;
						y--;
					}
				}
			}
			else if (currword->stateOrg  == third)/*there is a label*/
			{
				
				newS->are[first] = 1;
				newS->are[second] = 0;
				while (nextc != '\0')
				{

					com[i] = nextc;
					i++;
					l++;
					nextc =templine[l];
				}
				com[i] = '\0';	
				labAd = labelA(headS, com);
				if (labAd == 0)/* meening the label is extern*/
				{
					
					newS->are[first] = 0;
					newS->are[second] = 1;
				}
				else if (labAd != (-1))
				{
					while (labAd != 0)
					{
						if (j < 0)
						{
							temp = labAd & mask;
							newS->bitL[y] = temp;
							labAd >>= 1;
							y--;
						}
						else
						{
							temp = labAd & mask;
							newS->bitR[j] = temp;
							labAd >>= 1;
							j--;
							
						}
					}
					if (j >= 0)
					{
						while (j >= 0)
						{
							newS->bitR[j] = 0;
							j--;
						}
					}
					if (y >= 0)
					{
						while (y >= 0)
						{
							newS->bitL[y] = 0;
							y--;
						}
					}
				} 
			}
			firstW = newS;
			newS->next = NULL;
			newS = newS->next;
			fon = 1;
		}
		y = 4;
		j = 4;
		i = 0;
		strcpy(com, "");
	}
	
	return firstW;
}

/*the function numOFwords will thell us the number of words before the add of the data words*/
int numOFwords(word *head)
{
	int count = 0;
	word *temp = head;
	while (temp != NULL)
	{
		count++;
		count = count + temp->con;
		temp = temp->next;
	}
	return count;
}

/* the function addData is to add all the data list into the words list as binary and count how mant lines did we add so we'll know for the .ob file */
int addData(word *headW, datal *headD)
{
	int count = 0;
	int i = 0;
	int place = 0;
	int value;
	char nextc;
	int tempc;
	word *currword = headW;
	datal *currdata = headD;
	word *nextw;

	while (currword->next != NULL)
	{
		currword = currword->next;
	}
	while (currdata != NULL)
	{
		
		if (currdata->type == typeI)/*if the data type is integer*/
		{
			
			nextw = (word*)malloc(sizeof(word));
			tempc = currdata->value->x;
			 
			for (i = 11; i >= 0; --i)/* set the 12 bits in a word to be the value of tempc in binary*/
			{
				printf("%d",value);
				value = tempc & mask;
				if (i == 11) { nextw->are[second] = value; }
				else if (i == 10) { nextw->are[first] = value; }
				else if (i == 9) { nextw->des[third] = value; }
				else if (i == 8) { nextw->des[second] = value; }
				else if (i == 7) { nextw->des[first] = value; }
				else if (i == 6) { nextw->opcode[fourth] = value; }
				else if (i == 5) { nextw->opcode[third] = value; }
				else if (i == 4) { nextw->opcode[second] = value; }
				else if (i == 3) { nextw->opcode[first] = value; }
				else if (i == 2) { nextw->org[third] = value; }
				else if (i == 1) { nextw->org[second] = value; }
				else if (i == 0) { nextw->org[first] = value; }

				tempc >>= 1;
			}
			printf("\n");
			count++;
			currword->next = nextw;
			currword = currword->next;
		}
		else if (currdata->type == typeS)/* if the data type is a string*/
		{
			nextc =currdata->value->ch[place];
			while (currdata->value->ch[place] != '\0')
			{
				
				if(currdata->value->ch[place] == '"')
				{

				}
				else
				{
					nextw = (word*)malloc(sizeof(word));
					nextc = currdata->value->ch[place];/*get the next char*/
					tempc =nextc;/* convert it into a number*/
					nextw->con = 0;
					if(tempc == '0')
					{
						tempc = tempc - '0';
					}
					for (i = 11; i >= 0; --i)/* set the 12 bits in a word to be the value of tempc in binary*/
					{
						value = tempc & mask;
						if (i == 11) { nextw->are[second] = value; }
						else if (i == 10) { nextw->are[first] = value; }
						else if (i == 9) { nextw->des[third] = value; }
						else if (i == 8) { nextw->des[second] = value; }
						else if (i == 7) { nextw->des[first] = value; }
						else if (i == 6) { nextw->opcode[fourth] = value; }
						else if (i == 5) { nextw->opcode[third] = value; }
						else if (i == 4) { nextw->opcode[second] = value; }
						else if (i == 3) { nextw->opcode[first] = value; }
						else if (i == 2) { nextw->org[third] = value; }
						else if (i == 1) { nextw->org[second] = value; }
						else if (i == 0) { nextw->org[first] = value; }
					
						tempc >>= 1;
					}
					count++;
					currword->next = nextw;
					currword = currword ->next;
				}
				place++;
			}
		}
		currdata = currdata->next;
	}
	return count;
}

/*this function finds all the places were the label in entry and create a file with the labels name and addres*/
void addentry(entry *headE, label *headS,char *filename)
{
	entry *currE = headE;
	label *currlab = headS;
	FILE *entrypointer;
	char tempname[maxVsize] ;
	strcpy(tempname,filename);
	strtok(tempname,".");
	strcat(tempname, ".ent");
	entrypointer = fopen(tempname, "w+");
	while (currE != NULL)
	{
		while (strcmp(currlab->labelName, currE->labelName) != 0)
		{
			currlab = currlab->next;
		}
		fprintf(entrypointer, "%s \t %d \n", currlab->labelName, currlab->addres);
		currlab = headS;
		currE = currE->next;
	}
	fclose(entrypointer);
}

/*the function add extern finds the words who have extern varible and create a file with the label and the addres we need them*/
void addextern(line_s *headL, word *headW,char *filename)
{
	line_s *currline;
	word *currword = headW;
	subword *currsubword;
	FILE *externpointer = NULL;
	char com[maxVsize];
	char templine[maxVsize];
	char nextc;
	char tempname[maxVsize];
	int i=0;
	int l=0;
	int temp;
	int run = 0 ;
	int IC = 100;
	strcpy(tempname,filename);
	strtok(tempname,".");
	strcat(tempname, ".ext");
	while ((currword != NULL) && (currword->lineNum != 0))
	{
		if (currword->con > 0) /* if the word has ant subwords there might be an extern*/
		{
			currsubword = currword->subword;
			while (currsubword != NULL) /* while we still have subwords to check */
			{			
				if((currsubword->are[first] == 0) && (currsubword->are[second] == 1))/* meeinig its extern*/
				{
								
					if(run == 0)
					{
						externpointer = fopen(tempname, "w+");
					}
					temp = currword->lineNum;
					currline = headL;
					while (currline != NULL && currline->lineNum != temp)/*skip all the non relevent lines*/
					{
						currline = currline->next;
					}
					if (currline == NULL)/* do nothing*/
					{

					}
					else if (currline->lineNum == temp)/* meeining we found the line we needed*/
					{
						if (currword->con == 1)/* then theres only one subword*/
						{
							strcpy(templine ,currline->line);
							nextc = templine[l];
							while (nextc != '\0')/* the lines have only the varibles at that point so we just need to look for the right one */
							{
								com[i] = nextc;
								i++;
								l++;
								nextc =templine[l];
								if(isNspace(nextc))
								{
									while(isNspace(nextc))
									{
										l++;
										nextc =templine[l];
									}
								}
							}
							com[i] = '\0';
							fprintf(externpointer, "%s \t %d \n", com,IC + 1);/*the + 1 is because the varible is a subword for line ==temp */
							
						}
						else if (currword->con == 2)/* then theres 2 subwords*/
						{
							strcpy(templine ,currline->line);
							nextc = templine[l];
							if (currsubword->con == 0)/* meeinig we need the second varible*/
							{
								while (nextc != ',')
								{
									l++;
									nextc =templine[l];
								}
								l++; /* to skip the ','*/
								while (nextc != '\0')
								{
									com[i] = nextc;
									i++;
									l++;
									nextc =templine[l];
									if(isNspace(nextc))
									{
										while(isNspace(nextc))
										{
											l++;
											nextc =templine[l];
										}
									}
								}
								com[i] ='\0';
								fprintf(externpointer, "%s \t %d \n", com, IC+1);
							}
							else if(currsubword->con == 1)/* meeinig we need the first varible*/
							{
								while (nextc!= ',')
								{
									com[i] = nextc;
									i++;
									l++;
									nextc =templine[l];
									if(isNspace(nextc))
									{
										while(isNspace(nextc))
										{
											l++;
											nextc =templine[l];
										}
									}
								}
								com[i] ='\0';
								fprintf(externpointer, "%s \t %d \n", com, IC +1);
							}
						}
					}
					run ++;
				}
				currsubword = currsubword->next;
				l = 0;
				i = 0;
				IC++;
				strcpy(com,"");
				strcpy(templine,"");
			}
		}
		currword = currword->next;
		IC++;
	}
	fclose(externpointer);
}

int isNspace(unsigned char c)
{
	if(c == ' ' || c == '\f' || c == '\r' || c == '\t' || c == '\v')
		return 1;
	
	return 0;

}

void freeDataNode(datal *node)
{
	datal *next;
	datat *value;
	while(next != NULL)
	{
		value = node->value;
		next = node->next;
		if(node->type == typeS)
		{
			free(value->ch);
		}
		free(value);
		free(node);
		node = NULL;
		node = next;
	}
	return;
}

int freeSubwordNode(subword *node)
{
	subword *next;
	int i = 0;
	while(next != NULL)
	{
		next = node->next;
		free(node);
		i++;
		node = NULL;
		node = next;
		
	}
	return i;
}

void freeWordNode(word *node,int tnw)
{
	word *next;
	int run = 0;
	while((next != NULL) && (run < tnw))
	{
		if(node->con > 0)
		{
			run = run +freeSubwordNode(node->subword);
		}
		next = node->next;
		free(node);
		run ++;
		node = NULL;
		node = next;
	}
	return;
}

void freeEntryNode(entry *node)
{
	entry *next;
	while(next != NULL)
	{
		next = node->next;
		free(node->labelName);
		free(node);
		node = NULL;
		node = next;
	}
	return;
}

void freeLabelNode(label *node)
{
	label *next;
	while(next != NULL)
	{
		next = node->next;
		free(node->labelName);
		free(node);
		node = NULL;
		node = next;
	}
	return;
}

void freeLineNode(line_s *node)
{
	line_s *next;
	while(next != NULL)
	{
		next = node->next;
		free(node->line);
		if(node->insFlag != Z)
		{
			free(node->dsex);
		}
		if(node->labFlag == Yflag)
		{
			free(node->labName);
		}
		free(node);
		node = NULL;
		node = next;
	}
	return;
}
