// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FPS_UE54_2 : ModuleRules
{
	public FPS_UE54_2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
