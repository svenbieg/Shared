//===============
// Directory.cpp
//===============

#include "pch.h"


//=======
// Using
//=======

#include "Directory.h"
#include "Partition.h"


//===========
// Namespace
//===========

namespace Storage {
	namespace Filesystem {


//========
// Common
//========

Handle<Storage::Directory> Directory::Open(Handle<String> path)
{
auto db=Partition::Open();
return nullptr;
}


//===================
// Storage.Directory
//===================

Handle<Storage::File> Directory::CreateFile(Handle<String> path, FileCreateMode create, FileAccessMode access, FileShareMode share)
{
return hDirectory->CreateFile(path, create, access, share);
}

Handle<Storage::DirectoryIterator> Directory::First()
{
return hDirectory->First();
}

Handle<Object> Directory::Get(Handle<String> path)
{
return hDirectory->Get(path);
}


//==========================
// Con-/Destructors Private
//==========================

Directory::Directory(Handle<String> path):
Storage::Directory(path)
{}

}}