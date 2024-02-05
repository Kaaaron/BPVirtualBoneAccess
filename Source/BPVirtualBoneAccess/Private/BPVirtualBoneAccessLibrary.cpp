﻿// Copyright Epic Games, Inc. All Rights Reserved.

#include "BPVirtualBoneAccessLibrary.h"
#include "BPVirtualBoneAccess.h"


UBPVirtualBoneAccessLibrary::UBPVirtualBoneAccessLibrary(const FObjectInitializer& ObjectInitializer)
{}

TArray<FBPVirtualBone> UBPVirtualBoneAccessLibrary::GetVirtualBones(const USkeletalMesh* Mesh)
{	
	if((!Mesh) || (!Mesh->GetSkeleton()))
		{ return {}; }
	
	const TArray<FVirtualBone> NativeVBs = Mesh->GetSkeleton()->GetVirtualBones();
	TArray<FBPVirtualBone> RV;
	RV.Init(FBPVirtualBone(), NativeVBs.Num());

	for(int i = 0; i<NativeVBs.Num(); i++)
	{
		RV[i] = FBPVirtualBone(NativeVBs[i]);
	}
	
	return RV;
}

FBPVirtualBone UBPVirtualBoneAccessLibrary::GetVirtualBone(const USkeletalMesh* Mesh, FName Name)
{
	if((!Mesh) || (!Mesh->GetSkeleton()))
		{ return FBPVirtualBone(); }
	
	const TArray<FVirtualBone> NativeVBs = Mesh->GetSkeleton()->GetVirtualBones();
	for(const FVirtualBone& Current : NativeVBs)
	{
		if(Current.VirtualBoneName == Name)
			{ return FBPVirtualBone(Current); }
	}
	return FBPVirtualBone();
}
