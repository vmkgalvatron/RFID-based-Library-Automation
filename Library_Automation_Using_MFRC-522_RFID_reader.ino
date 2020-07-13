#include <LiquidCrystal.h>
#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal lcd(9, 7, 6, 4, 3, 2);

String studentUIDArray[]={"B1 3C CB 20","81 1B 00 1B"};
String bookUIDArray[]={"09 6E 99 6E","86 12 C3 F7"};
String studentnameArray[]={"Aditya","Vedant",};
String booknameArray[]={"PBL Book","Encyclopedia"};
 
void setup() 
  {
  Serial.begin(9600);
  Serial.print("Student Name          Book Name");
  Serial.println();
  SPI.begin();
  mfrc522.PCD_Init();
  lcd.begin(16,2);         
  delay(2000);
  }

void loop() 
{
lcd.print("Show StudentCard");
delay(1000);
lcd.clear();
delay(400);
String t;
String s;
String q;
int f[]={};
if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {return;}
if ( ! mfrc522.PICC_ReadCardSerial()) 
  {return;}
String content="";
byte letter;
for (byte i = 0; i < mfrc522.uid.size; i++) 
    {content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));}
content.toUpperCase();
for(int k=0;k<2;k++)
   {if (studentUIDArray[k]==content.substring(1))
    {lcd.setCursor(0,0);
    lcd.print("Varified Student");
    t=studentnameArray[k];
    delay(3000);
    break;}
   else
   {f[k]=1;}}
for(int g=0;g<2;g++)
   {if(f[g]==1)
   {Serial.println("Insecured attempt by "+ content.substring(1));
   delay(2000);
   break;}}
if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {return;}
if ( ! mfrc522.PICC_ReadCardSerial()) 
  {return;}
String content1="";
byte letter1;
for (byte i = 0; i < mfrc522.uid.size; i++) 
    {content1.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content1.concat(String(mfrc522.uid.uidByte[i], HEX));}
Serial.println();
content1.toUpperCase();
   {for(int z=0;z<1;z++)
   if (content1.substring(1)=bookUIDArray[z] and content.substring(1) == t)
   {lcd.clear();
   lcd.print("book issued");
   s=booknameArray[z];
   delay(3000);}
   }
Serial.println( t +"          "+ s );
delay(50);    
lcd.clear();
lcd.print("Sname "+t);
lcd.setCursor(0,1);
lcd.print("Bname "+s);
delay(2000);
lcd.clear();
lcd.print("      DONE      ");
delay(3000);
lcd.clear();  
}
