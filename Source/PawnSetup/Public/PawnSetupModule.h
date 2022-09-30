// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

//#include "PawnSetupModule.generated.h" // uncomment if we ever need reflection in here



/**
 * 
 */
class FPawnSetupModule : public FDefaultModuleImpl
{
public:
	//  BEGIN IModuleInterface interface
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	//  END IModuleInterface interface
};
