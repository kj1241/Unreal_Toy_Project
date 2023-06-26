// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../TestProject.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "GameFramework/Actor.h"
#include "Fountain.generated.h"

UCLASS()
class TESTPROJECT_API AFountain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFountain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override; // 시작할떄
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override; // 끝났을때
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Body;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Water;
	
	UPROPERTY(VisibleAnywhere)
		UPointLightComponent* Light;

	UPROPERTY(VisibleAnywhere)
		UParticleSystemComponent* Splash;

	UPROPERTY(VisibleAnywhere)
		URotatingMovementComponent* Movement;

	UPROPERTY(EditAnywhere,Category=ID)
		int32 ID;


private:
	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
		float RotateSpeed;


};
