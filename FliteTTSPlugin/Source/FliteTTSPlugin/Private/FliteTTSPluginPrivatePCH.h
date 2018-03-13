/*  Copyright (C) 2016 Ideoservo Games
	Modified (C) 2018 DoubleBuffered Games

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
    USA */

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