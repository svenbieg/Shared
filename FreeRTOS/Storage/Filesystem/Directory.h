//=============
// Directory.h
//=============

#pragma once


//=======
// Using
//=======

#include "Storage/Database/Directory.h"


//===========
// Namespace
//===========

namespace Storage {
	namespace Filesystem {


//===========
// Directory
//===========

class Directory: public Storage::Directory
{
public:
	// Common
	static Handle<Storage::Directory> Open(Handle<String> Path);

	// Storage.Directory
	Handle<Storage::File> CreateFile(Handle<String> Path, FileCreateMode CreateMode=FileCreateMode::OpenExisting, FileAccessMode AccessMode=FileAccessMode::ReadOnly, FileShareMode ShareMode=FileShareMode::ShareRead)override;
	Handle<Storage::DirectoryIterator> First()override;
	Handle<Object> Get(Handle<String> Path)override;

private:
	// Con-/Destructors
	Directory(Handle<String> Path);

	// Common
	Handle<Storage::Database::Directory> hDirectory;
};

}}