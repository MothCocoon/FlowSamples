using UnrealBuildTool;

public class FlowSoloEditorTarget : TargetRules
{
	public FlowSoloEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;

		ExtraModuleNames.AddRange(new[]
		{ 
			"FlowSolo"
		});

        DefaultBuildSettings = BuildSettingsVersion.V4;
    }
}
