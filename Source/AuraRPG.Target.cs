// No Copyright.

using UnrealBuildTool;

public class AuraRPGTarget : TargetRules
{
	public AuraRPGTarget(TargetInfo target) : base(target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V7;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_8;
		
		ExtraModuleNames.AddRange(["AuraRPG"]);
	}
}
