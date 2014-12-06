
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
    src/picture_data.cc \
    src/sprite.cc \
    src/sprites.cc \
    src/patch.cc \
    src/patches.cc \
    src/patch_names_lump.cc \
    src/texture_lump.cc \
    src/wall_texture.cc \
    src/wall_textures.cc \
    src/thing.cc \
    src/linedef.cc \
    src/sidedef.cc \
    src/vertex.cc \
    src/segment.cc \
    src/subsector.cc \
    src/node.cc \
    src/sector.cc \
    src/reject_table.cc \
    src/block_map.cc \
    src/episode_map.cc \
    src/episode_maps.cc \
    src/game.cc \
    src/main.cc 

all:
	$(CC) $(CCFLAGS) $(SRC) -o test
