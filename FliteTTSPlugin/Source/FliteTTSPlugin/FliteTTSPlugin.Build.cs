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
				}
			);

			PrivateIncludePaths.AddRange(
				new string[] {
					"FliteTTSPlugin/Private",
					"FliteTTSPlugin/ThirdParty/flite",
				}
			);

			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
					"CoreUObject",
					"Engine",
				}
			);

			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					"Projects",
					"AudioMixer",
				}
			);

			DynamicallyLoadedModuleNames.AddRange(
				new string[]
				{
				}
			);

			// Add Flite TTS libraries
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