#include <LiquidCrystal.h>
#include <Password.h>
#include <Keypad.h>

Password passworda = Password("1111");
Password passwordb = Password("2222");
Password passwordc = Password("3333");
Password passwordd = Password("4444");
Password passworde = Password("1234");

char keys[4][4] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte baris[4] = {A15, A14, A13, A12};
byte kolom[4] = {A11, A10, A9, A8};
Keypad keypad = Keypad(makeKeymap(keys), baris, kolom, 4, 4);
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
int coinPin = 42;
int buzzerPin = 40;
int pintuA = 22;
int pintuB = 24;
int pintuC = 26;
int pintuD = 28;
int pintuE = 30;
int casA = 32;
int casB = 34;
int casC = 36;
int casD = 38;
int telegramPin = 23;
int kodeMenu = 0;
int loker1 = 0;
int loker2 = 0;
int loker3 = 0;
int loker4 = 0;
float volt;
int waktu1 = -1;
int waktu2 = -1;
int waktu3 = -1;
int waktu4 = -1;
int jumlah1;
int jumlah2;
int jumlah3;
int jumlah4;
int status1;
int status2;
int status3;
int status4;
int statusU;
int tambahDetik = 30;
int jumlahPass;
int jumlahJawab;
int resPass;
int ada;
int ok;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(coinPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  pinMode(pintuA, OUTPUT);
  pinMode(pintuB, OUTPUT);
  pinMode(pintuC, OUTPUT);
  pinMode(pintuD, OUTPUT);
  pinMode(pintuE, OUTPUT);
  pinMode(casA, OUTPUT);
  pinMode(casB, OUTPUT);
  pinMode(casC, OUTPUT);
  pinMode(casD, OUTPUT);
  pinMode(telegramPin, OUTPUT);

  digitalWrite(pintuA, LOW);
  digitalWrite(pintuB, LOW);
  digitalWrite(pintuC, LOW);
  digitalWrite(pintuD, LOW);
  digitalWrite(pintuE, LOW);
  digitalWrite(casA, LOW);
  digitalWrite(casB, LOW);
  digitalWrite(casC, LOW);
  digitalWrite(casD, LOW);
  digitalWrite(telegramPin, HIGH);
  delay(200);
  digitalWrite(buzzerPin, HIGH);
  delay(200);
  digitalWrite(buzzerPin, LOW);
  menu(kodeMenu);
  delay(2000);
  lcd.clear();
  kodeMenu = 1;
}

void loop() {
  volt = ((((analogRead(A1))*0.00489)*5)*7.14);
    if(volt>100) {
      volt = 100;
    }
     if(volt < 35) {
      menu(22);
    }
  for(int i = 0; i < 100; i++) {
    menu(kodeMenu);
    matiCas();

    if(kodeMenu == 1) {
      char c = keypad.getKey();
      if(c == 'A') {
        if(loker1 == 0) {
          kodeMenu = 2;
        } else {
          kodeMenu = 10;
          if(status1 == 1) {
            menu(14);
            delay(1000);
            jumlahPass = 0;
            jumlahJawab = 0;
            passworda.reset();
            resPass = 1;
            kodeMenu = 18;
          }
        }
      }
      if(c == 'B') {
        if(loker2 == 0) {
          kodeMenu = 3;
        } else {
          kodeMenu = 11;
          if(status2 == 1) {
            menu(15);
            delay(1000);
            jumlahPass = 0;
            jumlahJawab = 0;
            passwordb.reset();
            resPass = 1;
            kodeMenu = 18;
          }
        }
      }
      if(c == 'C') {
        if(loker3 == 0) {
          kodeMenu = 4;
        } else {
          kodeMenu = 12;
          if(status3 == 1) {
            menu(16);
            delay(1000);
            jumlahPass = 0;
            jumlahJawab = 0;
            passwordc.reset();
            resPass = 1;
            kodeMenu = 18;
          }
        }
      }
      if(c == 'D') {
        if(loker4 == 0) {
          kodeMenu = 5;
        } else {
          kodeMenu = 13;
          if(status4 == 1) {
            menu(17);
            delay(1000);
            jumlahPass = 0;
            jumlahJawab = 0;
            passwordd.reset();
            resPass = 1;
            kodeMenu = 18;
          }
        }
      }
      if(c == '*') {
        resPass = 1;
        kodeMenu = 18;
        jumlahPass = 0;
        jumlahJawab = 0;
        statusU = 1;
        passworda.reset(); passwordb.reset(); passwordc.reset(); passwordd.reset(); passworde.reset();
      }
    }

    if(kodeMenu == 2) menuLokerKosong(kodeMenu);
    if(kodeMenu == 3) menuLokerKosong(kodeMenu);
    if(kodeMenu == 4) menuLokerKosong(kodeMenu);
    if(kodeMenu == 5) menuLokerKosong(kodeMenu);
    if(kodeMenu == 10) menuLokerIsi(kodeMenu);
    if(kodeMenu == 11) menuLokerIsi(kodeMenu);
    if(kodeMenu == 12) menuLokerIsi(kodeMenu);
    if(kodeMenu == 13) menuLokerIsi(kodeMenu);

    if(kodeMenu == 18) {
      if(resPass == 1) {
        lcd.setCursor(0, 1);
        lcd.print("                ");
        resPass = 0;
      }
        if(jumlahPass > 16) {
          jumlahPass = 0;
        }
        if(jumlahJawab == 3) {
          menu(21);
          resPass = 1;
          jumlahJawab = 0;
        }
        char c = keypad.getKey();
        if(c) {
          if(c == '*') {
            if(jumlahPass == 0) kodeMenu = 1;
            passworda.reset(); passwordb.reset(); passwordc.reset(); passwordd.reset(); passworde.reset();
            jumlahPass = 0;
            lcd.setCursor(0, 1);
            lcd.print("                ");
          } else {
            if(c == '#') {
              if(statusU == 1) {
                if((passworda.evaluate()) == true) {
                  digitalWrite(pintuA, HIGH);
                  digitalWrite(buzzerPin, HIGH);
                  delay(100);
                  digitalWrite(buzzerPin, LOW);
                  digitalWrite(casA, LOW);
                  kodeMenu = 19;
                  status1 = 2;
                  loker1 = 0;
                  jumlah1 = 0;
                  waktu1 = -1;
                } else if((passwordb.evaluate()) == true) {
                  digitalWrite(pintuB, HIGH);
                  digitalWrite(buzzerPin, HIGH);
                  delay(100);
                  digitalWrite(buzzerPin, LOW);
                  digitalWrite(casB, LOW);
                  kodeMenu = 19;
                  status2 = 3;
                  loker2 = 0;
                  jumlah2 = 0;
                  waktu2 = -1;
                } else if((passwordc.evaluate()) == true) {
                  digitalWrite(pintuC, HIGH);
                  digitalWrite(buzzerPin, HIGH);
                  delay(100);
                  digitalWrite(buzzerPin, LOW);
                  digitalWrite(casC, LOW);
                  kodeMenu = 19;
                  status3 = 3;
                  loker3 = 0;
                  jumlah3 = 0;
                  waktu3 = -1;
                } else if((passwordd.evaluate()) == true) {
                  digitalWrite(pintuD, HIGH);
                  digitalWrite(buzzerPin, HIGH);
                  delay(100);
                  digitalWrite(buzzerPin, LOW);
                  digitalWrite(casD, LOW);
                  kodeMenu = 19;
                  status4 = 3;
                  loker4 = 0;
                  jumlah4 = 0;
                  waktu4 = -1;
                } else if((passworde.evaluate()) == true) {
                  digitalWrite(pintuE, HIGH);
                  digitalWrite(buzzerPin, HIGH);
                  delay(100);
                  digitalWrite(buzzerPin, LOW);
                  kodeMenu = 20;
                  statusU = 3;
                  loker4 = 0;
                } else {
                  jumlahJawab++;
                  digitalWrite(buzzerPin, HIGH);
                  delay(100);
                  digitalWrite(buzzerPin, LOW);
                  passworda.reset(); passwordb.reset(); passwordc.reset(); passwordd.reset(); passworde.reset();
                  jumlahPass = 0;
                  lcd.setCursor(0, 1);
                  lcd.print("                ");
                }
              } else {
                if(status1 == 1) {
                  if((passworda.evaluate()) == true) {
                    digitalWrite(pintuA, HIGH);
                    digitalWrite(buzzerPin, HIGH);
                    delay(100);
                    digitalWrite(buzzerPin, LOW);
                    kodeMenu = 19;
                    status1 = 2;
                    jumlah1 = 0;
                    loker1 = 0;
                  } else {
                    jumlahJawab++;
                    digitalWrite(buzzerPin, HIGH);
                  delay(100);
                  digitalWrite(buzzerPin, LOW);
                    passworda.reset();
                    jumlahPass = 0;
                    lcd.setCursor(0, 1);
                    lcd.print("                ");
                  }
                }
                if(status2 == 1) {
                  if((passwordb.evaluate()) == true) {
                    digitalWrite(pintuB, HIGH);
                    digitalWrite(buzzerPin, HIGH);
                    delay(100);
                    digitalWrite(buzzerPin, LOW);
                    kodeMenu = 19;
                    status2 = 2;
                    loker2 = 0;
                    jumlah2 = 0;
                  } else {
                    jumlahJawab++;
                    digitalWrite(buzzerPin, HIGH);
                  delay(100);
                  digitalWrite(buzzerPin, LOW);
                    passwordb.reset();
                    jumlahPass = 0;
                    lcd.setCursor(0, 1);
                    lcd.print("                ");
                  }
                }
                if(status3 == 1) {
                  if((passwordc.evaluate()) == true) {
                    digitalWrite(pintuC, HIGH);
                    digitalWrite(buzzerPin, HIGH);
                    delay(100);
                    digitalWrite(buzzerPin, LOW);
                    kodeMenu = 19;
                    status3 = 2;
                    loker3 = 0;
                    jumlah3 = 0;
                  } else {
                    jumlahJawab++;
                    digitalWrite(buzzerPin, HIGH);
                  delay(100);
                  digitalWrite(buzzerPin, LOW);
                    passwordc.reset();
                    jumlahPass = 0;
                    lcd.setCursor(0, 1);
                    lcd.print("                ");
                  }
                }
                if(status4 == 1) {
                  if((passwordd.evaluate()) == true) {
                    digitalWrite(pintuD, HIGH);
                    digitalWrite(buzzerPin, HIGH);
                    delay(100);
                    digitalWrite(buzzerPin, LOW);
                    kodeMenu = 19;
                    status4 = 2;
                    loker4 = 0;
                    jumlah4 = 0;
                  } else {
                    jumlahJawab++;
                    digitalWrite(buzzerPin, HIGH);
                  delay(100);
                  digitalWrite(buzzerPin, LOW);
                    passwordd.reset();
                    jumlahPass = 0;
                    lcd.setCursor(0, 1);
                    lcd.print("                ");
                  }
                }
              }
            }
            if(statusU == 1) {
              if(c == '1') {
                passworda.append('1');
                passwordb.append('1');
                passwordc.append('1');
                passwordd.append('1');
                passworde.append('1');
              }
              if(c == '2') {
                passworda.append('2');
                passwordb.append('2');
                passwordc.append('2');
                passwordd.append('2');
                passworde.append('2');
              }
              if(c == '3') {
                passworda.append('3');
                passwordb.append('3');
                passwordc.append('3');
                passwordd.append('3');
                passworde.append('3');
              }
              if(c == '4') {
                passworda.append('4');
                passwordb.append('4');
                passwordc.append('4');
                passwordd.append('4');
                passworde.append('4');
              }
              if(c == '5') {
                passworda.append('5');
                passwordb.append('5');
                passwordc.append('5');
                passwordd.append('5');
                passworde.append('5');
              }
              if(c == '6') {
                passworda.append('6');
                passwordb.append('6');
                passwordc.append('6');
                passwordd.append('6');
                passworde.append('6');
              }
              if(c == '7') {
                passworda.append('7');
                passwordb.append('7');
                passwordc.append('7');
                passwordd.append('7');
                passworde.append('7');
              }
              if(c == '8') {
                passworda.append('8');
                passwordb.append('8');
                passwordc.append('8');
                passwordd.append('8');
                passworde.append('8');
              }
              if(c == '9') {
                passworda.append('9');
                passwordb.append('9');
                passwordc.append('9');
                passwordd.append('9');
                passworde.append('9');
              }
              if(c == '0') {
                passworda.append('0');
                passwordb.append('0');
                passwordc.append('0');
                passwordd.append('0');
                passworde.append('0');
              }
            } else {
              if(status1 == 1) {
                if(c == '1') passworda.append('1');
                if(c == '2') passworda.append('2');
                if(c == '3') passworda.append('3');
                if(c == '4') passworda.append('4');
                if(c == '5') passworda.append('5');
                if(c == '6') passworda.append('6');
                if(c == '7') passworda.append('7');
                if(c == '8') passworda.append('8');
                if(c == '9') passworda.append('9');
                if(c == '0') passworda.append('0');
              }
              if(status2 == 1) {
                if(c == '1') passwordb.append('1');
                if(c == '2') passwordb.append('2');
                if(c == '3') passwordb.append('3');
                if(c == '4') passwordb.append('4');
                if(c == '5') passwordb.append('5');
                if(c == '6') passwordb.append('6');
                if(c == '7') passwordb.append('7');
                if(c == '8') passwordb.append('8');
                if(c == '9') passwordb.append('9');
                if(c == '0') passwordb.append('0');
              }
              if(status3 == 1) {
                if(c == '1') passwordc.append('1');
                if(c == '2') passwordc.append('2');
                if(c == '3') passwordc.append('3');
                if(c == '4') passwordc.append('4');
                if(c == '5') passwordc.append('5');
                if(c == '6') passwordc.append('6');
                if(c == '7') passwordc.append('7');
                if(c == '8') passwordc.append('8');
                if(c == '9') passwordc.append('9');
                if(c == '0') passwordc.append('0');
              }
              if(status4 == 1) {
                if(c == '1') passwordd.append('1');
                if(c == '2') passwordd.append('2');
                if(c == '3') passwordd.append('3');
                if(c == '4') passwordd.append('4');
                if(c == '5') passwordd.append('5');
                if(c == '6') passwordd.append('6');
                if(c == '7') passwordd.append('7');
                if(c == '8') passwordd.append('8');
                if(c == '9') passwordd.append('9');
                if(c == '0') passwordd.append('0');
              }
            }
            if((c != 'A')&&(c != 'B')&&(c != 'C')&&(c != 'D')&&(c != '#')&&(c != '*')) {
              lcd.setCursor(jumlahPass, 1);
              lcd.print('*');
              jumlahPass++;
            }
          }
        }
    }

    if(kodeMenu == 19) {
        char c = keypad.getKey();
        if(c == '#') {
          if(status1 == 2) {
            digitalWrite(pintuA, LOW);
            status1 = 0;
            kodeMenu = 1;
          }
          if(status2 == 2) {
            digitalWrite(pintuB, LOW);
            status2 = 0;
            kodeMenu = 1;
        }
        if(status3 == 2) {
          digitalWrite(pintuC, LOW);
          status3 = 0;
          kodeMenu = 1;
        }
        if(status4 == 2) {
          digitalWrite(pintuD, LOW);
          status4 = 0;
          kodeMenu = 1;
        }
      }
    }
    
    if(kodeMenu == 20) {
      char c = keypad.getKey();
      if(c == '#') {
        if(statusU == 3) {
          digitalWrite(pintuE, LOW);
          statusU = 0;
          kodeMenu = 1;
        }      
      }
    }
    delay(1);
  }
  if(ok == 0) {
  if(waktu1 > 0) waktu1 = waktu1 - 1;
  if(waktu2 > 0) waktu2 = waktu2 - 1;
  if(waktu3 > 0) waktu3 = waktu3 - 1;
  if(waktu4 > 0) waktu4 = waktu4 - 1;
  }
}

void menu(int kode) {
  switch(kode) {
    case 0:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Smart Charging");
      lcd.setCursor(0, 1);
      lcd.print("Coin Acceptor");
      break;

    case 1:
      lcd.setCursor(0, 0);
      lcd.print("Batt : ");
      lcd.print(volt);
      lcd.print(" %");
      lcd.print("    ");
      lcd.setCursor(0, 1);
      lcd.print("A="); lcd.print(loker1);
      lcd.print(" B="); lcd.print(loker2);
      lcd.print(" C="); lcd.print(loker3);
      lcd.print(" D="); lcd.print(loker4);
      break;

    case 2:
      lcd.setCursor(0, 0);
      lcd.print("Loker A         ");
      lcd.setCursor(0, 1);
      lcd.print("Masukan Koin    ");
      break;
    
    case 3:
      lcd.setCursor(0, 0);
      lcd.print("Loker B         ");
      lcd.setCursor(0, 1);
      lcd.print("Masukan Koin    ");
      break;

    case 4:
      lcd.setCursor(0, 0);
      lcd.print("Loker C         ");
      lcd.setCursor(0, 1);
      lcd.print("Masukan Koin    ");
      break;

    case 5:
      lcd.setCursor(0, 0);
      lcd.print("Loker D         ");
      lcd.setCursor(0, 1);
      lcd.print("Masukan Koin    ");
      break;

    case 6:
      lcd.setCursor(0, 0);
      lcd.print("Jumlah Koin     ");
      lcd.setCursor(0, 1);
      lcd.print("Rp. ");
      lcd.print(jumlah1);
      lcd.print("        ");
      break; 

    case 7:
      lcd.setCursor(0, 0);
      lcd.print("Jumlah Koin");
      lcd.setCursor(0, 1);
      lcd.print("Rp. ");
      lcd.print(jumlah2);
      lcd.print("        ");
      break; 

    case 8:
      lcd.setCursor(0, 0);
      lcd.print("Jumlah Koin");
      lcd.setCursor(0, 1);
      lcd.print("Rp. ");
      lcd.print(jumlah3);
      lcd.print("        ");
      break;  

    case 9:
      lcd.setCursor(0, 0);
      lcd.print("Jumlah Koin");
      lcd.setCursor(0, 1);
      lcd.print("Rp. ");
      lcd.print(jumlah4);
      lcd.print("        ");
      break;
    
    case 10:
      lcd.setCursor(0, 0);
      lcd.print("Loker A Terisi..");
      lcd.setCursor(0, 1);
      lcd.print("Waktu : ");
      lcd.print(waktu1);
      lcd.print("      ");
      break;
    
    case 11:
      lcd.setCursor(0, 0);
      lcd.print("Loker B Terisi..");
      lcd.setCursor(0, 1);
      lcd.print("Waktu : ");
      lcd.print(waktu2);
      lcd.print("      ");
      break;
    
    case 12:
      lcd.setCursor(0, 0);
      lcd.print("Loker C Terisi..");
      lcd.setCursor(0, 1);
      lcd.print("Waktu : ");
      lcd.print(waktu3);
      lcd.print("      ");
      break;

    case 13:
      lcd.setCursor(0, 0);
      lcd.print("Loker D Terisi..");
      lcd.setCursor(0, 1);
      lcd.print("Waktu : ");
      lcd.print(waktu4);
      lcd.print("      ");
      break;

    case 14:
      lcd.setCursor(0, 0);
      lcd.print("Loker A         ");
      lcd.setCursor(0, 1);
      lcd.print("Selesai         ");
      break;

    case 15:
      lcd.setCursor(0, 0);
      lcd.print("Loker B         ");
      lcd.setCursor(0, 1);
      lcd.print("Selesai         ");
      break;

    case 16:
      lcd.setCursor(0, 0);
      lcd.print("Loker C         ");
      lcd.setCursor(0, 1);
      lcd.print("Selesai         ");
      break;

    case 17:
      lcd.setCursor(0, 0);
      lcd.print("Loker D         ");
      lcd.setCursor(0, 1);
      lcd.print("Selesai         ");
      break;

    case 18:
      lcd.setCursor(0, 0);
      lcd.print("Password :      ");
      break;

    case 19:
      lcd.setCursor(0, 0);
      lcd.print("Terima Kasih    ");
      lcd.setCursor(0, 1);
      lcd.print("                ");
      break;

    case 20:
      lcd.setCursor(0, 0);
      lcd.print("Loker Koin      ");
      lcd.setCursor(0, 1);
      lcd.print("Terbuka         ");
      break;
    
    case 21:
      lcd.setCursor(0,0);
      lcd.print("Kesalahan       ");
      lcd.setCursor(0,1);
      lcd.print("Melampaui batas ");
      digitalWrite(telegramPin, LOW);
      digitalWrite(buzzerPin, HIGH);
      delay(1000);
      digitalWrite(buzzerPin, LOW);
      delay(4000);
      digitalWrite(telegramPin, HIGH);
      break;

    case 22:
      lcd.setCursor(0, 0);
      lcd.print("Peringatan!    ");
      lcd.setCursor(0, 1);
      lcd.print("Low Battery    ");
      digitalWrite(buzzerPin, HIGH);
      delay(100);
      digitalWrite(buzzerPin, LOW);
      delay(100);
      digitalWrite(buzzerPin, HIGH);
      delay(100);
      digitalWrite(buzzerPin, LOW);
      delay(100);
      digitalWrite(buzzerPin, HIGH);
      delay(100);
      digitalWrite(buzzerPin, LOW);
      delay(100);
  }
}

void menuLokerKosong(int kode) {
  char tombolKeypad = cariKeypad(kode);
    char c = keypad.getKey();
    if(c == tombolKeypad) {
      if(ada == 1) {
        ok = 1;
        randomSeed(analogRead(0));
        int randomNumber = random(0,20);
        char* randomPassword = passwdrandom(randomNumber);
        if(kode == 2) passworda.set(randomPassword);
        if(kode == 3) passwordb.set(randomPassword);
        if(kode == 4) passwordc.set(randomPassword);
        if(kode == 5) passwordd.set(randomPassword);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Password Baru:");
        lcd.setCursor(0, 1);
        lcd.print(randomPassword);
        delay(5000);
        lokerTutup(kode);
        casHidup(kode);
        ok = 0;
        ada = 0;
      }
      kodeMenu = 1;
    }

    int coin = digitalRead(coinPin);
    if(coin == 0) {
      ada = 1;
      lokerBuka(kode);
      tambahKoin(kode);
      menu(kode+4);
      delay(1500);
      menu(kode);
    }
}

void menuLokerIsi(int kode) {
  char tombolKeypad = cariKeypad(kode-8);
    char c = keypad.getKey();
    if(c == tombolKeypad) {
      lcd.clear();
      kodeMenu = 1;
    }
    int coin = digitalRead(coinPin);
    if(coin == 0) {
      tambahKoin(kode-8);
      menu(kode-4);
      delay(1500);
      menu(kode);
    }
  if((waktu1 < 0)&&(kodeMenu == 10)) kodeMenu = 1;
  if((waktu2 < 0)&&(kodeMenu == 11)) kodeMenu = 1;
    if((waktu3 < 0)&&(kodeMenu == 12)) kodeMenu = 1;
    if((waktu4 < 0)&&(kodeMenu == 13)) kodeMenu = 1;
}

char cariKeypad(int kode) {
  if(kode == 2) return 'A';
  if(kode == 3) return 'B';
  if(kode == 4) return 'C';
  if(kode == 5) return 'D';
}

void tambahKoin(int kode) {
  if(kode == 2) {
    loker1 = 1;
    waktu1 = waktu1 + tambahDetik;
    jumlah1 = jumlah1 + 1000;
  }
  if(kode == 3) {
    loker2 = 1;
    waktu2 = waktu2 + tambahDetik;
    jumlah2 = jumlah2 + 1000;
  }
  if(kode == 4) {
    loker3 = 1;
    waktu3 = waktu3 + tambahDetik;
    jumlah3 = jumlah3 + 1000;
  }
  if(kode == 5) {
    loker4 = 1;
    waktu4 = waktu4 + tambahDetik;
    jumlah4 = jumlah4 + 1000;
  }
}

void lokerBuka(int kode) {
  if(kode == 2) digitalWrite(pintuA, HIGH);
  if(kode == 3) digitalWrite(pintuB, HIGH);
  if(kode == 4) digitalWrite(pintuC, HIGH);
  if(kode == 5) digitalWrite(pintuD, HIGH);
}

void lokerTutup(int kode) {
  if(kode == 2) digitalWrite(pintuA, LOW);
  if(kode == 3) digitalWrite(pintuB, LOW);
  if(kode == 4) digitalWrite(pintuC, LOW);
  if(kode == 5) digitalWrite(pintuD, LOW);
}

void casHidup(int kode) {
  if(kode == 2) digitalWrite(casA, HIGH);
  if(kode == 3) digitalWrite(casB, HIGH);
  if(kode == 4) digitalWrite(casC, HIGH);
  if(kode == 5) digitalWrite(casD, HIGH);
}

void matiCas() {
  if(waktu1 == 0) {
    status1 = 1;
    waktu1 = -1;
    jumlah1 = 0;
    digitalWrite(casA, LOW);
    menu(14);
    resPass = 1;
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
    delay(900);
    menu(kodeMenu);
  }
  if(waktu2 == 0) {
    status2 = 1;
    waktu2 = -1;
    jumlah2 = 0;
    digitalWrite(casB, LOW);
    menu(15);
    resPass = 1;
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
    delay(900);
    menu(kodeMenu);
  }
  if(waktu3 == 0) {
    status3 = 1;
    waktu3 = -1;
    jumlah3 = 0;
    digitalWrite(casC, LOW);
    menu(16);
    resPass = 1;
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
    delay(900);
    menu(kodeMenu);
  }
  if(waktu4 == 0) {
    status4 = 1;
    waktu4 = -1;
    jumlah4 = 0;
    digitalWrite(casD, LOW);
    menu(17);
    resPass = 1;
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
    delay(900);
    menu(kodeMenu);
  }
}

char* passwdrandom(int randomPassword) {
  if(randomPassword == 0) return "628";
  if(randomPassword == 1) return "961";
  if(randomPassword == 2) return "364";
  if(randomPassword == 3) return "986";
  if(randomPassword == 4) return "990";
  if(randomPassword == 5) return "236";
  if(randomPassword == 6) return "381";
  if(randomPassword == 7) return "911";
  if(randomPassword == 8) return "587";
  if(randomPassword == 9) return "149";
  if(randomPassword == 10) return "740";
  if(randomPassword == 11) return "489";
  if(randomPassword == 12) return "216";
  if(randomPassword == 13) return "745";
  if(randomPassword == 14) return "686";
  if(randomPassword == 15) return "704";
  if(randomPassword == 16) return "757";
  if(randomPassword == 17) return "557";
  if(randomPassword == 18) return "321";
  if(randomPassword == 19) return "722";
  if(randomPassword == 20) return "279";
}