#ifndef __CONVAR_H
#define __CONVAR_H

#include "quakedef.h"

enum class ConVarFlags
{
	None		= 0,
	Archive		= (1U << 0),	// if set, causes it to be saved to config
	Notify		= (1U << 1),	// changes will be broadcasted to all players (q1)
	ServerInfo	= (1U << 2),	// added to serverinfo will be sent to clients (q1/net_dgrm.c and qwsv)
	UserInfo	= (1U << 3),	// added to userinfo, will be sent to server (qwcl)
	Changed		= (1U << 4),
	ROM			= (1U << 6),
	Locked		= (1U << 8),	// locked temporarily
	Registered	= (1U << 10),	// the var is added to the list of variables
	Callback	= (1U << 16),	// var has a callback
};

class ConVar
{
	DECLARE_CLASS_NOBASE(ConVar);
public:


private:
	const char* m_Name;
	const char* m_String;
	ConVarFlags m_Flags;
	float		m_Value;
	const char* m_DefaultString;
	

};

#endif //__CONVAR_H