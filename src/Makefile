#-----------------------------------------------------------------------------#
#                                                                             #
#   Makefile                                                                  #
#                                                                             #
#-----------------------------------------------------------------------------#

CC=clang

all: mtool

mtool:	mutil.o mapp.o mlog.o mconfig.o main.o
	$(CC) mutil.o mapp.o mlog.o mconfig.o main.o -lmenu -lncurses -o $@

mutil.o:	mutil.c
	$(CC) -c -I/usr/include $< -o $@

mapp.o:	mapp.c
	$(CC) -c -I/usr/include $< -o $@

mlog.o:	mlog.c
	$(CC) -c -I/usr/include $< -o $@

mconfig.o: mconfig.c
	$(CC) -c -I/usr/include $< -o $@

main.o:		main.c
	$(CC) -c -I/usr/include $< -o $@

clean:
	rm *.o
	rm mtool
