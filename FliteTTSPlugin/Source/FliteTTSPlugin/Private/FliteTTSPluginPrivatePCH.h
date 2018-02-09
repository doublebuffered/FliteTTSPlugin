// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

// Disable crazy warnings that claim that standard C library is "deprecated".
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4996)
#pragma warning(disable:4668)
#endif

#pragma push_macro("ARRAY_COUNT")
#undef ARRAY_COUNT

#if PLATFORM_WINDOWS
#include "Windows/PreWindowsApi.h"
#endif

#include "../../../ThirdParty/flite/include/flite.h"

#pragma pop_macro("ARRAY_COUNT")

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#include "IFliteTTSPlugin.h"
#include "CoreMinimal.h"