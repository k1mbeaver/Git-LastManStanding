// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LastManStanding.h"
#include "Animation/AnimInstance.h"
#include "ABAnimInstance.generated.h"

// 공격 체크용 딜리게이트
DECLARE_MULTICAST_DELEGATE(FOnOnCollisonStart_PunchDelegate); // 공격 시작
DECLARE_MULTICAST_DELEGATE(FOnOnCollisonEnd_PunchDelegate); // 공격 끝
DECLARE_MULTICAST_DELEGATE(FPunchAnimation_PunchAnimationDelegate); // 공격 애니메이션 출력

// 미션 체크용 델리게이트
DECLARE_MULTICAST_DELEGATE(FDancingStart_MissionDelegate); // 댄스 시작
DECLARE_MULTICAST_DELEGATE(FDancingEnd_MissionDelegate); // 댄스 끝
/**
 * 
 */
UCLASS()
class LASTMANSTANDING_API UABAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UABAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void PlayAttackMontage(UAnimMontage* playPunch);
	void PlayDanceMontage(UAnimMontage* playDance);
	UAnimMontage* GetAttackMontage();
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackMontage;

	FOnOnCollisonStart_PunchDelegate OnOnCollisonStart_Punch;
	FOnOnCollisonEnd_PunchDelegate OnOnCollisonEnd_Punch;
	FPunchAnimation_PunchAnimationDelegate PunchAnimation_Punch;
	FDancingStart_MissionDelegate DancingStart_Mission;
	FDancingEnd_MissionDelegate DancingEnd_Mission;

	FName GetAttackMontageSectionName(int32 Section);
	void SetDeadAnim();

private:
	UFUNCTION()
		void AnimNotify_OnCollisonStart_Punch();
	UFUNCTION()
		void AnimNotify_OnCollisonEnd_Punch();
	UFUNCTION()
		void AnimNotify_DancingStart_Mission();
	UFUNCTION()
		void AnimNotify_DancingEnd_Mission();
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float CurrentPawnSpeed; // AnimInstance를 사용해서 C++ 스크립팅 한 것을 블루프린트에서 사용이 가능하다.

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsInAir;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsDead;
public:
};
