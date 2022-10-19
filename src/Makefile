#-----------------------------------------------------------------------------#
#                                                                             #
#   Makefile                                                                  #
#                                                                             #
#-----------------------------------------------------------------------------#

CC=clang

all: mytool

mytool:	mconfig.o main.o
	$(CC) mconfig.o main.o -lmenu -lncurses -o $@

mconfig.o: mconfig.c
	$(CC) -c -I/usr/include $< -o $@

main.o:		main.c
	$(CC) -c -I/usr/include $< -o $@

clean:
	rm *.o
	rm mytool
