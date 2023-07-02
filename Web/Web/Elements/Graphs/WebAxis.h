//===========
// WebAxis.h
//===========

#pragma once


//=======
// Using
//=======

#include "Collections/Map.h"
#include "Sentence.h"


//===========
// Namespace
//===========

namespace Web {
	namespace Elements {
		namespace Graphs {


//==========
// Web-Axis
//==========

class WebAxis: public Object
{
private:
	// Using
	using PointMap=Collections::Map<INT, Handle<Sentence>>;

public:
	// Con-/Destructors
	WebAxis();

	// Common
	Handle<Sentence> Name;
	Handle<PointMap> Points;
	Handle<Sentence> Unit;
};

}}}