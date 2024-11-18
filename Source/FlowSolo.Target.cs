// Copyright https://github.com/MothCocoon/FlowGraph/graphs/contributors

using UnrealBuildTool;

public class FlowSoloTarget : TargetRules
{
	public FlowSoloTarget(TargetInfo target) : base(target)
	{
		Type = TargetType.Game;

		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;

		NativePointerMemberBehaviorOverride = PointerMemberBehavior.AllowSilently;

		ExtraModuleNames.AddRange(new[]
		{ 
			"FlowSolo"
		});
    }
}
