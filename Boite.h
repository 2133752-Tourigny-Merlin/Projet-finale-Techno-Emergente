/**
* Fichier Boite.h
* Auteur: Merlin Tourigny
*
* Date: 20 décembre 2023
*
* Fichier qui s'occupe des boites dans le jeux
*/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Boite.generated.h"


/// <summary>
/// Classe ABoite qui s'occupe des boites
/// </summary>
UCLASS()
class USINE2_API ABoite : public AActor
{
	GENERATED_BODY()
	
public:	
	/// <summary>
	/// Constructeur
	/// </summary>
	ABoite();

protected:
	/// <summary>
	/// Fonction BeginPlay qui s'execute une fois lorsque l'objet s'instantie
	/// </summary>
	virtual void BeginPlay() override;

public:	
	/// <summary>
	/// Fonction Tick qui s'execute à chaque frame
	/// </summary>
	/// <param name="DeltaTime">temps entre chaque frame</param>
	virtual void Tick(float DeltaTime) override;

	/// <summary>
	/// Variable de la boite à généré
	/// </summary>
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> actorBPToSpawn;

	/// <summary>
	/// Fonction Genere qui fait apparaitre une boite sur le convoyeur
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "genrere")
	void Genere();

};
