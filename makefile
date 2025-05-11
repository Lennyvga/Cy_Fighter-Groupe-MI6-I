all : exec

combat.o : combat.c combat.h
	gcc -c combat.c -o combat.o

main.o : main.c 
	gcc -c main.c -o main.o

exec : combat.o main.o
	gcc -o exec combat.o main.o 


test:
	echo "Makefile fonctionne "