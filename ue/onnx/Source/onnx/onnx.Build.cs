// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class onnx : ModuleRules
{
	public onnx(ReadOnlyTargetRules Target) : base(Target)
	{
        //added to supress warnings from opencv plugin
        bEnableUndefinedIdentifierWarnings = false;
        DefaultBuildSettings = BuildSettingsVersion.V2;

        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput","OpenCV",
            "OpenCVHelper","NeuralNetworkInference", "MediaAssets" });
    }
}
