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
	
	bool isDestroy;//�Ƿ�����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ScaleRate)
	double ScaleRate;//��һ�α����е����ű���

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target", ReplicatedUsing = OnRep_IsImportantTarget)
	bool isImportantTarget;//�Ƿ�Ϊ��ҪĿ��

	// �ڿͻ��˽��յ�isImportantTarget�仯ʱ����
	UFUNCTION()
	void OnRep_IsImportantTarget();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target")
	int32 ScoreValue;//����
};
