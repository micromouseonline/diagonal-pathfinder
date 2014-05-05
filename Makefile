CFLAGS=-I.
CC=gcc
ODIR=obj

DEPS = commands.h testdata.h makepath.h
_OBJ = commands.o makepath.o testdata.o main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

diagonal-pathgen: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~