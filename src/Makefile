


app: main.o adlist.o
	gcc main.o adlist.o -o app

main.o: adlistmain.c
	gcc -c adlistmain.c -o main.o

adlist.o: adlist.c zmalloc.c
	gcc  adlist.c zmalloc.c -o adlist.o

