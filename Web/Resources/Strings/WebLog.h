//==========
// WebLog.h
//==========

#pragma once


//=======
// Using
//=======

#include "Resources/Strings/String.h"


//===========
// Namespace
//===========

namespace Resources {
	namespace Strings {


//=========
// Web-Log
//=========

constexpr STRING STR_WEB_LOG_CLEAR[]=
	{
	{ LNG::DE, "Löschen" },
	{ LNG::EN, "Clear" },
	{ LNG::None, nullptr }
	};

constexpr STRING STR_WEB_LOG_CLEARED[]=
	{
	{ LNG::DE, "Protokoll zurückgesetzt" },
	{ LNG::EN, "Protocol reset" },
	{ LNG::None, nullptr }
	};

}}