/*
 *
 * All the resources for this project: http://randomnerdtutorials.com/
 * Modified by Rui Santos
 *
 * Created by FILIPEFLOP
 *
 */
 
#include<SPI.h>
#include<MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
#define buzzer 8 //coi

MFRC522 mfrc522(SS_PIN,RST_PIN); // Create MFRC522 instance.
 
void setup()
{
 Serial.begin(9600); // Initiate a serial communication
  SPI.begin();     // Initiate  SPI bus
  mfrc522.PCD_Init(); // Initiate MFRC522
 Serial.println("Approximate your card to the reader...");
 Serial.println();
pinMode(buzzer,OUTPUT);
digitalWrite(buzzer,0);



}
void read_rfid(){
  // Look for new cards
 if(!mfrc522.PICC_IsNewCardPresent())
 {
   return;
 }
 // Select one of the cards
 if(!mfrc522.PICC_ReadCardSerial())
 {
   return;
 }
  digitalWrite(buzzer,1); 
  delay(2000);
  digitalWrite(buzzer,0);
}
void loop()
{
 read_rfid();
 

}
