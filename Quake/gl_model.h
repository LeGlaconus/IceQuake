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

#ifndef GL_MODEL_H
#define GL_MODEL_H

#include "modelgen.h"
#include "spritegn.h"
#include "client.h"

#include "gl_texmgr.h"

/*

d*_t structures are on-disk representations
m*_t structures are in-memory

*/

// entity effects

enum
{
//	EF_BRIGHTFIELD		= 1,
//	EF_MUZZLEFLASH 		= 2,
//	EF_BRIGHTLIGHT 		= 4,
//	EF_DIMLIGHT 		= 8,
	EF_QEX_QUADLIGHT	= 16,	// 2021 rerelease
	EF_QEX_PENTALIGHT	= 32,	// 2021 rerelease
	EF_QEX_CANDLELIGHT	= 64,	// 2021 rerelease
};


/*
==============================================================================

BRUSH MODELS

==============================================================================
*/


//
// in memory representation
//
// !!! if this is changed, it must be changed in asm_draw.h too !!!
struct mvertex_t
{
	vec3_t		position;
};

enum
{
	SIDE_FRONT = 0,
	SIDE_BACK,
	SIDE_ON,
};

// plane_t structure
// !!! if this is changed, it must be changed in asm_i386.h too !!!
struct mplane_t
{
	vec3_t	normal;
	float	dist;
	byte	type;			// for texture axis selection and fast side tests
	byte	signbits;		// signx + signy<<1 + signz<<1
	byte	pad[2];
};

// ericw -- each texture has two chains, so we can clear the model chains
//          without affecting the world
enum texchain_t
{
	chain_world = 0,
	chain_model,
};

struct msurface_t;

struct texture_t
{
	char				name[16];
	unsigned			width, height;
	unsigned			shift;		// Q64
	gltexture_t			*gltexture; //johnfitz -- pointer to gltexture
	gltexture_t			*fullbright; //johnfitz -- fullbright mask texture
	gltexture_t			*warpimage; //johnfitz -- for water animation
	qboolean			update_warp; //johnfitz -- update warp this frame
	msurface_t			*texturechains[2];	// for texture chains
	int					anim_total;				// total tenths in sequence ( 0 = no)
	int					anim_min, anim_max;		// time for this frame min <=time< max
	texture_t			*anim_next;		// in the animation sequence
	texture_t			*alternate_anims;	// bmodels in frmae 1 use these
};

enum
{
	SURF_PLANEBACK		= 2,
	SURF_DRAWSKY		= 4,
	SURF_DRAWSPRITE		= 8,
	SURF_DRAWTURB		= 0x10,
	SURF_DRAWTILED		= 0x20,
	SURF_DRAWBACKGROUND	= 0x40,
	SURF_UNDERWATER		= 0x80,
	SURF_NOTEXTURE		= 0x100, //johnfitz
	SURF_DRAWFENCE		= 0x200,
	SURF_DRAWLAVA		= 0x400,
	SURF_DRAWSLIME		= 0x800,
	SURF_DRAWTELE		= 0x1000,
	SURF_DRAWWATER		= 0x2000,
};

// !!! if this is changed, it must be changed in asm_draw.h too !!!
struct medge_t
{
	unsigned int	v[2];
	unsigned int	cachededgeoffset;
};

struct mtexinfo_t
{
	float		vecs[2][4];
	texture_t	*texture;
	int			flags;
};

#define	VERTEXSIZE	7

struct glpoly_t
{
	glpoly_t	*next;
	glpoly_t	*chain;
	int			numverts;
	float		verts[4][VERTEXSIZE];	// variable sized (xyz s1t1 s2t2)
};

struct msurface_t
{
	int			visframe;		// should be drawn when node is crossed
	float		mins[3];		// johnfitz -- for frustum culling
	float		maxs[3];		// johnfitz -- for frustum culling

	mplane_t	*plane;
	int			flags;

	int			firstedge;	// look up in model->surfedges[], negative numbers
	int			numedges;	// are backwards edges

	short		texturemins[2];
	short		extents[2];

	int			light_s, light_t;	// gl lightmap coordinates

	glpoly_t	*polys;				// multiple if warped
	msurface_t	*texturechain;

	mtexinfo_t	*texinfo;

	int			vbo_firstvert;		// index of this surface's first vert in the VBO

// lighting info
	int			dlightframe;
	unsigned int dlightbits[(MAX_DLIGHTS + 31) >> 5];
		// int is 32 bits, need an array for MAX_DLIGHTS > 32

	int			lightmaptexturenum;
	byte		styles[MAXLIGHTMAPS];
	int			cached_light[MAXLIGHTMAPS];	// values currently used in lightmap
	qboolean	cached_dlight;				// true if dynamic light in cache
	byte		*samples;		// [numstyles*surfsize]
};

struct mnode_t
{
// common with leaf
	int			contents;		// 0, to differentiate from leafs
	int			visframe;		// node needs to be traversed if current

	float		minmaxs[6];		// for bounding box culling

	mnode_t		*parent;

// node specific
	mplane_t	*plane;
	mnode_t		*children[2];

	unsigned int		firstsurface;
	unsigned int		numsurfaces;
};



struct mleaf_t
{
// common with node
	int			contents;		// wil be a negative contents number
	int			visframe;		// node needs to be traversed if current

	float		minmaxs[6];		// for bounding box culling

	mnode_t		*parent;

// leaf specific
	byte		*compressed_vis;
	efrag_t		*efrags;

	msurface_t	**firstmarksurface;
	int			nummarksurfaces;
	int			key;			// BSP sequence number for leaf's contents
	byte		ambient_sound_level[NUM_AMBIENTS];
};

//johnfitz -- for clipnodes>32k
struct mclipnode_t
{
	int			planenum;
	int			children[2]; // negative numbers are contents
};
//johnfitz

// !!! if this is changed, it must be changed in asm_i386.h too !!!
struct hull_t
{
	mclipnode_t	*clipnodes; //johnfitz -- was dclipnode_t
	mplane_t	*planes;
	int			firstclipnode;
	int			lastclipnode;
	vec3_t		clip_mins;
	vec3_t		clip_maxs;
};

/*
==============================================================================

SPRITE MODELS

==============================================================================
*/


// FIXME: shorten these?
struct mspriteframe_t
{
	int					width, height;
	float				up, down, left, right;
	float				smax, tmax; //johnfitz -- image might be padded
	gltexture_t			*gltexture;
};

struct mspritegroup_t
{
	int				numframes;
	float			*intervals;
	mspriteframe_t	*frames[1];
};

struct mspriteframedesc_t
{
	spriteframetype_t	type;
	mspriteframe_t		*frameptr;
};

struct msprite_t
{
	int					type;
	int					maxwidth;
	int					maxheight;
	int					numframes;
	float				beamlength;		// remove?
	void				*cachespot;		// remove?
	mspriteframedesc_t	frames[1];
};


/*
==============================================================================

ALIAS MODELS

Alias models are position independent, so the cache manager can move them.
==============================================================================
*/

//-- from RMQEngine
// split out to keep vertex sizes down
struct aliasmesh_t
{
	float st[2];
	unsigned short vertindex;
};

struct meshxyz_t
{
	byte xyz[4];
	signed char normal[4];
};

struct meshst_t
{
	float st[2];
};
//--

struct maliasframedesc_t
{
	int					firstpose;
	int					numposes;
	float				interval;
	trivertx_t			bboxmin;
	trivertx_t			bboxmax;
	int					frame;
	char				name[16];
};

struct maliasgroupframedesc_t
{
	trivertx_t			bboxmin;
	trivertx_t			bboxmax;
	int					frame;
};

struct maliasgroup_t
{
	int						numframes;
	int						intervals;
	maliasgroupframedesc_t	frames[1];
};

// !!! if this is changed, it must be changed in asm_draw.h too !!!
struct mtriangle_t
{
	int					facesfront;
	int					vertindex[3];
};


#define	MAX_SKINS	32
struct aliashdr_t
{
	int			ident;
	int			version;
	vec3_t		scale;
	vec3_t		scale_origin;
	float		boundingradius;
	vec3_t		eyeposition;
	int			numskins;
	int			skinwidth;
	int			skinheight;
	int			numverts;
	int			numtris;
	int			numframes;
	synctype_t	synctype;
	int			flags;
	float		size;

	//ericw -- used to populate vbo
	int			numverts_vbo;   // number of verts with unique x,y,z,s,t
	intptr_t		meshdesc;       // offset into extradata: numverts_vbo aliasmesh_t
	int			numindexes;
	intptr_t		indexes;        // offset into extradata: numindexes unsigned shorts
	intptr_t		vertexes;       // offset into extradata: numposes*vertsperframe trivertx_t
	//ericw --

	int					numposes;
	int					poseverts;
	int					posedata;	// numposes*poseverts trivert_t
	int					commands;	// gl command list with embedded s/t
	gltexture_t			*gltextures[MAX_SKINS][4]; //johnfitz
	gltexture_t			*fbtextures[MAX_SKINS][4]; //johnfitz
	int					texels[MAX_SKINS];	// only for player skins
	maliasframedesc_t	frames[1];	// variable sized
};

#define	MAXALIASVERTS	2000 //johnfitz -- was 1024
#define	MAXALIASFRAMES	1024 //spike -- was 256
#define	MAXALIASTRIS	4096 //ericw -- was 2048
extern	aliashdr_t	*pheader;
extern	stvert_t	stverts[MAXALIASVERTS];
extern	mtriangle_t	triangles[MAXALIASTRIS];
extern	trivertx_t	*poseverts[MAXALIASFRAMES];

//===================================================================

//
// Whole model
//

enum modtype_t
{
	mod_brush,
	mod_sprite,
	mod_alias,
};


enum
{
	EF_ROCKET	= 1,		// leave a trail
	EF_GRENADE	= 2,		// leave a trail
	EF_GIB		= 4,		// leave a trail
	EF_ROTATE	= 8,		// rotate (bonus items)
	EF_TRACER	= 16,		// green split trail
	EF_ZOMGIB	= 32,		// small blood trail
	EF_TRACER2	= 64,		// orange split trail + rotate
	EF_TRACER3	= 128,		// purple trail
};
#define	MF_HOLEY	(1u<<14)		// MarkV/QSS -- make index 255 transparent on mdl's

//johnfitz -- extra flags for rendering
enum
{
	MOD_NOLERP		= 256,	//don't lerp when animating
	MOD_NOSHADOW	= 512,	//don't cast a shadow
	MOD_FBRIGHTHACK	= 1024,	//when fullbrights are disabled, use a hack to render this model brighter
};
//johnfitz

struct qmodel_t
{
	char		name[MAX_QPATH];
	unsigned int	path_id;		// path id of the game directory
							// that this model came from
	qboolean	needload;		// bmodels and sprites don't cache normally

	modtype_t	type;
	int			numframes;
	synctype_t	synctype;

	int			flags;

//
// volume occupied by the model graphics
//
	vec3_t		mins, maxs;
	vec3_t		ymins, ymaxs; //johnfitz -- bounds for entities with nonzero yaw
	vec3_t		rmins, rmaxs; //johnfitz -- bounds for entities with nonzero pitch or roll
	//johnfitz -- removed float radius;

//
// solid volume for clipping
//
	qboolean	clipbox;
	vec3_t		clipmins, clipmaxs;

//
// brush model
//
	int			firstmodelsurface, nummodelsurfaces;

	int			numsubmodels;
	dmodel_t	*submodels;

	int			numplanes;
	mplane_t	*planes;

	int			numleafs;		// number of visible leafs, not counting 0
	mleaf_t		*leafs;

	int			numvertexes;
	mvertex_t	*vertexes;

	int			numedges;
	medge_t		*edges;

	int			numnodes;
	mnode_t		*nodes;

	int			numtexinfo;
	mtexinfo_t	*texinfo;

	int			numsurfaces;
	msurface_t	*surfaces;

	int			numsurfedges;
	int			*surfedges;

	int			numclipnodes;
	mclipnode_t	*clipnodes; //johnfitz -- was dclipnode_t

	int			nummarksurfaces;
	msurface_t	**marksurfaces;

	hull_t		hulls[MAX_MAP_HULLS];

	int			numtextures;
	texture_t	**textures;

	byte		*visdata;
	byte		*lightdata;
	char		*entities;

	qboolean	viswarn; // for Mod_DecompressVis()

	int			bspversion;
	qboolean	haslitwater;

// alias model


	GLuint		meshvbo;
	GLuint		meshindexesvbo;
	int			vboindexofs;    // offset in vbo of the hdr->numindexes unsigned shorts
	int			vboxyzofs;      // offset in vbo of hdr->numposes*hdr->numverts_vbo meshxyz_t
	int			vbostofs;       // offset in vbo of hdr->numverts_vbo meshst_t


// additional model data

	cache_user_t	cache;		// only access through Mod_Extradata

};

//============================================================================

void	Mod_Init (void);
void	Mod_ClearAll (void);
void	Mod_ResetAll (void); // for gamedir changes (Host_Game_f)
qmodel_t *Mod_ForName (const char *name, qboolean crash);
void	*Mod_Extradata (qmodel_t *mod);	// handles caching
void	Mod_TouchModel (const char *name);

mleaf_t *Mod_PointInLeaf (vec3_t p, qmodel_t *model);
byte	*Mod_LeafPVS (mleaf_t *leaf, qmodel_t *model);
byte	*Mod_NoVisPVS (qmodel_t *model);

void Mod_SetExtraFlags (qmodel_t *mod);

#endif	/* GL_MODEL_H */
