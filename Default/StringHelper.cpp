//==================
// StringHelper.cpp
//==================

#include "pch.h"


//=======
// Using
//=======

#include <cmath>
#include "CharHelper.h"
#include "StringHelper.h"


//========
// Common
//========

template <class _dst_t, class _src_t> ALWAYS_INLINE UINT StringCopy(_dst_t* dst, UINT size, _src_t const* src, UINT copy)
{
if(!src)
	{
	if(dst)
		dst[0]=0;
	return 0;
	}
if(size==0)
	size=UINT_MAX;
UINT end=size-1;
if(copy)
	end=MIN(end, copy);
UINT pos=0;
for(; pos<end; pos++)
	{
	if(src[pos]==0)
		break;
	if(dst)
		dst[pos]=CharToChar<_dst_t, _src_t>(src[pos]);
	}
if(dst)
	dst[pos]=0;
return pos;
}

UINT StringCopy(LPSTR dst, UINT size, LPCSTR src, UINT copy)
{
return StringCopy<CHAR, CHAR>(dst, size, src, copy);
}

UINT StringCopy(LPSTR dst, UINT size, LPCWSTR src, UINT copy)
{
return StringCopy<CHAR, WCHAR>(dst, size, src, copy);
}

UINT StringCopy(LPWSTR dst, UINT size, LPCSTR src, UINT copy)
{
return StringCopy<WCHAR, CHAR>(dst, size, src, copy);
}

UINT StringCopy(LPWSTR dst, UINT size, LPCWSTR src, UINT copy)
{
return StringCopy<WCHAR, WCHAR>(dst, size, src, copy);
}

template <class _char_t, class _find_t> ALWAYS_INLINE BOOL StringFind(_char_t const* str, _find_t const* find, UINT* pos_ptr, BOOL cs)
{
if(!str||!find)
	return false;
UINT find_len=StringLength(find);
if(!find_len)
	return false;
for(UINT pos=0; str[pos]; pos++)
	{
	if(StringCompare(&str[pos], find, find_len, cs)==0)
		{
		if(pos_ptr)
			*pos_ptr=pos;
		return true;
		}
	}
return false;
}

BOOL StringFind(LPCSTR str, LPCSTR find, UINT* pos_ptr, BOOL cs)
{
return StringFind<CHAR, CHAR>(str, find, pos_ptr, cs);
}

BOOL StringFind(LPCSTR str, LPCWSTR find, UINT* pos_ptr, BOOL cs)
{
return StringFind<CHAR, WCHAR>(str, find, pos_ptr, cs);
}

BOOL StringFind(LPCWSTR str, LPCSTR find, UINT* pos_ptr, BOOL cs)
{
return StringFind<WCHAR, CHAR>(str, find, pos_ptr, cs);
}

BOOL StringFind(LPCWSTR str, LPCWSTR find, UINT* pos_ptr, BOOL cs)
{
return StringFind<WCHAR, WCHAR>(str, find, pos_ptr, cs);
}

template <class _str_t, class _char_t> ALWAYS_INLINE BOOL StringFindChar(_str_t const* str, _char_t c, UINT* pos_ptr, BOOL cs)
{
if(!str||!c)
	return false;
for(UINT pos=0; str[pos]; pos++)
	{
	if(CharCompare(str[pos], c, cs)==0)
		{
		if(pos_ptr)
			*pos_ptr=pos;
		return true;
		}
	}
return false;
}

BOOL StringFindChar(LPCSTR str, CHAR c, UINT* pos_ptr, BOOL cs)
{
return StringFindChar<CHAR, CHAR>(str, c, pos_ptr, cs);
}

BOOL StringFindChar(LPCWSTR str, CHAR c, UINT* pos_ptr, BOOL cs)
{
return StringFindChar<WCHAR, CHAR>(str, c, pos_ptr, cs);
}

template <class _char_t, class _find_t> ALWAYS_INLINE BOOL StringFindChars(_char_t const* str, _find_t const* find, UINT* pos_ptr, BOOL cs)
{
if(!str||!find)
	return false;
for(UINT pos=0; str[pos]; pos++)
	{
	for(UINT find_pos=0; find[find_pos]; find_pos++)
		{
		if(CharCompare(str[pos], find[find_pos], cs)==0)
			{
			if(pos_ptr)
				*pos_ptr=pos;
			return true;
			}
		}
	}
return false;
}

BOOL StringFindChars(LPCSTR str, LPCSTR find, UINT* pos_ptr, BOOL cs)
{
return StringFindChars<CHAR, CHAR>(str, find, pos_ptr, cs);
}

BOOL StringFindChars(LPCWSTR str, LPCSTR find, UINT* pos_ptr, BOOL cs)
{
return StringFindChars<WCHAR, CHAR>(str, find, pos_ptr, cs);
}

template <class _char_t> ALWAYS_INLINE UINT StringLength(_char_t const* Value)
{
if(!Value)
	return 0;
UINT len=0;
for(; Value[len]; len++);
return len;
}

UINT StringLength(LPCSTR str)
{
return StringLength<CHAR>(str);
}

UINT StringLength(LPCWSTR str)
{
return StringLength<WCHAR>(str);
}

template <class _char_t> ALWAYS_INLINE UINT StringLength(_char_t const* Value, UINT Maximum)
{
if(!Value)
	return 0;
if(!Maximum)
	Maximum=UINT_MAX;
UINT len=0;
for(; Value[len]; len++)
	{
	if(len==Maximum)
		break;
	}
return len;
}

UINT StringLength(LPCSTR str, UINT max)
{
return StringLength<CHAR>(str, max);
}

UINT StringLength(LPCWSTR str, UINT max)
{
return StringLength<WCHAR>(str, max);
}


//==============
// Modification
//==============

UINT StringAppend(LPSTR dst, UINT size, LPCSTR str, LPCSTR append)
{
UINT len=StringLength(str);
if(!len)
	return StringCopy(dst, size, append);
UINT append_len=StringLength(append);
if(!append_len)
	return StringCopy(dst, size, str);
UINT new_len=len+append_len;
if(!size)
	return new_len;
if(new_len+1>size)
	return 0;
size-=StringCopy(dst, size, str);
StringCopy(&dst[len], size, append);
return new_len;
}

UINT StringInsert(LPSTR dst, UINT size, LPCSTR str, UINT pos, LPCSTR insert)
{
UINT len=StringLength(str);
if(pos>len)
	return StringCopy(dst, size, str);
UINT insert_len=StringLength(insert);
if(insert_len==0)
	return StringCopy(dst, size, str);
UINT new_len=len+insert_len;
if(!size)
	return new_len;
if(new_len+1>size)
	return 0;
size-=StringCopy(dst, size, str, pos);
size-=StringCopy(&dst[pos], size, insert);
StringCopy(&dst[pos+insert_len], size, &str[pos]);
return new_len;
}

UINT StringLowerCase(LPSTR dst, UINT size, LPCSTR str)
{
if(!str)
	return 0;
UINT pos=0;
for(; str[pos]; pos++)
	{
	if(pos+1==size)
		break;
	if(dst)
		dst[pos]=CharToSmall(str[pos]);
	}
if(dst)
	dst[pos]=0;
return pos;
}

UINT StringUpperCase(LPSTR dst, UINT size, LPCSTR str)
{
if(!str)
	return 0;
UINT pos=0;
for(; str[pos]; pos++)
	{
	if(pos+1==size)
		break;
	if(dst)
		dst[pos]=CharToCapital(str[pos]);
	}
if(dst)
	dst[pos]=0;
return pos;
}

template <class _dst_t, class _char_t, class _find_t, class _insert_t> ALWAYS_INLINE UINT StringReplace(_dst_t* dst, UINT size, _char_t const* str, _find_t const* find, _insert_t const* insert, BOOL cs, BOOL repeat)
{
if(!str)
	return 0;
UINT find_len=StringLength(find);
if(find_len==0)
	return StringCopy(dst, size, str);
BOOL parse=true;
UINT pos=0;
while(*str)
	{
	if(pos==size-1)
		{
		if(dst)
			*dst=0;
		return pos;
		}
	if(parse)
		{
		if(StringCompare(str, find, find_len, cs)==0)
			{
			UINT insert_len=StringCopy(dst, size, insert);
			if(dst)
				{
				dst+=insert_len;
				size-=insert_len;
				}
			pos+=insert_len;
			if(!repeat)
				parse=false;
			str+=find_len;
			continue;
			}
		}
	if(dst)
		{
		*dst++=*str;
		}
	str++;
	pos++;
	}
if(dst)
	*dst=0;
return pos;
}

UINT StringReplace(LPSTR dst, UINT size, LPCSTR str, LPCSTR find, LPCSTR insert, BOOL cs, BOOL repeat)
{
return StringReplace<CHAR, CHAR, CHAR, CHAR>(dst, size, str, find, insert, cs, repeat);
}

UINT StringReplace(LPWSTR dst, UINT size, LPCWSTR str, LPCSTR find, LPCSTR insert, BOOL cs, BOOL repeat)
{
return StringReplace<WCHAR, WCHAR, CHAR, CHAR>(dst, size, str, find, insert, cs, repeat);
}


//==========
// Scanning
//==========

template <class _char_t, class _int_t> UINT StringScanInt(_char_t const* str, _int_t* value_ptr)
{
if(!str)
	return 0;
UINT pos=0;
BOOL negative=false;
for(; CharEqual(str[pos], '-'); pos++)
	{
	negative=!negative;
	}
if(!CharIsNumber(str[pos]))
	return 0;
_int_t i=(_int_t)str[pos]-'0';
for(pos++; str[pos]; pos++)
	{
	if(!CharIsNumber(str[pos]))
		break;
	i*=10;
	i+=(_int_t)str[pos]-'0';
	}
if(negative)
	i*=-1;
if(value_ptr)
	*value_ptr=i;
return pos;
}

template <class _char_t, class _uint_t> UINT StringScanUInt(_char_t const* str, _uint_t* value_ptr, bool hex)
{
if(!str)
	return 0;
UINT pos=0;
if(!CharIsNumber(str[pos]))
	return 0;
BOOL binary=false;
if(CharEqual(str[pos], '0'))
	{
	if(CharEqual(str[pos+1], 'b'))
		{
		binary=true;
		pos+=2;
		}
	if(CharEqual(str[pos+1], 'x'))
		{
		hex=true;
		pos+=2;
		}
	}
if(binary)
	{
	_uint_t u=0;
	UINT start=pos;
	for(; str[pos]; pos++)
		{
		if(!CharIsBinary(str[pos]))
			break;
		u*=2;
		u+=(_uint_t)str[pos]-'0';
		}
	if(pos==start)
		return 0;
	if(value_ptr)
		*value_ptr=u;
	return pos;
	}
if(hex)
	{
	_uint_t u=0;
	UINT start=pos;
	for(; str[pos]; pos++)
		{
		if(!CharIsHex(str[pos]))
			break;
		_char_t c=(_char_t)(str[pos]-'0');
		if(c>9)
			c=(_char_t)(c-7);
		u*=16;
		u+=c;
		}
	if(pos==start)
		return 0;
	if(value_ptr)
		*value_ptr=u;
	return pos;
	}
_uint_t u=(_uint_t)str[pos]-'0';
for(pos++; str[pos]; pos++)
	{
	if(!CharIsNumber(str[pos]))
		break;
	u*=10;
	u+=(_uint_t)str[pos]-'0';
	}
if(value_ptr)
	*value_ptr=u;
return pos;
}

UINT StringScanUInt(LPCSTR str, UINT* value_ptr, bool hex)
{
return StringScanUInt<CHAR, UINT>(str, value_ptr, hex);
}

UINT StringScanUInt(LPCWSTR str, UINT* value_ptr, bool hex)
{
return StringScanUInt<WCHAR, UINT>(str, value_ptr, hex);
}

template <class _char_t, class _float_t> UINT StringScanFloat(_char_t const* str, _float_t* value_ptr)
{
if(!str)
	return 0;
UINT pos=0;
BOOL negative=false;
for(; CharEqual(str[pos], '-'); pos++)
	{
	negative=!negative;
	}
if(!CharIsNumber(str[pos]))
	return 0;
_float_t f=(_float_t)str[pos]-'0';
for(pos++; str[pos]; pos++)
	{
	if(!CharIsNumber(str[pos]))
		break;
	f*=10;
	f+=(_float_t)str[pos]-'0';
	}
if(str[pos])
	{
	if(CharEqual(str[pos], '.')||CharEqual(str[pos], ','))
		{
		_float_t div=10;
		for(pos++; str[pos]; pos++)
			{
			if(!CharIsNumber(str[pos]))
				break;
			f+=((_float_t)str[pos]-'0')/div;
			div*=10;
			}
		}
	}
if(str[pos])
	{
	if(CharEqual(str[pos], 'E')||CharEqual(str[pos], 'e'))
		{
		pos++;
		INT ex=0;
		UINT ex_len=StringScanInt(&str[pos], &ex);
		if(ex_len==0)
			return 0;
		pos+=ex_len;
		ex*=10;
		if(ex<0)
			{
			f/=(_float_t)-ex;
			}
		else
			{
			f*=(_float_t)ex;
			}
		}
	}
if(negative)
	f*=-1;
if(value_ptr)
	*value_ptr=f;
return pos;
}

template <class _char_t, class _buf_t, class _stop_t> UINT StringScanString(_char_t const* str, _buf_t* buf, UINT size, _stop_t stop)
{
if(!str)
	return 0;
UINT pos=0;
for(; str[pos]; pos++)
	{
	if(CharEqual(str[pos], stop))
		break;
	if(pos<size)
		buf[pos]=CharToChar<_buf_t, _char_t>(str[pos]);
	}
if(pos<size)
	buf[pos]=0;
return pos;
}


//========
// Format
//========

UINT StringGetFormat(LPCSTR str, StringFormat& format, StringFormatFlags& flags, UINT& width, UINT& precision)
{
if(!str)
	return 0;
if(!CharEqual(str[0], '%'))
	return 0;
if(str[1]==0)
	{
	format=StringFormat::Percent;
	return 1;
	}
if(CharEqual(str[1], '%'))
	{
	format=StringFormat::Percent;
	return 2;
	}
// Flags
UINT pos=1;
for(; str[pos]; pos++)
	{
	if(CharCompare(str[pos], ' ')==0)
		{
		SetFlag(flags, StringFormatFlags::Space);
		}
	else if(CharCompare(str[pos], '+')==0)
		{
		SetFlag(flags, StringFormatFlags::Signed);
		}
	else if(CharCompare(str[pos], '-')==0)
		{
		SetFlag(flags, StringFormatFlags::Left);
		}
	else if(CharCompare(str[pos], '#')==0)
		{
		SetFlag(flags, StringFormatFlags::Numeric);
		}
	else if(CharCompare(str[pos], '0')==0)
		{
		if(GetFlag(flags, StringFormatFlags::Zero))
			break;
		SetFlag(flags, StringFormatFlags::Zero);
		}
	else
		{
		break;
		}
	}
// Width
if(CharEqual(str[pos], '*'))
	{
	SetFlag(flags, StringFormatFlags::Width);
	pos++;
	}
else
	{
	pos+=StringScanUInt(&str[pos], &width);
	}
// Precision
if(CharEqual(str[pos], '.'))
	{
	pos++;
	if(CharEqual(str[pos], '*'))
		{
		SetFlag(flags, StringFormatFlags::Precision);
		pos++;
		}
	else
		{
		UINT len=StringScanUInt(&str[pos], &precision);
		if(len==0)
			precision=0;
		pos+=len;
		}
	}
// Size
for(; str[pos]; pos++)
	{
	if(CharEqual(str[pos], 'h'))
		continue;
	else if(CharEqual(str[pos], 'l'))
		continue;
	break;
	}
// Type
CHAR type=str[pos];
if(type==0)
	{
	format=StringFormat::None;
	return pos;
	}
switch(type)
	{
	case 'c':
		{
		format=StringFormat::Char;
		break;
		}
	case 'd':
		{
		format=StringFormat::Double;
		break;
		}
	case 'f':
		{
		format=StringFormat::Float;
		break;
		}
	case 'i':
		{
		format=StringFormat::Int;
		break;
		}
	case 's':
		{
		format=StringFormat::String;
		break;
		}
	case 'u':
		{
		format=StringFormat::UInt;
		break;
		}
	case 'x':
		{
		format=StringFormat::Hex;
		break;
		}
	default:
		{
		format=StringFormat::None;
		break;
		}
	}
return pos+1;
}


//=====================
// Printing Characters
//=====================

template <class _buf_t, class _char_t> UINT StringPrintChar(_buf_t* buf, UINT size, _char_t c)
{
if(!buf)
	return 1;
if(!size)
	return 0;
buf[0]=CharToChar<_buf_t, _char_t>(c);
return 1;
}

template <class _buf_t, class _char_t> UINT StringPrintChars(_buf_t* buf, UINT size, _char_t c, UINT count)
{
if(!buf)
	return count;
UINT print=MIN(size, count);
for(UINT u=0; u<print; u++)
	buf[u]=CharToChar<_buf_t, _char_t>(c);
return print;
}

template <class _buf_t, class _char_t> UINT StringPrintString(_buf_t* buf, UINT size, _char_t const* value)
{
if(!value)
	return 0;
UINT pos=0;
for(; value[pos]; pos++)
	{
	if(size)
		{
		if(pos==size)
			return pos;
		}
	if(buf)
		buf[pos]=CharToChar<_buf_t, _char_t>(value[pos]);
	}
return pos;
}

template <class _buf_t, class _char_t> UINT StringPrintString(_buf_t* buf, UINT size, _char_t const* value, StringFormatFlags flags, UINT width)
{
if(!value)
	return 0;
UINT len=0;
if(width>0)
	len=StringLength(value);
UINT pos=0;
if(len<width)
	{
	if(!GetFlag(flags, StringFormatFlags::Left))
		pos+=StringPrintChars(buf, size, ' ', width-len);
	}
pos+=StringPrintString(buf? &buf[pos]: nullptr, size>pos? size-pos: 0, value);
if(len<width)
	{
	if(GetFlag(flags, StringFormatFlags::Left))
		pos+=StringPrintChars(buf? &buf[pos]: nullptr, size>pos? size-pos: 0, ' ', width-len);
	}
if(pos<size)
	buf[pos]=0;
return pos;
}


//===================
// Printing Integers
//===================

template <class _char_t, class _uint_t> UINT StringPrintUInt(_char_t* str, UINT size, _uint_t value)
{
CHAR chars[22];
LPSTR buf=&chars[21];
*buf=0;
do
	{
	*--buf=(CHAR)((value%10)+'0');
	value/=10;
	}
while(value);
return StringPrintString(str, size, buf);
}

template <class _char_t, class _uint_t> UINT StringPrintUInt(_char_t* str, UINT size, _uint_t value, StringFormatFlags flags, UINT width)
{
UINT len=0;
if(width>0)
	len=StringPrintUInt<_char_t, _uint_t>(nullptr, 0, value, flags, 0);
UINT pos=0;
if(len<width)
	{
	if(!GetFlag(flags, StringFormatFlags::Left)&&!GetFlag(flags, StringFormatFlags::Zero))
		pos+=StringPrintChars(str, size, ' ', width-len);
	}
if(GetFlag(flags, StringFormatFlags::Signed))
	pos+=StringPrintChar(str? &str[pos]: nullptr, size>pos? size-pos: 0, '+');
if(len<width)
	{
	if(!GetFlag(flags, StringFormatFlags::Left)&&GetFlag(flags, StringFormatFlags::Zero))
		pos+=StringPrintChars(str? &str[pos]: nullptr, size>pos? size-pos: 0, '0', width-len);
	}
pos+=StringPrintUInt(str? &str[pos]: nullptr, size>pos? size-pos: 0, value);
if(len<width)
	{
	if(GetFlag(flags, StringFormatFlags::Left))
		pos+=StringPrintChars(str? &str[pos]: nullptr, size>pos? size-pos: 0, ' ', width-len);
	}
if(pos<size)
	str[pos]=0;
return pos;
}

template <class _char_t, class _int_t> UINT StringPrintInt(_char_t* str, UINT size, _int_t value, StringFormatFlags flags, UINT width)
{
UINT len=0;
if(width>0)
	len=StringPrintInt<_char_t, _int_t>(nullptr, 0, value, flags, 0);
UINT pos=0;
if(len<width)
	{
	if(!GetFlag(flags, StringFormatFlags::Left)&&!GetFlag(flags, StringFormatFlags::Zero))
		pos+=StringPrintChars(str, size, ' ', width-len);
	}
if(value<0)
	{
	pos+=StringPrintChar(str? &str[pos]: nullptr, size>pos? size-pos: 0, '-');
	value*=-1;
	}
else if(GetFlag(flags, StringFormatFlags::Signed))
	{
	pos+=StringPrintChar(str? &str[pos]: nullptr, size>pos? size-pos: 0, '+');
	}
if(len<width)
	{
	if(!GetFlag(flags, StringFormatFlags::Left)&&GetFlag(flags, StringFormatFlags::Zero))
		pos+=StringPrintChars(str? &str[pos]: nullptr, size>pos? size-pos: 0, '0', width-len);
	}
pos+=StringPrintUInt(str? &str[pos]: nullptr, size>pos? size-pos: 0, value);
if(len<width)
	{
	if(GetFlag(flags, StringFormatFlags::Left))
		pos+=StringPrintChars(str? &str[pos]: nullptr, size>pos? size-pos: 0, ' ', width-len);
	}
if(pos<size)
	str[pos]=0;
return pos;
}

template <class _char_t, class _uint_t> UINT StringPrintHex(_char_t* str, UINT size, _uint_t value)
{
CHAR chars[20];
LPSTR buf=&chars[19];
*buf=0;
do
	{
	CHAR c=(CHAR)((value%16)+'0');
	if(c>'9')
		c=(CHAR)(c+7);
	*--buf=c;
	value/=16;
	}
while(value);
return StringPrintString(str, size, buf);
}

template <class _char_t, class _uint_t> UINT StringPrintHex(_char_t* str, UINT size, _uint_t value, StringFormatFlags flags, UINT width)
{
UINT len=0;
if(width>0)
	len=StringPrintHex<_char_t, _uint_t>(nullptr, 0, value, flags, 0);
UINT pos=0;
if(len<width)
	{
	if(!GetFlag(flags, StringFormatFlags::Left)&&!GetFlag(flags, StringFormatFlags::Zero))
		pos+=StringPrintChars(str, size, ' ', width-len);
	}
if(GetFlag(flags, StringFormatFlags::Numeric))
	pos+=StringPrintString(str? &str[pos]: nullptr, size>pos? size-pos: 0, "0x");
if(len<width)
	{
	if(!GetFlag(flags, StringFormatFlags::Left)&&GetFlag(flags, StringFormatFlags::Zero))
		pos+=StringPrintChars(str? &str[pos]: nullptr, size>pos? size-pos: 0, '0', width-len);
	}
pos+=StringPrintHex(str? &str[pos]: nullptr, size>pos? size-pos: 0, value);
if(len<width)
	{
	if(GetFlag(flags, StringFormatFlags::Left))
		StringPrintChars(str? &str[pos]: nullptr, size>pos? size-pos: 0, ' ', width-len);
	}
if(pos<size)
	str[pos]=0;
return pos;
}

UINT StringPrintHex(LPSTR str, UINT size, UINT value, StringFormatFlags flags, UINT width)
{
return StringPrintHex<CHAR, UINT>(str, size, value, flags, width);
}

UINT StringPrintHex64(LPSTR str, UINT size, UINT64 value, StringFormatFlags flags, UINT width)
{
return StringPrintHex<CHAR, UINT64>(str, size, value, flags, width);
}

UINT StringPrintInt(LPSTR str, UINT size, INT value, StringFormatFlags flags, UINT width)
{
return StringPrintInt<CHAR, INT>(str, size, value, flags, width);
}

UINT StringPrintInt64(LPSTR str, UINT size, INT64 value, StringFormatFlags flags, UINT width)
{
return StringPrintInt<CHAR, INT64>(str, size, value, flags, width);
}

UINT StringPrintUInt(LPSTR str, UINT size, UINT value)
{
return StringPrintUInt<CHAR, UINT>(str, size, value);
}

UINT StringPrintUInt64(LPSTR str, UINT size, UINT64 value)
{
return StringPrintUInt<CHAR, UINT64>(str, size, value);
}

UINT StringPrintUInt(LPSTR str, UINT size, UINT value, StringFormatFlags flags, UINT width)
{
return StringPrintUInt<CHAR, UINT>(str, size, value, flags, width);
}

UINT StringPrintUInt64(LPSTR str, UINT size, UINT64 value, StringFormatFlags flags, UINT width)
{
return StringPrintUInt<CHAR, UINT64>(str, size, value, flags, width);
}


//=================
// Printing Floats
//=================

template <class _float_t> INT FloatNormalize(_float_t& f, _float_t max, _float_t min)
{
if(f==0)
	return 0;
INT ex=0;
if(f>=max)
	{
	if(f>=1e32f)
		{
		f/=1e32f;
		ex+=32;
		}
	if(f>=1e16f)
		{
		f/=1e16f;
		ex+=16;
		}
	if(f>=1e8f)
		{
		f/=1e8f;
		ex+=8;
		}
	if(f>=1e4f)
		{
		f/=1e4f;
		ex+=4;
		}
	if(f>=1e2f)
		{
		f/=1e2f;
		ex+=2;
		}
	if(f>=1e1f)
		{
		f/=1e1f;
		ex+=1;
		}
	return ex;
	}
if(f<min)
	{
	if(f<1e-31f)
		{
		f*=1e32f;
		ex-=32;
		}
	if(f<1e-15f)
		{
		f*=1e16f;
		ex-=16;
		}
	if(f<1e-7f)
		{
		f*=1e8f;
		ex-=8;
		}
	if(f<1e-3f)
		{
		f*=1e4f;
		ex-=4;
		}
	if(f<1e-1f)
		{
		f*=1e2f;
		ex-=2;
		}
	if(f<1e0f)
		{
		f*=1e1f;
		ex-=1;
		}
	}
return ex;
}

template <> INT FloatNormalize<DOUBLE>(DOUBLE& f, DOUBLE max, DOUBLE min)
{
if(f==0)
	return 0;
INT ex=0;
if(f>=max)
	{
	if(f>=1e256)
		{
		f/=1e256;
		ex+=256;
		}
	if(f>=1e128)
		{
		f/=1e128;
		ex+=128;
		}
	if(f>=1e64)
		{
		f/=1e64;
		ex+=64;
		}
	if(f>=1e32)
		{
		f/=1e32;
		ex+=32;
		}
	if(f>=1e16)
		{
		f/=1e16;
		ex+=16;
		}
	if(f>=1e8)
		{
		f/=1e8;
		ex+=8;
		}
	if(f>=1e4)
		{
		f/=1e4;
		ex+=4;
		}
	if(f>=1e2)
		{
		f/=1e2;
		ex+=2;
		}
	if(f>=1e1)
		{
		f/=1e1;
		ex+=1;
		}
	return ex;
	}
if(f<min)
	{
	if(f<1e-255)
		{
		f*=1e256;
		ex-=256;
		}
	if(f<1e-127)
		{
		f*=1e128;
		ex-=128;
		}
	if(f<1e-63)
		{
		f*=1e64;
		ex-=64;
		}
	if(f<1e-31)
		{
		f*=1e32;
		ex-=32;
		}
	if(f<1e-15)
		{
		f*=1e16;
		ex-=16;
		}
	if(f<1e-7)
		{
		f*=1e8;
		ex-=8;
		}
	if(f<1e-3)
		{
		f*=1e4;
		ex-=4;
		}
	if(f<1e-1)
		{
		f*=1e2;
		ex-=2;
		}
	if(f<1e0)
		{
		f*=1e1;
		ex-=1;
		}
	}
return ex;
}

template <class _float_t> VOID FloatSplit(_float_t f, UINT& integral, UINT& decimal, INT& exponent, UINT& width, UINT& precision)
{
_float_t mul[]={ 1e0f, 1e1f, 1e2f, 1e3f, 1e4f, 1e5f, 1e6f, 1e7f, 1e8f, 1e9f };
_float_t div[]={ 1e0f, 1e-1f, 1e-2f, 1e-3f, 1e-4f, 1e-5f };
UINT sel=MIN(width, ARRAYSIZE(mul)-1);
UINT prec=MIN(precision, ARRAYSIZE(div)-1);
exponent=FloatNormalize<_float_t>(f, mul[sel], div[prec]);
integral=(UINT)f;
_float_t remainder=f-(_float_t)integral;
remainder*=mul[prec];
decimal=(UINT)remainder;
remainder-=(_float_t)decimal;
if(remainder>=0.5)
	{
	decimal++;
	if(decimal==1000000000)
		{
		integral++;
		decimal=0;
		if((_float_t)integral>=mul[sel])
			{
			exponent++;
			integral/=10;
			}
		}
	}
}

template <class _char_t, class _float_t> UINT StringPrintFloat(_char_t* str, UINT size, _float_t f, StringFormatFlags flags, UINT width, UINT precision)
{
UINT pos=0;
if(std::isnan(f))
	{
	pos+=StringPrintString(str, size, "nan");
	return pos;
	}
if(f<0)
	{
	pos+=StringPrintChar(str, size, '-');
	f*=-1;
	}
else if(GetFlag(flags, StringFormatFlags::Signed))
	{
	pos+=StringPrintChar(str, size, '+');
	}
if(std::isinf(f))
	{
	pos+=StringPrintString(str? &str[pos]: nullptr, size>pos? size-pos: 0, "inf");
	return pos;
	}
UINT integral=0;
UINT decimal=0;
INT exponent=0;
FloatSplit(f, integral, decimal, exponent, width, precision);
pos+=StringPrintUInt(str? &str[pos]: nullptr, size>pos? size-pos: 0, integral);
CHAR chars[16];
LPSTR buf=&chars[15];
*buf=0;
INT idec=precision;
for(; idec>1&&decimal%10==0; idec--)
	{
	if(GetFlag(flags, StringFormatFlags::Zero))
		*--buf='0';
	decimal/=10;
	}
for(; idec>0; idec--)
	{
	*--buf=(CHAR)((decimal%10)+'0');
	decimal/=10;
	}
if(precision)
	*--buf='.';
pos+=StringPrintString(str? &str[pos]: nullptr, size>pos? size-pos: 0, buf);
if(exponent!=0||GetFlag(flags, StringFormatFlags::Numeric))
	{
	pos+=StringPrintChar(str? &str[pos]: nullptr, size>pos? size-pos: 0, 'e');
	if(exponent<0)
		{
		pos+=StringPrintChar(str? &str[pos]: nullptr, size>pos? size-pos: 0, '-');
		exponent*=-1;
		}
	pos+=StringPrintUInt(str? &str[pos]: nullptr, size>pos? size-pos: 0, exponent);
	}
if(pos<size)
	str[pos]=0;
return pos;
}

UINT StringPrintDouble(LPSTR str, UINT size, DOUBLE value, StringFormatFlags flags, UINT width, UINT prec)
{
return StringPrintFloat<CHAR, DOUBLE>(str, size, value, flags, width, prec);
}

UINT StringPrintFloat(LPSTR str, UINT size, FLOAT value, StringFormatFlags flags, UINT width, UINT prec)
{
return StringPrintFloat<CHAR, FLOAT>(str, size, value, flags, width, prec);
}


//============
// Formatting
//============

template <class _char_t> ALWAYS_INLINE UINT StringPrintArgs(_char_t* str, UINT size, LPCSTR format, VariableArguments const& args)
{
if(!format)
	return 0;
UINT pos=0;
UINT arg=0;
for(UINT fmt=0; format[fmt]; )
	{
	if(pos+1==size)
		break;
	StringFormat str_format=StringFormat::None;
	StringFormatFlags flags=StringFormatFlags::None;
	UINT width=UINT_MAX;
	UINT prec=UINT_MAX;
	fmt+=StringGetFormat(&format[fmt], str_format, flags, width, prec);
	if(str_format==StringFormat::None)
		{
		pos+=StringPrintChar(str? &str[pos]: nullptr, size? size-pos: 0, format[fmt++]);
		continue;
		}
	if(str_format==StringFormat::Percent)
		{
		pos+=StringPrintChar(str? &str[pos]: nullptr, size? size-pos: 0, '%');
		continue;
		}
	if(GetFlag(flags, StringFormatFlags::Width))
		{
		if(!args.GetAt(arg++, width))
			return 0;
		}
	if(GetFlag(flags, StringFormatFlags::Precision))
		{
		if(!args.GetAt(arg++, prec))
			return 0;
		}
	UINT copy=size>pos? size-pos: 0;
	switch(str_format)
		{
		case StringFormat::Int:
			{
			INT64 i=0;
			if(!args.GetAt(arg++, i))
				return 0;
			pos+=StringPrintInt(str? &str[pos]: nullptr, copy, i, flags, width==(UINT)-1? 0: width);
			continue;
			}
		case StringFormat::UInt:
			{
			UINT64 u=0;
			if(!args.GetAt(arg++, u))
				return 0;
			pos+=StringPrintUInt(str? &str[pos]: nullptr, copy, u, flags, width==(UINT)-1? 0: width);
			continue;
			}
		case StringFormat::Hex:
			{
			UINT64 u=0;
			if(!args.GetAt(arg++, u))
				return 0;
			pos+=StringPrintHex(str? &str[pos]: nullptr, copy, u, flags, width==(UINT)-1? 0: width);
			continue;
			}
		case StringFormat::Float:
			{
			FLOAT f=0;
			if(!args.GetAt(arg++, f))
				return 0;
			pos+=StringPrintFloat(str? &str[pos]: nullptr, copy, f, flags, width, prec);
			continue;
			}
		case StringFormat::Double:
			{
			DOUBLE d=0;
			if(!args.GetAt(arg++, d))
				return 0;
			pos+=StringPrintFloat(str? &str[pos]: nullptr, copy, d, flags, width, prec);
			continue;
			}
		case StringFormat::Char:
			{
			WCHAR c=' ';
			if(!args.GetAt(arg++, c))
				return 0;
			pos+=StringPrintChar(str? &str[pos]: nullptr, copy, c);
			continue;
			}
		case StringFormat::String:
			{
			LPCSTR p=nullptr;
			if(args.GetAt(arg, p))
				{
				arg++;
				pos+=StringPrintString(str? &str[pos]: nullptr, copy, p, flags, width==(UINT)-1? 0: width);
				continue;
				}
			LPCWSTR pw=nullptr;
			if(args.GetAt(arg, pw))
				{
				arg++;
				pos+=StringPrintString(str? &str[pos]: nullptr, copy, pw, flags, width==(UINT)-1? 0: width);
				continue;
				}
			return 0;
			}
		default:
			continue;
		}
	}
if(pos<size)
	str[pos]=0;
return pos;
}

UINT StringPrintArgs(LPSTR str, UINT size, LPCSTR format, VariableArguments const& args)
{
return StringPrintArgs<CHAR>(str, size, format, args);
}

UINT StringPrintArgs(LPWSTR str, UINT size, LPCSTR format, VariableArguments const& args)
{
return StringPrintArgs<WCHAR>(str, size, format, args);
}


//==========
// Scanning
//==========

template <class _char_t> ALWAYS_INLINE UINT StringScanArgs(_char_t const* str, LPCSTR format, VariableArguments& args)
{
if(!str||!format)
	return 0;
UINT pos=0;
UINT arg=0;
UINT read=0;
for(UINT fmt=0; format[fmt]; )
	{
	if(str[pos]==0)
		return read;
	StringFormat str_format=StringFormat::None;
	StringFormatFlags flags=StringFormatFlags::None;
	UINT width=UINT_MAX;
	UINT prec=UINT_MAX;
	fmt+=StringGetFormat(&format[fmt], str_format, flags, width, prec);
	if(str_format==StringFormat::None)
		{
		if(str[pos++]!=format[fmt++])
			return read;
		continue;
		}
	if(str_format==StringFormat::Percent)
		{
		if(!CharEqual(str[pos++], '%'))
			return read;
		continue;
		}
	bool hex=false;
	switch(str_format)
		{
		case StringFormat::Char:
			{
			_char_t tc=str[pos];
			CHAR* pc=nullptr;
			if(args.GetAt(arg, pc))
				{
				*pc=CharToChar<CHAR, _char_t>(tc);
				arg++;
				read++;
				pos++;
				continue;
				}
			WCHAR* pwc=nullptr;
			if(args.GetAt(arg, pwc))
				{
				*pwc=CharToChar<WCHAR, _char_t>(tc);
				arg++;
				read++;
				pos++;
				continue;
				}
			return read;
			}
		case StringFormat::Int:
			{
			INT64 i=0;
			UINT len=StringScanInt(&str[pos], &i);
			if(!len)
				return read;
			INT* p32=nullptr;
			if(args.GetAt(arg, p32))
				{
				if(i<-2147483647||i>2147483647)
					return read;
				*p32=(INT)i;
				arg++;
				read++;
				pos+=len;
				continue;
				}
			INT64* p64=nullptr;
			if(args.GetAt(arg, p64))
				{
				*p64=i;
				arg++;
				read++;
				pos+=len;
				continue;
				}
			return read;
			}
		case StringFormat::Hex:
			{
			hex=true;
			}
		case StringFormat::UInt:
			{
			UINT64 u=0;
			UINT len=StringScanUInt(&str[pos], &u, hex);
			if(!len)
				return read;
			UINT* p32=nullptr;
			if(args.GetAt(arg, p32))
				{
				if(u>0xFFFFFFFF)
					return read;
				*p32=(UINT)u;
				arg++;
				read++;
				pos+=len;
				continue;
				}
			UINT64* p64=nullptr;
			if(args.GetAt(arg, p64))
				{
				*p64=u;
				arg++;
				read++;
				pos+=len;
				continue;
				}
			return read;
			}
		case StringFormat::Float:
			{
			FLOAT f=0;
			UINT len=StringScanFloat(&str[pos], &f);
			if(!len)
				return read;
			FLOAT* p=nullptr;
			if(args.GetAt(arg, p))
				{
				*p=f;
				arg++;
				read++;
				pos+=len;
				continue;
				}
			return read;
			}
		case StringFormat::Double:
			{
			DOUBLE d=0;
			UINT len=StringScanFloat(&str[pos], &d);
			if(!len)
				return read;
			DOUBLE* p=nullptr;
			if(args.GetAt(arg, p))
				{
				*p=d;
				arg++;
				read++;
				pos+=len;
				continue;
				}
			return read;
			}
		case StringFormat::String:
			{
			LPSTR p=nullptr;
			LPWSTR pw=nullptr;
			if(!args.GetAt(arg, p))
				{
				if(!args.GetAt(arg, pw))
					return read;
				}
			UINT size=0;
			if(!args.GetAt(arg+1, size))
				return read;
			UINT len=0;
			if(p)
				{
				len=StringScanString(&str[pos], p, size, format[fmt]);
				}
			else if(pw)
				{
				len=StringScanString(&str[pos], pw, size, format[fmt]);
				}
			if(!len)
				return read;
			arg+=2;
			read++;
			pos+=len;
			continue;
			}
		default:
			break;
		}
	}
return read;
}

UINT StringScanArgs(LPCSTR str, LPCSTR format, VariableArguments& args)
{
return StringScanArgs<CHAR>(str, format, args);
}

UINT StringScanArgs(LPCWSTR str, LPCSTR format, VariableArguments& args)
{
return StringScanArgs<WCHAR>(str, format, args);
}


//============
// Comparison
//============

template <class _char1_t, class _char2_t> inline INT StringCompare(_char1_t const* str1, _char2_t const* str2, UINT count, BOOL cs)
{
if(!str1)
	{
	if(!str2)
		return 0;
	if(!str2[0])
		return 0;
	return -1;
	}
if(!str2)
	{
	if(!str1[0])
		return 0;
	return 1;
	}
UINT pos1=0;
UINT pos2=0;
while(str1[pos1]&&str2[pos2])
	{
	#ifndef _DRIVER
	FLOAT f1=0;
	UINT len1=StringScanFloat(&str1[pos1], &f1);
	FLOAT f2=0;
	UINT len2=StringScanFloat(&str2[pos2], &f2);
	if(len1==0)
		{
		if(len2==0)
			{
			#endif
			INT cmp=CharCompare(str1[pos1], str2[pos2], cs);
			if(cmp==0)
				{
				pos1++;
				pos2++;
				if(pos2==count)
					return 0;
				continue;
				}
			return cmp;
			#ifndef _DRIVER
			}
		return -1;
		}
	if(len2==0)
		return 1;
	if(f1>f2)
		return 1;
	if(f2>f1)
		return -1;
	pos1+=len1;
	pos2+=len2;
	#endif
	}
if(str1[pos1]==0)
	{
	if(str2[pos2]==0)
		return 0;
	return -1;
	}
return 1;
}

INT StringCompare(LPCSTR str1, LPCSTR str2, UINT len, BOOL cs)
{
return StringCompare<CHAR, CHAR>(str1, str2, len, cs);
}

INT StringCompare(LPCSTR str1, LPCWSTR str2, UINT len, BOOL cs)
{
return StringCompare<CHAR, WCHAR>(str1, str2, len, cs);
}

INT StringCompare(LPCWSTR str1, LPCSTR str2, UINT len, BOOL cs)
{
return StringCompare<WCHAR, CHAR>(str1, str2, len, cs);
}

INT StringCompare(LPCWSTR str1, LPCWSTR str2, UINT len, BOOL cs)
{
return StringCompare<WCHAR, WCHAR>(str1, str2, len, cs);
}
