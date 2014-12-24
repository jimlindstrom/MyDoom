#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "thing_definitions.h"

/*typedef struct
{
  uint16_t type_num_dec;
  char     type_num_hex[5];  	-- doesn't need to be persisted
  char     version[3];		-- doesn't need to be persisted
  uint16_t radius;
  char     sprite_prefix[6];
  char     sequence[8];
  char     klass[8];
  char     description[40];
} thing_definition;*/

static thing_definition artifacts[] = 
{
  {2023,	"7E7",	"R",	20,	"PSTR",	"A",		"AP",	"Berserk"},
  {2026,	"7EA",	"S",	20,	"PMAP",	"ABCDCB",	"AP1",	"Computer map"},
  {2014,	"7DE",	"S",	20,	"BON1",	"ABCDCB",	"AP",	"Health potion"},
  {2024,	"7E8",	"S",	20,	"PINS",	"ABCD",		"AP",	"Invisibility"},
  {2022,	"7E6",	"R",	20,	"PINV",	"ABCD",		"AP",	"Invulnerability"},
  {2045,	"7FD",	"S",	20,	"PVIS",	"AB",		"AP",	"Light amplification visor"},
  {83,		"53",	"2",	20,	"MEGA",	"ABCD",		"AP",	"Megasphere"},
  {2013,	"7DD",	"S",	20,	"SOUL",	"ABCDCB",	"AP",	"Soul sphere"},
  {2015,	"7DF",	"S",	20,	"BON2",	"ABCDCB",	"AP",	"Spiritual armor"},
  {0xffff,	"",	"",	0,	"",	"",		"",	"END OF LIST"},
};

static thing_definition power_ups[] = 
{
  {8,		"8",	"S",	20,	"BPAK",	"A",	"P",	"Backpack"},
  {2019,	"7E3",	"S",	20,	"ARM2",	"AB",	"P1",	"Blue armor"},
  {2018,	"7E2",	"S",	20,	"ARM1",	"AB",	"P2",	"Green armor"},
  {2012,	"7DC",	"S",	20,	"MEDI",	"A",	"P3",	"Medikit"},
  {2025,	"7E9",	"S",	20,	"SUIT",	"A",	"P",	"Radiation suit"},
  {2011,	"7DB",	"S",	20,	"STIM",	"A",	"P3",	"Stimpack"},
  {0xffff,	"",	"",	0,	"",	"",	"",	"END OF LIST"},
};


static thing_definition weapons[] = 
{
  {2006,	"7D6",	"R",	20,	"BFUG",	"A",	"WP1",	"BFG 9000"},
  {2002,	"7D2",	"S",	20,	"MGUN",	"A",	"WP1",	"Chaingun"},
  {2005,	"7D5",	"S",	20,	"CSAW",	"A",	"WP2",	"Chainsaw"},
  {2004,	"7D4",	"R",	20,	"PLAS",	"A",	"WP1",	"Plasma rifle"},
  {2003,	"7D3",	"S",	20,	"LAUN",	"A",	"WP1",	"Rocket launcher"},
  {2001,	"7D1",	"S",	20,	"SHOT",	"A",	"WP1",	"Shotgun"},
  {8,		"52",	"2",	20,	"SGN2",	"A",	"WP1",	"Super shotgun"},
  {0xffff,	"",	"",	0,	"",	"",	"",	"END OF LIST"},
};

static thing_definition ammo[] = 
{
  {2007,	"7D7",	"S",	20,	"CLIP",	"A",	"P1",	"Ammo clip"},
  {2048,	"800",	"S",	20,	"AMMO",	"A",	"P1",	"Box of ammo"},
  {2046,	"7FE",	"S",	20,	"BROK",	"A",	"P1",	"Box of rockets"},
  {2049,	"801",	"S",	20,	"SBOX",	"A",	"P1",	"Box of shells"},
  {2047,	"7FF",	"R",	20,	"CELL",	"A",	"P1",	"Cell charge"},
  {17,		"11",	"R",	20,	"CELP",	"A",	"P1",	"Cell charge pack"},
  {2010,	"7DA",	"S",	20,	"ROCK",	"A",	"P1",	"Rocket"},
  {2008,	"7D8",	"S",	20,	"SHEL",	"A",	"P1",	"Shotgun shells"},
  {0xffff,	"",	"",	0,	"",	"",	"",	"END OF LIST"},
};

static thing_definition keys[] = 
{
  {5,		"5",	"S",	20,	"BKEY",	"AB",	"P",	"Blue keycard"},
  {40,		"28",	"R",	20,	"BSKU",	"AB",	"P",	"Blue skull key"},
  {13,		"D",	"S",	20,	"RKEY",	"AB",	"P",	"Red keycard"},
  {38,		"26",	"R",	20,	"RSKU",	"AB",	"P",	"Red skull key"},
  {6,		"6",	"S",	20,	"YKEY",	"AB",	"P",	"Yellow keycard"},
  {39,		"27",	"R",	20,	"YSKU",	"AB",	"P",	"Yellow skull key"},
  {0xffff,	"",	"",	0,	"",	"",	"",	"END OF LIST"},
};

static thing_definition monsters[] = 
{
  {68,		"44",	"2",	64,	"BSPI",	"+",	"MO",	"Arachnotron"},
  {64,		"40",	"2",	20,	"VILE",	"+",	"MO",	"Arch-Vile"},
  {3003,	"BBB",	"S",	24,	"BOSS",	"+",	"MO",	"Baron of Hell"},
  {3005,	"BBD",	"R",	31,	"HEAD",	"+",	"MO^",	"Cacodemon"},
  {65,		"41",	"2",	20,	"CPOS",	"+",	"MO",	"Chaingunner"},
  {72,		"48",	"2",	16,	"KEEN",	"A+",	"MO^",	"Commander Keen"},
  {16,		"10",	"R",	40,	"CYBR",	"+",	"MO",	"Cyberdemon"},
  {3002,	"BBA",	"S",	30,	"SARG",	"+",	"MO",	"Demon"},
  {3004,	"BBC",	"S",	20,	"POSS",	"+",	"MO",	"Former Human Trooper"},
  {9,		"9",	"S",	20,	"SPOS",	"+",	"MO",	"Former Human Sergeant"},
  {69,		"45",	"2",	24,	"BOS2",	"+",	"MO",	"Hell Knight"},
  {3001,	"BB9",	"S",	20,	"TROO",	"+",	"MO",	"Imp"},
  {3006,	"BBE",	"R",	16,	"SKUL",	"+",	"M1O^",	"Lost Soul"},
  {67,		"43",	"2",	48,	"FATT",	"+",	"MO",	"Mancubus"},
  {71,		"47",	"2",	31,	"PAIN",	"+",	"MO^",	"Pain Elemental"},
  {66,		"42",	"2",	20,	"SKEL",	"+",	"MO",	"Revenant"},
  {58,		"3A",	"S",	30,	"SARG",	"+",	"MO",	"Spectre"},
  {7,		"7",	"R",	128,	"SPID",	"+",	"MO",	"Spider Mastermind"},
  {84,		"54",	"2",	20,	"SSWV",	"+",	"MO",	"Wolfenstein SS"},
  {0xffff,	"",	"",	0,	"",	"",	"",	"END OF LIST"},
};

static thing_definition obstacles[] = 
{
  {2035,	"7F3",	"S",	10,	"BAR1",	"AB+",	"O",	"Barrel"},
  {70,		"46",	"2",	10,	"FCAN",	"ABC",	"O",	"Burning barrel"},
  {43,		"2B",	"R",	16,	"TRE1",	"A",	"O",	"Burnt tree"},
  {35,		"23",	"S",	16,	"CBRA",	"A",	"O",	"Candelabra"},
  {41,		"29",	"R",	16,	"CEYE",	"ABCB",	"O",	"Evil eye"},
  {28,		"1C",	"R",	16,	"POL2",	"A",	"O",	"Five skulls \"shish kebab\""},
  {42,		"2A",	"R",	16,	"FSKU",	"ABC",	"O",	"Floating skull"},
  {2028,	"7EC",	"S",	16,	"COLU",	"A",	"O",	"Floor lamp"},
  {53,		"35",	"R",	16,	"GOR5",	"A",	"O^",	"Hanging leg"},
  {52,		"34",	"R",	16,	"GOR4",	"A",	"O^",	"Hanging pair of legs"},
  {78,		"4E",	"2",	16,	"HDB6",	"A",	"O^",	"Hanging torso, brain removed"},
  {75,		"4B",	"2",	16,	"HDB3",	"A",	"O^",	"Hanging torso, looking down"},
  {77,		"4D",	"2",	16,	"HDB5",	"A",	"O^",	"Hanging torso, looking up"},
  {76,		"4C",	"2",	16,	"HDB4",	"A",	"O^",	"Hanging torso, open skull"},
  {50,		"32",	"R",	16,	"GOR2",	"A",	"O^",	"Hanging victim, arms out"},
  {74,		"4A",	"2",	16,	"HDB2",	"A",	"O^",	"Hanging victim, guts and brain removed"},
  {73,		"49",	"2",	16,	"HDB1",	"A",	"O^",	"Hanging victim, guts removed"},
  {51,		"33",	"R",	16,	"GOR3",	"A",	"O^",	"Hanging victim, one-legged"},
  {49,		"31",	"R",	16,	"GOR1",	"ABCB",	"O^",	"Hanging victim, twitching"},
  {25,		"19",	"R",	16,	"POL1",	"A",	"O",	"Impaled human"},
  {54,		"36",	"R",	32,	"TRE2",	"A",	"O",	"Large brown tree"},
  {29,		"1D",	"R",	16,	"POL3",	"AB",	"O",	"Pile of skulls and candles"},
  {55,		"37",	"R",	16,	"SMBT",	"ABCD",	"O",	"Short blue firestick"},
  {56,		"38",	"R",	16,	"SMGT",	"ABCD",	"O",	"Short green firestick"},
  {31,		"1F",	"R",	16,	"COL2",	"A",	"O",	"Short green pillar"},
  {36,		"24",	"R",	16,	"COL5",	"AB",	"O",	"Short green pillar with beating heart"},
  {57,		"39",	"R",	16,	"SMRT",	"ABCD",	"O",	"Short red firestick"},
  {33,		"21",	"R",	16,	"COL4",	"A",	"O",	"Short red pillar"},
  {37,		"25",	"R",	16,	"COL6",	"A",	"O",	"Short red pillar with skull"},
  {86,		"56",	"2",	16,	"TLP2",	"ABCD",	"O",	"Short techno floor lamp"},
  {27,		"1B",	"R",	16,	"POL4",	"A",	"O",	"Skull on a pole"},
  {47,		"2F",	"R",	16,	"SMIT",	"A",	"O",	"Stalagmite"},
  {44,		"2C",	"R",	16,	"TBLU",	"ABCD",	"O",	"Tall blue firestick"},
  {45,		"2D",	"R",	16,	"TGRN",	"ABCD",	"O",	"Tall green firestick"},
  {30,		"1E",	"R",	16,	"COL1",	"A",	"O",	"Tall green pillar"},
  {46,		"2E",	"S",	16,	"TRED",	"ABCD",	"O",	"Tall red firestick"},
  {32,		"20",	"R",	16,	"COL3",	"A",	"O",	"Tall red pillar"},
  {85,		"55",	"2",	16,	"TLMP",	"ABCD",	"O",	"Tall techno floor lamp"},
  {48,		"30",	"S",	16,	"ELEC",	"A",	"O",	"Tall techno pillar"},
  {26,		"1A",	"R",	16,	"POL6",	"AB",	"O",	"Twitching impaled human"},
  {0xffff,	"",	"",	0,	"",	"",	"",	"END OF LIST"},
};

static thing_definition decorations[] = 
{
  {10,		"A",	"S",	16,	"PLAY",	"W",	"",	"Bloody mess"},
  {12,		"C",	"S",	16,	"PLAY",	"W",	"",	"Bloody mess"},
  {34,		"22",	"S",	16,	"CAND",	"A",	"",	"Candle"},
  {22,		"16",	"R",	31,	"HEAD",	"L",	"",	"Dead cacodemon"},
  {21,		"15",	"S",	30,	"SARG",	"N",	"",	"Dead demon"},
  {18,		"12",	"S",	20,	"POSS",	"L",	"",	"Dead former human"},
  {19,		"13",	"S",	20,	"SPOS",	"L",	"",	"Dead former sergeant"},
  {20,		"14",	"S",	20,	"TROO",	"M",	"",	"Dead imp"},
  {23,		"17",	"R",	16,	"SKUL",	"K",	"",	"Dead lost soul (invisible)"},
  {15,		"F",	"S",	16,	"PLAY",	"N",	"",	"Dead player"},
  {62,		"3E",	"R",	16,	"GOR5",	"A",	"^",	"Hanging leg"},
  {60,		"3C",	"R",	16,	"GOR4",	"A",	"^",	"Hanging pair of legs"},
  {59,		"3B",	"R",	16,	"GOR2",	"A",	"^",	"Hanging victim, arms out"},
  {61,		"3D",	"R",	16,	"GOR3",	"A",	"^",	"Hanging victim, one-legged"},
  {63,		"3F",	"R",	16,	"GOR1",	"ABCB",	"^",	"Hanging victim, twitching"},
  {79,		"4F",	"2",	16,	"POB1",	"A",	"",	"Pool of blood"},
  {80,		"50",	"2",	16,	"POB2",	"A",	"",	"Pool of blood"},
  {24,		"18",	"S",	16,	"POL5",	"A",	"",	"Pool of blood and flesh"},
  {81,		"51",	"2",	16,	"BRS1",	"A",	"",	"Pool of brains"},
  {0xffff,	"",	"",	0,	"",	"",	"",	"END OF LIST"},
};

static thing_definition other_things[] = 
{
  {88,		"58",	"2",	16,	"BBRN",	"+",	"O1",	"Boss Brain"},
  {11,		"B",	"S",	20,	"none",	"-",	"",	"Deathmatch start"},
  {1,		"1",	"S",	16,	"PLAY",	"+",	"",	"Player 1 start"},
  {2,		"2",	"S",	16,	"PLAY",	"+",	"",	"Player 2 start"},
  {3,		"3",	"S",	16,	"PLAY",	"+",	"",	"Player 3 start"},
  {4,		"4",	"S",	16,	"PLAY",	"+",	"",	"Player 4 start"},
  {89,		"59",	"2",	20,	"none2","-",	"",	"Spawn shooter"},
  {87,		"57",	"2",	0,	"none3","-",	"",	"Spawn spot"},
  {14,		"E",	"S",	20,	"none4","-",	"",	"Teleport landing"},
  {0xffff,	"",	"",	0,	"",	"",	"",	"END OF LIST"},
};

static thing_definition *defn_lists[] = 
{
  artifacts,
  power_ups,
  weapons,
  ammo,
  keys,
  monsters,
  obstacles,
  decorations,
  other_things,
};

thing_definition const *thing_definition_lookup(uint16_t type_num_dec)
{
  uint16_t num_defn_lists = sizeof(defn_lists) / sizeof(defn_lists[0]);
  thing_definition *defn;
  int i;

  for(i=0; i<num_defn_lists; i++)
  {
    for(defn = defn_lists[i]; defn->type_num_dec!=0xffff; defn++)
    {
      if(defn->type_num_dec == type_num_dec)
      {
        return defn;
      }
    }
  }
  
  printf("ERROR: could not find thing definition for type %d\n", type_num_dec);
  exit(0);
  return NULL;
}
