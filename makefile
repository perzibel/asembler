asembler: base64.o firstpass.o secondpass.o gettext.o helpfunctions.o main.o functions.h
	gcc -g base64.o firstpass.o secondpass.o gettext.o helpfunctions.o main.o -o asembler

base64.o:base64.c functions.h 
	gcc -c base64.c  -o base64.o 

firstpass.o:firstpass.c functions.h 
	gcc -c firstpass.c -o firstpass.o 

secondpass.o:secondpass.c functions.h 
	gcc -c secondpass.c -o secondpass.o 

gettext.o:gettext.c functions.h 
	gcc -c -Wall gettext.c -o gettext.o 

helpfunctions.o:helpfunctions.c functions.h 
	gcc -c helpfunctions.c -o helpfunctions.o 

main.o:main.c functions.h 
	gcc -c main.c -o main.o

 
