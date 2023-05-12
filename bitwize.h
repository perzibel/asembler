#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* i desided two create 10 bits devided into 2 parts because of the registers and we may need to split any way.
	in the function sopcode we will solve the problam for big numbers */
struct subword{

	unsigned int are[2];
	unsigned int bitL[5];
	unsigned int bitR[5];
	int con;/*the number of the next words*/
	struct subword *next;

} ;

typedef struct subword subword;

struct word
{

	unsigned int are[2];/*abslute , relocatble , external*/
	unsigned int des[3];/*destention operand*/
	unsigned int opcode[4];
	unsigned int org[3];/* orgin operand*/
	int con;/*how many subwords are they */
	int lineNum;
	int stateDes;
	int stateOrg;
	subword *subword;
	struct word *next;
};

typedef struct word word;
