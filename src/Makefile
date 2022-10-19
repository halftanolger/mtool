#-----------------------------------------------------------------------------#
#                                                                             #
#   Makefile                                                                  #
#                                                                             #
#-----------------------------------------------------------------------------#

CC=clang

all: mtool

mtool:	mlog.o mconfig.o main.o
	$(CC) mlog.o mconfig.o main.o -lmenu -lncurses -o $@

mlog.o:	mlog.c
	$(CC) -c -I/usr/include $< -o $@

mconfig.o: mconfig.c
	$(CC) -c -I/usr/include $< -o $@

main.o:		main.c
	$(CC) -c -I/usr/include $< -o $@

clean:
	rm *.o
	rm mtool
