# projeler
Lazerli Ev Güvenlik Modülü
#include <Keypad.h> //kullandığımız 4x4 keypad in kütüphanesine kodumuza import ettik
#include <LiquidCrystal_I2C.h> //kullandığımız l2c li 16x2 lcd ekranımızın kütüphanesini kodumuza import ettik

LiquidCrystal_I2C lcd(0x27,16,2); //lcd ekranımızın 16x2 olduğunu sisteme söyledik


const byte satir = 4; //keypadimizin bir satırında bulunan buton sayısının 4 olduğunu
const byte sutun = 4;//keypadimizin bir sütununda bulunan buton sayısının 4 olduğunu

char tus_takimi[satir][sutun] = {//keypedimizde hangi tuşa basıldığında hangi karekteri vereceğini yazdık
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}

};

byte satir_pinleri[satir] = {9, 8, 7, 6};//keypadimizin sütun pinleri
byte sutun_pinleri[sutun] = {5, 4, 3, 2};//keypadimizin satır pinleri

Keypad kasa = Keypad(makeKeymap(tus_takimi), satir_pinleri, sutun_pinleri, satir, sutun);



String girilen_sifre="";//girilen şifreyi hafızada tutmak için bir string tanımladık
String sifre="1947#";//doğru şifreyi belirledik

int kled=11;//sistemde kullancağımız kompanentlerin hangi pinlerde takılı olduğunu int değişkeni altında belirledik
int yled=A2;
int x=0;
int a=0;
int e=0;
int s=0;
int n=0;
int k=10;
int ldr =A0;
int pir=12;
int touch=10;
int buzer1=1;
int buzer2=13;
int laser=A3;
int berat=A1;

int ra=0;



void setup()
{
  Serial.begin(9600);//seri haberleşmeyi 9600 bantında başlattık
  lcd.begin();//lcd için bir haberleşme başlattık

  pinMode(kled,OUTPUT);//kullandığımız kompanentlerden veri alacağımızı veya güç vereceğimizi belirledik
  pinMode(ldr,INPUT);
  pinMode(pir,INPUT);
  pinMode(touch,INPUT);
  pinMode(yled,OUTPUT);
  pinMode(buzer1,OUTPUT);
  pinMode(buzer2,OUTPUT);
  pinMode(laser,OUTPUT);
  pinMode(berat,OUTPUT);
}

void loop()
{
  
  lcd.setCursor(0,0);//lcdnin x ve y deki yazacağı yazının başlangıç noktasının (0,0) olduğunu belirtiyoruz
  lcd.print("BASLATMAK iCiN");//lcd de (0,0) koordinatında yazılacak yazıyı belirtiyoruz
lcd.setCursor(0,1);
lcd.print("BASIN");
 digitalWrite(buzer1,0);
digitalWrite(buzer2,0);
analogWrite(yled,0);
digitalWrite(kled,0);
 
int touch_deger=digitalRead(touch);//touch sensörümüzden aldığımız değeri başka bir değişken tanımlayarak ileride kullanmak için içine atıyoruz
if(touch_deger==1){//touch sensörümüze basıldığında sistem başlaması için if komutu ile şartlandırıyoruz
lcd.clear();//lcd ekranımızdaki yazıyı temizliyoruz
 analogWrite(berat,255);
 analogWrite(laser,255);
 digitalWrite(buzer1,0);
  digitalWrite(buzer2,0);
  for(ra=0;ra<11;ra++){//touch sensörümüzden 1 verisi gelince evden çıkmak için 60 saniyemiz olduğunu ekrana geri sayımla yazdırmak için bir for döngüsünde kısa bir kod ile yazıyoruz

    Serial.println(k);
    lcd.setCursor(0,0);
    lcd.print("BASLAMASINA SON");
    lcd.setCursor(0,1);
    lcd.print(k);
    k=k-1;//k sayısını k-1 olarak tanımlıyoruz ki her for döngüsüne girdiğinde geri sayım olması için 1 eksilerek devam etsin
    delay(1000);//burada 1 saniye beklemesini sağlıyoruz ki iki sayı arasında bir saniye geçerek ekrana yazsın
    lcd.clear();
  }
  Serial.println("SİSTEM BAŞLADI");
  lcd.setCursor(0,0);
  lcd.print("SiSTEM BASLADI");
   delay(1000);
 lcd.clear();
while(e==0){//burada bir while döngüsüne alıyoruz çünkü şifre girilmediği sürece sürekli sistem çalışmaya devam etsin
int pir_deger=digitalRead(pir);//pır sensörü yani hareket sensöründen aldığımız veriyi int değişkeni altında tanımladığımız pir_deger değişkeni içine aktarıyoruz
analogWrite(yled,1);

   int ldr_deger=analogRead(ldr);//ldr ye gelen değeri int değişkeni altında tanımladığımız bir değişkene aktararak ileride karşılaştırma yapmak amacı ile tuttuk
   Serial.println(ldr_deger);
   touch_deger=digitalRead(touch);//touch sensöründen gelen veriyi dijital pine bağladığımız için digitalRead komutu altında tekrar okuduk
 
 
  if(ldr_deger<930){//pır sensörümüzün hareket algıması halinde if koşulununun içindeki kodları işlemeye başlayacak
    lcd.clear();//lcd ekranımızdaki yazıyı sildik
    digitalWrite(kled,1);//kırmızı ledimize pır sensörümüzün hareket algılaması halinde yanması için kodladık
    digitalWrite(buzer1,1);//buzzer1 titreşim sensörümüzün pır sensörümüzün hareket algılaması halinde titremesi için kodladık
      digitalWrite(buzer2,1);//buzzer2 titreşim sensörümüzün pır sensörümüzün hareket algılaması halinde titremesi için kodladık
      analogWrite(yled,0);//yeşil ledi söndürdük
lcd.setCursor(1,0);//lcd ekranımızın (1,0) koordinatlarında yazı yazacağımızı bildirdik
  lcd.print("SiFRE GiRiN");

    while(a==0){//a değişkenini daha önce int değişkeni altında 0 olarak tanımladığımız için while döngüsünde koşul olarak yazarak bir sonsuz döngüye alıyoruz tabi istediğimiz zaman çıkmak koşuluyla
  char tus = kasa.getKey();//4x4 keypadimizden gelen veriyi tus değişkenine atayarak kullanabilmemizi sağlıyoruz

  

   
  if (tus != NO_KEY)//if koşul olarak 4x4 keypadimizde bir tuşa basılması halinde içindeki komutları gerçekleştirecek
  {
    girilen_sifre = girilen_sifre+tus;//girilen_sifre adında string değişkeni altında oluşturduğumuz değişkeni bir kasa gibi kullanarak tus verisini üzerine ekleyerek devam etmesi sağlıyoruz
    Serial.println(girilen_sifre);
    lcd.setCursor(0,1);
    lcd.print(girilen_sifre);//girilen sifreyi lcdnin (0,1)  koordintlarından başlayarak yazmasını istiyoruz
    
  }

  if(tus == '#')//burada hashtag tuşuna basılması halinde şifrenin doğru veya yanlış olması sorgulayacak bir koşuldur
    {
      
      
      if(girilen_sifre == sifre)//girilen_sifre nin belirlediğimiz şifreye eşit olması koşulunda şifrenin doğru olduğunu belirleyen bir koşul
      {
       lcd.clear();
        Serial.println("SiFRE DOGRU");
        lcd.setCursor(0,0);
        lcd.print("SiFRE DOGRU");
        digitalWrite(kled,0);
        analogWrite(yled,1);
        digitalWrite(buzer1,0);
      digitalWrite(buzer2,0);
      delay(100);
      digitalWrite(buzer2,1);
      delay(100);
     digitalWrite(buzer2,0);
      delay(100);
      digitalWrite(buzer2,1);
      delay(100);
      digitalWrite(buzer2,0);
         girilen_sifre="";//girilen_sifre adında oluşturduğumuz değişkenin içini boşaltarak tekrar kullanılabilir bir hale getiriyoruz
         lcd.clear();
         lcd.setCursor(0,0);
         lcd.print("SiSTEMiN YENiDEN");
         lcd.setCursor(0,1);
         lcd.print("BASLAMASINA");
         k=10;
         ra=0;
         for(ra=0;ra<11;ra++){//Sistemin tekrar başlamadan önce bir ara vermesi için for döngüsü altında k sayısını bir eksilterek bir geri sayım oluşturuyoruz
k=k-1;
lcd.setCursor(11,1);
lcd.print(k);
         }
         lcd.clear();
          break;// şifremizin doğru olması koşulunda girdiğimiz sonsuz while döngüsünden çıkıyoruz
       
        }
      else//şifremizin doğru olmaması koşulunda geriye sadece yanlış olması seçeneği kaldığı için ayrı bir else if koşulu bildirmeden else kullandık
      {
      lcd.clear();
      Serial.print("YANLIS :");
      Serial.println(girilen_sifre);
      lcd.setCursor(0,0);
      lcd.print("YANLIS SiFRE");
      lcd.setCursor(0,1);
      lcd.print(girilen_sifre);
      analogWrite(yled,0);
 digitalWrite(kled,0);
 digitalWrite(buzer1,0);
  digitalWrite(buzer2,0);
 delay(150);
 digitalWrite(kled,1);
 digitalWrite(buzer1,1);
  digitalWrite(buzer2,1);
 delay(150);
 digitalWrite(kled,0);
 digitalWrite(buzer1,0);
  digitalWrite(buzer2,0);
  delay(150);
  digitalWrite(kled,1);
 digitalWrite(buzer1,1);
  digitalWrite(buzer2,1);
 lcd.clear();
     
       girilen_sifre="";//girilen_sifre adında oluşturduğumuz değişkenin içini boşaltarak tekrar kullanılabilir bir hale getiriyoruz
      
      }
      
      }
   
    }}
    else if(pir_deger==1){// ldr ye gelen lazer ışığı ortalama olarak 950 verisini ldr üzerinde  oluşturduğu için 950 den az bir veri gelmesi halinde birinin lazer üzerinden geçtiğini anlıyoruz
      while(x==0){//x değişkenini daha önce 0 olarak tanımladığımız için while döngüsüne koşul olarak yazdığımızda sonsuz bir while döngüsü oluşturmuş oluyoruz 
      digitalWrite(kled,1);
      analogWrite(yled,0);
        digitalWrite(buzer1,1);
        digitalWrite(buzer2,1);
      char tus = kasa.getKey();//4x4 keypadimizden gelen veriyi tus değişkenine atıyoruz
  if (tus != NO_KEY)//tuşa basıldığı zaman aşağıdaki kodları işlemeye başlayacak
  {
    lcd.clear();
    girilen_sifre = girilen_sifre+tus;//girilen_sifre adında oluşturduğumuz string değişkenine tus verisini üzerine ekleyerek kasada tutmasını sağlıyoruz
    Serial.println(girilen_sifre);
    
    lcd.setCursor(0,0);
    lcd.print("SiFRE GiRiN");
    lcd.setCursor(0,1);
    lcd.print(girilen_sifre);
   
  }
  if(tus == '#')//hashtag tuşuna basılması halinde şifrenin doğruluğu veya yanlışlığını sorgulamak için bu koşulu kullanıyoruz
    {
      if(girilen_sifre == sifre)//girilen_sifrenin belirlediğimiz sifreye eşit olması durumunda bu koşula girerek şifrenin doğru olduğunu bize bildirir
      {
        lcd.clear();
        Serial.println("SiFRE DOGRU");
        lcd.setCursor(0,0);
        lcd.print("SiFRE DOGRU");
          digitalWrite(kled,0);
        analogWrite(yled,1);
        digitalWrite(buzer1,0);
      digitalWrite(buzer2,0);
      delay(100);
      digitalWrite(buzer2,1);
      delay(100);
     digitalWrite(buzer2,0);
      delay(100);
      digitalWrite(buzer2,1);
      delay(100);
      digitalWrite(buzer2,0);
         girilen_sifre="";
        
      delay(1500);
      lcd.clear();
         lcd.setCursor(0,0);
         lcd.print("SiSTEMiN YENiDEN");
         lcd.setCursor(0,1);
         lcd.print("BASLAMASINA");
         k=10;
         ra=0;
         for(ra=0;ra<11;ra++){
k=k-1;
lcd.setCursor(11,1);
lcd.print(k);
         }
         lcd.clear();
    
       
        break;
        }
      else
      {
        lcd.clear();
      Serial.print("YANLIS :");
      Serial.println(girilen_sifre);
      lcd.setCursor(0,0);
      lcd.print("Yanlış");
       lcd.setCursor(0,1);
       lcd.print(girilen_sifre);
           analogWrite(yled,0);
 digitalWrite(kled,0);
 digitalWrite(buzer1,0);
  digitalWrite(buzer2,0);
 delay(150);
 digitalWrite(kled,1);
 digitalWrite(buzer1,1);
  digitalWrite(buzer2,1);
 delay(150);
 digitalWrite(kled,0);
 digitalWrite(buzer1,0);
  digitalWrite(buzer2,0);
  delay(150);
  digitalWrite(kled,1);
 digitalWrite(buzer1,1);
  digitalWrite(buzer2,1);
 
     
       girilen_sifre="";
      }
      }
   delay(100);
      }}
  else{
    digitalWrite(buzer1,0);
  digitalWrite(buzer2,0);
    digitalWrite(kled,1);
    analogWrite(yled,0);
    delay(100);
    digitalWrite(kled,0);
    analogWrite(yled,1);
    delay(100);
     analogWrite(yled,0);
    digitalWrite(kled,0);
    delay(1000);
  }
}
}

}
