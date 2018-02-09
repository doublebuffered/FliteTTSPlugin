// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "FliteTTSPluginPrivatePCH.h"
#include "Interfaces/IPluginManager.h"
#include "Containers/StringConv.h"

extern "C" {

	typedef cst_voice*(*FliteRegisterFunc)(const char*);

	// Functions for built in voices
	cst_voice *register_cmu_us_rms(const char *voxdir);
	cst_voice *register_cmu_us_slt(const char *voxdir);
}

struct FFliteVoice
{
	FFliteVoice(FName InName, void* InLibrary, cst_voice* InVoice)
		: Name(InName), Library(InLibrary), Voice(InVoice)
	{
	}

	/** Name of the voice, derived from name in function */
	FName Name;

	/** Library loaded for this voice */
	void* Library;

	/** Actual voice data for this voice */
	cst_voice* Voice;
};

class FFliteTTSPlugin : public IFliteTTSPlugin
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	virtual void GetVoiceNames(TArray<FName>& OutVoices) override;
	virtual bool PlayVoice(FName VoiceName, const TCHAR* StringToPlay) override;

protected:
	static void FreeDependency(void*& Handle);
	static bool LoadDependency(const FString& Dir, const FString& Name, void*& Handle);

	void* LibFlite;
	TArray<FFliteVoice> LoadedVoices;

	bool RegisterVoice(cst_voice* Voice, void* Library);
	FFliteVoice* FindVoice(FName VoiceName);
};

IMPLEMENT_MODULE( FFliteTTSPlugin, FliteTTSPlugin )

void FFliteTTSPlugin::StartupModule()
{
	// This code will execute after your module is loaded into memory (but after global variables are initialized, of course.)
	const FString BaseDir = IPluginManager::Get().FindPlugin("FliteTTSPlugin")->GetBaseDir();
	const FString FliteDir = FPaths::Combine(*BaseDir, TEXT("ThirdParty"), TEXT("flite"), TEXT("lib"));

#if PLATFORM_64BITS
	const FString LibDir = FPaths::Combine(*FliteDir, TEXT("x64"));
#else
	const FString LibDir = FPaths::Combine(*FliteDir, TEXT("Win32"));
#endif

	if (!LoadDependency(LibDir, TEXT("fliteDll"), LibFlite))
	{
		ShutdownModule();
		return;// false;
	}

	flite_init();

	void* LoadedLibrary = nullptr;
	if (LoadDependency(LibDir, TEXT("cmu_us_rms"), LoadedLibrary))
	{
		RegisterVoice(register_cmu_us_rms(nullptr), LoadedLibrary);
	}

	if (LoadDependency(LibDir, TEXT("cmu_us_slt"), LoadedLibrary))
	{
		RegisterVoice(register_cmu_us_slt(nullptr), LoadedLibrary);
	}
}


void FFliteTTSPlugin::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	for (FFliteVoice& LoadedVoice : LoadedVoices)
	{
		delete_voice(LoadedVoice.Voice);
		FreeDependency(LoadedVoice.Library);
	}

	LoadedVoices.Empty();

	FreeDependency(LibFlite);
}

void FFliteTTSPlugin::FreeDependency(void*& Handle)
{
	if (Handle != nullptr)
	{
		FPlatformProcess::FreeDllHandle(Handle);
		Handle = nullptr;
	}
}


bool FFliteTTSPlugin::LoadDependency(const FString& Dir, const FString& Name, void*& Handle)
{
	FString Lib = Name + TEXT(".") + FPlatformProcess::GetModuleExtension();
	FString Path = Dir.IsEmpty() ? *Lib : FPaths::Combine(*Dir, *Lib);

	Handle = FPlatformProcess::GetDllHandle(*Path);

	if (Handle == nullptr)
	{
		GLog->Logf(ELogVerbosity::Warning, TEXT("FliteTTSPlugin: Failed to load required library %s. Plug-in will not be functional."), *Lib);
		return false;
	}

	return true;
}


bool FFliteTTSPlugin::RegisterVoice(cst_voice* Voice, void* Library)
{
	if (Voice && Library)
	{
		new(LoadedVoices) FFliteVoice(Voice->name, Library, Voice);
		return true;
	}
	return false;
}

FFliteVoice* FFliteTTSPlugin::FindVoice(FName VoiceName)
{
	for (FFliteVoice& LoadedVoice : LoadedVoices)
	{
		if (LoadedVoice.Name == VoiceName)
		{
			return &LoadedVoice;
		}
	}
	return nullptr;
}

void FFliteTTSPlugin::GetVoiceNames(TArray<FName>& OutVoices)
{
	for (FFliteVoice& LoadedVoice : LoadedVoices)
	{
		OutVoices.Add(LoadedVoice.Name);
	}
}

bool FFliteTTSPlugin::PlayVoice(FName VoiceName, const TCHAR* StringToPlay)
{
	FFliteVoice* FoundVoice = FindVoice(VoiceName);

	if (FoundVoice)
	{
		auto AnsiText = StringCast<ANSICHAR>(StringToPlay);

		flite_text_to_speech(AnsiText.Get(), FoundVoice->Voice, "play");
	}
	return false;
}