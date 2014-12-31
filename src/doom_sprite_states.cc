#ifdef SOMETHING_NOT_DEFINED
// generated from a snippet of info.c with:
// 
// cat /tmp/jbl | \
//  sed -e 's/ *//g' | \
//  sed -e 's/  //g' | \
//  sed -e 's/,*\/\///'  | \
//  sed -e 's/^{//' | \
//  sed -e 's/,{/,/'| \
//  sed -e 's/},/,/' | \
//  sed -e 's/}/,/' | \
//  awk -F"," '{print "{" $8 ",\t\"" $1 "\",\t" ($2 % 32768) ",\t" $3 ",\t" ($2 - ($2 % 32768) )/ 32768 ",\t\"" $4 "\",\t" $5 ",\t" $6 ",\t" $7 "},"}' | \
//  sed -e 's/"SPR_/"/' > /tmp/sprite_states.cc

sprite_state_t xyz_states[] = 
{
{true,	STATE_NULL,		"TROO",	0,	-1,	0,	"",			STATE_NULL,		0,	0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},
};

{true,	STATE_LIGHTDONE,	"SHTG",	4,	0,	0,	"A_Light0",		STATE_NULL,		0,	0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},

{true,	STATE_PUNCH,		"PUNG",	0,	1,	0,	"A_WeaponReady",	STATE_PUNCH,		0,	0},
{true,	STATE_PUNCHDOWN,	"PUNG",	0,	1,	0,	"A_Lower",		STATE_PUNCHDOWN,	0,	0},
{true,	STATE_PUNCHUP,		"PUNG",	0,	1,	0,	"A_Raise",		STATE_PUNCHUP,		0,	0},
{true,	STATE_PUNCH1,		"PUNG",	1,	4,	0,	"",			STATE_PUNCH2,		0,	0},
{true,	STATE_PUNCH2,		"PUNG",	2,	4,	0,	"A_Punch",		STATE_PUNCH3,		0,	0},
{true,	STATE_PUNCH3,		"PUNG",	3,	5,	0,	"",			STATE_PUNCH4,		0,	0},
{true,	STATE_PUNCH4,		"PUNG",	2,	4,	0,	"",			STATE_PUNCH5,		0,	0},
{true,	STATE_PUNCH5,		"PUNG",	1,	5,	0,	"A_ReFire",		STATE_PUNCH,		0,	0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},

{true,	STATE_PISTOL,		"PISG",	0,	1,	0,	"A_WeaponReady",	STATE_PISTOL,		0,	0},
{true,	STATE_PISTOLDOWN,	"PISG",	0,	1,	0,	"A_Lower",		STATE_PISTOLDOWN,	0,	0},
{true,	STATE_PISTOLUP,		"PISG",	0,	1,	0,	"A_Raise",		STATE_PISTOLUP,		0,	0},
{true,	STATE_PISTOL1,		"PISG",	0,	4,	0,	"",			STATE_PISTOL2,		0,	0},
{true,	STATE_PISTOL2,		"PISG",	1,	6,	0,	"A_FirePistol",		STATE_PISTOL3,		0,	0},
{true,	STATE_PISTOL3,		"PISG",	2,	4,	0,	"",			STATE_PISTOL4,		0,	0},
{true,	STATE_PISTOL4,		"PISG",	1,	5,	0,	"A_ReFire",		STATE_PISTOL,		0,	0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},

{true,	STATE_PISTOLFLASH,	"PISF",	0,	7,	1,	"A_Light1",		STATE_LIGHTDONE,	0,	0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},

{true,	STATE_SGUN,		"SHTG",	0,	1,	0,	"A_WeaponReady",	STATE_SGUN,		0,	0},
{true,	STATE_SGUNDOWN,		"SHTG",	0,	1,	0,	"A_Lower",		STATE_SGUNDOWN,		0,	0},
{true,	STATE_SGUNUP,		"SHTG",	0,	1,	0,	"A_Raise",		STATE_SGUNUP,		0,	0},
{true,	STATE_SGUN1,		"SHTG",	0,	3,	0,	"",			STATE_SGUN2,		0,	0},
{true,	STATE_SGUN2,		"SHTG",	0,	7,	0,	"A_FireShotgun",	STATE_SGUN3,		0,	0},
{true,	STATE_SGUN3,		"SHTG",	1,	5,	0,	"",			STATE_SGUN4,		0,	0},
{true,	STATE_SGUN4,		"SHTG",	2,	5,	0,	"",			STATE_SGUN5,		0,	0},
{true,	STATE_SGUN5,		"SHTG",	3,	4,	0,	"",			STATE_SGUN6,		0,	0},
{true,	STATE_SGUN6,		"SHTG",	2,	5,	0,	"",			STATE_SGUN7,		0,	0},
{true,	STATE_SGUN7,		"SHTG",	1,	5,	0,	"",			STATE_SGUN8,		0,	0},
{true,	STATE_SGUN8,		"SHTG",	0,	3,	0,	"",			STATE_SGUN9,		0,	0},
{true,	STATE_SGUN9,		"SHTG",	0,	7,	0,	"A_ReFire",		STATE_SGUN,		0,	0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},

{true,	STATE_SGUNFLASH1,	"SHTF",	0,	4,	1,	"A_Light1",		STATE_SGUNFLASH2,	0,	0},
{true,	STATE_SGUNFLASH2,	"SHTF",	1,	3,	1,	"A_Light2",		STATE_LIGHTDONE,	0,	0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},

{true,	STATE_DSGUN,		"SHT2",	0,	1,	0,	"A_WeaponReady",	STATE_DSGUN,		0,	0},
{true,	STATE_DSGUNDOWN,	"SHT2",	0,	1,	0,	"A_Lower",		STATE_DSGUNDOWN,	0,	0},
{true,	STATE_DSGUNUP,		"SHT2",	0,	1,	0,	"A_Raise",		STATE_DSGUNUP,		0,	0},
{true,	STATE_DSGUN1,		"SHT2",	0,	3,	0,	"",			STATE_DSGUN2,		0,	0},
{true,	STATE_DSGUN2,		"SHT2",	0,	7,	0,	"A_FireShotgun2",	STATE_DSGUN3,		0,	0},
{true,	STATE_DSGUN3,		"SHT2",	1,	7,	0,	"",			STATE_DSGUN4,		0,	0},
{true,	STATE_DSGUN4,		"SHT2",	2,	7,	0,	"A_CheckReload",	STATE_DSGUN5,		0,	0},
{true,	STATE_DSGUN5,		"SHT2",	3,	7,	0,	"A_OpenShotgun2",	STATE_DSGUN6,		0,	0},
{true,	STATE_DSGUN6,		"SHT2",	4,	7,	0,	"",			STATE_DSGUN7,		0,	0},
{true,	STATE_DSGUN7,		"SHT2",	5,	7,	0,	"A_LoadShotgun2",	STATE_DSGUN8,		0,	0},
{true,	STATE_DSGUN8,		"SHT2",	6,	6,	0,	"",			STATE_DSGUN9,		0,	0},
{true,	STATE_DSGUN9,		"SHT2",	7,	6,	0,	"A_CloseShotgun2",	STATE_DSGUN10,		0,	0},
{true,	STATE_DSGUN10,		"SHT2",	0,	5,	0,	"A_ReFire",		STATE_DSGUN,		0,	0},
{true,	STATE_DSNR1,		"SHT2",	1,	7,	0,	"",			STATE_DSNR2,		0,	0},
{true,	STATE_DSNR2,		"SHT2",	0,	3,	0,	"",			STATE_DSGUNDOWN,	0,	0},
{true,	STATE_DSGUNFLASH1,	"SHT2",	8,	5,	1,	"A_Light1",		STATE_DSGUNFLASH2,	0,	0},
{true,	STATE_DSGUNFLASH2,	"SHT2",	9,	4,	1,	"A_Light2",		STATE_LIGHTDONE,	0,	0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},

{true,	STATE_CHAIN,		"CHGG",	0,	1,	0,	"A_WeaponReady",	STATE_CHAIN,		0,	0},
{true,	STATE_CHAINDOWN,	"CHGG",	0,	1,	0,	"A_Lower",		STATE_CHAINDOWN,	0,	0},
{true,	STATE_CHAINUP,		"CHGG",	0,	1,	0,	"A_Raise",		STATE_CHAINUP,		0,	0},
{true,	STATE_CHAIN1,		"CHGG",	0,	4,	0,	"A_FireCGun",		STATE_CHAIN2,		0,	0},
{true,	STATE_CHAIN2,		"CHGG",	1,	4,	0,	"A_FireCGun",		STATE_CHAIN3,		0,	0},
{true,	STATE_CHAIN3,		"CHGG",	1,	0,	0,	"A_ReFire",		STATE_CHAIN,		0,	0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},

{true,	STATE_CHAINFLASH1,	"CHGF",	0,	5,	1,	"A_Light1",		STATE_LIGHTDONE,	0,	0},
{true,	STATE_CHAINFLASH2,	"CHGF",	1,	5,	1,	"A_Light2",		STATE_LIGHTDONE,	0,	0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},

{true,	STATE_MISSILE,		"MISG",	0,	1,	0,	"A_WeaponReady",	STATE_MISSILE,		0,	0},
{true,	STATE_MISSILEDOWN,	"MISG",	0,	1,	0,	"A_Lower",		STATE_MISSILEDOWN,	0,	0},
{true,	STATE_MISSILEUP,	"MISG",	0,	1,	0,	"A_Raise",		STATE_MISSILEUP,	0,	0},
{true,	STATE_MISSILE1,		"MISG",	1,	8,	0,	"A_GunFlash",		STATE_MISSILE2,		0,	0},
{true,	STATE_MISSILE2,		"MISG",	1,	12,	0,	"A_FireMissile",	STATE_MISSILE3,		0,	0},
{true,	STATE_MISSILE3,		"MISG",	1,	0,	0,	"A_ReFire",		STATE_MISSILE,		0,	0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},

{true,	STATE_MISSILEFLASH1,	"MISF",	0,	3,	1,	"A_Light1",		STATE_MISSILEFLASH2,	0,	0},
{true,	STATE_MISSILEFLASH2,	"MISF",	1,	4,	1,	"",			STATE_MISSILEFLASH3,	0,	0},
{true,	STATE_MISSILEFLASH3,	"MISF",	2,	4,	1,	"A_Light2",		STATE_MISSILEFLASH4,	0,	0},
{true,	STATE_MISSILEFLASH4,	"MISF",	3,	4,	1,	"A_Light2",		STATE_LIGHTDONE,	0,	0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},

{true,	STATE_SAW,		"SAWG",	2,	4,	0,	"A_WeaponReady",	STATE_SAWB,		0,	0},
{true,	STATE_SAWB,		"SAWG",	3,	4,	0,	"A_WeaponReady",	STATE_SAW,		0,	0},
{true,	STATE_SAWDOWN,		"SAWG",	2,	1,	0,	"A_Lower",		STATE_SAWDOWN,		0,	0},
{true,	STATE_SAWUP,		"SAWG",	2,	1,	0,	"A_Raise",		STATE_SAWUP,		0,	0},
{true,	STATE_SAW1,		"SAWG",	0,	4,	0,	"A_Saw",		STATE_SAW2,		0,	0},
{true,	STATE_SAW2,		"SAWG",	1,	4,	0,	"A_Saw",		STATE_SAW3,		0,	0},
{true,	STATE_SAW3,		"SAWG",	1,	0,	0,	"A_ReFire",		STATE_SAW,		0,	0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},

{true,	STATE_PLASMA,		"PLSG",	0,	1,	0,	"A_WeaponReady",	STATE_PLASMA,		0,	0},
{true,	STATE_PLASMADOWN,	"PLSG",	0,	1,	0,	"A_Lower",		STATE_PLASMADOWN,	0,	0},
{true,	STATE_PLASMAUP,		"PLSG",	0,	1,	0,	"A_Raise",		STATE_PLASMAUP,		0,	0},
{true,	STATE_PLASMA1,		"PLSG",	0,	3,	0,	"A_FirePlasma",		STATE_PLASMA2,		0,	0},
{true,	STATE_PLASMA2,		"PLSG",	1,	20,	0,	"A_ReFire",		STATE_PLASMA,		0,	0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},

{true,	STATE_PLASMAFLASH1,	"PLSF",	0,	4,	1,	"A_Light1",		STATE_LIGHTDONE,	0,	0},
{true,	STATE_PLASMAFLASH2,	"PLSF",	1,	4,	1,	"A_Light1",		STATE_LIGHTDONE,	0,	0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},

{true,	STATE_BFG,		"BFGG",	0,	1,	0,	"A_WeaponReady",	STATE_BFG,		0,	0},
{true,	STATE_BFGDOWN,		"BFGG",	0,	1,	0,	"A_Lower",		STATE_BFGDOWN,		0,	0},
{true,	STATE_BFGUP,		"BFGG",	0,	1,	0,	"A_Raise",		STATE_BFGUP,		0,	0},
{true,	STATE_BFG1,		"BFGG",	0,	20,	0,	"A_BFGsound",		STATE_BFG2,		0,	0},
{true,	STATE_BFG2,		"BFGG",	1,	10,	0,	"A_GunFlash",		STATE_BFG3,		0,	0},
{true,	STATE_BFG3,		"BFGG",	1,	10,	0,	"A_FireBFG",		STATE_BFG4,		0,	0},
{true,	STATE_BFG4,		"BFGG",	1,	20,	0,	"A_ReFire",		STATE_BFG,		0,	0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},

{true,	STATE_BFGFLASH1,	"BFGF",	0,	11,	1,	"A_Light1",		STATE_BFGFLASH2,	0,	0},
{true,	STATE_BFGFLASH2,	"BFGF",	1,	6,	1,	"A_Light2",		STATE_LIGHTDONE,	0,	0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},

{true,	STATE_BRAINEXPLODE1,	"MISL",	1,	10,	1,	"",			STATE_BRAINEXPLODE2,	0,	0},
{true,	STATE_BRAINEXPLODE2,	"MISL",	2,	10,	1,	"",			STATE_BRAINEXPLODE3,	0,	0},
{true,	STATE_BRAINEXPLODE3,	"MISL",	3,	10,	1,	"A_BrainExplode",	STATE_NULL,		0,	0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},

{true,	STATE_STALAG,		"SMT2",	0,	-1,	0,	"",			STATE_NULL,		0,	0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},

{true,	STATE_DEADTORSO,	"PLAY",	13,	-1,	0,	"",			STATE_NULL,		0,	0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},

{true,	STATE_DEADBOTTOM,	"PLAY",	18,	-1,	0,	"",			STATE_NULL,		0,	0},
{false, STATE_NULL,             "",     0,      0,      0,      "",                     STATE_NULL,             0,      0},

#endif
