/**
* Fichier Boite.cpp
* Auteur: Merlin Tourigny
* 
* Date: 20 d�cembre 2023
* 
* Fichier qui s'occupe des boites dans le jeux
*/
#include "Boite.h"

ABoite::ABoite()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABoite::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABoite::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABoite::Genere() {
	//L'acteur � faire apparaitre
	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	// Met des positions fixs � l'ateur
	FVector SpawnLocation = FVector(352.307240, 1931.281552, 170.491840);
	FTransform SpawnTransform = FTransform(SpawnLocation);

	// Fait spawn l'acteur avec les informations plus haut
	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(actorBPToSpawn, SpawnTransform, spawnParams);

	// Regarde si l'acteur a bel et bien �t� g�n�r�
	if (!SpawnedActor) {
		// Log l'erreur dans la console
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn actor."));
	}
}

