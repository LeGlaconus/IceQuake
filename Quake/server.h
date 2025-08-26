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

#ifndef QUAKE_SERVER_H
#define QUAKE_SERVER_H

#include "gl_model.h"

// server.h

struct client_t;

struct server_static_t
{
	int			maxclients;
	int			maxclientslimit;
	client_t*	clients;			// [maxclients]
	int			serverflags;		// episode completion information
	bool	changelevel_issued;	// cleared when at SV_SpawnServer
};

//=============================================================================

#define MAX_SIGNON_BUFFERS 256

enum server_state_t
{
	ss_loading,
	ss_active,
};

struct server_t
{
	bool	active;				// false if only a net client

	bool	paused;
	bool	loadgame;			// handle connections specially
	bool	nomonsters;			// server started with 'nomonsters' cvar active

	double		time;

	int			lastcheck;			// used by PF_checkclient
	double		lastchecktime;

	char		name[64];			// map name
	char		modelname[64];		// maps/<name>.bsp, for model_precache[0]
	qmodel_t	*worldmodel;
	const char	*model_precache[MAX_MODELS];	// NULL terminated
	qmodel_t	*models[MAX_MODELS];
	const char	*sound_precache[MAX_SOUNDS];	// NULL terminated
	const char	*lightstyles[MAX_LIGHTSTYLES];
	int			num_edicts;
	int			max_edicts;
	edict_t		*edicts;			// can NOT be array indexed, because
									// edict_t is variable sized, but can
									// be used to reference the world ent
	server_state_t	state;			// some actions are only valid during load

	sizebuf_t	datagram;
	byte		datagram_buf[MAX_DATAGRAM];

	sizebuf_t	reliable_datagram;	// copied to all clients at end of frame
	byte		reliable_datagram_buf[MAX_DATAGRAM];

	sizebuf_t	*signon;
	int			num_signon_buffers;
	sizebuf_t	*signon_buffers[MAX_SIGNON_BUFFERS];

	unsigned	protocol; //johnfitz
	unsigned	protocolflags;
};


#define	NUM_PING_TIMES		16
#define	NUM_SPAWN_PARMS		16

enum sendsignon_e
{
	PRESPAWN_DONE,
	PRESPAWN_FLUSH=1,
	PRESPAWN_SIGNONBUFS,
	PRESPAWN_SIGNONMSG,
};

struct client_t
{
	bool		active;				// false = client is free
	bool		spawned;			// false = don't send datagrams
	bool		dropasap;			// has been told to go to another level
	sendsignon_e	sendsignon;			// only valid before spawned
	int				signonidx;

	double			last_message;		// reliable messages must be sent
										// periodically

	qsocket_t		*netconnection;	// communications handle

	usercmd_t		cmd;				// movement
	vec3_t			wishdir;			// intended motion calced from cmd

	sizebuf_t		message;			// can be added to at any time,
										// copied and clear once per frame
	byte			msgbuf[MAX_MSGLEN];
	edict_t			*edict;				// EDICT_NUM(clientnum+1)
	char			name[32];			// for printing to other people
	int				colors;

	float			ping_times[NUM_PING_TIMES];
	int				num_pings;			// ping_times[num_pings%NUM_PING_TIMES]

// spawn parms are carried from level to level
	float			spawn_parms[NUM_SPAWN_PARMS];

// client known data for deltas
	int				old_frags;
};


//=============================================================================

// edict->movetype values
enum
{
	MOVETYPE_NONE			= 0,		// never moves
	MOVETYPE_ANGLENOCLIP	,
	MOVETYPE_ANGLECLIP		,
	MOVETYPE_WALK			,		// gravity
	MOVETYPE_STEP			,		// gravity, special edge handling
	MOVETYPE_FLY			,
	MOVETYPE_TOSS			,		// gravity
	MOVETYPE_PUSH			,		// no clip to world, push and crush
	MOVETYPE_NOCLIP			,
	MOVETYPE_FLYMISSILE		,		// extra size to monsters
	MOVETYPE_BOUNCE			,
	MOVETYPE_GIB			,		// 2021 rerelease gibs
};

// edict->solid values
enum
{
	SOLID_NOT				= 0,		// no interaction with other objects
	SOLID_TRIGGER			,		// touch on edge, but not blocking
	SOLID_BBOX				,		// touch on edge, block
	SOLID_SLIDEBOX			,		// touch on edge, but not an onground
	SOLID_BSP				,		// bsp clip, touch on edge, block
};


// edict->deadflag values
enum
{
	DEAD_NO					= 0,
	DEAD_DYING				,
	DEAD_DEAD				,
};

enum
{
	DAMAGE_NO				= 0,
	DAMAGE_YES				,
	DAMAGE_AIM				,
};


// edict->flags
enum
{
	FL_FLY					= 1,
	FL_SWIM					= 2,
	//FL_GLIMPSE			= 4,
	FL_CONVEYOR				= 4,
	FL_CLIENT				= 8,
	FL_INWATER				= 16,
	FL_MONSTER				= 32,
	FL_GODMODE				= 64,
	FL_NOTARGET				= 128,
	FL_ITEM					= 256,
	FL_ONGROUND				= 512,
	FL_PARTIALGROUND		= 1024,	// not all corners are valid
	FL_WATERJUMP			= 2048,	// player jumping out of water
	FL_JUMPRELEASED			= 4096,	// for jump debouncing
};


// entity effects

enum
{
	EF_BRIGHTFIELD	= 1,
	EF_MUZZLEFLASH 	= 2,
	EF_BRIGHTLIGHT 	= 4,
	EF_DIMLIGHT 	= 8,
};

enum
{
	SPAWNFLAG_NOT_EASY			= 256,
	SPAWNFLAG_NOT_MEDIUM		= 512,
	SPAWNFLAG_NOT_HARD			= 1024,
	SPAWNFLAG_NOT_DEATHMATCH	= 2048,
};


//============================================================================

extern	cvar_t	teamplay;
extern	cvar_t	skill;
extern	cvar_t	deathmatch;
extern	cvar_t	coop;
extern	cvar_t	fraglimit;
extern	cvar_t	timelimit;

extern	server_static_t	svs;				// persistant server info
extern	server_t		sv;					// local server

extern	client_t	*host_client;

extern	edict_t		*sv_player;

//===========================================================

void SV_Init ();

void SV_StartParticle (vec3_t org, vec3_t dir, int color, int count);
void SV_StartSound (edict_t *entity, int channel, const char *sample, int volume,
    float attenuation);
void SV_LocalSound (client_t *client, const char *sample); // for 2021 rerelease

void SV_DropClient (bool crash);

void SV_SendClientMessages ();
void SV_ClearDatagram ();
void SV_ReserveSignonSpace (int numbytes);

int SV_ModelIndex (const char *name);

void SV_SetIdealPitch ();

void SV_AddUpdates ();

void SV_ClientThink ();
void SV_AddClientToServer (qsocket_t *ret);

void SV_ClientPrintf (const char *fmt, ...) FUNC_PRINTF(1,2);
void SV_BroadcastPrintf (const char *fmt, ...) FUNC_PRINTF(1,2);

void SV_Physics ();

bool SV_CheckBottom (edict_t *ent);
bool SV_movestep (edict_t *ent, vec3_t move, bool relink);

void SV_WriteClientdataToMessage (edict_t *ent, sizebuf_t *msg);

void SV_MoveToGoal ();

void SV_CheckForNewClients ();
void SV_RunClients ();
void SV_SaveSpawnparms ();
void SV_SpawnServer (const char *server);

#endif	/* QUAKE_SERVER_H */
