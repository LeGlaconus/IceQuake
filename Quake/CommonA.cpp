#include "CommonA.hpp"

//void common::InitEndianism()
//{
//	int	i = 0x12345678;
//	/*    U N I X */
//
///*
//BE_ORDER:  12 34 56 78
//	   U  N  I  X
//
//LE_ORDER:  78 56 34 12
//	   X  I  N  U
//
//PDP_ORDER: 34 12 78 56
//	   N  U  X  I
//*/
//	if (*(char*)&i == 0x12)
//		host_bigendian = true;
//	else if (*(char*)&i == 0x78)
//		host_bigendian = false;
//	else /* if ( *(char *)&i == 0x34 ) */
//		Sys_Error("Unsupported endianism.");
//
//	if (host_bigendian)
//	{
//		BigShort = ShortNoSwap;
//		LittleShort = ShortSwap;
//		BigLong = LongNoSwap;
//		LittleLong = LongSwap;
//		BigFloat = FloatNoSwap;
//		LittleFloat = FloatSwap;
//	}
//	else /* assumed LITTLE_ENDIAN. */
//	{
//		BigShort = ShortSwap;
//		LittleShort = ShortNoSwap;
//		BigLong = LongSwap;
//		LittleLong = LongNoSwap;
//		BigFloat = FloatSwap;
//		LittleFloat = FloatNoSwap;
//	}
//}