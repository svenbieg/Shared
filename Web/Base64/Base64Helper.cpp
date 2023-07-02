//==================
// Base64Helper.cpp
//==================

#include "pch.h"


//=======
// Using
//=======

#include "Base64Helper.h"


//===========
// Namespace
//===========

namespace Storage {
	namespace Base64 {


//=======
// Table
//=======

//BASE64    ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/
//Base64Url ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_

const BYTE Base64Table[]=
	{
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, // 0x00
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, // 0x10
//                                                           +         -         /
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,  62, 255,  62, 255,  63, // 0x20
//    0    1    2    3    4    5    6    7    8    9                   =
	 52,  53,  54,  55,  56,  57,  58,  59,  60,  61, 255, 255, 255,   0, 255, 255, // 0x30
//         A    B    C    D    E    F    G    H    I    J    K    L    M    N    O
	255,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14, // 0x40
//    P    Q    R    S    T    U    V    W    X    Y    Z                        _
	 15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25, 255, 255, 255, 255,  63, // 0x50
//         a    b    c    d    e    f    g    h    i    j    k    l    m    n    o
	255,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40, // 0x60
//    p    q    r    s    t    u    v    w    x    y    z
	 41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51, 255, 255, 255, 255, 255, // 0x70
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, // 0x80
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, // 0x90
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, // 0xA0
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, // 0xB0
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, // 0xC0
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, // 0xD0
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, // 0xE0
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, // 0xF0
	};


//========
// Common
//========

Handle<Buffer> Base64Decode(LPCSTR input, UINT input_size)
{
UINT size=Base64Decode(input, input_size, nullptr, 0);
if(!size)
	return nullptr;
Handle<Buffer> buf=new Buffer(size);
Base64Decode(input, input_size, buf->Begin(), size);
return buf;
}

Handle<String> Base64DecodeString(Handle<String> input)
{
if(!input)
	return nullptr;
return Base64DecodeString(input->Begin(), 0);
}

Handle<String> Base64DecodeString(LPCSTR input, UINT input_size)
{
UINT size=Base64Decode(input, input_size, nullptr, 0);
if(!size)
	return nullptr;
Handle<String> str=new String(size+1, nullptr);
auto str_ptr=(BYTE*)str->Begin();
Base64Decode(input, input_size, str_ptr, size);
str_ptr[size]=0;
return str;
}

UINT Base64Decode(LPCSTR input, UINT input_size, BYTE* output, UINT output_size)
{
if(!input)
	return 0;
UINT size=0;
if(input_size==0)
	input_size=-1;
UINT pos=0;
for(; pos<input_size; pos++)
	{
	if(!input[pos])
		break;
	if(Base64Table[(int)input[pos]]!=255)
		size++;
	}
if(input_size==-1)
	input_size=pos;
UINT block_size=BlockAlign(size, 4);
UINT pad=block_size-size;
if(block_size==0||pad>2)
	return 0;
UINT len=block_size/4*3-pad;
if(!output)
	return len;
if(output_size<len)
	return 0;
BYTE block[4];
size=0;
pad=0;
auto in=input;
auto in_end=in+input_size;
auto out=output;
while(out-output<(INT)len)
	{
	CHAR c='=';
	if(in<in_end)
		c=*in++;
	BYTE tmp=Base64Table[(int)c];
	if(tmp==255)
		continue;
	if(c=='=')
		pad++;
	block[size]=tmp;
	size++;
	if(size==4)
		{
		*out++=(block[0]<<2)|(block[1]>>4);
		if(pad<2)
			*out++=(block[1]<<4)|(block[2]>>2);
		if(pad<1)
			*out++=(block[2]<<6)|block[3];
		size=0;
		if(pad>0)
			break;
		}
	}
return len;
}

UINT Base64Encode(VOID const* input, UINT input_size, LPSTR output, UINT output_size)
{
UINT size=input_size*4/3+4;
size+=size/72+1;
if(!output)
	return size;
if(output_size<size)
	return 0;
auto in=(BYTE const*)input;
auto in_end=in+input_size;
auto out=output;
UINT line_len=0;
while(in_end-in>=3)
	{
	*out++=Base64Table[in[0]>>2];
	*out++=Base64Table[((in[0]&0x03)<<4)|(in[1]>>4)];
	*out++=Base64Table[((in[1]&0x0F)<<2)|(in[2]>>6)];
	*out++=Base64Table[in[2]&0x3F];
	in+=3;
	line_len+=4;
	if(line_len>=72)
		{
		*out++='\n';
		line_len=0;
		}
	}
if(in<in_end)
	{
	*out++=Base64Table[in[0]>>2];
	if(in_end-in==1)
		{
		*out++=Base64Table[(in[0]&0x03)<<4];
		*out++='=';
		}
	else
		{
		*out++=Base64Table[((in[0]&0x03)<<4)|(in[1]>>4)];
		*out++=Base64Table[(in[1]&0x0F)<<2];
		}
	*out++='=';
	line_len+=4;
	if(line_len>=72)
		{
		*out++='\n';
		line_len=0;
		}
	}
*out++=0;
return (UINT)(out-output);
}

}}