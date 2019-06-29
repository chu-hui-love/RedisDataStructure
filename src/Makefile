


#app: main.o adlist.o
#	gcc main.o adlist.o -o app

#main.o: adlistmain.c
#	gcc -c adlistmain.c -o main.o

#adlist.o: adlist.c zmalloc.c
#	gcc  adlist.c zmalloc.c -o adlist.o


app: main.o serverlog.o localtime.o
	gcc main.o  serverlog.o localtime.o -o app

main.o: adlistmain.c serverlog.c localtime.c
	gcc adlistmain.c serverlog.c localtime.c -o main.o
	
serverlog.o: serverlog.c localtime.c
	gcc 

