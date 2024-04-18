#pragma once
#include "Platform.h"

struct FNameEntryId
{
	//FNameEntryId() : Value(0) {}
	////FNameEntryId() {}
	//uint32 ToUnstableInt() const { return Value; }

	uint32 Value;
};

struct FNameEntryHeader
{
	uint16 bIsWide : 1;
	uint16 LowercaseProbeHash : 5;
	uint16 Len : 10;
};

struct FNameEntry
{
	FNameEntryHeader Header;
	union
	{
		char	AnsiName[1024];
		wchar_t	WideName[1024];
	};
};

class FName
{
public:
	FNameEntryId	ComparisonIndex;
	uint32			Number;
};
