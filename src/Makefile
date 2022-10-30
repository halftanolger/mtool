#-----------------------------------------------------------------------------#
#                                                                             #
#   Makefile                                                                  #
#                                                                             #
#-----------------------------------------------------------------------------#

CC=clang

all: mtool

mtool:	mmenubar.o mmenu.o mutil.o mapp.o mlog.o mconfig.o main.o
	$(CC) mmenubar.o mmenu.o mutil.o mapp.o mlog.o mconfig.o main.o -lmenu -lncurses -o $@

mmenubar.o:	mmenubar.c
	$(CC) -c -I/usr/include $< -o $@

mmenu.o:	mmenu.c
	$(CC) -c -I/usr/include $< -o $@

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
