// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class FPS_UE54_2_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	UStaticMeshComponent* StaticMeshComp;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	bool isDestroy;//是否销毁

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ScaleRate)
	double ScaleRate;//第一次被命中的缩放倍率

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target", ReplicatedUsing = OnRep_IsImportantTarget)
	bool isImportantTarget;//是否为重要目标

	// 在客户端接收到isImportantTarget变化时调用
	UFUNCTION()
	void OnRep_IsImportantTarget();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target")
	int32 ScoreValue;//积分
};
