// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/PSActorComponent_PawnExtension.h"



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

}
