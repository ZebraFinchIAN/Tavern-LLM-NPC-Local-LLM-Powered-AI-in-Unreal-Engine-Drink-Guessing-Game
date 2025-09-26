// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LLMProjem : ModuleRules
{
	public LLMProjem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
        PrivateDependencyModuleNames.AddRange(new string[] { "HTTP", "Json", "JsonUtilities" });

    }
}
