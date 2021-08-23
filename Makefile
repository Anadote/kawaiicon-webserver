.DEFAULT_GOAL := all

IDIR := include
ODIR := obj
SDIR := src
BDIN := bin
CC := gcc
CFLAGS := -I$(IDIR)

_DEPS = connection.h send.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o connection.o send.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean all

all: server

server: $(OBJ)
	$(CC) -o $(BDIN)/$@ $^ $(CFLAGS)

debug: CFLAGS += -ggdb -O0
debug: all

clean:
	rm -f $(ODIR)/*.o $(BDIN)/server