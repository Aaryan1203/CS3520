IDIR =../include
CC=g++
CFLAGS= -I$(IDIR) -g -std=c++11 -O0

ODIR=.

LIBS=-lncurses

_DEPS = 
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = black_friday.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -std=c++11 -c -o $@ $< $(CFLAGS)

black_friday: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f *~ core $(INCDIR)/*~ 
	rm -f black_friday
	rm -f *.o

etags: 
	find . -type f -iname "*.[ch]" | xargs etags --append         
