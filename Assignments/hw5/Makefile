CC = g++
CFLAGS = -I$(IDIR) -g -std=c++11
LDFLAGS = $(LIBS)

IDIR = .
ODIR = .

LIBS = -lncurses

_DEPS = ant.hpp cell.hpp critter.hpp doodlebug.hpp simulation.hpp grid.hpp worker.hpp queen.hpp male.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = ant.o cell.o critter.o doodlebug.o simulation.o grid.o worker.o main.o queen.o male.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

hw5: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(ODIR)/*.o hw5

.PHONY: etags
etags:
	find . -type f -iname "*.[ch]" | xargs etags --append
