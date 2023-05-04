#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BoidSystem.h"
#include "BoidsGameModeBase.generated.h"

UCLASS()
class ABoidsGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	UPROPERTY() UBoidSystem* base;
private:
	int tickNumber = 0;
public:
	ABoidsGameModeBase();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	static bool useGoal;
};