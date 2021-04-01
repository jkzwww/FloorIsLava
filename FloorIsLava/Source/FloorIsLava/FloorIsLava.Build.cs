// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FloorIsLava : ModuleRules
{
	public FloorIsLava(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
