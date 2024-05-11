IDIR =../include
CC=g++
CFLAGS= -I$(IDIR) -g -O0

ODIR=.

LIBS=-lncurses

_DEPS = 
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ1 = file1.o
_OBJ2 = file2.o
_OBJ3 = file3.o
_OBJ4 = compoundInterest.o
_OBJ5 = statistics.o
_OBJ6 = findAndReplace.o

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -std=c++11 -c -o $@ $< $(CFLAGS)

all: file1 file2 file3 compoundInterest statistics findAndReplace

	
file1: $(_OBJ1)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

file2: $(_OBJ2)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

file3: $(_OBJ3)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

compoundInterest: $(_OBJ4)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

statistics: $(_OBJ5)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

findAndReplace: $(_OBJ6)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f *~ core $(INCDIR)/*~ 
	rm -f file1
	rm -f file2
	rm -f file3
	rm -f compoundInterest
	rm -f statistics
	rm -f findAndReplace
	rm -f *.o

etags: 
	find . -type f -iname "*.[ch]" | xargs etags --append 