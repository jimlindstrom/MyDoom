
CC=clang++ 
CCFLAGS=-g

SRC=wad_header.cc \
    wad_directory.cc \
    wad_lump.cc \
    wad_file.cc \
    palette.cc \
    palettes.cc \
    colormap.cc \
    colormaps.cc \
    flat.cc \
    flats.cc \
    sprite.cc \
    sprites.cc \
    test.cc 

all:
	$(CC) $(CCFLAGS) $(SRC) -o test
