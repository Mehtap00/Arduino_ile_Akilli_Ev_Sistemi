#include <LiquidCrystal.h>
#include <Keypad.h>

#define yangin_pin A0
#define buzzer 52
#define hareket 15
#define role 16
int kontrol = LOW;
int sicaklik_sensoru=A15;
int giris_degeri=0;
float sicaklik2=0;
float sicaklik1=0;

int dogru=0;
char klavye_tuslari[4][3]={{'1','2','3'},{'4','5','6'},{'7','8','9'},{'*','0','#'}};
byte satir_pinleri[4]={48,49,30,31};
byte sutun_pinleri[3]={43,39,35};
char girilen_karakter;
String kayitli_sifre="9876";
String girilen_sifre="";

LiquidCrystal lcd_ekran(20,21,22,23,24,25);
Keypad klavye=Keypad(makeKeymap(klavye_tuslari),satir_pinleri,sutun_pinleri,4,3); 

void setup() {
  pinMode(hareket, INPUT);
  pinMode(role, OUTPUT);
  pinMode(28,OUTPUT);
  pinMode(53,OUTPUT);
  pinMode(yangin_pin, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  lcd_ekran.begin(32,2);
  lcd_ekran.print("Sifreyi Giriniz: ");
  
  do{
  dogru=0;
  girilen_karakter=klavye.getKey();
  if(girilen_karakter){  
    
  if(girilen_karakter!='#'){
  girilen_sifre=girilen_sifre+girilen_karakter;
  lcd_ekran.print(girilen_karakter);}
   
  if(girilen_karakter=='#'){
  if(girilen_sifre==kayitli_sifre){
  digitalWrite(53,HIGH);
  delay(850);
  digitalWrite(53,LOW);
  girilen_sifre="";
  dogru=1;}
  
  else if(girilen_sifre!=kayitli_sifre){
  digitalWrite(28,HIGH);
  delay(850);
  digitalWrite(28,LOW);
  girilen_sifre="";
  lcd_ekran.setCursor(17,0);
  lcd_ekran.print("               ");
  lcd_ekran.setCursor(17,0);}
  }
  }}while(dogru==0);

  lcd_ekran.clear();
  lcd_ekran.setCursor(0,0);
  giris_degeri=analogRead(sicaklik_sensoru);
  delay(500); 
}


void loop() {
  
  int yangin = digitalRead(yangin_pin);
  if(yangin==HIGH)
  {
    digitalWrite(buzzer, HIGH);  
  }
  else
  {
    digitalWrite(buzzer, LOW); 
  }
  
  kontrol = digitalRead(hareket);
  delay(100);

  if (kontrol == HIGH) {
    digitalWrite(role, HIGH);
  } 
  
  else {
    digitalWrite(role, LOW);
  }
  giris_degeri=analogRead(sicaklik_sensoru);
  delay(10);

  sicaklik2=giris_degeri*(5000.0/1023.0);
  sicaklik1=sicaklik2/10.0;

  lcd_ekran.setCursor(0,0);
  lcd_ekran.print("TEMPERATURE IS: ");
  lcd_ekran.print((int)sicaklik1);
  lcd_ekran.print("  ");

  if((int)sicaklik1<20){
  lcd_ekran.setCursor(0,1);
  lcd_ekran.print("Sicaklik dustu");}

  else if((int)sicaklik1>30){
  lcd_ekran.setCursor(0,1);
  lcd_ekran.print("Sicaklik yukseldi");}

  else{
  lcd_ekran.setCursor(0,1);
  lcd_ekran.print("                  ");  
  }
  
   
}
