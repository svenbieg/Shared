//=============
// DataRow.cpp
//=============

#include "pch.h"


//=======
// Using
//=======

#include "DataRow.h"


//===========
// Namespace
//===========

namespace Math {


//========
// Common
//========

FLOAT DataRow::Calculate(FLOAT x, FLOAT const* pxs, FLOAT const* pys, SIZE_T count, FLOAT error)
{
for(SIZE_T u=0; u<count; u++)
	{
	if(x<pxs[u])
		{
		if(u==0)
			return error;
		FLOAT fx=x-pxs[u-1];
		FLOAT fdx=pxs[u]-pxs[u-1];
		FLOAT fdy=pys[u]-pys[u-1];
		FLOAT y=pys[u-1]+(fx/fdx)*fdy;
		return y;
		}
	}
return error;
}

}