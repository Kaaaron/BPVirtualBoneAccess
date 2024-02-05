// Copyright 2024 Aaron Kemner, All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class FBPVirtualBoneAccessModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
