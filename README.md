**One More Flip**
=========

An arduino game designed on a 8x8 matrix.
___

Initially you have 32 leds on, and 32 off. The goal is to light up as many leds as posible, by fliping a line, or a column. Flip means to invert the leds of an entire line/column.

E.g. 

![flipcolumn](https://user-images.githubusercontent.com/37237590/50056682-08f4d380-0168-11e9-9133-24fa6410bb8d.png)
![fliprow](https://user-images.githubusercontent.com/37237590/50056683-0c885a80-0168-11e9-8f6a-d807b4d61230.png)

**Game Configuration**
_____

*   Arduino Uno
*   2 Breadboards
    * 8x8 Matrix 
    * Matrix Driver 
    * 16x2 LCD
    * Pullup Reset Botton
    * Resistances, Capacitors and Cables
    * Joystick

![img_20181216_195109](https://user-images.githubusercontent.com/37237590/50057167-49a41b00-016f-11e9-9e8d-5d51ea6734fe.jpg)

First of all, you chose the difficulty, by pressing the Reset Button. When you are ready, you press start by the swich of the joystick. You can press the Reset Button anytime while playing to restart a new game.

![img_20181216_195141](https://user-images.githubusercontent.com/37237590/50057175-5de81800-016f-11e9-833d-2e5807598285.jpg)

You play with a joystick:
* If you want to chose a Row, you move it on the Oy axis
* If you want to chose a Column, you move it on the Ox axis
* When you're ready to flip, click on the switch button of the joystick

The LCD will wellcome you and while playing it will tell you the item selected to flip.

![img_20181216_195214](https://user-images.githubusercontent.com/37237590/50057184-748e6f00-016f-11e9-9299-cc01c4d0b16f.jpg)

Eventually, you will see your score. It's a percentage of how much leds you've just lighted up.

![img_20181216_194924](https://user-images.githubusercontent.com/37237590/50057191-83752180-016f-11e9-93f1-9ef233ce3526.jpg)

Have fun!


