#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "floatmaster-33368.firebaseio.com"
//#define FIREBASE_AUTH "token_or_secret"
#define WIFI_SSID "monsunz"
#define WIFI_PASSWORD "qwertyuiop"


char f1[50];
char f2[50];
char f3[50];
char difference[50];

int threshold = 20;

const int led1 = D0;
const int buzzer = D5;
const int wifi_led = D6;

float prevTime = 0;

void setup() {
  pinMode(led1,OUTPUT);
  Serial.begin(115200);

  lcd.begin();
  lcd.backlight();

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  //Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    //Serial.print(".");
    delay(500);
  }
  //Serial.println();
  //Serial.print("connected: ");
  //Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST);
  digitalWrite(wifi_led,HIGH);
  lcd.print("Connected");
  // put your setup code here, to run once:

}

void loop() {
 

  
  
      
      int flow1 = Firebase.getInt("FLOWRATE_Sensor1");
      int flow2 = Firebase.getInt("FLOWRATE_Sensor2");
      //int flow3 = Firebase.getInt("FLOWRATE_Sensor3");
      int flow3 = 0;
      int diff;
    
      diff = flow1 - flow2;
    
      Serial.print(flow1);
      Serial.print(" ");
      Serial.print(flow2);
      Serial.print(" ");
      Serial.print(flow3);
      Serial.print(" ");
      Serial.print(diff);
      Serial.print(" ");
      Serial.println();

      lcd.clear();
      lcd.print("Flow 1: ");
      lcd.print(flow1);

      lcd.setCursor(0,1);

      lcd.print("Flow 2: ");
      lcd.print(flow2);
      
    
  
  
  
  digitalWrite(led1,LOW);
  

  sprintf(f1, "\"%d\"", flow1);
  sprintf(f2, "\"%d\"", flow2);
  sprintf(f3, "\"%d\"", flow3);
  sprintf(difference,"\"%d\"",diff);

  Firebase.setString("SENSOR1", f1);
  Firebase.setString("SENSOR2", f2);
  Firebase.setString("SENSOR3", f3);

  //float currentTime = millis();

  //delay(5000);

  

  
  

  if(diff>threshold)
  {

      float currentTime = millis();

      float difer = currentTime-prevTime;
      


      

     

      ///delay(5000);

      

      if(difer>5000)
      {

        int flow1 = Firebase.getInt("FLOWRATE_Sensor1");
        int flow2 = Firebase.getInt("FLOWRATE_Sensor2");
        //int flow3 = Firebase.getInt("FLOWRATE_Sensor3");
        int flow3 = 0;
        int diff;

        
    
        diff = flow1 - flow2;

        if(diff>threshold)
        {
          while(diff>threshold)
          {
            lcd.clear();
            lcd.print("   WARNING!!!");
            lcd.setCursor(0,1);
            lcd.print("WATER LEAKAGE");
            
          Firebase.setString("WARNING","\"B\"");
          
          digitalWrite(led1,HIGH);

          digitalWrite(buzzer,HIGH);
          delay(1000);
          digitalWrite(buzzer,LOW);
          delay(2000);

          //String e = 

          Serial.println(Firebase.getString("WARNING"));
          //delay(5000)
          }
        
        }

        else
        {
          digitalWrite(led1,LOW);
        }

        prevTime = currentTime;

        Serial.println(difer);
      
      
      
        
      
    
    }

  
  // put your main code here, to run repeatedly:

}

}
