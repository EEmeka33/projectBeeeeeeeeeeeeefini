#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <string.h> 
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/*
to start the program use the commande make then ./PROJECTC1
some librairies might be necessary in particular SDL and SDL-image to install run this command  :
sudo apt-get install libsdl2-dev
sudo apt-get install libsdl2-image-dev
*/


typedef struct BEE BEE;
typedef struct HIVE HIVE;
typedef struct FRAME FRAME;
typedef struct OutsideBee OutsideBee;
typedef struct frameCELL frameCELL;


struct BEE {
  unsigned long int id;
  int health;
  int pollen;
  int honey;
  int jelly;
  int water;
  int age;
  char role[10];
  char roleDuJour[20]; // Role of the day
  char position[10];
  int frame; // Pointer to the frame the bee is currently on
  BEE* next;
};
//type 1 = QUEEN
//type 2 = BEE
//type 3 = BEE male
//
/*
J1 à J3 : Nettoyage de l’intérieur de la ruche. L'abeille ouvrière d'été s’occupe d'abord de la 
préparation des cellules pour les nouvelles pontes, le temps que ses glandes nourricières se développent
J3 à J13 : elle devient nourricière des jeunes larves avec la gelée royale et la bouillie 
larvaire qu’elle sécrète.
J5 à J20 : elle devient cirière avec un pic de production à J12. Ses glandes nourricières 
s'atrophient pendant que les glandes cirières se développent. Elle participe alors à l’agrandissement 
des rayons, au nettoyage.
J6 : elle réceptionne le nectar amené par les butineuses et le transforme en miel.
J12 à J25 : elle devient gardienne pour la protection contre les prédateurs (guêpes et frelon 
notamment) et les voleurs (abeilles étrangères, etc.).
J14 à J19 : elle devient ventileuse pour la régulation thermique de la ruche.
J16 : la jeune abeille procède à son 1er vol d’orientation autour de la ruche.
J20 à J40 : elle devient butineuse et parcourt la campagne dans un rayon de deux à 
cinq kilomètres afin d’approvisionner la ruche en nectar, miellat, pollen, propolis 
ou en eau. Après quoi, sa vie s’achève. En général, une ouvrière meurt pendant un 
dernier voyage de butinage, de portage d'eau (dévolu aux plus anciennes), ou 
pendant qu'elle dort.
*/

/*
Être nourrice, un travail à temps plein!
Lorsqu’elle est nourrice, l’abeille travaille sans relâche! Nourrir une larve peut 
prendre jusqu’à 20 secondes, et elle visitera jusqu’à 1300 alvéoles par jour!

En s’acquittant de ces tâches pour elle, les aides permettent à Sa Majesté de se 
concentrer sur son principal objectif: maintenir la colonie bien active en pondant jusqu’à 
2000 œufs par jour.
Quand une abeille devient-elle aide à la reine?
Une ouvrière peut être choisie aide à la reine n’importe quand entre son 7e et 12e jour de vie.

*/

struct HIVE {
  unsigned long int id;
  int water;
  int honey;
  int jelly;
  int pollen;
  int nbFrame;
  int nbBee; // Total bees inside and outside
  unsigned long int nbBeeProduced;
  int nbEgg;
  int nblarvae;
  int nbParasite;
  double temperature;
  bool hasQueen; // A hive has a queen or not
  int cleaner;
  int nurse;
  int waxer;
  int honeyMaker;
  int guard;
  int ventillator;
  int forager;
  int waterCarrier;
  int deathToday;
  BEE* queen;
  FRAME* frames[10]; // Array of pointers to frames
};

struct frameCELL {
  char type[10];//honey,jelly,egg,dirty,larvae,empty,broken,notmade,pollen,beebread
  int value;//can store 1000 of each type or 1 egg
  int age;
  frameCELL* next;
};


struct FRAME {
  int nbBee;
  int nbEgg;
  int honey;
  int jelly;
  int pollen;
  int HoneyCELL;
  int JellyCELL;
  int EggCELL;
  int DirtyCELL;
  int LarvaeCELL;
  int EmptyCELL;
  int BrokenCELL;
  int NotMadeCELL;
  int PollenCELL;
  int BeeBreadCELL;
  frameCELL* first;
};

struct OutsideBee {
  BEE* bee;
  struct OutsideBee* next; // Linked list of bees outside the hive
};

HIVE* createHIVE(int ihivenumber,int inbofstartingbee);
void increaseHoneyLvl(HIVE* hive, int amount);
void decreaseHoneyLvl(HIVE* hive, int amount);
void addBeeToHIVE( HIVE* hive, BEE* bee);
void removeBeeFromHIVE( HIVE* hive, BEE* bee);
BEE* createBEE(int type,HIVE* theHIVE,int nboftheframe);
FRAME* createFRAME(HIVE* theHIVE,int nboftheframe);
frameCELL* createframeCELL();
void assignRoleForToday(HIVE* therHive);
void queenLayEgg(HIVE* theHive,int eggNumber);
void putEggInCell(HIVE* theHive,int eggNumber);
void doRoleFor1Period(HIVE* theHive);
void doRoleForNight(HIVE* theHive);
void beesEat(HIVE* theHive);
void nextDay(HIVE* theHive);
void getOut(HIVE* theHive);
int affichage(HIVE* HIVE1);