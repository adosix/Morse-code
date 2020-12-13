#include <LiquidCrystal.h>
//LCD display
const int pin_RS = 8;
const int pin_EN = 9;
const int pin_d4 = 4;
const int pin_d5 = 5;
const int pin_d6 = 6;
const int pin_d7 = 7;
const int pin_BL = 10;
LiquidCrystal lcd( pin_RS,  pin_EN,  pin_d4,  pin_d5,  pin_d6,  pin_d7);

//led and buzzer
int buzzer = 13;

int red_light_pin= 3;
int green_light_pin = 11;
int blue_light_pin = 12;

String ch = "";
String translated ="";
char cha[2];
int pressed = 0;
int silence = 0;


//morse code
String morsecode[] = {
  ".-",     // "a" 
  "-...",   // "b" -... --- -.. -.--
  "-.-.",   // "c"
  "-..",    // "d"
  ".",      // "e"
  "..-.",   // "f"
  "--.",    // "g"
  "....",   // "h"
  "..",     // "i"
  ".---",   // "j"
  "-.-",    // "k"
  ".-..",   // "l"
  "--",     // "m"
  "-.",     // "n"
  "---",    // "o"
  ".--.",   // "p"
  "--.-",   // "q"
  ".-.",    // "r"
  "...",    // "s"
  "-",      // "t"
  "..-",    // "u"
  "...-",   // "v"
  ".--",    // "w"
  "-..-",   // "x"
  "-.--",   // "y"
  "--..",   // "z"
  " "       // " "
};
String alpha [] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p",
                   "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", " "
                  };

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);
}
void loop() {
  int x;
  silence++;
  x = analogRead (0);

  if (x < 60) {
    pressed++;
    silence = 0;    
    RGB_color(0, 0, 255);
    tone(buzzer, 1000, 10);

    lcd.setCursor(0, 0);
  }
  else if (x < 200) {
    //lcd.print ("Up    ");
  }
  else if (x < 400) {
    //lcd.print ("Down  ");
  }
  else if (x < 600) {
    //lcd.print ("Left  ");
  }
  else if (x < 800) {
    //lcd.print ("Select");
  }
  else if (pressed != 0) {
    lcd.setCursor(0, 1);
    lcd.print(pressed);
    if(ch == ""){
      lcd.setCursor(10, 1);
      lcd.print("      ");
    }
    lcd.setCursor(10, 1);
    if (pressed < 400) {
      ch = ch + ".";
      lcd.print(ch);
    }
    else {
      ch = ch + "-";
      lcd.print(ch);
    }
    pressed = 0;
    digitalWrite(12, LOW);
  }

  if (silence > 1000 && (silence % 10000 == 0)) {
    if (ch != "") {

      lcd.setCursor(10, 1);
      lcd.print("      ");
      lcd.setCursor(10, 1);
      ch = findMorse(ch);
      if(ch == "fail"){
        tone(buzzer, 120,200);
        RGB_color(255, 0, 0);
        lcd.print("failed");
      }
      else{
        tone(buzzer, 400, 100);
        delay(100);
        tone(buzzer, 900, 70);
        RGB_color(0, 255, 0);
        lcd.print(ch);
        translated.concat(ch);
        lcd.setCursor(0,0);
        lcd.print(translated);
      }
      ch = "";
    }
  }
}

String findMorse(String m_code) {
  int v = 26;
  for (int x = 0; x < 26; x++){
    if (morsecode[x].equals(m_code))
      return alpha[x];
  }
  return "fail";
}

void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
{
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}
