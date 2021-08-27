.DEFAULT_GOAL := all

IDIR := include
ODIR := obj
SDIR := src
BDIR := bin
CC := gcc
CFLAGS := -I$(IDIR)

_DEPS = connection.h send.h request.h html.h util.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o connection.o send.o request.o html.o util.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean all server debug release

all: server

server: $(OBJ)
	$(CC) -o $(BDIR)/$@ $^ $(CFLAGS)

debug: CFLAGS += -ggdb
debug: all

release: CFLAGS += -s -O2
release: all

clean:
	rm -f $(ODIR)/*.o $(BDIR)/server

run:
	./bin/server