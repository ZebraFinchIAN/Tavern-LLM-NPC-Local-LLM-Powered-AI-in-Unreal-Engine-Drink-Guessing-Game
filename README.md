Yerel bir Büyük Dil Modeli (LLM) kullanarak Unreal Engine 5 içinde dinamik NPC diyalogları oluşturan bir  proje.
Bu projenin temel amacı, bir LLM'i yerel bir sunucu üzerinden çalıştırarak Unreal Engine ile entegre etmektir. LLM'den alınan metin cevapları, oyun içinde NPC diyalogları olarak kullanılır.

Bu projedeki temel entegrasyon mantığı, **Joe Gibbs**'in **[local-llms-ue5](https://github.com/joe-gibbs/local-llms-ue5)** deposundan uyarlanmıştır.
Proje üç ana katmandan oluşur:
## Kurulum Adımları

Projeyi çalıştırmak için bir backend (LLM sunucusu) ve bir frontend (Unreal projesi) kurulmalıdır.

### Bölüm 1: Backend Kurulumu (LLM Sunucusu)

1.  **Llama.cpp Kurulumu:**
    *  https://github.com/ggml-org/llama.cpp den llama.cpp yi indirin ve kurun.

2.  **Model İndirme:**
    *   Hugging Face gibi bir kaynaktan `Mistral 7B Instruct` modelinin `.gguf` formatını indirin.
    *   Modeli `llama.cpp/models` klasörüne taşıyın.

3.  **Sunucuyu Başlatma:**
    *   `llama.cpp` klasöründe terminali açın ve serveri çalıştırın.

### Bölüm 2: Frontend Kurulumu (Unreal Projesi)

1.  **Yapılandırma:**
    *   `Source/LLMProjem/AICharacter.cpp` dosyasını açın.
    *   `PromptGonder` fonksiyonundaki `nodeExePath` ve `scriptPath` değişkenlerini kendi bilgisayarınızdaki mutlak dosya yolları ile değiştirin.

2.  **Projeyi Derleme ve Çalıştırma:**
    *   `.uproject` dosyasına sağ tıklayıp "Generate Visual Studio project files" seçeneğine tıklayın.
    *   Oluşan `.sln` dosyasını Visual Studio'da açın ve projeyi derleyin (Build).
    *   Unreal Engine editörünü açın ve Play butonuna basın.
