/*
Copyright (C) 1996-2001 Id Software, Inc.
Copyright (C) 2002-2009 John Fitzgibbons and others

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

#ifndef __SPRITEGEN_H
#define __SPRITEGEN_H

//
// spritegn.h: header file for sprite generation program
//

// **********************************************************
// * This file must be identical in the spritegen directory *
// * and in the Quake directory, because it's used to       *
// * pass data from one to the other via .spr files.        *
// **********************************************************

//-------------------------------------------------------
// This program generates .spr sprite package files.
// The format of the files is as follows:
//
// dsprite_t file header structure
// <repeat dsprite_t.numframes times>
//   <if spritegroup, repeat dspritegroup_t.numframes times>
//     dspriteframe_t frame header structure
//     sprite bitmap
//   <else (single sprite frame)>
//     dspriteframe_t frame header structure
//     sprite bitmap
// <endrepeat>
//-------------------------------------------------------

#ifdef INCLUDELIBS

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "cmdlib.h"
#include "scriplib.h"
#include "dictlib.h"
#include "trilib.h"
#include "lbmlib.h"
#include "mathlib.h"

#endif

#define SPRITE_VERSION	1

// must match definition in modelgen.h
#ifndef SYNCTYPE_T
#define SYNCTYPE_T
enum synctype_t
{
	ST_SYNC=0,
	ST_RAND 
};
#endif

// TODO: shorten these?
struct dsprite_t
{
	int			ident;
	int			version;
	int			type;
	float		boundingradius;
	int			width;
	int			height;
	int			numframes;
	float		beamlength;
	synctype_t	synctype;
};

enum
{
	SPR_VP_PARALLEL_UPRIGHT		= 0,
	SPR_FACING_UPRIGHT			,
	SPR_VP_PARALLEL				,
	SPR_ORIENTED				,
	SPR_VP_PARALLEL_ORIENTED	,
};


struct dspriteframe_t
{
	int			origin[2];
	int			width;
	int			height;
};

struct dspritegroup_t
{
	int			numframes;
};

struct dspriteinterval_t
{
	float	interval;
};

enum spriteframetype_t
{ 
	SPR_SINGLE=0,
	SPR_GROUP,
	SPR_ANGLED 
};

struct dspriteframetype_t
{
	spriteframetype_t	type;
};

// little-endian "IDSP"
#define IDSPRITEHEADER	(('P'<<24)+('S'<<16)+('D'<<8)+'I') 									

#endif	/* __SPRITEGEN_H */

