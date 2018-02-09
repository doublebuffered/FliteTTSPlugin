// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
using System.IO;
namespace UnrealBuildTool.Rules
{
    using System.IO;
	public class FliteTTSPlugin : ModuleRules
	{
		public FliteTTSPlugin(ReadOnlyTargetRules Target) : base(Target)
        {
			PublicIncludePaths.AddRange(
				new string[] {
					"FliteTTSPlugin/Private",
                    "FliteTTSPlugin/ThirdParty/flite",
					// ... add public include paths required here ...
				}
				);

			PrivateIncludePaths.AddRange(
				new string[] {
					// ... add other private include paths required here ...
				}
				);

			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
					// ... add other public dependencies that you statically link with here ...
				}
				);

			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
                    "Projects"
					// ... add private dependencies that you statically link with here ...
				}
				);

			DynamicallyLoadedModuleNames.AddRange(
				new string[]
				{
					// ... add any modules that your module loads dynamically here ...
				}
				);
				
			// add Flite TTS libraries
            string BaseDirectory = Path.GetFullPath(Path.Combine(ModuleDirectory, "..", ".."));         
			
			if (Target.Platform == UnrealTargetPlatform.Win32 || Target.Platform == UnrealTargetPlatform.Win64)
            {
                string PlatformString = Target.Platform == UnrealTargetPlatform.Win32 ? "Win32" : "x64";

                string FliteDirectory = Path.Combine(BaseDirectory, "ThirdParty", "flite", "lib", PlatformString);
                PublicLibraryPaths.Add(FliteDirectory);
                PublicAdditionalLibraries.Add(Path.Combine(FliteDirectory, "fliteDll.lib"));
                PublicAdditionalLibraries.Add(Path.Combine(FliteDirectory, "cmu_us_rms.lib"));
                PublicAdditionalLibraries.Add(Path.Combine(FliteDirectory, "cmu_us_slt.lib"));
                RuntimeDependencies.Add(new RuntimeDependency(Path.Combine(FliteDirectory, "fliteDll.dll")));
				RuntimeDependencies.Add(new RuntimeDependency(Path.Combine(FliteDirectory, "cmu_us_rms.dll")));
                RuntimeDependencies.Add(new RuntimeDependency(Path.Combine(FliteDirectory, "cmu_us_slt.dll")));
                PublicDelayLoadDLLs.Add("fliteDll.dll");
                PublicDelayLoadDLLs.Add("cmu_us_rms.dll");
                PublicDelayLoadDLLs.Add("cmu_us_slt.dll");
            }
			else
			{
				// Linux, Mac, WinRT: not supported
			}
			
		}
	}
}