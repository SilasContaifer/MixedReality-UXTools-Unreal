// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UxtHandInteractionActor.generated.h"

class UUxtTouchPointer;
class UUxtFarPointerComponent;
class UMaterialParameterCollection;


/**
 * Actor that drives hand interactions with components that implement the far and touch target interfaces.
 * A hand has two interaction modes:
 * - Near: interactions performed by poking at or grabbing touch targets directly.
 * - Far: interactions performed by pointing at far targets from a distance via a hand ray.
 * The actor transitions between modes depending on whether there is a touch target within the near activation distance.
 */
UCLASS(ClassGroup = UXTools)
class UXTOOLS_API AUxtHandInteractionActor : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AUxtHandInteractionActor(const FObjectInitializer& ObjectInitializer);

	//
	// UActorComponent interface

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintGetter)
	EControllerHand GetHand() const { return Hand; }
	UFUNCTION(BlueprintSetter)
	void SetHand(EControllerHand NewHand);

	UFUNCTION(BlueprintGetter)
	ECollisionChannel GetTraceChannel() const { return TraceChannel; }
	UFUNCTION(BlueprintSetter)
	void SetTraceChannel(ECollisionChannel NewTraceChannel);

	UFUNCTION(BlueprintGetter)
	float GetTouchRadius() const { return TouchRadius; }
	UFUNCTION(BlueprintSetter)
	void SetTouchRadius(float NewTouchRadius);

	UFUNCTION(BlueprintGetter)
	float GetRayStartOffset() const { return RayStartOffset; }
	UFUNCTION(BlueprintSetter)
	void SetRayStartOffset(float NewRayStartOffset);

	UFUNCTION(BlueprintGetter)
	float GetRayLength() const { return RayLength; }
	UFUNCTION(BlueprintSetter)
	void SetRayLength(float NewRayLength);

	/** Distance from the hand to the closest touch target at which near interaction activates. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hand Interaction", meta = (DisplayAfter = "TouchRadius"))
	float NearActivationDistance = 20.0f;

	/** When set create default visuals automatically for near and far cursors and far beam */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hand Interaction", meta = (DisplayAfter = "NearActivationDistance"))
	bool bUseDefaultVisuals = true;

private:

	/** Articulated hand used to drive interactions. */
	UPROPERTY(EditAnywhere, BlueprintGetter = "GetHand", BlueprintSetter = "SetHand", Category = "Hand Interaction")
	EControllerHand Hand;

	/** Offset from the hand ray origin at which the far ray used for far target selection starts. */
	UPROPERTY(EditAnywhere, BlueprintGetter = "GetRayStartOffset", BlueprintSetter = "SetRayStartOffset", Category = "Hand Interaction")
	float RayStartOffset = 5.0f;

	/** Length of the far ray */
	UPROPERTY(EditAnywhere, BlueprintGetter = "GetRayLength", BlueprintSetter = "SetRayLength", Category = "Hand Interaction")
	float RayLength = 500.0f;

	/** Maximum distance around the finger tip at which we look for touch targets. */
	UPROPERTY(EditAnywhere, BlueprintGetter = "GetTouchRadius", BlueprintSetter = "SetTouchRadius", Category = "Hand Interaction")
	float TouchRadius = 20.0f;

	/** Trace channel used for targeting queries. */
	UPROPERTY(EditAnywhere, BlueprintGetter = "GetTraceChannel", BlueprintSetter = "SetTraceChannel", Category = "Hand Interaction")
	TEnumAsByte<ECollisionChannel> TraceChannel = ECollisionChannel::ECC_Visibility;


	UPROPERTY(Transient)
	UUxtTouchPointer* NearPointer;

	UPROPERTY(Transient)
	UUxtFarPointerComponent* FarPointer;

	UPROPERTY(Transient)
	UMaterialParameterCollection* ParameterCollection;
};