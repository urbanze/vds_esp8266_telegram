#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#define BOTtoken "135924:AAErDKEJaQpEnqs_xj35asdGQ5kK6dQet4"//Define o Token do *seu* BOT

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

String id, text;//Váriaveis para armazenamento do ID e TEXTO gerado pelo Usuario
unsigned long tempo;

void setup()
{
   pinMode(D4, OUTPUT);//LED conectado à saida
   WiFi.mode(WIFI_STA);//Define o WiFi como Estaçao
   connect();//Funçao para Conectar ao WiFi
}

void loop()
{
   if (millis() - tempo > 2000)//Faz a verificaçao das funçoes a cada 2 Segundos
   {
      connect();//Funçao para verificar se ainda há conexao
      readTel();//Funçao para ler o telegram
      tempo = millis();//Reseta o tempo
   }
}

void connect()//Funçao para Conectar ao wifi e verificar à conexao.
{
   if (WiFi.status() != WL_CONNECTED)//Caso nao esteja conectado ao WiFi, Ira conectarse
   {
      WiFi.begin("SUA REDE", "SUA SENHA");//Insira suas informaçoes da rede
      delay(2000);
   }
}

void readTel()//Funçao que faz a leitura do Telegram.
{
   int newmsg = bot.getUpdates(bot.last_message_received + 1);

   for (int i = 0; i < newmsg; i++)//Caso haja X mensagens novas, fara este loop X Vezes.
   {
      id = bot.messages[i].chat_id;//Armazenara o ID do Usuario à Váriavel.
      text = bot.messages[i].text;//Armazenara o TEXTO do Usuario à Váriavel.
      text.toUpperCase();//Converte a STRING_TEXT inteiramente em Maiuscúla.

      if (text.indexOf("ON") > -1)//Caso o texto recebido contenha "ON"
      {
         digitalWrite(D4, 0);//Liga o LED
         bot.sendMessage(id, "LED ON", "");//Envia uma Mensagem para a pessoa que enviou o Comando.
      }

      else if (text.indexOf("OFF") > -1)//Caso o texto recebido contenha "OFF"
      {
         digitalWrite(D4, 1);//Desliga o LED
         bot.sendMessage(id, "LED OFF", "");//Envia uma Mensagem para a pessoa que enviou o Comando.
      }

      else if (text.indexOf("START") > -1)//Caso o texto recebido contenha "START"
      {
         bot.sendSimpleMessage(id, id, "");//Envia uma mensagem com seu ID.
      }

      else//Caso o texto recebido nao for nenhum dos acima, Envia uma mensagem de erro.
      {
         bot.sendSimpleMessage(id, "Comando Invalido", "");
      }
   }

}
