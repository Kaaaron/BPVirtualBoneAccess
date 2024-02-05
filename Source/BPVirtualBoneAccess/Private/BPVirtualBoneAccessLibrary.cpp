// Copyright 2024 Aaron Kemner, All Rights Reserved.
#include "BPVirtualBoneAccessLibrary.h"
#include "Engine/SkeletalMesh.h"


UBPVirtualBoneAccessLibrary::UBPVirtualBoneAccessLibrary(const FObjectInitializer& ObjectInitializer)
{}

TArray<FBPVirtualBone> UBPVirtualBoneAccessLibrary::GetVirtualBones(const USkeletalMesh* Mesh)
{
	TArray<FBPVirtualBone> RV = {};
	if((!Mesh) || (!Mesh->GetSkeleton()))
		{ return RV; }
	
	const TArray<FVirtualBone>& NativeVBs = Mesh->GetSkeleton()->GetVirtualBones();
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
	
	const TArray<FVirtualBone>& NativeVBs = Mesh->GetSkeleton()->GetVirtualBones();
	for(const FVirtualBone& Current : NativeVBs)
	{
		if(Current.VirtualBoneName == Name)
			{ return FBPVirtualBone(Current); }
	}
	return FBPVirtualBone();
}
