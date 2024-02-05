// Copyright 2024 Aaron Kemner, All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Animation/Skeleton.h"
#include "BPVirtualBoneAccessLibrary.generated.h"


/**
 * Wrapper for a native virtual bone struct, since they are not exposed to Blueprints as of now.
 */
USTRUCT(BlueprintType, Category="Virtual Bone")
struct BPVIRTUALBONEACCESS_API FBPVirtualBone
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, Category="Virtual Bone")
	FName SourceBoneName;

	UPROPERTY(BlueprintReadOnly, Category="Virtual Bone")
	FName TargetBoneName;

	UPROPERTY(BlueprintReadOnly, Category="Virtual Bone")
	FName VirtualBoneName;

	FBPVirtualBone()
		:SourceBoneName(NAME_None),
		TargetBoneName(NAME_None),
		VirtualBoneName(NAME_None)
	{};

	explicit FBPVirtualBone(const FVirtualBone& NativeVB)
		:SourceBoneName(NativeVB.SourceBoneName),
		TargetBoneName(NativeVB.TargetBoneName),
		VirtualBoneName(NativeVB.VirtualBoneName)
	{};

	friend uint32 GetTypeHash(const FBPVirtualBone& Key)
	{
		return HashCombine(
				HashCombine(
					GetTypeHash(Key.SourceBoneName),
					GetTypeHash(Key.TargetBoneName)),
				GetTypeHash(Key.VirtualBoneName));
	};

	bool operator==(const FBPVirtualBone& Other) const
	{
		return ( SourceBoneName == Other.SourceBoneName &&
			TargetBoneName == Other.TargetBoneName &&
			VirtualBoneName == Other.VirtualBoneName);
	};

	bool operator==(const FVirtualBone& Other) const
	{
		return ( SourceBoneName == Other.SourceBoneName &&
			TargetBoneName == Other.TargetBoneName &&
			VirtualBoneName == Other.VirtualBoneName);
	};
};

/* 
* Core Function Library of the Plugin to enable access to Virtual Bones from Blueprints.
*/
UCLASS(Category="Virtual Bone")
class BPVIRTUALBONEACCESS_API UBPVirtualBoneAccessLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()
public:
	/** Accessor for the array of virtual bones on the skeleton of the input mesh */
	UFUNCTION(BlueprintCallable, Category="Virtual Bone")
	static TArray<FBPVirtualBone> GetVirtualBones(const USkeletalMesh* Mesh);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Virtual Bone")
	static FBPVirtualBone GetVirtualBone(const USkeletalMesh* Mesh, FName Name);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "Equal (Virtual Bone)", CompactNodeTitle = "==", Keywords = "== equal"), Category="Virtual Bone")
	static bool EqualEqual_BPVirtualBoneBPVirtualBone(FBPVirtualBone A, FBPVirtualBone B)
		{ return A == B; }
	
};
