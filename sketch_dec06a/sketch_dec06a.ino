#include "LedControl.h"
#include <LiquidCrystal.h>
LedControl lc = LedControl(12, 11, 10, 1);
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
#define intPin 9
#define joyX A0
#define joyY A1
#define switchPin 8
#define resetPin 13
int posX, posY, remTurns = 15, difficulty = 0;
bool matrix[8][8] = {0};
const int refreshRate = 500;
int state = 2;
int lastSwitchTime, lastResetTime, lastPrintedTime;
boolean switchValue, prevSwitchValue = true;
boolean resetValue, prevResetValue = true;
boolean lastReset = false, lastSwitch = true;
boolean selected = false;
void printNow()
{
    lc.clearDisplay(0);
    int i, j;
    for (i = 0; i < 8; i++)
      for (j = 0; j < 8; j++)
      {
          lc.setLed(0, i, j, matrix[i][j]);
      }
    lcd.clear();
    if (selected == false)
    {
        lcd.setCursor(5, 0);
        lcd.print("Row ");
        lcd.print(posX + 1);
        Serial.print("Row ");
        Serial.println(posX + 1);
    }
    else
    {
        lcd.setCursor(4, 0);
        lcd.print("Column ");
        lcd.print(posY + 1);
        Serial.print("Column ");
        Serial.println(posY + 1);
    }
    if (difficulty != 3)
    {
    	lcd.setCursor(2, 1);
    	lcd.print(remTurns);
    	Serial.print(remTurns);
    	lcd.print(" remaining");
    	Serial.println(" remaining");
    }
    else
    {
    	lcd.setCursor(4, 1);
    	lcd.print("Endless");
    	Serial.print("Endless");
    }
}
void invertRow(int i)
{
    int j;
      for (j = 0; j < 8; j++)
      {
          matrix[i][j] = !matrix[i][j];
      }
}
void invertColumn(int j)
{
    int i;
      for (i = 0; i < 8; i++)
      {
          matrix[i][j] = !matrix[i][j];
      }
}
void initiate()
{
    posX = 0;
    posY = 0;
    lc.clearDisplay(0);
    int i, j;
    int randRow, randColumn, flips;
    if (difficulty == 3)
	{
		for (i = 0; i < 8; i++)
	    	for (j = 0; j < 8; j++)
		    {
		        matrix[i][j] = false;
		    }
		for (i = 0; i < 32; )
	    {
	        randRow = random(0, 8);
	        randColumn = random(0, 8);
	        if (matrix[randRow][randColumn] == false)
	        {
	            matrix[randRow][randColumn] = true;
	            i++;
	        }
	    }
	}
	else
	{
		for (i = 0; i < 8; i++)
	    	for (j = 0; j < 8; j++)
		    {
		        matrix[i][j] = true;
		    }
		flips = difficulty * 10;
		for (i = 0; i < flips / 2; i++)
		{
			randRow = random(0, 8);
			invertRow(randRow);
		}
		for (; i < flips; i++)
		{
			randColumn = random(0, 8);
			invertColumn(randColumn);
		}
	}
}
bool checkComplete()
{
	int i, j;
	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)
			if (matrix[i][j] == false)
				return false;
	return true;
}
void printScore()
{
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("Congrats");
    Serial.print("Congrats");
    lcd.setCursor(1, 1);
    lcd.print("Your score");
    Serial.print("Your score");
    
    int count = 0, i, j;
    for (i = 0; i < 8; i++)
      for (j = 0; j < 8; j++)
      {
          if (matrix[i][j] == true)
              count++; 
      }
    float score = (count * 100.0) / 64;
    lcd.setCursor(12, 1);
    lcd.print(score, 1);
    Serial.println(score, 1);
}
void setup()
{
    lc.shutdown(0, false); 
    lc.setIntensity(0, 2); 
    lc.clearDisplay(0);

    lcd.begin(16, 2);
    lcd.clear();
    analogWrite(intPin, 120); // 0 -> 180
    
    pinMode(switchPin, INPUT_PULLUP);
    pinMode(resetPin, INPUT_PULLUP);
    Serial.begin(9600);

    lcd.setCursor(3, 0);
    lcd.print("Welcome to");
    Serial.println("Welcome to");
    lcd.setCursor(1, 1);
    lcd.print("One More Flip");
    Serial.println("One More Flip");

    delay(3000);
    lcd.clear();
}
boolean movedX = false, movedY = false;
void play()
{
  int valX = analogRead(joyX);
  int valY = analogRead(joyY);

  if (valY < 400)
  {
    if (movedY == false)
    {
      posY++;
      movedY = true;
      selected = true;
    }
  }
  else
  {
    if (valY > 600)
    {
      if (movedY == false)
      {
        posY--;
        movedY = true;
        selected = true;
      }
    }
    else 
      movedY = false;
  }
  
    if (valX < 400)
    {
      if (movedX == false)
      {
        posX--;
        movedX = true;
        selected = false;
      }
    }
    else
    {
      if (valX > 600)
      {
        if (movedX == false)
        {
          posX++;
          movedX = true;
          selected = false;
        }
      }
      else 
        movedX = false;
    }
  
  if (posY == 8) 
    posY = 0;
  if (posY == -1) 
    posY = 7;
  
  if (posX == 8) 
    posX = 0;
  if (posX == -1) 
    posX = 7;

  Serial.println(remTurns);
  
  switchValue = digitalRead(switchPin);
  if (switchValue != lastSwitch)
  {
      lastSwitchTime = millis();
  }
  if (millis() - lastSwitchTime > 4)
  {
      if (switchValue != prevSwitchValue)
      {
          prevSwitchValue = switchValue;
          if (switchValue == LOW)
          {
              if (selected == false)
              {
                  invertRow(posX);
              }
              else
              {
                  invertColumn(posY);
              }
              if (difficulty < 3)
              {
              	remTurns--;
              	if (remTurns == 0)
              	{
                  	printScore();
                  	state = 1; // goto final
              	}
              }
              else
              {
              	if (checkComplete() == true)
              	{
              		printScore();
                  	state = 1; // goto final
              	}
              }
          }
      }
  }
  lastSwitch = switchValue;

  resetValue = digitalRead(resetPin);
  if (resetValue != lastReset)
  {
      lastResetTime = millis();
  }
  if (millis() - lastResetTime > 4)
  {
      if (resetValue != prevResetValue)
      {
          prevResetValue = resetValue;
          if (resetValue == HIGH)
          {
              initiate();
              state = 2;
              lcd.clear();
          }
      }
  }
  lastReset = resetValue;
  
  if (state == 0)
  {
    if (millis() - lastPrintedTime > refreshRate)
    {
        lastPrintedTime = millis();
        printNow();
    }
  }
}
void final()
{
  resetValue = digitalRead(resetPin);
  if (resetValue != lastReset)
  {
      lastResetTime = millis();
  }
  if (millis() - lastResetTime > 4)
  {
      if (resetValue != prevResetValue)
      {
          prevResetValue = resetValue;
          if (resetValue == HIGH)
          {
              initiate();
              lcd.clear();
              state = 2;
          }
      }
  }
  lastReset = resetValue;
}
void chooseDiff()
{
    lcd.setCursor(3, 0);
    lcd.print("Choose dif.");
    if (difficulty == 0)
    {
        lcd.setCursor(6, 1);
        lcd.print("Hard");
        Serial.println("Hard");
    }
    else
      if (difficulty == 1)
      {
          lcd.setCursor(5, 1);
          lcd.print("Medium");
          Serial.println("Medium");
      }
      else
      	if (difficulty == 2)
		{
	        lcd.setCursor(6, 1);
	        lcd.print("Easy");
	        Serial.println("Easy");
	    }
	    else
	    {
	    	lcd.setCursor(5, 1);
	        lcd.print("Endless");
	        Serial.println("Endless");
	    }
    resetValue = digitalRead(resetPin);
    if (resetValue != lastReset)
    {
        lastResetTime = millis();
    }
    if (millis() - lastResetTime > 4)
    {
        if (resetValue != prevResetValue)
        {
            prevResetValue = resetValue;
            if (resetValue == HIGH)
            {
                difficulty = (difficulty + 1) % 4;
                if (difficulty < 3)
                	remTurns = 15 * (difficulty + 1);
                lcd.clear();
            }
        }
    }
    lastReset = resetValue;

    switchValue = digitalRead(switchPin);
    if (switchValue != lastSwitch)
    {
        lastSwitchTime = millis();
    }
    if (millis() - lastSwitchTime > 4)
    {
        if (switchValue != prevSwitchValue)
        {
            prevSwitchValue = switchValue;
            if (switchValue == LOW)
            {
                state = 0;
                initiate();
            }
        }
    }
    lastSwitch = switchValue;
}
void loop()
{
    switch(state)
    {
      case 0:
        play();
        //Serial.println("play");
        break;
      case 1:
        final();
        //Serial.println("final");
        break;
      case 2:
        chooseDiff();
        //Serial.println("ChooseDiff");
        break;
    }
}
