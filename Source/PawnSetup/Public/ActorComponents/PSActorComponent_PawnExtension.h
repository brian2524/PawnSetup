// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "PSActorComponent_PawnExtension.generated.h"


struct FInputActionValue;

/**
 * 
 */
UCLASS(ClassGroup=(PawnSetup), Within=Pawn)
class PAWNSETUP_API UPSActorComponent_PawnExtension : public UActorComponent
{
	GENERATED_BODY()

public:
	UPSActorComponent_PawnExtension(const FObjectInitializer& ObjectInitializer);


	/** Call at the end of your Pawn's SetupPlayerInputComponent() event */
	void OnOwnerSetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

protected:
	virtual void OnRegister() override;


	//  BEGIN Input binding
	virtual void OnMove(const FInputActionValue& InputActionValue);
	virtual void OnLook(const FInputActionValue& InputActionValue);
	//  END Input bindings

	UPROPERTY(Transient)
		TWeakObjectPtr<APawn> OwnerPawn;
};
