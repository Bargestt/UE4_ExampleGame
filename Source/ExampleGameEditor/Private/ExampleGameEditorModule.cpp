// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ExampleGameEditorModule.h"
#include "Modules/ModuleManager.h"
#include "Modules/ModuleInterface.h"
#include "AssetToolsModule.h"
#include "AbilitySetActions.h"

IMPLEMENT_GAME_MODULE(FExampleGameEditorModule, ExampleGameEditor);

DEFINE_LOG_CATEGORY(ExampleGameEditor)

#define LOCTEXT_NAMESPACE "ExampleGameEditor"

void FExampleGameEditorModule::StartupModule()
{
	UE_LOG(ExampleGameEditor, Warning, TEXT("ExampleGameEditor: Log Started"));

	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	

	TSharedRef<IAssetTypeActions> AbilitySetActions = MakeShareable(new FAbilitySetActions());
	AssetTools.RegisterAssetTypeActions(AbilitySetActions);
	
}

void FExampleGameEditorModule::ShutdownModule()
{
	UE_LOG(ExampleGameEditor, Warning, TEXT("ExampleGameEditor: Log Ended"));
}

#undef LOCTEXT_NAMESPACE