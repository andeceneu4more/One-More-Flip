**One More Flip**
=========

An arduino game designed on a 8x8 matrix.
___

Initially you have 32 leds on, and 32 off. The goal is to light up as many leds as posible, by fliping a line, or a column. Flip means to invert the leds of an entire line/column.

E.g. 

![flipcolumn](https://user-images.githubusercontent.com/37237590/50056682-08f4d380-0168-11e9-9133-24fa6410bb8d.png)
![fliprow](https://user-images.githubusercontent.com/37237590/50056683-0c885a80-0168-11e9-8f6a-d807b4d61230.png)

***Game Configuration***
_____

*   Arduino Uno
*   2 Breadboards
    * 8x8 Matrix 
    * Matrix Driver 
    * 16x2 LCD
    * Pullup Reset Botton
    * Resistances, Capacitors and Cables
    * Joystick

First of all, you chose the difficulty, by pressing the Reset Button. When you are ready, you press start by the swich of the joystick.



You play with a joystick:
* If you want to chose a Row, you move it on the Oy axis
* If you want to chose a Column, you move it on the Ox axis
* When you're ready to flip, click on the switch button of the joystick

The LCD will wellcome you and while playing it will tell you the item selected to flip.



Eventually, you will see your score. It's a percentage of how much leds you've just lighted up.



Have fun!
