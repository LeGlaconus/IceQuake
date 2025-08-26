/*
Copyright (C) 1996-2001 Id Software, Inc.
Copyright (C) 2002-2009 John Fitzgibbons and others
Copyright (C) 2010-2014 QuakeSpasm developers

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

#ifndef _QUAKE_PROTOCOL_H
#define _QUAKE_PROTOCOL_H

// protocol.h -- communications protocols

enum
{
	PROTOCOL_NETQUAKE	= 15, //johnfitz -- standard quake protocol
	PROTOCOL_FITZQUAKE	= 666, //johnfitz -- added new protocol for fitzquake 0.85
	PROTOCOL_RMQ		= 999,
};

// PROTOCOL_RMQ protocol flags
enum
{
	PRFL_SHORTANGLE		= (1 << 1),
	PRFL_FLOATANGLE		= (1 << 2),
	PRFL_24BITCOORD		= (1 << 3),
	PRFL_FLOATCOORD		= (1 << 4),
	PRFL_EDICTSCALE		= (1 << 5),
	PRFL_ALPHASANITY	= (1 << 6),		// cleanup insanity with alpha
	PRFL_INT32COORD		= (1 << 7),
	PRFL_MOREFLAGS		= (1 << 31),	// not supported
};


// if the high bit of the servercmd is set, the low bits are fast update flags:
enum
{
	U_MOREBITS		= (1<<0),
	U_ORIGIN1		= (1<<1),
	U_ORIGIN2		= (1<<2),
	U_ORIGIN3		= (1<<3),
	U_ANGLE2		= (1<<4),
	U_STEP			= (1<<5),	//johnfitz -- was U_NOLERP, renamed since it's only used for MOVETYPE_STEP
	U_FRAME			= (1<<6),
	U_SIGNAL		= (1<<7),	// just differentiates from other updates

	// svc_update can pass all of the fast update bits, plus more
	U_ANGLE1		= (1<<8),
	U_ANGLE3		= (1<<9),
	U_MODEL			= (1<<10),
	U_COLORMAP		= (1<<11),
	U_SKIN			= (1<<12),
	U_EFFECTS		= (1<<13),
	U_LONGENTITY	= (1<<14),

	//johnfitz -- PROTOCOL_FITZQUAKE -- new bits
	U_EXTEND1		= (1<<15),
	U_ALPHA			= (1<<16), // 1 byte, uses ENTALPHA_ENCODE, not sent if equal to baseline
	U_FRAME2		= (1<<17), // 1 byte, this is .frame & 0xFF00 (second byte)
	U_MODEL2		= (1<<18), // 1 byte, this is .modelindex & 0xFF00 (second byte)
	U_LERPFINISH	= (1<<19), // 1 byte, 0.0-1.0 maps to 0-255, not sent if exactly 0.1, this is ent->v.nextthink - sv.time, used for lerping
	U_SCALE			= (1<<20), // 1 byte, for PROTOCOL_RMQ PRFL_EDICTSCALE
	U_UNUSED21		= (1<<21),
	U_UNUSED22		= (1<<22),
	U_EXTEND2		= (1<<23), // another byte to follow, future expansion
	//johnfitz


	//johnfitz -- PROTOCOL_NEHAHRA transparency
	U_TRANS			= (1<<15),
	//johnfitz
};

enum
{
	SU_VIEWHEIGHT	= (1<<0),
	SU_IDEALPITCH	= (1<<1),
	SU_PUNCH1		= (1<<2),
	SU_PUNCH2		= (1<<3),
	SU_PUNCH3		= (1<<4),
	SU_VELOCITY1	= (1<<5),
	SU_VELOCITY2	= (1<<6),
	SU_VELOCITY3	= (1<<7),
	SU_UNUSED8		= (1<<8),  //AVAILABLE BIT
	SU_ITEMS		= (1<<9),
	SU_ONGROUND		= (1<<10),	// no data follows, the bit is it
	SU_INWATER		= (1<<11),	// no data follows, the bit is it
	SU_WEAPONFRAME	= (1<<12),
	SU_ARMOR		= (1<<13),
	SU_WEAPON		= (1<<14),

	//johnfitz -- PROTOCOL_FITZQUAKE -- new bits
	SU_EXTEND1		= (1<<15), // another byte to follow
	SU_WEAPON2		= (1<<16), // 1 byte, this is .weaponmodel & 0xFF00 (second byte)
	SU_ARMOR2		= (1<<17), // 1 byte, this is .armorvalue & 0xFF00 (second byte)
	SU_AMMO2		= (1<<18), // 1 byte, this is .currentammo & 0xFF00 (second byte)
	SU_SHELLS2		= (1<<19), // 1 byte, this is .ammo_shells & 0xFF00 (second byte)
	SU_NAILS2		= (1<<20), // 1 byte, this is .ammo_nails & 0xFF00 (second byte)
	SU_ROCKETS2		= (1<<21), // 1 byte, this is .ammo_rockets & 0xFF00 (second byte)
	SU_CELLS2		= (1<<22), // 1 byte, this is .ammo_cells & 0xFF00 (second byte)
	SU_EXTEND2		= (1<<23), // another byte to follow
	SU_WEAPONFRAME2	= (1<<24), // 1 byte, this is .weaponframe & 0xFF00 (second byte)
	SU_WEAPONALPHA	= (1<<25), // 1 byte, this is alpha for weaponmodel, uses ENTALPHA_ENCODE, not sent if ENTALPHA_DEFAULT
	SU_UNUSED26		= (1<<26),
	SU_UNUSED27		= (1<<27),
	SU_UNUSED28		= (1<<28),
	SU_UNUSED29		= (1<<29),
	SU_UNUSED30		= (1<<30),
	SU_EXTEND3		= (1<<31), // another byte to follow, future expansion
	//johnfitz
};

enum
{
	// a sound with no channel is a local only sound
	SND_VOLUME		= (1<<0),	// a byte
	SND_ATTENUATION	= (1<<1),	// a byte
	SND_LOOPING		= (1<<2),	// a long

	//johnfitz -- PROTOCOL_FITZQUAKE -- new bits
	SND_LARGEENTITY	= (1<<3),	// a short + byte (instead of just a short)
	SND_LARGESOUND	= (1<<4),	// a short soundindex (instead of a byte)
	//johnfitz
};

#define DEFAULT_SOUND_PACKET_VOLUME		255
#define DEFAULT_SOUND_PACKET_ATTENUATION	1.0

enum
{
	//johnfitz -- PROTOCOL_FITZQUAKE -- flags for entity baseline messages
	B_LARGEMODEL	= (1<<0),	// modelindex is short instead of byte
	B_LARGEFRAME	= (1<<1),	// frame is short instead of byte
	B_ALPHA			= (1<<2),	// 1 byte, uses ENTALPHA_ENCODE, not sent if ENTALPHA_DEFAULT
	B_SCALE			= (1<<3),
	//johnfitz
};

//johnfitz -- PROTOCOL_FITZQUAKE -- alpha encoding
#define ENTALPHA_DEFAULT	0	//entity's alpha is "default" (i.e. water obeys r_wateralpha) -- must be zero so zeroed out memory works
#define ENTALPHA_ZERO		1	//entity is invisible (lowest possible alpha)
#define ENTALPHA_ONE		255 //entity is fully opaque (highest possible alpha)
#define ENTALPHA_ENCODE(a)	(((a)==0)?ENTALPHA_DEFAULT:Q_rint(CLAMP(1.0f,(a)*254.0f+1,255.0f))) //server convert to byte to send to client
#define ENTALPHA_DECODE(a)	(((a)==ENTALPHA_DEFAULT)?1.0f:((float)(a)-1)/(254)) //client convert to float for rendering
#define ENTALPHA_TOSAVE(a)	(((a)==ENTALPHA_DEFAULT)?0.0f:(((a)==ENTALPHA_ZERO)?-1.0f:((float)(a)-1)/(254))) //server convert to float for savegame
//johnfitz

#define ENTSCALE_DEFAULT	16 // Equivalent to float 1.0f due to byte packing.
#define ENTSCALE_ENCODE(a)	((a) ? ((a) * ENTSCALE_DEFAULT) : ENTSCALE_DEFAULT) // Convert to byte
#define ENTSCALE_DECODE(a)	((float)(a) / ENTSCALE_DEFAULT) // Convert to float for rendering

// defaults for clientinfo messages
#define	DEFAULT_VIEWHEIGHT	22

// game types sent by serverinfo
// these determine which intermission screen plays
#define	GAME_COOP			0
#define	GAME_DEATHMATCH		1

//==================
// note that there are some defs.qc that mirror to these numbers
// also related to svc_strings[] in cl_parse
//==================


// server to client
enum
{
	svc_bad					= 0,
	svc_nop					,
	svc_disconnect			,
	svc_updatestat			,	// [byte] [long]
	svc_version				,	// [long] server version
	svc_setview				,	// [short] entity number
	svc_sound				,	// <see code>
	svc_time				,	// [float] server time
	svc_print				,	// [string] null terminated string
	svc_stufftext			,	// [string] stuffed into client's console buffer
									// the string should be \n terminated
	svc_setangle			,	// [angle3] set the view angle to this absolute value
	svc_serverinfo			,	// [long] version
								// [string] signon string
								// [string]..[0]model cache
								// [string]...[0]sounds cache
	svc_lightstyle			,	// [byte] [string]
	svc_updatename			,	// [byte] [string]
	svc_updatefrags			,	// [byte] [short]
	svc_clientdata			,	// <shortbits + data>
	svc_stopsound			,	// <see code>
	svc_updatecolors		,	// [byte] [byte]
	svc_particle			,	// [vec3] <variable>
	svc_damage				,
	svc_spawnstatic			,
	//svc_spawnbinary		= 21,
	svc_spawnbaseline		= 22,
	svc_temp_entity			,
	svc_setpause			,	// [byte] on / off
	svc_signonnum			,	// [byte]  used for the signon sequence
	svc_centerprint			,	// [string] to put in center of the screen
	svc_killedmonster		,
	svc_foundsecret			,
	svc_spawnstaticsound	,	// [coord3] [byte] samp [byte] vol [byte] aten
	svc_intermission		,	// [string] music
	svc_finale				,	// [string] music [string] text
	svc_cdtrack				,	// [byte] track [byte] looptrack
	svc_sellscreen			,
	svc_cutscene			,

	//johnfitz -- PROTOCOL_FITZQUAKE -- new server messages
	svc_skybox				,	// [string] name
	svc_bf					,
	svc_fog					,	// [byte] density [byte] red [byte] green [byte] blue [float] time
	svc_spawnbaseline2		,	// support for large modelindex, large framenum, alpha, using flags
	svc_spawnstatic2		,	// support for large modelindex, large framenum, alpha, using flags
	svc_spawnstaticsound2	,	// [coord3] [short] samp [byte] vol [byte] aten
	//johnfitz

	// 2021 re-release server messages - see:
	// https://steamcommunity.com/sharedfiles/filedetails/?id=2679459726
	svc_botchat				,
	svc_setviews			,
	svc_updateping			,
	svc_updatesocial		,
	svc_updateplinfo		,
	svc_rawprint			,
	svc_servervars			,
	svc_seq					,
	// Note: svc_achievement has same value as svcdp_effect!
	svc_achievement			,	// [string] id
	svc_chat				,
	svc_levelcompleted		,
	svc_backtolobby			,
	svc_localsound			,
};


// client to server

enum
{
	clc_bad			= 0,
	clc_nop 		,
	clc_disconnect	,
	clc_move		,		// [usercmd_t]
	clc_stringcmd	,		// [string] message
};

// temp entity events

enum
{
	TE_SPIKE			= 0,
	TE_SUPERSPIKE		,
	TE_GUNSHOT			,
	TE_EXPLOSION		,
	TE_TAREXPLOSION		,
	TE_LIGHTNING1		,
	TE_LIGHTNING2		,
	TE_WIZSPIKE			,
	TE_KNIGHTSPIKE		,
	TE_LIGHTNING3		,
	TE_LAVASPLASH		,
	TE_TELEPORT			,
	TE_EXPLOSION2		,

	// PGM 01/21/97
	TE_BEAM				,
	// PGM 01/21/97
};




struct entity_state_t
{
	vec3_t		origin;
	vec3_t		angles;
	unsigned short 	modelindex;	//johnfitz -- was int
	unsigned short 	frame;		//johnfitz -- was int
	unsigned char 	colormap;	//johnfitz -- was int
	unsigned char 	skin;		//johnfitz -- was int
	unsigned char	alpha;		//johnfitz -- added
	unsigned char	scale;		//Quakespasm: for model scale support.
	int		effects;
};

struct usercmd_t
{
	vec3_t	viewangles;

	// intended velocities
	float	forwardmove;
	float	sidemove;
	float	upmove;
};

#endif	/* _QUAKE_PROTOCOL_H */
