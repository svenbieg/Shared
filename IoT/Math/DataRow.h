//===========
// DataRow.h
//===========

#pragma once


//===========
// Namespace
//===========

namespace Math {


//==========
// Data-Row
//==========

class DataRow
{
public:
	// Common
	static FLOAT Calculate(FLOAT X, FLOAT const* Xs, FLOAT const* Ys, SIZE_T Count, FLOAT Error=0.f);
};

}