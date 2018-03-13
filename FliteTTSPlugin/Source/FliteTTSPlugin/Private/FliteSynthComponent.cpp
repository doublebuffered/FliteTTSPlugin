/*  Copyright (C) 2018 DoubleBuffered Games

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

#include "FliteSynthComponent.h"
#include "FliteTTsPluginPrivatePCH.h"

UFliteSynthComponent::UFliteSynthComponent()
{	
}


void UFliteSynthComponent::Play(float StartTime)
{
	InitializeVoice();

	Super::Play(StartTime);
}

void UFliteSynthComponent::FadeIn(float FadeInDuration, float FadeVolumeLevel, float StartTime)
{
	InitializeVoice();
	
	Super::FadeIn(FadeInDuration, FadeVolumeLevel, StartTime);
}

void UFliteSynthComponent::Stop()
{
	Super::Stop();
}

void UFliteSynthComponent::PlayVoice(const FString& StringToPlay)
{
	InitializeVoice();

	if (VoiceBuffer)
	{
		IFliteTTSPlugin& TTSPlugin = IFliteTTSPlugin::Get();

		TArray<uint8> AudioBuffer;
		int32 SampleRate = 0;
		int32 NumChannels = 0;
		if (TTSPlugin.GenerateVoiceData(VoiceName, *StringToPlay, AudioBuffer, SampleRate, NumChannels))
		{
			VoiceBuffer->ResetAudio();
			VoiceBuffer->NumChannels = NumChannels;
			VoiceBuffer->SampleRate = SampleRate;
			VoiceBuffer->Duration = (float)AudioBuffer.Num() / sizeof(short) / SampleRate / NumChannels;
			VoiceBuffer->QueueAudio(AudioBuffer.GetData(), AudioBuffer.Num());

			PlayInternal();
		}
	}
}

void UFliteSynthComponent::SetVoiceName(FName NewVoiceName)
{
	VoiceName = NewVoiceName;
}

void UFliteSynthComponent::GetValidVoiceNames(TArray<FName>& OutVoiceNames)
{
	IFliteTTSPlugin& TTSPlugin = IFliteTTSPlugin::Get();
	TTSPlugin.GetVoiceNames(OutVoiceNames);
}

void UFliteSynthComponent::InitializeVoice()
{
	ensureMsgf(!Sound || Cast<USoundWaveProcedural>(Sound), TEXT("Flite components cannot have Set Sound called on them!"));

	FAudioDevice* AudioDevice = GetAudioDevice();
	if (AudioDevice && (!Sound || Sound != VoiceBuffer))
	{
		if (VoiceName == NAME_None)
		{
			TArray<FName> ValidVoices;
			GetValidVoiceNames(ValidVoices);

			if (ValidVoices.Num() > 0)
			{
				SetVoiceName(ValidVoices[0]);
			}
		}

		VoiceBuffer = NewObject<USoundWaveProcedural>(this, TEXT("VoiceBuffer"), RF_Transient);

		// Copy sound base data to the sound
		VoiceBuffer->SourceEffectChain = SourceEffectChain;
		VoiceBuffer->SoundSubmixObject = SoundSubmix;
		VoiceBuffer->SoundSubmixSends = SoundSubmixSends;

		SetSound(VoiceBuffer);
	}
}