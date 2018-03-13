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

#pragma once

#include "ModuleManager.h"


/**
 * The public interface to this module.  In most cases, this interface is only public to sibling modules 
 * within this plugin.
 */
class IFliteTTSPlugin : public IModuleInterface
{

public:

	/**
	 * Singleton-like access to this module's interface.  This is just for convenience!
	 * Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
	 *
	 * @return Returns singleton instance, loading the module on demand if needed
	 */
	static inline IFliteTTSPlugin& Get()
	{
		return FModuleManager::LoadModuleChecked< IFliteTTSPlugin >( "FliteTTSPlugin" );
	}

	/**
	 * Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
	 *
	 * @return True if the module is loaded and ready to use
	 */
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded( "FliteTTSPlugin" );
	}

	/** Returns list of valid voices */
	virtual void GetVoiceNames(TArray<FName>& OutVoices) = 0;

	/** Plays text with given voice */
	virtual bool PlayVoice(FName VoiceName, const TCHAR* StringToPlay) = 0;

	/** Fills a buffer with 16bit PCM data for the string to play */
	virtual bool GenerateVoiceData(FName VoiceName, const TCHAR* StringToPlay, TArray<uint8>& AudioBuffer, int32& OutSampleRate, int32& OutNumChannels) = 0;
};

