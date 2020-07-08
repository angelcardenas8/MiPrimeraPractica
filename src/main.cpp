#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

//Aqui se modificaron el nombre de algunas clases.

class estaEsLaConexionWeb{
  private:

  public:
    estaEsLaConexionWeb(const char *_SSID, const char* _PASSWORD ){
      WiFi.begin(_SSID, _PASSWORD);
      while(WiFi.status()!= WL_CONNECTED){
          delay(500);
          Serial.print("...");
      }
    }

}; 

class DatosDelTiempo
{
private:
  int defaultTime;
  struct tm timeinfo;
  const char *ntpServer = "pool.ntp.org";
  const long gmtOffset_sec = 0;
  const int daylightOffset_sec = 0;

public:
  char timeStringBuff[20];
  DatosDelTiempo()
  {
    defaultTime = 0;
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    getTime();
  }

  void getTime()
  {   
    setLocalTime();
  }

  void setLocalTime()
  {
    
    if (!getLocalTime(&timeinfo))
    {
    }
    strftime(timeStringBuff, sizeof(timeStringBuff), "%Y-%m-%dT%H:%M:%SZ", &timeinfo);
  }
};
estaEsLaConexionWeb *webInterface;
DatosDelTiempo *reloj;
StaticJsonDocument<512> horaActual;


const char *ssid="Ubee16F8-2.4G";
const char *passwrd="5F99F616F8";


void setup() {
  Serial.begin(115200);
  webInterface= new estaEsLaConexionWeb(ssid,passwrd);
  reloj=new DatosDelTiempo();
  
}
int suma=0;
void loop() {
  suma++;
  horaActual.clear();
  reloj->getTime();
  horaActual["hora"]=reloj->timeStringBuff;
  horaActual["Sumatoria"]=suma;
  serializeJson(horaActual,Serial);
  Serial.println("");
  delay(1000);
}

