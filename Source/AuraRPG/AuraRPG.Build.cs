// No Copyright.

using UnrealBuildTool;

public class AuraRPG : ModuleRules
{
	public AuraRPG(ReadOnlyTargetRules target) : base(target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(
		[
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"UMG"
		]);
		
		PrivateDependencyModuleNames.AddRange([]);
	}
}
