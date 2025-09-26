// Fill out your copyright notice in the Description page of Project Settings.

#include "AICharacter.h"
#include "Misc/InteractiveProcess.h"
#include "AIGameState.h" 
#include "Async/Async.h"

// Sets default values
AAICharacter::AAICharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    bCevapBekleniyor = false;
    KonusmaAsamasi = 0;
}

void AAICharacter::BeginPlay()
{
    Super::BeginPlay();
}

void AAICharacter::AniyiBaslat()
{
    if (bCevapBekleniyor || !MusteriVeriTablosu || MusteriKimligi.IsNone()) return;
    FST_MusteriAnisi* MusteriVerisi = MusteriVeriTablosu->FindRow<FST_MusteriAnisi>(MusteriKimligi, "");
    if (MusteriVerisi)
    {
        KonusmaAsamasi = 1;
        AktifMusteriKimligi = MusteriKimligi;
        KonusmaGecmisi.Empty();
        FString FullPrompt = MusteriVerisi->Sistem_Mesaji_IpucuToplama + "\n\n" + MusteriVerisi->Ani_Promptu;
        PromptGonder(FullPrompt);
    }
}

void AAICharacter::KonusmayaDevamEt(const FString& OyuncuCevabi)
{
    if (bCevapBekleniyor || !MusteriVeriTablosu || AktifMusteriKimligi.IsNone()) return;

    
    KonusmaGecmisi.Add(FConversationLine{ OyuncuCevabi, "Player", TEXT("") });

    
    AsyncTask(ENamedThreads::GameThread, [this]() {
        if (OnKonusmaGuncellendi.IsBound())
        {
            OnKonusmaGuncellendi.Broadcast();
        }
        });

    
    FST_MusteriAnisi* MusteriVerisi = MusteriVeriTablosu->FindRow<FST_MusteriAnisi>(AktifMusteriKimligi, "");
    if (MusteriVerisi)
    {
        FString FullPrompt = "";
        if (KonusmaAsamasi == 1) { FullPrompt = MusteriVerisi->Sistem_Mesaji_IpucuToplama; }
        else { FullPrompt = MusteriVerisi->Sistem_Mesaji_Sohbet; }

        FullPrompt += "\n\n";
        for (const FConversationLine& Line : KonusmaGecmisi) { FullPrompt += Line.Speaker + ": " + Line.Line + "\n"; }
        FullPrompt += this->KarakterAdi + ":";

        PromptGonder(FullPrompt);
    }
}

void AAICharacter::TahminSonucunuBildir(const FString& SonucPromptu)
{
    
    if (bCevapBekleniyor || !MusteriVeriTablosu || AktifMusteriKimligi.IsNone()) return;

 
    KonusmaGecmisi.Add(FConversationLine{ SonucPromptu, KarakterAdi, TEXT("") });


    AsyncTask(ENamedThreads::GameThread, [this]() {
        if (OnKonusmaGuncellendi.IsBound())
        {
            OnKonusmaGuncellendi.Broadcast();
        }
        });
}
void AAICharacter::PromptGonder(const FString& GonderilecekPrompt)
{
 
    if (AktifSurec.IsValid())
    {
        UE_LOG(LogTemp, Warning, TEXT("Zaten aktif bir LLM süreci var, yeni istek gönderilmedi."));
        return;
    }

    bCevapBekleniyor = true;

    FString nodeExePath = TEXT("D:\\node.exe");
    FString scriptPath = TEXT("D:/ProjectLLM/LLMProjem/local-llms-ue5/node/index.js");
    FString arguments = FString::Printf(TEXT("\"%s\" \"%s\""), *scriptPath, *GonderilecekPrompt);

    //UE_LOG(LogTemp, Warning, TEXT("Sending Prompt: %s"), *GonderilecekPrompt);

    
    AktifSurec = MakeShareable(new FInteractiveProcess(nodeExePath, arguments, true, false));

    
    AktifSurec->OnOutput().BindLambda([this](const FString& Output) {
        FString SearchString = TEXT("--- Modelin Cevabý ---");
        int32 Index = Output.Find(SearchString, ESearchCase::IgnoreCase);
        FString ResponseText = (Index != INDEX_NONE) ? Output.RightChop(Index + SearchString.Len()).TrimStartAndEnd() : Output;

        //UE_LOG(LogTemp, Warning, TEXT("Model Response Parsed: %s"), *ResponseText);

        KonusmaGecmisi.Add(FConversationLine{ ResponseText, KarakterAdi, TEXT("") });

     
        AsyncTask(ENamedThreads::GameThread, [this]()
            {
                if (OnKonusmaGuncellendi.IsBound())
                {
                    OnKonusmaGuncellendi.Broadcast();
                }
            });
        });

    
    AktifSurec->OnCompleted().BindLambda([this](int32 ReturnCode, bool bSuccess) {
        bCevapBekleniyor = false;
        UE_LOG(LogTemp, Warning, TEXT("Node.js process completed. Return Code: %d"), ReturnCode);

 
        AktifSurec.Reset();
        });

    AktifSurec->Launch();
}

void AAICharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}