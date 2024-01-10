#include "functions.h"
/*
to start the program use the commande make then ./PROJECTC1
some librairies might be necessary in particular SDL and SDL-image to install run this command  :
sudo apt-get install libsdl2-dev
sudo apt-get install libsdl2-image-dev
*/
/*
How to use the program :
When the program start a window will appear it will represent each cell inside the hive in the hive there is 10 frames, and each frame have 
8100 cell, a frame has 2 sides so the window will show the sides of all the frames one by one so 4050 by 4050 cells.
if you want to look at the next side press RIGHT ARROW on the keyboard it will show the next side of the first frame and if you press again 
it will show the first side of the second frame.
Each collor represent different things honey color is a cell that contain honey, purple is a cell that contain jelly, white circle
is a cell that contain an egg,grey is a cell that contain nothing, green is a cell that is dirty, yellow is a cell that contain pollen,
black is a cell that is not yet made.
to go to the next day you need to press TAB on the keyboard ,while being on the window that opened, it will simulate the next day.
You must watch the terminal because some information are displayed there like the number of bee, the number of bee for each role, the number 
of honey, of jelly and of pollen
You must remember that you must press the keys when the actual window is the cells otherwise nothing will happend*/

int main(){
  HIVE* HIVE1=createHIVE(1,6000);
    affichage(HIVE1);

}