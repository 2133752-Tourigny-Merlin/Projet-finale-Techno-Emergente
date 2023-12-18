/**
* Fichier TutorielPersonnage.h
* Auteur: Merlin Tourigny
*
* Date: 20 décembre 2023
*
* Fichier qui s'occupe des mouvements et animations du joueur
*/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "TutorielPersonnage.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;


DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/// <summary>
/// Class ATutorielPersonnage
/// </summary>
UCLASS(config = Game)
class USINE2_API ATutorielPersonnage : public ACharacter
{
	GENERATED_BODY()

	/// <summary>
	/// Variable CameraBoom qui contient le lien entre la caméra et le joueur dans l'objet du joueur
	/// </summary>
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/// <summary>
	/// Variable FollowCamera qui contient la caméra du joueur
	/// </summary>
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/// <summary>
	/// Variable DefaultMappingContext qui contient les actions possibles du joueur
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/// <summary>
	/// Variable JumpAction qui contient l'action de sauter
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/// <summary>
	/// Variable MoveAction qui contient les mouvements du joueur
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;


	/// <summary>
	/// Variable LookAction qui contient les actions de la caméra
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
public:

	/// <summary>
	/// Constructeur de la classe
	/// </summary>
	ATutorielPersonnage();

	/// <summary>
	/// Variable qui contient la boite à générer
	/// </summary>
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> actorBPToSpawn;

protected:
	/// <summary>
	/// Fonction BeginPlay qui s'execute une fois lorsque l'objet s'instantie
	/// </summary>
	virtual void BeginPlay() override;

	/// <summary>
	/// Fonction Move qui bouge le joueur selon son input
	/// </summary>
	/// <param name="Value">La valeur de la touche appuyé</param>
	void Move(const FInputActionValue& Value);

	/// <summary>
	/// Fonction Look qui bouge la camera selon son input
	/// </summary>
	/// <param name="Value">La valeur de la touche appuyé</param>
	void Look(const FInputActionValue& Value);

	/// <summary>
	/// Fonction SetupPlayerInputComponent qui s'occupe d'ajouter les options de controle au joueur
	/// </summary>
	/// <param name="PlayerInputComponent">Le joueur</param>
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:	
	/// <summary>
	/// Fonction Tick qui s'execute à chque frame
	/// </summary>
	/// <param name="DeltaTime">le temps entre chaque frame</param>
	virtual void Tick(float DeltaTime) override;


	/// <summary>
	/// Classe USpringArmComponent qui s'occupe du CameraBoom
	/// </summary>
	/// <returns>Return le cameraBoom du joueur</returns>
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/// <summary>
	/// Classe UCameraComponent qui s'occupe des mouvements de la camera
	/// </summary>
	/// <returns>Return la camera du joueur</returns>
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
