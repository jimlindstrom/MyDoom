CC=clang++ 
CFLAGS=-g -Wall -DNORMALUNIX -DLINUX -m32 -Ihdr/
LDFLAGS=
LIBS=-framework Cocoa

BIN=test

SOURCES=$(wildcard src/*.cc)
OBJECTS=$(subst src, obj, $(patsubst %.cc, %.o, $(SOURCES)))


all: $(BIN)

clean:
	rm -f $(OBJECTS) $(BIN)

re: clean all

$(BIN): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) -o $(BIN) $(LIBS)

$(OBJECTS): obj/%.o: src/%.cc
	$(CC) $(CFLAGS) -c $< -o $@
