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

#pragma once

#include "CoreMinimal.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundWaveProcedural.h"
#include "FliteSynthComponent.generated.h"

/** Implements interaction between Flite library and the UE4 audio mixer */
UCLASS(ClassGroup = Audio, meta = (BlueprintSpawnableComponent))
class FLITETTSPLUGIN_API UFliteSynthComponent : public UAudioComponent
{
	GENERATED_BODY()

public:
	/** Constructor */
	UFliteSynthComponent();

	//~ Begin UAudioComponent Interface
	virtual void Play(float StartTime) override;
	virtual void FadeIn(float FadeInDuration, float FadeVolumeLevel, float StartTime) override;
	virtual void Stop() override;
	//~ End AudioComponent Interface.

	/** The voice name to use for this component, will affect future generation */
	UPROPERTY(EditAnywhere, Category = Voice)
	FName VoiceName;

	/** The source effect chain to use for this sound. */
	UPROPERTY(EditAnywhere, Category = Effects)
	USoundEffectSourcePresetChain* SourceEffectChain;

	/** Submix this sound belongs to */
	UPROPERTY(EditAnywhere, Category = Effects)
	USoundSubmix* SoundSubmix;

	/** An array of submix sends. Audio from this sound will send a portion of its audio to these effects.  */
	UPROPERTY(EditAnywhere, Category = Effects)
	TArray<FSoundSubmixSendInfo> SoundSubmixSends;

	/** Play a string */
	UFUNCTION(BlueprintCallable, Category = "Flite")
	virtual void PlayVoice(const FString& StringToPlay);

	/** Sets voice to specified name */
	UFUNCTION(BlueprintCallable, Category = "Flite")
	virtual void SetVoiceName(FName NewVoiceName);

	/** Gets list of valid voice names */
	UFUNCTION(BlueprintCallable, Category = "Flite")
	virtual void GetValidVoiceNames(TArray<FName>& OutVoiceNames);

protected:
	/** Procoedural wave that holds voice data */
	UPROPERTY(Transient)
	USoundWaveProcedural* VoiceBuffer;

	void InitializeVoice();
};