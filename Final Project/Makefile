IDIR = .
CC = g++
CFLAGS = -I$(IDIR) -g -O0 -std=c++11

ODIR = .
LIBS = -lncurses

_DEPS = user.hpp event.hpp public_event.hpp private_event.hpp facility.hpp facility_manager.hpp enums.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o user.o event.o public_event.o private_event.o facility.o facility_manager.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: main

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f *~ core $(IDIR)/*~
	rm -f main
	rm -f $(ODIR)/*.o

etags:
	find . -type f -iname "*.[ch]" | xargs etags --append