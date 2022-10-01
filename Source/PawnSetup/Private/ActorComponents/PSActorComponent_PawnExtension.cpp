// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/PSActorComponent_PawnExtension.h"

#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "InputTriggers.h"
#include "ISEngineSubsystem_InputActions.h"


UPSActorComponent_PawnExtension::UPSActorComponent_PawnExtension(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPSActorComponent_PawnExtension::OnRegister()
{
	Super::OnRegister();

	OwnerPawn = Cast<APawn>(GetOwner());
}

void UPSActorComponent_PawnExtension::OnOwnerSetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (IsValid(PlayerEnhancedInputComponent))
	{
		const UISEngineSubsystem_InputActions* InputActionsSubsystem = GEngine->GetEngineSubsystem<UISEngineSubsystem_InputActions>();
		if (IsValid(InputActionsSubsystem))
		{
			const UInputAction* InputActionMove = InputActionsSubsystem->GetInputAction(PSNativeGameplayTags::InputAction_Move);
			if (IsValid(InputActionMove))
			{
				PlayerEnhancedInputComponent->BindAction(InputActionMove, ETriggerEvent::Triggered, this, &ThisClass::OnMove);
			}

			const UInputAction* InputActionLook = InputActionsSubsystem->GetInputAction(PSNativeGameplayTags::InputAction_Look);
			if (IsValid(InputActionLook))
			{
				PlayerEnhancedInputComponent->BindAction(InputActionLook, ETriggerEvent::Triggered, this, &ThisClass::OnLook);
			}
		}
	}
}

void UPSActorComponent_PawnExtension::OnMove(const FInputActionValue& InputActionValue)
{
	if (OwnerPawn.IsValid())
	{
		const AController* Controller = OwnerPawn->GetController();
		if (IsValid(Controller) && InputActionValue.GetMagnitudeSq() > 0.f)
		{
			const FRotator YawRotation(0, Controller->GetControlRotation().Yaw, 0);

			const FVector2D MovementInput = InputActionValue.Get<FVector2D>();

			const FVector ForwardDirection = YawRotation.RotateVector(FVector::ForwardVector);
			OwnerPawn->AddMovementInput(ForwardDirection, MovementInput.Y);
			const FVector RightDirection = YawRotation.RotateVector(FVector::RightVector);
			OwnerPawn->AddMovementInput(RightDirection, MovementInput.X);
		}
	}
}

void UPSActorComponent_PawnExtension::OnLook(const FInputActionValue& InputActionValue)
{
	if (OwnerPawn.IsValid())
	{
		if (InputActionValue.GetMagnitudeSq() > 0.f)
		{
			const FVector2D LookInput = InputActionValue.Get<FVector2D>();

			OwnerPawn->AddControllerYawInput(LookInput.X * 0.5f);
			OwnerPawn->AddControllerPitchInput(LookInput.Y * 0.5f);
		}
	}
}
