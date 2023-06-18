// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class VRMultiplayer : ModuleRules
{
	public VRMultiplayer(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "UMG", "OnlineSubsystem", "OnlineSubsystemSteam" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true

        // Woogle's debug macro
        PublicDefinitions.Add("WG_LOG(x)=UE_LOG(LogTemp, Warning, TEXT(x));");
        PublicDefinitions.Add("WG_TEXT(x)=if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, TEXT(x));}");
        PublicDefinitions.Add("WG_STRING(x)=if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, x);}");
        PublicDefinitions.Add("WG_BOOL(x)=if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, (x ? FString(\"true\") : FString(\"false\")));}");
        PublicDefinitions.Add("WG_INT(x)=if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Turquoise, FString::FromInt(x));}");
        PublicDefinitions.Add("WG_FLOAT(x)=if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Emerald, FString::SanitizeFloat(x));}");
        PublicDefinitions.Add("WG_VECTOR(x)=if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, x.ToString());}");
        PublicDefinitions.Add("WG_ROTATOR(x)=if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Silver, x.ToString());}");
        PublicDefinitions.Add("WG_FUNC()=if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, (FString(__FUNCTION__) + TEXT(\"(\") + FString::FromInt(__LINE__) + TEXT(\")\")));}");
    }
}
