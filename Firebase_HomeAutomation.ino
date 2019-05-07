
#include <ESP8266WiFi.h>
#include<FirebaseArduino.h>
#define FIREBASE_HOST "home-automation-2b50a.firebaseio.com"                     //fire base URL
#define FIREBASE_AUTH "BZoZjIws11PJWca8E7tZM1Yv1sjYU2pdt40nbzRU"       //Firebase Database Secret
#define WIFI_SSID "Realme C1"             //WiFi SSID  NodeMCU connects
#define WIFI_PASSWORD "mieayambakso"        //Password wifi 

#define Relay1 12 //D6
int val1;

#define Relay2 14 //D2
int val2;

#define Relay3 4  //D1
int val3;

#define Relay4 5 //D5
int val4;

void setup() 
{
  Serial.begin(115200);                                                   //baud rate on Serial Monitor
  pinMode(Relay1,OUTPUT);
  pinMode(Relay2,OUTPUT);
  pinMode(Relay3,OUTPUT);
  pinMode(Relay4,OUTPUT);

  digitalWrite(Relay1,HIGH);
  digitalWrite(Relay2,HIGH);
  digitalWrite(Relay3,HIGH);
  digitalWrite(Relay4,HIGH);



  
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status()!=WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected:");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
  Firebase.setInt("S1",0);                     //variabel"S1","S2","S3" and "S4" yang digunakan di  Firebase dan MIT App Inventor
  Firebase.setInt("S2",0); 
  Firebase.setInt("S3",0); 
  Firebase.setInt("S4",0); 
  
}
void firebasereconnect()
{
  Serial.println("Trying to reconnect");
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  }

void loop() 
{
  if (Firebase.failed())
      {
      Serial.print("setting number failed:");
      Serial.println(Firebase.error());
      firebasereconnect();
      return;
      }
      
  val1=Firebase.getString("S1").toInt();                                        //pembacaan nilai status dari firebase
  
  if(val1==1)                                                             // jika ,  Statusnya 1, relay1 on
     {
      digitalWrite(Relay1,LOW);
      Serial.println("light 1 ON");
    }
    else if(val1==0)                                                      // jika, Status status 0, Relay1 off
    {                                      
      digitalWrite(Relay1,HIGH);
      Serial.println("light 1 OFF");
    }

  val2=Firebase.getString("S2").toInt();                                        //pembacaan nilai status dari firebase
  
  if(val2==1)                                                             // jika ,  Statusnya 1, relay2 on
     {
      digitalWrite(Relay2,LOW);
      Serial.println("light 2 ON");
    }
    else if(val2==0)                                                      // jika, Status status 0, Relay2 off
    {                                      
      digitalWrite(Relay2,HIGH);
      Serial.println("light 2 OFF");
    }

   val3=Firebase.getString("S3").toInt();                                        //pembacaan nilai status dari firebase
  
  if(val3==1)                                                             // jika ,  Statusnya 1, relay3 on
     {
      digitalWrite(Relay3,LOW);
      Serial.println("light 3 ON");
    }
    else if(val3==0)                                                      // jika, Status status 0, Relay3 off
    {                                      
      digitalWrite(Relay3,HIGH);
      Serial.println("light 3 OFF");
    }

   val4=Firebase.getString("S4").toInt();                                        //pembacaan nilai status dari firebase
  
  if(val4==1)                                                             //  jika ,  Statusnya 1, relay4 on
     {
      digitalWrite(Relay4,LOW);
      Serial.println("light 4 ON");
    }
    else if(val4==0)                                                      //  jika, Status status 0, Relay4 off
    {                                      
      digitalWrite(Relay4,HIGH);
      Serial.println("light 4 OFF");
    }    
}
