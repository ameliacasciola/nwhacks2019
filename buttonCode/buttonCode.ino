
#include <Wire.h>
#include <rgb_lcd.h>
#include <math.h>

/*
 * Two player game:
 * First player to press their button 100 times wins!
 * Displays exciting colours and keeps track of scores.
 */

rgb_lcd lcd;
int button1 = 3;
int button2 = 2;
volatile int count1 = 0;
volatile int count2 = 0;
volatile bool done = 0;
bool fn_done = 0;
bool just_won = 0;

void setup() {
    //using interrupts to track counter use
    attachInterrupt(digitalPinToInterrupt(button1),counter1, RISING);
    attachInterrupt(digitalPinToInterrupt(button2),counter2, RISING);
    pinMode(button1, INPUT);
    pinMode(button2, INPUT);

    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    
    delay(1000);

}

void loop() {
  //loop while game is playing
  if(!done) {
    if(just_won) {
      lcd.clear();
      just_won = 0;
      count1=0;
      count2=0;
    }
    lcd.setRGB(maxe(count1, count2)*2, 255 - maxe(count1, count2)*2.55, 0);  
    fn_done = 0;
    lcd.setCursor(0,1);
    lcd.print(count1);
    lcd.setCursor(14,1);
    lcd.print(count2);
  
    lcd.setCursor(0,0);
    lcd.print("P1");
    lcd.setCursor(14,0);
    lcd.print("P2");
  }
  else {
    //display finished message
    if(!fn_done) {
      lcd.clear();
      lcd.setCursor(0,0);
      if(count1>count2)
        lcd.print("P1 WON!");
      else if(count2>count1)
        lcd.print("P2 WON!");
      else
        lcd.print("IT'S A TIE!");
        
      lcd.setCursor(0,1);
      lcd.print("PRESS ANY BTN");
      fn_done = 1;
      just_won = 1;
  
      delay(1000);
      count1 = 0;
      count2 = 0;
    }
    else {
      //display fun winning colours
      lcd.setRGB(rand()*255,rand()*255,rand()*255);
      delay(200);
    }
     
  }
}

//interrupt functions to increase scores
void counter1() {
  count1++;
  if(fn_done) {
    done = 0;
  }
  if(count1>=100) {
    done = 1;
  }
}
void counter2() {
  count2++;
  if(fn_done) {
    done = 0;
  }
  if(count2>=100) {
    done = 1;
  }
}

//max function
int maxe(int one, int two) {
  return one > two? one : two;
}


