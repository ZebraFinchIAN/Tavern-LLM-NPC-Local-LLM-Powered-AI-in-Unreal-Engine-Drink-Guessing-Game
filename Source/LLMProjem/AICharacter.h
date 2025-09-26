// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Character.h"
#include "Misc/InteractiveProcess.h" 


#include "AICharacter.generated.h"


USTRUCT(BlueprintType)
struct FST_MusteriAnisi : public FTableRowBase
{
    GENERATED_BODY()


public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Ani_Promptu;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Sistem_Mesaji_IpucuToplama; 

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Sistem_Mesaji_Sohbet; 

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName Dogru_Icecek_Kimligi;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Dogru_Secim_Promptu;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Yanlis_Secim_Promptu;
};


// KONUÞMA GEÇMÝÞÝ ÝÇÝN KULLANDIÐIMIZ STRUCT
USTRUCT(BlueprintType)
struct FConversationLine
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Line;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Speaker;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Audio;
};


// ANA KARAKTER SINIFIMIZ
UCLASS()
class LLMPROJEM_API AAICharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AAICharacter();

    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnKonusmaGuncellendi);

    UPROPERTY(BlueprintAssignable, Category = "AI")
    FOnKonusmaGuncellendi OnKonusmaGuncellendi;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
    TArray<FConversationLine> KonusmaGecmisi;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
    bool bCevapBekleniyor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    UDataTable* MusteriVeriTablosu;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FString KarakterAdi;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FName MusteriKimligi;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
    FName AktifMusteriKimligi;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
    int32 KonusmaAsamasi; // 0 = Baþlamadý, 1 = Ýpucu Toplama, 2 = Sohbet

    UFUNCTION(BlueprintCallable, Category = "AI")
    void AniyiBaslat();

    UFUNCTION(BlueprintCallable, Category = "AI")
    void KonusmayaDevamEt(const FString& OyuncuCevabi);

    UFUNCTION(BlueprintCallable, Category = "AI")
    void TahminSonucunuBildir(const FString& SonucPromptu);

    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
    virtual void BeginPlay() override;

private:
    void PromptGonder(const FString& GonderilecekPrompt);

    // Node.js sürecini canlý tutmak için referansýný burada saklýyoruz.
    TSharedPtr<FInteractiveProcess> AktifSurec;
};