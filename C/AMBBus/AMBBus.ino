#include <ESP8266WiFi.h>
#include <Wire.h>  // Include Wire if you're using I2C
#include <SFE_MicroOLED.h>  // Include the SFE_MicroOLED library

#define BUS_LINE_PATTERN "60 - "    

/**OLED**/
#define PIN_RESET 255  //
#define DC_JUMPER 0  // I2C Addres: 0 - 0x3C, 1 - 0x3D

#define INITHEIGHT 7
#define SPACEFONT 8

MicroOLED oled(PIN_RESET, DC_JUMPER);  // I2C Example

int SCREEN_WIDTH = oled.getLCDWidth();
int SCREEN_HEIGHT = oled.getLCDHeight();

/************************* WiFi Access Point *********************************/

#define WLAN_SSID "Orange-7360"
#define WLAN_PASS "zhpKKkmc"
WiFiClient client;

//Change to your server domain
char serverName[] = "www.ambmobilitat.cat";

// change to your server's port
int serverPort = 80;

// change to the page on that server
char pageName[] = "/ambtempsbus";

//Exp
char expresion[] = BUS_LINE_PATTERN;
int esize = 5;
char tiempo[] = "99 min.<";

bool first = true;

int totalCount = 0;
// insure params is big enough to hold your variables
char params[32];

// set this to the number of milliseconds delay
// this is 30 seconds
#define delayMillis 10000UL

unsigned long thisMillis = 0;
unsigned long lastMillis = 0;

void setup() {
  Serial.print("SETUP");

  oled.begin();
  oled.clear(PAGE);
  //oled.display();  
  oled.setFontType(0);

  Serial.begin(115200);
  delay(10);
  
  //listNetworks();

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS); 
  while (WiFi.status() != WL_CONNECTED) {    
    Serial.print(".");       
    delay(500);
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); 
  Serial.println(WiFi.localIP());

  //Init CURL params
  sprintf(params,"codi=817");//%i",totalCount);

}

void loop()
{
  Serial.print("LOOP");
  // If using a static IP, comment out the next line
  
  thisMillis = millis();

  if(thisMillis - lastMillis > delayMillis)
  {
    lastMillis = thisMillis;
       
    if(!postPage(serverName,serverPort,pageName,params)) Serial.print(F("Fail "));
    else {
      Serial.print(F("Pass "));
      oled.display();
    }
    totalCount++;
    Serial.println(totalCount,DEC);
  }
  delay(500);
}


byte postPage(char* domainBuffer,int thisPort,char* page,char* thisData)
{
  int inChar;
  char outBuf[64];

  Serial.print(F("connecting..."));

  if(client.connect(domainBuffer,thisPort) == 1)
  {
    Serial.println(F("connected"));

    // send the header
    sprintf(outBuf,"POST %s HTTP/1.1",page);
    client.println(outBuf);
    sprintf(outBuf,"Host: %s",domainBuffer);
    client.println(outBuf);
    client.println(F("Connection: close\r\nContent-Type: application/x-www-form-urlencoded"));
    sprintf(outBuf,"Content-Length: %u\r\n",strlen(thisData));
    client.println(outBuf);
    Serial.println(outBuf);
    

    // send the body (variables)
    client.print(thisData);
    Serial.println(thisData);
    
  }
  else
  {
    Serial.println(F("failed"));
    return 0;
  }

  int connectLoop = 0;
  
  int i = 0;
  bool markerOK = false;  
  int t = 0;

  Serial.println(tiempo);

  first = true;
  while(client.connected())
  {
    while(client.available())
    {
      inChar = client.read();
      //Serial.write(inChar);
      connectLoop = 0;
      if (!markerOK) {
        if (inChar == expresion[i]) {
          ++i;        
        } else {
          i = 0;
        }
  
        //IF it matches with expression
        if (i == esize) {
          Serial.println("MATCH!");
          i = 0;
          markerOK = true;
        }
      } else {
        if (inChar == '<') {
          //Serial.println("CODO OPEN");
          while(inChar != '>') { //Discard decorations
             inChar = client.read(); 
          }
          t = 0;
          while(inChar != '<') {
            inChar = client.read(); 
            //Serial.print(inChar);
            tiempo[t++] = inChar; 
          }          
          Serial.println("TIEMPO");
          Serial.println(tiempo);          
          if (first) {
            oled.clear(PAGE);
            oled.setCursor(0, INITHEIGHT);
            first= false;
          }
          else {
            oled.setCursor(0, INITHEIGHT+SPACEFONT);
          }
          oled.println(tiempo);
          markerOK = false;
        }
      }
      
    }

    delay(1);
    connectLoop++;
    if(connectLoop > 10000)
    {
      Serial.println();
      Serial.println(F("Timeout"));
      client.stop();
    }
  }

  Serial.println();
  Serial.println(F("disconnecting."));
  client.stop();

  if(first){
    oled.clear(PAGE);
    oled.setCursor(0, INITHEIGHT);
    first= false;
    oled.println("No data");
  }
  
  return 1;
}
