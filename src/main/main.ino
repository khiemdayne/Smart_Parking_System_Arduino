#include <Servo.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);
#include <SPI.h> 
#include <MFRC522.h>

Servo myservo_vao;
Servo myservo_ra;
int servoPin_vao = 6; 
int servoPin_ra = 7;

#define ir_car1 A1
#define ir_car2 A0
#define ir_car3 2
#define ir_car4 3
#define ir_car5 4
#define ir_car6 5

#define buzzer 8 //coi
#define RST_PIN 9
#define SS_PIN 10
MFRC522 mfrc522(SS_PIN, RST_PIN);

int UID[4];
int IDs[7][4] = {
  {115, 17, 122, 22},
  {243, 217, 104, 22},
  {51, 28, 108, 22},
  {179, 158, 117, 22},
  {163, 100, 97, 22},
  {83, 221, 91, 22},
  {00, 126, 137, 26}
};

bool code_IDs[7] = {true, true, true, true, true, true, true};
int S1 = 0, S2 = 0, S3 = 0, S4 = 0, S5 = 0, S6 = 0;
int total;

void setup() {

  pinMode(ir_car1, INPUT);
  pinMode(ir_car2, INPUT);
  pinMode(ir_car3, INPUT);
  pinMode(ir_car4, INPUT);
  pinMode(ir_car5, INPUT);
  pinMode(ir_car6, INPUT);

  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, 0);

  lcd.init();
  lcd.backlight();
  lcd.setCursor (6, 0);
  lcd.print("TEKY");
  lcd.setCursor (1, 1);
  lcd.print("San Pham Demo");
  delay (2000);
  lcd.clear();

  myservo_vao.attach(servoPin_vao); 
  myservo_ra.attach(servoPin_ra); 
  myservo_vao.write(90);
  myservo_ra.write(90); 

  SPI.begin();               // Init SPI bus
  mfrc522.PCD_Init();      
}
void control_servo_vao() {  //  xe vao
  lcd.clear();
  lcd.setCursor (3, 0);
  lcd.print("Xin Chao!");
  myservo_vao.write(180);
  digitalWrite(buzzer, 1);
  delay(100);
  digitalWrite(buzzer, 0);
  delay(2800);
  myservo_vao.write(90);
  lcd.clear();
}
void control_servo_ra() {  // mo cua cho xe ra
  lcd.clear();
  lcd.setCursor (0, 0);
  lcd.print("Cam On Quy Khach");
  myservo_ra.write(180);
  digitalWrite(buzzer, 1);
  delay(100);
  digitalWrite(buzzer, 0);
  delay(2800);
  myservo_ra.write(90);
  lcd.clear();
}
void Read_Sensor() {
  if (digitalRead(ir_car1) == 0)  S1 = 1; else  S1 = 0;
  if (digitalRead(ir_car2) == 0)  S2 = 1; else  S2 = 0;
  if (digitalRead(ir_car3) == 0)  S3 = 1; else  S3 = 0;
  if (digitalRead(ir_car4) == 0)  S4 = 1; else  S4 = 0;
  if (digitalRead(ir_car5) == 0)  S5 = 1; else  S5 = 0;
  if (digitalRead(ir_car6) == 0)  S6 = 1; else  S6 = 0;
  
  total = S1 + S2 + S3 + S4 + S5 + S6;
  
  lcd.setCursor (0, 0);
  lcd.print("VT: 1 2 3 4 5 6");
  lcd.setCursor (4, 1);
  if (S1 == 1) lcd.print("x");  else lcd.print("0");
  lcd.setCursor (6, 1);
  if (S2 == 1) lcd.print("x");  else lcd.print("0");
  lcd.setCursor (8, 1);
  if (S3 == 1) lcd.print("x");  else lcd.print("0");
  lcd.setCursor (10, 1);
  if (S4 == 1) lcd.print("x");  else lcd.print("0");
  lcd.setCursor (12, 1);
  if (S5 == 1) lcd.print("x");  else lcd.print("0");
  lcd.setCursor (14, 1);
  if (S6 == 1) lcd.print("x");  else lcd.print("0");
}
void loop() {
  Read_Sensor(); 
  if(total<6){
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
//    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    UID[i] = mfrc522.uid.uidByte[i];
  }
 
  for (int i = 0; i < 7; i++) {
  if (UID[0] == IDs[i][0]) {
    if (code_IDs[i] == true) {
      control_servo_vao();
      code_IDs[i] = false;
    } else {
      control_servo_ra();
      code_IDs[i] = true;
    }
    break;
  }} 
  }
  if(total == 6){
   if(!mfrc522.PICC_ReadCardSerial())
   {
     return;
   } 
    for (byte i = 0; i < mfrc522.uid.size; i++)
    {
      UID[i] = mfrc522.uid.uidByte[i];
    }
    for (int i = 0; i < 7; i++) {
      if (UID[0] == IDs[i][0]) {
        if (code_IDs[i] == true) {
          lcd.clear();
          lcd.setCursor (3, 0);
          lcd.print("Da day xe!");
          digitalWrite(buzzer,1); 
          delay(1000);
          digitalWrite(buzzer,0);  
        } else {
          control_servo_ra();
          code_IDs[i] = true;
        }
        break; // Kết thúc vòng lặp khi tìm thấy ID tương ứng
      }
    }
  }
}
