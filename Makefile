
CC=clang++ 
CCFLAGS=-g -Ihdr/

SRC=src/wad_header.cc \
    src/wad_directory.cc \
    src/wad_lump.cc \
    src/wad_file.cc \
    src/palette.cc \
    src/palettes.cc \
    src/colormap.cc \
    src/colormaps.cc \
    src/flat.cc \
    src/flats.cc \
    src/sprite.cc \
    src/sprites.cc \
    src/texture_lump.cc \
    src/wall_texture.cc \
    src/wall_textures.cc \
    src/test.cc 

all:
	$(CC) $(CCFLAGS) $(SRC) -o test
