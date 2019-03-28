// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ExampleGameEditorModule.h"

#include "Modules/ModuleManager.h"
#include "Modules/ModuleInterface.h"

#include "AssetToolsModule.h"
#include "PropertyEditorModule.h"

#include "AbilitySetActions.h"
#include "AbilitySetCustomization.h"

IMPLEMENT_GAME_MODULE(FExampleGameEditorModule, ExampleGameEditor);

DEFINE_LOG_CATEGORY(ExampleGameEditor)

#define LOCTEXT_NAMESPACE "ExampleGameEditor"

void FExampleGameEditorModule::StartupModule()
{
	UE_LOG(ExampleGameEditor, Warning, TEXT("ExampleGameEditor: Log Started"));

	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();	
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked< FPropertyEditorModule >("PropertyEditor");

	TSharedRef<IAssetTypeActions> AbilitySetActions = MakeShareable(new FAbilitySetActions());
	AssetTools.RegisterAssetTypeActions(AbilitySetActions);





	// Register our customization to be used by a class 'UMyClass' or 'AMyClass'. Note the prefix must be dropped.
	PropertyModule.RegisterCustomClassLayout("AbilitySet",FOnGetDetailCustomizationInstance::CreateStatic(&FAbilitySetCustomization::MakeInstance));
	PropertyModule.NotifyCustomizationModuleChanged();
	
}

void FExampleGameEditorModule::ShutdownModule()
{
	UE_LOG(ExampleGameEditor, Warning, TEXT("ExampleGameEditor: Log Ended"));

	if (FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
	{
		auto& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

		PropertyModule.UnregisterCustomClassLayout("AbilitySet");
	}
}

#undef LOCTEXT_NAMESPACE