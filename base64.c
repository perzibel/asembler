#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "functions.h"


void baseturn(int arrL[], int arrR[] , FILE *filepointer)
{
	unsigned char base64[64] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
				     'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
 				     'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
				     'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/' };
	
	int pow = 1;
	int place = 5;
	int numL = 0;
	int numR = 0;
	while (place >= 0)/* claculate the sum of bits for the left charcter*/
	{
		numL = (arrL[place] * pow) + numL;
		pow = pow * 2;
		place--;
	}
	pow = 1;
	place = 5;
	while (place >= 0)/*calculate the sum of the bits for the right charcter*/
	{
		numR = (arrR[place] * pow) + numR;
		pow = pow * 2;
		place--;
	}
	fprintf(filepointer, "%c   %c  \n", base64[numL], base64[numR]);

	
}

void addBase64(word *headW, char *filename , int numwords , int numdata)
{

	word *currword = headW;
	subword *currsub;
	int baseL[6];
	int baseR[6];
	int run =0;
	FILE *obfile;
	char tempname[maxVsize] ;
	strcpy(tempname , filename);
	strtok(tempname,".");
	strcat(tempname, ".ob");
	obfile = fopen(tempname, "w+");
	fprintf(obfile, "%d  \t %d\n", numwords, numdata);
	while ((currword != NULL) && (run < (numwords+numdata)))
	{
		baseL[0] = currword->org[first] ;/* create the 6 bits for base 64 left word*/
		baseL[1] = currword->org[second];
		baseL[2] = currword->org[third];
		baseL[3] = currword->opcode[first];
		baseL[4] = currword->opcode[second];
		baseL[5] = currword->opcode[third];
		baseR[0] = currword->opcode[fourth];/* create the 6 bits for base 64 right word*/
		baseR[1] = currword->des[first];
		baseR[2] = currword->des[second];
		baseR[3] = currword->des[third];
		baseR[4] = currword->are[first];
		baseR[5] = currword->are[second];
		
		baseturn(baseL, baseR,obfile);
		memset(baseL, 0,6 * sizeof(int));
		memset(baseR, 0, 6);
		if (currword->con > 0)
		{
			currsub = currword->subword;
			while (currsub != NULL)
			{;
				baseL[0] = currsub->bitL[first];/* create the 6 bits for base 64 left word*/
				baseL[1] = currsub->bitL[second];
				baseL[2] = currsub->bitL[third];
				baseL[3] = currsub->bitL[fourth];
				baseL[4] = currsub->bitL[fifth];
				baseL[5] = currsub->bitR[first];
				baseR[0] = currsub->bitR[second];/* create the 6 bits for base 64 right word*/
				baseR[1] = currsub->bitR[third];
				baseR[2] = currsub->bitR[fourth];
				baseR[3] = currsub->bitR[fifth];
				baseR[4] = currsub->are[first];
				baseR[5] = currsub->are[second];
				baseturn(baseL, baseR, obfile);
				run++;
				currsub = currsub->next;
				memset(baseL, 0, 6 * sizeof(int));
				memset(baseR, 0, 6 * sizeof(int));
			}
		}
		run++;
		currword = currword->next;
	}
	fclose(obfile);

}
