// POUR LA PETITE FABRIQUE -- PHILHARMONIE DE PARIS
//built largely upon this code here: https://www.hackster.io/condorapps1/nfc-controller-for-osc-a8aef1 

#include <SPI.h>
#include <MFRC522.h>
#include <WiFi.h>
#include <WiFiUDP.h>
#include <ArduinoOSC.h> // libary version 1.6


WiFiUDP udp;
ArduinoOSC<WiFiUDP> osc; 

////////////////set here the IP and the port of the receiving computer////////////
///////////////The port is usually indicated in the software you want to controll////
//////////////The ip can be left as it is if you use AP mode, but if not make sure you input the computer IP////////////////

const int recv_port = 57120;
const int send_port = 57120;
const char* host = "192.168.0.2";



///////////////////Set the ID for the NFC Tags Here/////////////////

// FIND THE TAG ID AND NOTE TO START WITH

const char* tag1 = "4 107 165 82";
const char* tag2 = "4 75 165 82";
const char* tag3 = "4 12 166 82";
const char* tag4 = "4 74 165 82";
const char* tag5= "4 43 165 82";

const char* tag6 = "4 245 110 50";
const char* tag7 = "4 214 110 50";
const char* tag8 = "4 21 110 50";
const char* tag9 = "4 246 110 50";
const char* tag10 = "4 55 110 50";

const char* tag11 = "4 244 108 50";
const char* tag12 = "4 49 108 50";
const char* tag13 = "4 19 108 50";
const char* tag14 = "4 80 108 50";
const char* tag15 = "4 50 108 50";

const char* tag16 = "4 74 146 82";
const char* tag17 = "4 10 146 82";
const char* tag18 = "4 42 146 82";
const char* tag19 = "4 232 146 82";
const char* tag20 = "4 9 146 82";

const char* tag21 = "4 93 170 82";
const char* tag22 = "4 64 170 82";
const char* tag23 = "4 127 170 82";
const char* tag24 = "4 94 170 82";
const char* tag25 = "4 116 171 82";

String previousTag = "";

////////////////Set OSC Commands here//////////////////

const char* command1 =  "/oscControl/1";

const char* command2 =  "/oscControl/2";

const char* command3 =  "/oscControl/3";

const char* command4 =  "/oscControl/4";

const char* command5 =  "/oscControl/five";


////Failsafe - if an unregistred tag is detected will send this command///
const char* other =  "/oscControl/stop";



//////////////////Define your SSID and Password - if on AP mode this will be used as settings for AP if in Wifi mode this will be used to connect to an existing WiFi network//////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char* ssid = "JDD-"; // add a,b,c,d,e etc. 
const char* password =  "mozomozo"; // make sure aligns with found solution
 


////Wifi stuff
WiFiServer server(80);
IPAddress IP(192,168,0,1);
IPAddress mask = (255, 255, 255, 0);

///nfc stuff
const int resetPin = 22; // Reset pin
const int ssPin = 21;    // Slave select pin
MFRC522 rfid = MFRC522(ssPin, resetPin); // Create instance
int code[] = {69,141,8,136}; //This is the stored UID
int codeRead = 0;
String uidString;
int selectedChannel = 0;



void setup() {

  ///serial setup
  Serial.begin(115200);
 
  SPI.begin();   
 
  rfid.PCD_Init();
  rfid.PCD_DumpVersionToSerial();  



//////////////Use this code if you want to connect the ESP32 to an existing WIFI/////////////
////////////////////////////////////////////////////////////////////////////////////////////


  /////Wifi connect

   WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
   
    delay(500);
    Serial.println("Connecting to WiFi..");
 
  }
 
  Serial.println("Connected to the WiFi network");


//////////////Use this code if you want to enable ESP32 AP mode and create a WiFI network/////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

 WiFi.mode(WIFI_AP);
 WiFi.softAP(ssid, password);
 WiFi.softAPConfig(IP, IP, mask);
 server.begin();

Serial.println();
Serial.println("Server started.");
Serial.print("IP: ");     Serial.println(WiFi.softAPIP());
Serial.print("MAC:");     Serial.println(WiFi.softAPmacAddress());


/////osc init
osc.begin(udp, recv_port);
}

void loop() {
//////Uncomment next line if you use the AP mode
runWifi();
runRfid();

}



void runWifi(){

  WiFiClient client = server.available();
  if (!client) {return;}
  
  String request = client.readStringUntil('\r');
  client.flush();

}

void runRfid(){

 // Look for new cards
  if ( ! rfid.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! rfid.PICC_ReadCardSerial()) {
    return;
  }

  // Dump debug info about the card. PICC_HaltA() is automatically called.
   uidString = String(rfid.uid.uidByte[0])+" "+String(rfid.uid.uidByte[1])+" "+String(rfid.uid.uidByte[2])+ " "+String(rfid.uid.uidByte[3]);

Serial.println("Detected:");
Serial.println(uidString);

///////You can use this code if all you need is to just send the next osc command when a new NFC is detected////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//if(uidString != previousTag){
//
//
//  previousTag = uidString;
//  if(selectedChannel == 6){
//
//    selectedChannel = 1;
//  }
//  else{
//
//  selectedChannel++;
//  }
//  sendOscSignal(selectedChannel);
//  
//}

///////////////////////////Use this code if you want to control the sent OSC Command When a certain NFC Tag is detected/////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

if(uidString == tag1){

  if(selectedChannel != 1){
  selectedChannel =  1;
  sendOscSignal(selectedChannel);
  }
}

else if(uidString == tag2){

  if(selectedChannel != 2){
  selectedChannel =  2;
  sendOscSignal(selectedChannel);
  }
}

else if(uidString == tag3){

  if(selectedChannel != 3){
  selectedChannel =  3;
  sendOscSignal(selectedChannel);
  }
}

else if(uidString == tag4){

  if(selectedChannel != 4){
  selectedChannel =  4;
  sendOscSignal(selectedChannel);
  }
}


else if(uidString == tag5){

  if(selectedChannel != 5){
  selectedChannel =  5;
  sendOscSignal(selectedChannel);
  }
}
 
else if(uidString == tag6){

  if(selectedChannel != 6){
  selectedChannel =  6;
  sendOscSignal(selectedChannel);
  }
}

else if(uidString == tag7){

  if(selectedChannel != 7){
  selectedChannel =  7;
  sendOscSignal(selectedChannel);
  }
}


else if(uidString == tag8){

  if(selectedChannel != 8){
  selectedChannel =  8;
  sendOscSignal(selectedChannel);
  }
}
 
else if(uidString == tag9){

  if(selectedChannel != 9){
  selectedChannel =  9;
  sendOscSignal(selectedChannel);
  }
} 
 
else if(uidString == tag10){

  if(selectedChannel != 10){
  selectedChannel =  10; // this shall appear in serial monitor in arduino ide
  sendOscSignal(selectedChannel);
  }
}

 if(uidString == tag11){

  if(selectedChannel != 11){
  selectedChannel =  11;
  sendOscSignal(selectedChannel);
  }
}

else if(uidString == tag12){

  if(selectedChannel != 12){
  selectedChannel =  12;
  sendOscSignal(selectedChannel);
  }
}

else if(uidString == tag13){

  if(selectedChannel != 13){
  selectedChannel =  13;
  sendOscSignal(selectedChannel);
  }
}

else if(uidString == tag14){

  if(selectedChannel != 14){
  selectedChannel =  14;
  sendOscSignal(selectedChannel);
  }
}


else if(uidString == tag15){

  if(selectedChannel != 15){
  selectedChannel =  15;
  sendOscSignal(selectedChannel);
  }
}
 
else if(uidString == tag16){

  if(selectedChannel != 16){
  selectedChannel =  16;
  sendOscSignal(selectedChannel);
  }
}

else if(uidString == tag17){

  if(selectedChannel != 17){
  selectedChannel =  17;
  sendOscSignal(selectedChannel);
  }
}


else if(uidString == tag18){

  if(selectedChannel != 18){
  selectedChannel =  18;
  sendOscSignal(selectedChannel);
  }
}
 
else if(uidString == tag19){

  if(selectedChannel != 19){
  selectedChannel =  19;
  sendOscSignal(selectedChannel);
  }
} 
 
else if(uidString == tag20){

  if(selectedChannel != 20){
  selectedChannel =  20; // this shall appear in serial monitor in arduino ide
  sendOscSignal(selectedChannel);
  }
} 
 
if(uidString == tag21){

  if(selectedChannel != 21){
  selectedChannel =  21;
  sendOscSignal(selectedChannel);
  }
}

else if(uidString == tag22){

  if(selectedChannel != 22){
  selectedChannel =  22;
  sendOscSignal(selectedChannel);
  }
}

else if(uidString == tag23){

  if(selectedChannel != 23){
  selectedChannel =  23;
  sendOscSignal(selectedChannel);
  }
}

else if(uidString == tag24){

  if(selectedChannel != 24){
  selectedChannel =  24;
  sendOscSignal(selectedChannel);
  }
} 

else if(uidString == tag25){

  if(selectedChannel != 25){
  selectedChannel =  25;
  sendOscSignal(selectedChannel);
  }
} 

 delay(500); 
  
}

void sendOscSignal(int v){
Serial.println("Preparing OSC:");
 OSCMessage msg;
    msg.beginMessage(host, send_port);

//READER 1
if(v == 1){
Serial.println("sending v1:");
 msg.setOSCAddress(command1);
 msg.addArgInt32(1); //this value is OSC message value
  Serial.println("a 1");
}
else if(v == 2){
Serial.println("sending v2:");
 msg.setOSCAddress(command1);
 msg.addArgInt32(2);
  Serial.println("a 2");
}

else if(v == 3){
Serial.println("sending v3:");
 msg.setOSCAddress(command1);
 msg.addArgInt32(3);
  Serial.println("a 3");
}

else if(v == 4){
Serial.println("sending v4:");
 msg.setOSCAddress(command1);
 msg.addArgInt32(4);
  Serial.println("a 4");
}

else if(v == 5){
Serial.println("sending v5:");
 msg.setOSCAddress(command1);
 msg.addArgInt32(5);
  Serial.println("a 5");
}



// READER 2

else if(v == 6){
Serial.println("sending v6:");
 msg.setOSCAddress(command2);
 msg.addArgInt32(1);
  Serial.println("b 1");
}

else if(v == 7){
Serial.println("sending v7:");
 msg.setOSCAddress(command2);
 msg.addArgInt32(2);
  Serial.println("b 2");
}

else if(v == 8){
Serial.println("sending v8:");
 msg.setOSCAddress(command2);
 msg.addArgInt32(3);
  Serial.println("b 3");
}

else if(v == 9){
Serial.println("sending v9:");
 msg.setOSCAddress(command2);
 msg.addArgInt32(4);
  Serial.println("b 4");
}

else if(v == 10){
Serial.println("sending v10:");
 msg.setOSCAddress(command2);
 msg.addArgInt32(5);
  Serial.println("b 5");
}


// READER 3


if(v == 11){
Serial.println("sending v11:");
 msg.setOSCAddress(command3);
 msg.addArgInt32(1); //this value is OSC message value
  Serial.println("c 1");
}
else if(v == 12){
Serial.println("sending v12:");
 msg.setOSCAddress(command3);
 msg.addArgInt32(2);
  Serial.println("c 2");
}

else if(v == 13){
Serial.println("sending v13:");
 msg.setOSCAddress(command3);
 msg.addArgInt32(3);
  Serial.println("c 3");
}

else if(v == 14){
Serial.println("sending v14:");
 msg.setOSCAddress(command3);
 msg.addArgInt32(4);
  Serial.println("c 4");
}

else if(v == 15){
Serial.println("sending v15:");
 msg.setOSCAddress(command3);
 msg.addArgInt32(5);
  Serial.println("c 5");
}


// READER 4

else if(v == 16){
Serial.println("sending v16:");
 msg.setOSCAddress(command4);
 msg.addArgInt32(1);
  Serial.println("d 1");
}

else if(v == 17){
Serial.println("sending v17:");
 msg.setOSCAddress(command4);
 msg.addArgInt32(2);
  Serial.println("d 2");
}

else if(v == 18){
Serial.println("sending v18:");
 msg.setOSCAddress(command4);
 msg.addArgInt32(3);
  Serial.println("d 3");
}

else if(v == 19){
Serial.println("sending v19:");
 msg.setOSCAddress(command4);
 msg.addArgInt32(4);
  Serial.println("d 4");
}

else if(v == 20){
Serial.println("sending v20:");
 msg.setOSCAddress(command4);
 msg.addArgInt32(5);
  Serial.println("d 5");
}


// READER 5


else if(v == 21){
Serial.println("sending v21:");
 msg.setOSCAddress(command5);
 msg.addArgInt32(1);
  Serial.println("e 1");
}

else if(v == 22){
Serial.println("sending v22:");
 msg.setOSCAddress(command5);
 msg.addArgInt32(2);
  Serial.println("e 2");
}

else if(v == 23){
Serial.println("sending v23:");
 msg.setOSCAddress(command5);
 msg.addArgInt32(3);
  Serial.println("e 3");
}

else if(v == 24){
Serial.println("sending v24:");
 msg.setOSCAddress(command5);
 msg.addArgInt32(4);
  Serial.println("e 4");
}

else if(v == 25){
Serial.println("sending v25:");
 msg.setOSCAddress(command5);
 msg.addArgInt32(5);
  Serial.println("e 5");
}

/*
else{

  Serial.println("sending other:");
 msg.setOSCAddress(command8);
 msg.addArgInt32(1);
  Serial.println("Sent other:");
}
*/
osc.send(msg);
}
