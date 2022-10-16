#-----------------------------------------------------------------------------#
#                                                                             #
#   Makefile                                                                  #
#                                                                             #
#-----------------------------------------------------------------------------#

CXX=c++
RM=rm -f
CPPFLAGS=-g
LDFLAGS=-g
LDLIBS=-lncurses -lc++

all: mytool

mytool: main.o mtool.o 
	$(CXX) $(LDFLAGS) -o mytool main.o mtool.o $(LDLIBS)

main.o:	 main.cpp

mtool.o: mtool.cpp mtool.h 

clean:
	$(RM) *.o

distclean: clean
	$(RM) mytool
