/*
Copyright (C) 1996-2001 Id Software, Inc.
Copyright (C) 2002-2009 John Fitzgibbons and others
Copyright (C) 2007-2008 Kristian Duske
Copyright (C) 2010-2019 QuakeSpasm developers

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#ifndef QUAKEDEFS_H
#define QUAKEDEFS_H

// quakedef.h -- primary header for client

#define	QUAKE_GAME		// as opposed to utilities

#define	VERSION			1.09
#define	GLQUAKE_VERSION		1.00
#define	D3DQUAKE_VERSION	0.01
#define	WINQUAKE_VERSION	0.996
#define	LINUX_VERSION		1.30
#define	X11_VERSION		1.10

#define	FITZQUAKE_VERSION	0.85	//johnfitz
#define	QUAKESPASM_VERSION	0.97
#define	QUAKESPASM_VER_PATCH	0	// helper to print a string like 0.94.7
#ifndef	QUAKESPASM_VER_SUFFIX
#define	QUAKESPASM_VER_SUFFIX		// optional version suffix string literal like "-beta1"
#endif

#define	QS_STRINGIFY_(x)	#x
#define	QS_STRINGIFY(x)	QS_STRINGIFY_(x)

// combined version string like "0.92.1-beta1"
#define	QUAKESPASM_VER_STRING	QS_STRINGIFY(QUAKESPASM_VERSION) "." QS_STRINGIFY(QUAKESPASM_VER_PATCH) QUAKESPASM_VER_SUFFIX

//define	PARANOID			// speed sapping error checking

#define	GAMENAME	"id1"		// directory to look in by default

#define BSP29_VALVE			// enable Half-Life map support

#include "q_stdinc.h"

// !!! if this is changed, it must be changed in d_ifacea.h too !!!
#define CACHE_SIZE	32	// used to align key data structures

#define Q_UNUSED(x)	(x = x)	// for pesky compiler / lint warnings

#define	MINIMUM_MEMORY	0x550000
#define	MINIMUM_MEMORY_LEVELPAK	(MINIMUM_MEMORY + 0x100000)

#define MAX_NUM_ARGVS	50

enum
{
	PITCH	= 0,	// up / down
	YAW		,		// left / right
	ROLL	,		// fall over
};


#define	MAX_QPATH	64		// max length of a quake game pathname

#define	ON_EPSILON	0.1		// point on plane side epsilon

#define	DIST_EPSILON	(0.03125)	// 1/32 epsilon to keep floating point happy (moved from world.c)

#define	MAX_MSGLEN	64000		// max length of a reliable message //ericw -- was 32000
#define	MAX_DATAGRAM	64000		// max length of unreliable message //johnfitz -- was 1024

#define	DATAGRAM_MTU	1400		// johnfitz -- actual limit for unreliable messages to nonlocal clients


// per-level limits

#define	MIN_EDICTS	256		// johnfitz -- lowest allowed value for max_edicts cvar
#define	MAX_EDICTS	32000		// johnfitz -- highest allowed value for max_edicts cvar
						// ents past 8192 can't play sounds in the standard protocol
#define	MAX_LIGHTSTYLES	64
#define	MAX_MODELS	2048		// johnfitz -- was 256
#define	MAX_SOUNDS	2048		// johnfitz -- was 256

#define	SAVEGAME_COMMENT_LENGTH	39

#define	MAX_STYLESTRING		64


// stats are integers communicated to the client by the server

#define	MAX_CL_STATS		32

enum
{
	STAT_HEALTH = 0,
	STAT_FRAGS,
	STAT_WEAPON,
	STAT_AMMO,
	STAT_ARMOR,
	STAT_WEAPONFRAME,
	STAT_SHELLS,
	STAT_NAILS,
	STAT_ROCKETS,
	STAT_CELLS,
	STAT_ACTIVEWEAPON,
	STAT_TOTALSECRETS,
	STAT_TOTALMONSTERS,
	STAT_SECRETS,		// bumped on client side by svc_foundsecret
	STAT_MONSTERS,		// bumped by svc_killedmonster
};


// stock defines

enum
{
	IT_SHOTGUN			= 1,
	IT_SUPER_SHOTGUN	= 2,
	IT_NAILGUN			= 4,
	IT_SUPER_NAILGUN	= 8,
	IT_GRENADE_LAUNCHER	= 16,
	IT_ROCKET_LAUNCHER	= 32,
	IT_LIGHTNING		= 64,
	IT_SUPER_LIGHTNING	= 128,
	IT_SHELLS			= 256,
	IT_NAILS			= 512,
	IT_ROCKETS			= 1024,
	IT_CELLS			= 2048,
	IT_AXE				= 4096,
	IT_ARMOR1			= 8192,
	IT_ARMOR2			= 16384,
	IT_ARMOR3			= 32768,
	IT_SUPERHEALTH		= 65536,
	IT_KEY1				= 131072,
	IT_KEY2				= 262144,
	IT_INVISIBILITY		= 524288,
	IT_INVULNERABILITY	= 1048576,
	IT_SUIT				= 2097152,
	IT_QUAD				= 4194304,
	IT_SIGIL1			= (1<<28),
	IT_SIGIL2			= (1<<29),
	IT_SIGIL3			= (1<<30),
	IT_SIGIL4			= (1<<31),
};

//===========================================
//rogue changed and added defines

enum
{

	RIT_SHELLS				= 128,
	RIT_NAILS				= 256,
	RIT_ROCKETS				= 512,
	RIT_CELLS				= 1024,
	RIT_AXE					= 2048,
	RIT_LAVA_NAILGUN		= 4096,
	RIT_LAVA_SUPER_NAILGUN	= 8192,
	RIT_MULTI_GRENADE		= 16384,
	RIT_MULTI_ROCKET		= 32768,
	RIT_PLASMA_GUN			= 65536,
	RIT_ARMOR1				= 8388608,
	RIT_ARMOR2				= 16777216,
	RIT_ARMOR3				= 33554432,
	RIT_LAVA_NAILS			= 67108864,
	RIT_PLASMA_AMMO			= 134217728,
	RIT_MULTI_ROCKETS		= 268435456,
	RIT_SHIELD				= 536870912,
	RIT_ANTIGRAV			= 1073741824,
	RIT_SUPERHEALTH			= 2147483648,
};

//MED 01/04/97 added hipnotic defines
//===========================================
//hipnotic added defines
#define	HIT_PROXIMITY_GUN_BIT	16
#define	HIT_MJOLNIR_BIT			7
#define	HIT_LASER_CANNON_BIT	23
#define	HIT_PROXIMITY_GUN		(1<<HIT_PROXIMITY_GUN_BIT)
#define	HIT_MJOLNIR				(1<<HIT_MJOLNIR_BIT)
#define	HIT_LASER_CANNON		(1<<HIT_LASER_CANNON_BIT)
#define	HIT_WETSUIT				(1<<(23+2))
#define	HIT_EMPATHY_SHIELDS		(1<<(23+3))

//===========================================

#define	MAX_SCOREBOARD		16
#define	MAX_SCOREBOARDNAME	32

#define	SOUND_CHANNELS		8



#include "HostDefs.hpp"

#include "common.h"
#include "bspfile.h"
#include "sys.h"
#include "zone.h"
#include "mathlib.h"
#include "cvar.h"

#include "protocol.h"
#include "net.h"

#include "cmd.h"
#include "crc.h"

#include "progs.h"
#include "server.h"

#include "platform.h"

#if defined(SDL_FRAMEWORK) || defined(NO_SDL_CONFIG)
#if defined(USE_SDL2)
#ifdef __EMSCRIPTEN__
#include <GL/gl.h>
#include <GL/glext.h>
#endif
#include <SDL2/SDL.h>
#ifndef __EMSCRIPTEN__
#include <SDL2/SDL_opengl.h>
#endif
#else /* SDL-1.2: */
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#endif
#else /**/
#include "SDL.h"
#include "SDL_opengl.h"
#endif

#ifndef APIENTRY
#define	APIENTRY
#endif

#include "console.h"
#include "wad.h"
#include "vid.h"
#include "screen.h"
#include "draw.h"
#include "render.h"
#include "view.h"
#include "sbar.h"
#include "q_sound.h"
#include "client.h"

#include "gl_model.h"
#include "world.h"

#include "image.h"	//johnfitz
#include "gl_texmgr.h"	//johnfitz
#include "input.h"
#include "keys.h"
#include "menu.h"
#include "cdaudio.h"
#include "glquake.h"


//=============================================================================

// the host system specifies the base of the directory tree, the
// command line parms passed to the program, and the amount of memory
// available for the program to use

extern bool noclip_anglehack;

// host

extern	QuakeHostParams *host_parms;

extern	cvar_t		sys_ticrate;
extern	cvar_t		sys_throttle;
extern	cvar_t		sys_nostdout;
extern	cvar_t		developer;
extern	cvar_t		max_edicts; //johnfitz

extern	qboolean	host_initialized;	// true if into command execution
extern	double		host_frametime;
extern	byte		*host_colormap;
extern	int		host_framecount;	// incremented every frame, never reset
extern	double		realtime;		// not bounded in any way, changed at
							// start of every frame, never reset

struct filelist_item_t
{
	char				name[32];
	unsigned int		path_id;
	filelist_item_t		*next;
};

extern filelist_item_t	*modlist;
extern filelist_item_t	*extralevels;
extern filelist_item_t	*demolist;

void Host_ClearMemory ();
void Host_ServerFrame ();
void Host_InitCommands ();
void Host_Init ();
void Host_Shutdown();
void Host_Callback_Notify (cvar_t *var);	/* callback function for CVAR_NOTIFY */
FUNC_NORETURN void Host_Error (const char *error, ...) FUNC_PRINTF(1,2);
FUNC_NORETURN void Host_EndGame (const char *message, ...) FUNC_PRINTF(1,2);
#ifdef __WATCOMC__
#pragma aux Host_Error aborts;
#pragma aux Host_EndGame aborts;
#endif
void Host_Frame (float time);
void Host_Quit_f ();
void Host_ClientCommands (const char *fmt, ...) FUNC_PRINTF(1,2);
void Host_ShutdownServer (qboolean crash);
void Host_WriteConfiguration ();
void Host_Resetdemos ();

void ExtraMaps_Init ();
void Modlist_Init ();
void DemoList_Init ();

void ExtraMaps_NewGame ();
void DemoList_Rebuild ();

void Host_SyncExternalFS ();

extern int		current_skill;	// skill level for currently loaded level (in case
					//  the user changes the cvar while the level is
					//  running, this reflects the level actually in use)

extern qboolean		isDedicated;

extern int		minimum_memory;

#endif	/* QUAKEDEFS_H */

