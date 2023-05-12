/*the function.h header file is so we could have a single place for all functions includeing first and second pass
 all thou the code it self is writen in diffrenct .c files*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "text.h"
#include "bitwize.h"
#include "labellist.h"
#include "datalist.h"
#include "entrylist.h"
#define actionSize 16
#define first 0
#define second 1
#define third 2
#define fourth 3
#define fifth 4
#define maxVsize 30
#define mask 1
#define maxLineSeize 40

/*the function readtext get the file and create a linked list of all the lines for farther use*/
line_s *readtext(int *lineNum, FILE *filePointer,char *filename, int *numOfErr);

/*the function push sets a new node into the line_s list */
void push(line_s *head, char *line, int lineNum, int labFlag,char *labName,char *ins, int insFlag);

/* the function strsize get a string and check its size*/
int strsize(char *str);
	
/*this function check what instraction is given and return its value as int */
int checkins(char *ins);

/* this function check if a given label is already stated*/
int checkLab(char *labName, label *headS);
	
/* this funtion pushs a new label into the label list*/
label *pushL(line_s *current, int *addres,int type);

/* this funtion pushs a new entry label into the entry list*/
entry *pushE(line_s *current,int *addres,int type);

/*this function get a line without the simbol and instraction and push the data into the data list*/
datal *pushD(int *DC, int type, char *line);

/*pushW is a function to push into a list all the first words*/
word *pushW(int *L, char *line, int instract, int *numOfErr, int lineNum, FILE *errorFile,char *filename);

/*checkact is a function that check what action was called and return a number based on the table in the task*/
int checkact(char *line);

/*this function is to update the addres and DC for the data list and the data type labels*/
void updateS(label *headS, datal *headD, int *IC);

/*this function is to find the first data node that has the same DC as a label*/
datal *findnextd(datal *head, int addres);

/* this function (Csubword) is to create the subwords  */
subword *Csubword(word *currword, line_s *currline,label *headS);

/*this function (instract opcode) is to set the opcode for a given word*/
void Iopcode(word *current, int instract);

/*the function firstpass does the first pass on the file we resived by the algoritem of the tesk*/
int firstpass(line_s *headL , datal **headD ,label **headS,word **headW ,entry **headE,char *filename, int *numOfErr , int *IC ,int *DC);

/*the function secondpass does the second pass on the file by the algoritem if the tesk */
int secondpass(line_s *headL, datal *headD, label *headS, word *headW, int *numOfErr, int *IC ,char *filename);

/* the function findCurrWord is to find the word we need to work on based on the line number*/
word *findCurrWord(word *headW, int lineNum);

/* hte function labelA is to find a labels addres and send in back so we could put her binery code into a subword*/
int labelA(label *headS, char *com);

/*the function numOFwords will thell us the number of words before the add of the data words*/
int numOFwords(word *head);

/* the function addData is to add all the data list into the words list as binary and count how mant lines did we add so we'll know for the .ob file */
int addData(word *headW, datal *headD);

/*this function finds all the places were the label in entry and create a file with the labels name and addres*/
void addentry(entry *headE, label *headS,char *filename);

/*the function add extern finds the words who have extern varible and create a file with the label and the addres we need them*/
void addextern(line_s *headL, word *headW,char *filename);

/* the function addBase64 create the object file and sets each 6 bits into an arry so we could clculate the letter we should print in base 64*/
void addBase64(word *headW, char *filename , int numwords , int numdata);

/*isNspace is a function so we could skip spaces and not skip the char '\n' */
int isNspace(unsigned char c);

/*the function free line node is to free all the line_s nodes we created*/
void freeLineNode(line_s *node);

/*the function free label node is to free all the labels we created */
void freeLabelNode(label *node);

/*the function free entry node is to free all the entry nodes we created */
void freeEntryNode(entry *node);

/*the function free subword node is to free all the subwords we created */
int freeSubwordNode(subword *node);

/*the function free word node is to free all the words we created */
void freeWordNode(word *node,int tnw);

/*the function free data node is to free all the data nodes we created */
void freeDataNode(datal *node);

