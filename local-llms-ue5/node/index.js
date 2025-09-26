import fetch from 'node-fetch'; 
import EventSource from "eventsource"; 


global.EventSource = EventSource;

const main = async () => {

  const promptText = process.argv[2];

  if (!promptText) {
    console.error("Hata: Lütfen bir soru girin.");
    console.log('Örnek Kullanım: node index.js "Türkiye\'nin başkenti neresidir?"');
    process.exit(1); 
  }

  //console.log(`Model'e gönderilen soru: ${promptText}`);

  const body = JSON.stringify({
    stream: true, 
    n_predict: 400,
    temperature: 0.7,
   
    stop: ["</s>", "Player:", "\nPlayer:", "Human:", "\nHuman:"], 
    
    prompt: promptText, 
  });

  let fullResponse = "";

  try {
    const response = await fetch("http://127.0.0.1:8080/completion", {
      headers: {
        "Content-Type": "application/json",
        "Accept": "text/event-stream"
      },
      method: "POST",
      body,
    });

    const reader = response.body;

    reader.on('readable', () => {
      let chunk;
      while (null !== (chunk = reader.read())) {
        const decodedChunk = chunk.toString();
        const lines = decodedChunk.split('\n');
        for (const line of lines) {
          if (line.startsWith('data: ')) {
            try {
              const jsonData = JSON.parse(line.substring(6));
              if (jsonData.content) {
                fullResponse += jsonData.content;
              }
              if (jsonData.stop) {
               
                //console.log("\n--- Modelin Cevabı ---");
                console.log(fullResponse.trim());
                process.exit(0);
              }
            } catch (e) { /* JSON parse hatası olabilir, devam et */ }
          }
        }
      }
    });

    reader.on('end', () => {
        
        //console.log("\n--- Modelin Cevabı (Akış Sonu) ---");
        console.log(fullResponse.trim());
        process.exit(0);
    });

  } catch (error) {
    console.error("Sunucuya bağlanırken bir hata oluştu:", error);
    process.exit(1); 
  }
};

main();