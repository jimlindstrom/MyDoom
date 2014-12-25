CC=clang++ 
CFLAGS=-g -O2 -Wall -DNORMALUNIX -DLINUX -m32 -Ihdr/
LDFLAGS=
LIBS=-framework Cocoa

BIN=mydoom

CC_SOURCES=$(wildcard src/*.cc)
CC_OBJECTS=$(subst src, obj, $(patsubst %.cc, %.occ, $(CC_SOURCES)))

M_SOURCES=$(wildcard src/*.m)
M_OBJECTS=$(subst src, obj, $(patsubst %.m, %.om, $(M_SOURCES)))

SOURCES=$(CC_SOURCES) $(M_SOURCES)
OBJECTS=$(CC_OBJECTS) $(M_OBJECTS)


all: $(BIN)

clean:
	rm -f $(OBJECTS) $(BIN)

re: clean all

$(BIN): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) -o $(BIN) $(LIBS)

$(CC_OBJECTS): obj/%.occ: src/%.cc
	$(CC) $(CFLAGS) -c $< -o $@

$(M_OBJECTS): obj/%.om: src/%.m
	$(CC) $(CFLAGS) -c $< -o $@
