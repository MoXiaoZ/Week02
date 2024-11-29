// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Components/StaticMeshComponent.h"
#include "../FPS_UE54_2Projectile.h"
#include "MyPlayerState.h"
#include "MyGameState.h"
#include "../FPS_UE54_2PlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include <Net/UnrealNetwork.h>
#include "Materials/MaterialInstanceConstant.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 启用复制
	bReplicates = true;
	SetReplicateMovement(true);//复制移动

	//USceneComponent* Root = CreateDefaultSubobject<USceneComponent>("Root");
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = StaticMeshComp;
	
	// 开启碰撞响应
	StaticMeshComp->SetSimulatePhysics(true);
	StaticMeshComp->OnComponentHit.AddDynamic(this, &AMyActor::OnHit);//绑定撞击事件

	ScaleRate = 0.5;
	isDestroy = false;
	isImportantTarget = false;
	ScoreValue = 5;

	// Load the static mesh asset
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/LevelPrototyping/Meshes/SM_ChamferCube1.SM_ChamferCube1'"));

	// Check if the asset was found
	if (StaticMeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(StaticMeshAsset.Object);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Static mesh not found!"));
	}
}

void AMyActor::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// 第二次撞击销毁MyActor(需要判断撞击的物体是不是子弹)
	if (isDestroy && OtherActor->IsA(AFPS_UE54_2Projectile::StaticClass())) {
		if (AFPS_UE54_2PlayerController* PC = Cast<AFPS_UE54_2PlayerController>(OtherActor->GetInstigatorController()))//这里不要用GetOwner，因为子弹撞击到MyActor后Destroy了，拿不到Owner的值
		{
			AMyPlayerState* PS = PC->GetPlayerState<AMyPlayerState>();
			if (PS)
			{
				int32 FinalScore = isImportantTarget ? ScoreValue * 2 : ScoreValue;
				PS->AddScore(FinalScore);

				// 更新全局积分
				AMyGameState* GS = GetWorld()->GetGameState<AMyGameState>();
				if (GS)
				{
					GS->PrintAllPlayersScore();
				}

			}
		}

		Destroy();
		return;
	}

	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherActor->IsA(AFPS_UE54_2Projectile::StaticClass()))
	{
		this->SetActorScale3D(GetActorScale3D() * ScaleRate);
		//HitComp->SetWorldScale3D(GetActorScale3D() * ScaleRate);
		isDestroy = true;

		if (AFPS_UE54_2PlayerController* PC = Cast<AFPS_UE54_2PlayerController>(OtherActor->GetInstigatorController()))
		{
			AMyPlayerState* PS = PC->GetPlayerState<AMyPlayerState>();
			if (PS)
			{
				int32 FinalScore = isImportantTarget ? ScoreValue * 2 : ScoreValue;
				PS->AddScore(FinalScore);

				// 更新全局积分
				AMyGameState* GS = GetWorld()->GetGameState<AMyGameState>();
				if (GS)
				{
					GS->PrintAllPlayersScore();
				}

				//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, FString::Printf(TEXT("111%s:%d"), *PS->GetPlayerName(), PS->GetCurrentScore()));
			}
		}

	}
}


void AMyActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// 注册 isImportantTarget 属性的复制
	DOREPLIFETIME(AMyActor, isImportantTarget);
}

void AMyActor::OnRep_IsImportantTarget()
{
	// 在客户端同步时应用材质变化
	if (isImportantTarget)
	{
		// 在非构造函数中使用StaticLoadObject加载资产，用FObjectFinder会报错
		UMaterialInstanceConstant* MaterialAsset = Cast<UMaterialInstanceConstant>(
			StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("/Game/LevelPrototyping/Materials/MI_Solid_Red.MI_Solid_Red"))
		);
		if (MaterialAsset)
		{
			// Set the material on the static mesh component
			StaticMeshComp->SetMaterial(0, MaterialAsset);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Material instance not found!"));
		}
	}
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

