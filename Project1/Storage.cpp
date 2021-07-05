#include "Storage.h"

Storage::Storage()
{
	storagePos = { 0 , 0 };
	isEmpty = true;
	id = -1;
	RECT storageRc = { 0,0,0,0 };
	skullTile = nullptr;
}

Storage::~Storage()
{
}
