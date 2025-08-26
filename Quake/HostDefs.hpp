#ifndef __HOSTDEFS_H
#define __HOSTDEFS_H

struct IHostParams
{
	IHostParams()
	{
		memset(this, 0, sizeof(this));
	}

	const char* basedir;
	const char* userdir;	// user's directory on UNIX platforms.
	// if user directories are enabled, basedir
	// and userdir will point to different
	// memory locations, otherwise to the same.
	int	argc;
	char** argv;
	void* membase;	//Begginning of Quake's heap
	int	memsize;	//Size of the Quake heap
	int	numcpus;
	int	errstate;
};

struct QuakeHostParams : public IHostParams
{ };

#endif //__HOSTDEFS_H