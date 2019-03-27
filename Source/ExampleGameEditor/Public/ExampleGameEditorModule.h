// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Engine.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"
#include "UnrealEd.h"

DECLARE_LOG_CATEGORY_EXTERN(ExampleGameEditor, All, All)

class FExampleGameEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

};