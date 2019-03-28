// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ExampleGameEditor : ModuleRules
{
	public ExampleGameEditor(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "ExampleGame",
                "Core",
                "CoreUObject",
                "Engine",
                "InputCore",
                "Slate",
                "SlateCore",
                "UnrealEd",
                "PropertyEditor"
            });



        PublicIncludePaths.AddRange(
            new string[]
            {
                "ExampleGameEditor/Public"
            });

        PrivateIncludePaths.AddRange(
            new string[] 
            {
                "ExampleGameEditor/Private"
            });
        }
}
