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

#ifndef _QUAKE_WAD_H
#define _QUAKE_WAD_H

//===============
//   TYPES
//===============

enum
{
	CMP_NONE		= 0,
	CMP_LZSS		,
};

enum
{
	TYP_NONE			= 0,
	TYP_LABEL			,

	TYP_LUMPY			= 64,				// 64 + grab command number
	TYP_PALETTE			= 64,
	TYP_QTEX			,
	TYP_QPIC			,
	TYP_SOUND			,
	TYP_MIPTEX_PALETTE	= 67,
	TYP_MIPTEX			,
};




#define WADID		('W' | ('A' << 8) | ('D' << 16) | ('2' << 24))
#define WADID_VALVE	('W' | ('A' << 8) | ('D' << 16) | ('3' << 24))

#define	WADFILENAME "gfx.wad" //johnfitz -- filename is now hard-coded for honesty

struct qpic_t
{
	int			width, height;
	byte		data[4];			// variably sized
};

struct wadinfo_t
{
	char		identification[4];		// should be WAD2 or 2DAW
	int			numlumps;
	int			infotableofs;
};

struct lumpinfo_t
{
	int			filepos;
	int			disksize;
	int			size;					// uncompressed
	char		type;
	char		compression;
	char		pad1, pad2;
	char		name[16];				// must be null terminated
};

struct wad_t
{
	char		name[MAX_QPATH];
	int			id;
	fshandle_t	fh;
	int			numlumps;
	lumpinfo_t	*lumps;
	wad_t	*next;
};

extern	int			wad_numlumps;
extern	lumpinfo_t	*wad_lumps;
extern	byte		*wad_base;

void	W_LoadWadFile (); //johnfitz -- filename is now hard-coded for honesty
void	W_CleanupName (const char *in, char *out);
void	*W_GetLumpName (const char *name);
void	*W_GetLumpNum (int num);

wad_t	*W_LoadWadList (const char *names);
void	W_FreeWadList (wad_t *wads);
lumpinfo_t *W_GetLumpinfoList (wad_t *wads, const char *name, wad_t **out_wad);

void SwapPic (qpic_t *pic);

#endif	/* _QUAKE_WAD_H */

