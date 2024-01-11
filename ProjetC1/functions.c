#include "functions.h"

/*
to start the program use the commande make then ./PROJECTC1
some librairies might be necessary in particular SDL and SDL-image to install run this command  :
sudo apt-get install libsdl2-dev
sudo apt-get install libsdl2-image-dev
*/

//nombre max de unsigned long int 4 294 967 295

HIVE* createHIVE(int ihivenumber,int inbofstartingbee) {
  char  JELLY[10]="JELLY     ";
  char  HONEY[10]="HONEY     ";
  char    EGG[10]="EGG       ";
  char  DIRTY[10]="DIRTY     ";
  char LARVAE[10]="LARVAE    ";
  char  EMPTY[10]="EMPTY     ";
  char BROKEN[10]="BROKEN    ";
  char NOTMADE[10]="NOTMADE   ";
  char  POLLEN[10]="POLLEN    ";
  char BEEBREAD[10]="BEEBREAD  ";
  HIVE* newHIVE = malloc(sizeof(HIVE));
  if (!newHIVE) {
    return NULL;
  }

  newHIVE->id = ihivenumber*10000000;
  newHIVE->water = 0;
  newHIVE->honey = 800000; 
  newHIVE->jelly = 200000; 
  newHIVE->pollen = 0;
  newHIVE->nbFrame = 10; 
  newHIVE->nbBee=0;
  newHIVE->nbBeeProduced=0;
  newHIVE->nbEgg = 0; 
  newHIVE->nbParasite = 0;
  newHIVE->temperature = 35.0; //CHECK LES VRAI VALEURS
  newHIVE->hasQueen = true;
  newHIVE->cleaner = 0;
  newHIVE->nurse = 0;
  newHIVE->waxer = 0;
  newHIVE->honeyMaker = 0;
  newHIVE->guard = 0;
  newHIVE->ventillator = 0;
  newHIVE->forager = 0;
  newHIVE->waterCarrier = 0;
  newHIVE->deathToday = 0;

  BEE* newBEEQUEEN = createBEE(1,newHIVE,0);
  newHIVE->queen=newBEEQUEEN;
  newHIVE->nbBeeProduced+=1;
  newHIVE->nbBee+=1;
  BEE* newBEEQUEENsave;
  newBEEQUEENsave = newBEEQUEEN;
  for(int i = 0; i < inbofstartingbee;i++){
    BEE* newBEE = createBEE(2,newHIVE,0);
    int randomNumber2 = rand() % 40;
    if(newBEE->role[0]=='M'){
      newBEE->age=randomNumber2+24;//meurt a 114 jours
    }else{
    newBEE->age=randomNumber2+22;//meurt a 61 jours
    }
    newBEEQUEENsave->next=newBEE;
    newBEEQUEENsave=newBEEQUEENsave->next;
    newHIVE->nbBeeProduced+=1;
    newHIVE->nbBee+=1;
    //changer leur age pour qu'elle deviennes adultes sinon no activity
  }

  for(int i=0;i<10;i++){
    newHIVE->frames[i]=createFRAME(newHIVE,i);
  }
  newHIVE->frames[0]->honey=newHIVE->honey;
  newHIVE->frames[0]->jelly=newHIVE->jelly;
  newHIVE->frames[0]->nbBee=newHIVE->nbBee;
  newHIVE->frames[0]->nbEgg=newHIVE->nbEgg;
  frameCELL* saveCELL=newHIVE->frames[0]->first;
  for(int i = 0;i<800;i++){
    strncpy(saveCELL->type,HONEY,10);
    saveCELL->value=1000;
    saveCELL=saveCELL->next;
    newHIVE->frames[0]->HoneyCELL+=1;
    newHIVE->frames[0]->NotMadeCELL-=1;
  }
  for(int i = 0;i<200;i++){
    strncpy(saveCELL->type,JELLY,10);
    saveCELL->value=1000;
    saveCELL=saveCELL->next;
    newHIVE->frames[0]->JellyCELL+=1;
    newHIVE->frames[0]->NotMadeCELL-=1;
  }
  for(int i = 0;i<7100;i++){
    strncpy(saveCELL->type,EMPTY,10);
    saveCELL->value=0;
    saveCELL=saveCELL->next;
    newHIVE->frames[0]->EmptyCELL+=1;
    newHIVE->frames[0]->NotMadeCELL-=1;
    
  }
  saveCELL=newHIVE->frames[1]->first;
  for(int i = 0;i<8100;i++){
    strncpy(saveCELL->type,EMPTY,10);
    saveCELL->value=0;
    saveCELL=saveCELL->next;
    newHIVE->frames[1]->EmptyCELL+=1;
    newHIVE->frames[1]->NotMadeCELL-=1;
    
  }
  saveCELL=newHIVE->frames[2]->first;
  for(int i = 0;i<8100;i++){
    strncpy(saveCELL->type,EMPTY,10);
    saveCELL->value=0;
    saveCELL=saveCELL->next;
    newHIVE->frames[1]->EmptyCELL+=1;
    newHIVE->frames[1]->NotMadeCELL-=1;
    
  }
  

  

  return newHIVE;
}

BEE* createBEE(int type,HIVE* theHIVE,int nboftheframe){
    char QUEEN[10]="QUEEN     ";
    char WORKERBEE[10]="WORKER BEE";
    char MALE[10]="MALE      ";
    char EMPTY[10]="          ";
    char EMPTY20[20]="                    ";
    BEE* newBEE=malloc(sizeof(BEE));
    
    newBEE->id=theHIVE->id+theHIVE->nbBeeProduced+1;
    newBEE->health=100;
    newBEE->pollen=0;
    newBEE->honey=0;
    newBEE->jelly=0;
    newBEE->water=0;
    newBEE->age=0;
    if(type==1){
        strncpy(newBEE->role,QUEEN,10);
        //copie les 10 premier charactere de QUEEN au debut de newBEE->role
    }
    if(type==2){
      // Randomly choose a number between 0 and 99
      int randomNumber = rand() % 100;
      
      // Check if the random number is less than or equal to 5
      if (randomNumber <= 5) {
        strncpy(newBEE->role,MALE,10);
      }else{
        strncpy(newBEE->role,WORKERBEE,10);
      }
    }
    strncpy(newBEE->roleDuJour,EMPTY20,20);
    strncpy(newBEE->position,EMPTY,10);
    newBEE->frame=nboftheframe;

    newBEE->next=NULL;
    return newBEE;

}

FRAME* createFRAME(HIVE* theHIVE,int nboftheframe){
    char  EMPTY[10]="EMPTY     ";
    char  NOTMADE[10]="NOTMADE   ";
    FRAME* newFRAME=malloc(sizeof(FRAME));
    newFRAME->nbBee=0;
    newFRAME->nbEgg=0;
    newFRAME->honey=0;
    newFRAME->jelly=0;
    newFRAME->pollen=0;
    newFRAME->HoneyCELL=0;
    newFRAME->JellyCELL=0;
    newFRAME->EggCELL=0;
    newFRAME->DirtyCELL=0;
    newFRAME->LarvaeCELL=0;
    newFRAME->EmptyCELL=0;
    newFRAME->BrokenCELL=0;
    newFRAME->NotMadeCELL=0;
    newFRAME->PollenCELL=0;
    newFRAME->BeeBreadCELL=0;
    theHIVE->nbFrame+=1;
    newFRAME->first=createframeCELL();
    frameCELL* saveCELL=newFRAME->first;
    for(int i = 0;i<8100;i++){
        frameCELL* newCELL= createframeCELL();
        strncpy(saveCELL->type,NOTMADE,10);
        saveCELL->value=0;
        newFRAME->NotMadeCELL+=1;
        saveCELL->next=newCELL;
        saveCELL=saveCELL->next;
    }
    return newFRAME;
}

frameCELL* createframeCELL(){
    char EMPTY[10]="          ";
    frameCELL* CELL=malloc(sizeof(frameCELL));
    strncpy(CELL->type,EMPTY,10);
    CELL->value=0;
    CELL->age=0;
    CELL->next=NULL;
    return CELL;
}

void increaseHoneyLvl(HIVE* hive, int amount) {
  hive->honey += amount;
}

void decreaseHoneyLvl(HIVE* hive, int amount) {
  hive->honey -= amount;


  if (hive->honey <= 0) {
    // S'IL Y A PLUS DE MIEL
  }
}

void addBeeToHIVE( HIVE* hive, BEE* bee){
  // Add the bee to the hive
  

}

void removeBeeFromHIVE( HIVE* hive, BEE* bee){
  // Remove the bee from the hive

}
void assignRoleForToday(HIVE* theHive){
  char EMPTY[20]="                    ";
    char CLEANER[20]="CLEANER             ";
    char NURSE[20]="NURSE               ";
    char WAXER[20]="WAXER               ";
    char HONNEYMAKER[20]="HONNEYMAKER         ";
    char GUARD[20]="GUARD               ";
    char VENTILLATOR[20]="VENTILLATOR         ";
    char FORAGER[20]="FORAGER             ";
    char WATERCARRIER[20]="WATERCARRIER        ";
    BEE* BEEselector=malloc(sizeof(BEE));
    BEEselector=theHive->queen;
    theHive->cleaner=0;
    theHive->nurse=0;
    theHive->waxer=0;
    theHive->honeyMaker=0;
    theHive->guard=0;
    theHive->ventillator=0;
    theHive->forager=0;
    theHive->waterCarrier=0;


    while(BEEselector->next!=NULL){
        if(BEEselector->role[0]=='W'){
            if(BEEselector->age<=3+21 && BEEselector->age>=1+21){
                strncpy(BEEselector->roleDuJour,CLEANER,10);
                theHive->cleaner+=1;
            }
            if(BEEselector->age<=5+21 && BEEselector->age>4+21){
                strncpy(BEEselector->roleDuJour,HONNEYMAKER,10);
                theHive->honeyMaker+=1;
            }
            if(BEEselector->age<=13+21 && BEEselector->age>=6+21){
                if(theHive->honeyMaker<=theHive->waxer && theHive->honeyMaker<=theHive->guard * 2 ){
                    strncpy(BEEselector->roleDuJour,HONNEYMAKER,10);
                    theHive->honeyMaker+=1;
                }else{
                    if(theHive->waxer<=theHive->honeyMaker && theHive->waxer<=theHive->guard * 2 ){
                        strncpy(BEEselector->roleDuJour,WAXER,10);
                        theHive->waxer+=1;
                    }else{
                        if(theHive->guard * 2 <=theHive->waxer && theHive->guard * 2 <=theHive->honeyMaker){
                            strncpy(BEEselector->roleDuJour,GUARD,10);
                            theHive->guard+=1;
                        }
                    }
                }
            }
            if(BEEselector->age<=19+21 && BEEselector->age>=14+21){
                if(theHive->waxer<=theHive->ventillator *2  && theHive->waxer<=theHive->guard * 2){
                    strncpy(BEEselector->roleDuJour,WAXER,10);
                    theHive->waxer+=1;
                }else{
                    if(theHive->ventillator *2 <=theHive->waxer && theHive->ventillator *2 <=theHive->guard * 2){
                        strncpy(BEEselector->roleDuJour,VENTILLATOR,10);
                        theHive->ventillator+=1;
                    }else{
                        if(theHive->guard * 2 <=theHive->waxer && theHive->guard * 2 <=theHive->ventillator *2 ){
                            strncpy(BEEselector->roleDuJour,GUARD,10);
                            theHive->guard+=1;
                        }
                    }
                }
            }
            if(BEEselector->age<=25+21 && BEEselector->age>=20+21){
                if((theHive->guard)*5<=theHive->forager){
                    strncpy(BEEselector->roleDuJour,GUARD,10);
                    theHive->guard+=1;
                }else{
                    strncpy(BEEselector->roleDuJour,FORAGER,10);
                    theHive->forager+=1;
                }
            }
            if(BEEselector->age<=30+21 && BEEselector->age>=26+21){
                strncpy(BEEselector->roleDuJour,FORAGER,10);
                theHive->forager+=1;
            }
            if(BEEselector->age<=40+21 && BEEselector->age>=31+21){
                if((theHive->forager)/3<=theHive->waterCarrier){
                    strncpy(BEEselector->roleDuJour,FORAGER,10);
                    theHive->forager+=1;
                }else{
                    strncpy(BEEselector->roleDuJour,WATERCARRIER,10);
                    theHive->waterCarrier+=1;
                }
            }
        }
        BEEselector=BEEselector->next;
    }
}

void queenLayEgg(HIVE* theHive,int eggNumber){
  BEE* BEEselector=malloc(sizeof(BEE));
  BEEselector=theHive->queen;
  while(BEEselector->next!=NULL){
    
    BEEselector=BEEselector->next;
  }
  for(int i = 0;i<eggNumber;i++){
    BEE* newBEE = createBEE(2,theHive,0);
    BEEselector->next=newBEE;
    BEEselector=BEEselector->next;
    theHive->nbBee+=1;
    theHive->nbBeeProduced+=1;
    theHive->nbEgg+=1;
  }
}

void putEggInCell(HIVE* theHive,int eggNumber){
  char    EGG[10]="EGG       ";
  char  EMPTY[10]="EMPTY     ";
  frameCELL* saveCELL=malloc(sizeof(frameCELL));
  for(int i=0;i<10;i++){
    saveCELL=theHive->frames[i]->first;
    while(eggNumber>0 && saveCELL->next!=NULL){
      if(strncmp(saveCELL->type,EMPTY,10)==0){
        strncpy(saveCELL->type,EGG,10);
        saveCELL->value=1;
        theHive->frames[i]->EggCELL+=1;
        theHive->frames[i]->nbEgg+=1;
        theHive->frames[i]->EmptyCELL-=1;
        eggNumber-=1;
      }
      saveCELL=saveCELL->next;
    }
  }
  if(eggNumber>0){
    printf("not enough space for the eggs%d\n",eggNumber);
    //theHive->nbEgg-=eggNumber;
  }
}

void doRoleFor1Period(HIVE* theHive){
  int count1=0,count2=0;
  int selector=100,waxerror=0,pollenerror=0,honeyerror=0,emptyerror=0,randomguard=0,hiveprotected=0;
  char  JELLY[10]="JELLY     ";
  char  HONEY[10]="HONEY     ";
  char    EGG[10]="EGG       ";
  char  DIRTY[10]="DIRTY     ";
  char LARVAE[10]="LARVAE    ";
  char  EMPTY[10]="EMPTY     ";
  char BROKEN[10]="BROKEN    ";
  char NOTMADE[10]="NOTMADE   ";
  char  POLLEN[10]="POLLEN    ";
  char BEEBREAD[10]="BEEBREAD  ";
  char CLEANER[20]="CLEANER             ";
  char NURSE[20]="NURSE               ";
  char WAXER[20]="WAXER               ";
  char HONNEYMAKER[20]="HONNEYMAKER         ";
  char GUARD[20]="GUARD               ";
  char VENTILLATOR[20]="VENTILLATOR         ";
  char FORAGER[20]="FORAGER             ";
  char WATERCARRIER[20]="WATERCARRIER        ";
  BEE* BEEselector=malloc(sizeof(BEE));
  BEEselector=theHive->queen;
  frameCELL* CELLselector=malloc(sizeof(frameCELL));
  while(BEEselector->next!=NULL){
    if(BEEselector->role[0]=='W'){
      if(strncmp(BEEselector->roleDuJour,FORAGER,10)==0){
        selector=100;
        BEEselector->pollen=5;
        theHive->pollen+=5;
        for(int y=0;y<5;y++){
          for(int i =0;i<10;i++){
            if(theHive->frames[i]->PollenCELL>0 && selector==100 && theHive->frames[i]->pollen % 1000 != 0){
              selector=i;
            }
          }
          if(selector!=100){
            CELLselector=theHive->frames[selector]->first;
            while((CELLselector->next!=NULL) && (strncmp(CELLselector->type,POLLEN,10)!=0 || CELLselector->value == 1000)){
              CELLselector=CELLselector->next;
            }
            if(strncmp(CELLselector->type,POLLEN,10)==0 && selector!=100){
              CELLselector->value+=1;
              theHive->frames[selector]->pollen+=1;
            }
          }else{
            for(int i =0;i<10;i++){
              if(theHive->frames[i]->EmptyCELL>0 && selector==100){
                selector=i;
              }
            }
            if(selector!=100){
              CELLselector=theHive->frames[selector]->first;
              while(CELLselector->next!=NULL && strncmp(CELLselector->type,EMPTY,10)!=0){
                CELLselector=CELLselector->next;
              }
              if(strncmp(CELLselector->type,EMPTY,10)==0 && selector!=100){
                strncpy(CELLselector->type,POLLEN,10);
                CELLselector->value=1;
                theHive->frames[selector]->EmptyCELL-=1;
                theHive->frames[selector]->PollenCELL+=1;
                theHive->frames[selector]->pollen+=1;
              }
            }else{
              //printf("not enough space (empty) for the pollen\n");
              pollenerror+=1;
            }
          }
        }
      }
      if(strncmp(BEEselector->roleDuJour,WATERCARRIER,10)==0){
        selector=100;
        if(BEEselector->water==0){
          theHive->water+=1;
        }
        BEEselector->water=1;
      }
    }
    BEEselector=BEEselector->next;
  }
  BEEselector=theHive->queen;
  while(BEEselector->next!=NULL){
    if(BEEselector->role[0]=='W'){
      if(strncmp(BEEselector->roleDuJour,CLEANER,10)==0){
        selector=100;
        for(int i =0;i<10;i++){
          if(theHive->frames[i]->DirtyCELL>0 && selector==100){
            selector=i;
          }
        }
        if(selector!=100){
          CELLselector=theHive->frames[selector]->first;
          while(CELLselector->next!=NULL && strncmp(CELLselector->type,DIRTY,10)!=0){
            CELLselector=CELLselector->next;
          }
          if(strncmp(CELLselector->type,DIRTY,10)==0 && selector!=100){
            strncpy(CELLselector->type,EMPTY,10);
            theHive->frames[selector]->DirtyCELL-=1;
            theHive->frames[selector]->EmptyCELL+=1;
          }
          BEEselector->frame=selector;
          selector=100;
        }
      }
      if(strncmp(BEEselector->roleDuJour,HONNEYMAKER,10)==0){
        selector=100;
        if(theHive->pollen>=15){
        for(int i = 0;i<15;i++){
          for(int i =0;i<10;i++){
              if(theHive->frames[i]->PollenCELL>0 && selector==100){
                selector=i;
              }
          }
          CELLselector=theHive->frames[selector]->first;
          while(CELLselector->next!=NULL && strncmp(CELLselector->type,POLLEN,10)!=0){
            CELLselector=CELLselector->next;
          }
          if(strncmp(CELLselector->type,POLLEN,10)==0 && selector!=100){
            if(CELLselector->value>=2){
              CELLselector->value-=1;
              BEEselector->pollen+=1;
              theHive->frames[selector]->pollen-=1;
            }else{
            strncpy(CELLselector->type,EMPTY,10);
            theHive->frames[selector]->PollenCELL-=1;
            theHive->frames[selector]->EmptyCELL+=1;
            CELLselector->value=0;
            BEEselector->pollen+=1;
            theHive->frames[selector]->pollen-=1;
            }
          }
        }
        BEEselector->honey=6;
        //theHive->honey+=6;
        BEEselector->pollen-=15;
        theHive->pollen-=15;
        BEEselector->frame=selector;
        for(int y=0;y<6;y++){
        selector=100;
        for(int i =0;i<10;i++){
          if(theHive->frames[i]->HoneyCELL>0 && selector==100 && theHive->frames[i]->honey % 1000 != 0){
            selector=i;
          }
        }
        if(selector!=100){
          CELLselector=theHive->frames[selector]->first;
          while((CELLselector->next!=NULL) && (strncmp(CELLselector->type,HONEY,10)!=0 || CELLselector->value == 1000)){
            CELLselector=CELLselector->next;
          }
          if(strncmp(CELLselector->type,HONEY,10)==0 && selector!=100){
            CELLselector->value+=1;
            theHive->honey+=1;
            BEEselector->honey-=1;
            theHive->frames[selector]->honey+=1;
          }
        }else{
          for(int i =0;i<10;i++){
            if(theHive->frames[i]->EmptyCELL>0 && selector==100){
              selector=i;
            }
          }
        if(selector!=100){
          CELLselector=theHive->frames[selector]->first;
          while(CELLselector->next!=NULL && strncmp(CELLselector->type,EMPTY,10)!=0){
            CELLselector=CELLselector->next;
          }
          if(strncmp(CELLselector->type,EMPTY,10)==0 && selector!=100){
            strncpy(CELLselector->type,HONEY,10);
            CELLselector->value=1;
            theHive->honey+=1;
            BEEselector->honey-=1;
            theHive->frames[selector]->EmptyCELL-=1;
            theHive->frames[selector]->HoneyCELL+=1;
            theHive->frames[selector]->honey+=1;
          }
        }else{
          //printf("not enough space (empty) for the honey\n");
        }
        }
        }
        }else{
          //printf("%d\n",theHive->pollen);
          honeyerror+=1;
        }
      }
      if(strncmp(BEEselector->roleDuJour,WAXER,10)==0){
        selector=100;
        for(int i =0;i<10;i++){
          if(theHive->frames[i]->NotMadeCELL>0 && selector==100){
            selector=i;
          }
        }
        if(selector!=100){
          CELLselector=theHive->frames[selector]->first;
          while(CELLselector->next!=NULL && strncmp(CELLselector->type,NOTMADE,10)!=0){
            CELLselector=CELLselector->next;
          }
          if(strncmp(CELLselector->type,NOTMADE,10)==0 && selector!=100){
            strncpy(CELLselector->type,EMPTY,10);
            theHive->frames[selector]->NotMadeCELL-=1;
            theHive->frames[selector]->EmptyCELL+=1;
          }
          BEEselector->frame=selector;
        }else{
          
        }
      }
      if(strncmp(BEEselector->roleDuJour,GUARD,10)==0){
        randomguard=rand() % 1000;
        if(randomguard==0){
          hiveprotected+=1;
        }
      }
    }
    BEEselector=BEEselector->next;
  }
  if(honeyerror!=0){
    //printf("not enough pollen for the honey x%d\n",honeyerror);
  }
  printf("hive was protected %d times in this period\n",hiveprotected);//ajouter animation sdl
}
void doRoleForNight(HIVE* theHive){
  int selector=100,waxerror=0,pollenerror=0,honeyerror=0,emptyerror=0,randomguard=0,hiveprotected=0,jellyerror=0;
  char  JELLY[10]="JELLY     ";
  char  HONEY[10]="HONEY     ";
  char    EGG[10]="EGG       ";
  char  DIRTY[10]="DIRTY     ";
  char LARVAE[10]="LARVAE    ";
  char  EMPTY[10]="EMPTY     ";
  char BROKEN[10]="BROKEN    ";
  char NOTMADE[10]="NOTMADE   ";
  char  POLLEN[10]="POLLEN    ";
  char BEEBREAD[10]="BEEBREAD  ";
  char CLEANER[20]="CLEANER             ";
  char NURSE[20]="NURSE               ";
  char WAXER[20]="WAXER               ";
  char HONNEYMAKER[20]="HONNEYMAKER         ";
  char GUARD[20]="GUARD               ";
  char VENTILLATOR[20]="VENTILLATOR         ";
  char FORAGER[20]="FORAGER             ";
  char WATERCARRIER[20]="WATERCARRIER        ";
  BEE* BEEselector=malloc(sizeof(BEE));
  BEEselector=theHive->queen;
  frameCELL* CELLselector=malloc(sizeof(frameCELL));
  while(BEEselector->next!=NULL){
    if(BEEselector->role[0]=='W'){
      if(strncmp(BEEselector->roleDuJour,HONNEYMAKER,10)==0){
        if(theHive->jelly<10000){  
        selector=100;
        if(theHive->honey>=15){
        for(int i = 0;i<15;i++){
          for(int i =0;i<10;i++){
              if(theHive->frames[i]->HoneyCELL>0 && selector==100){
                selector=i;
              }
          }
          CELLselector=theHive->frames[selector]->first;
          while(CELLselector->next!=NULL && strncmp(CELLselector->type,HONEY,10)!=0){
            CELLselector=CELLselector->next;
          }
          if(strncmp(CELLselector->type,HONEY,10)==0 && selector!=100){
            if(CELLselector->value>=2){
              CELLselector->value-=1;
              BEEselector->honey+=1;
              theHive->frames[selector]->honey-=1;
            }else{
            strncpy(CELLselector->type,EMPTY,10);
            theHive->frames[selector]->HoneyCELL-=1;
            theHive->frames[selector]->EmptyCELL+=1;
            CELLselector->value=0;
            BEEselector->honey+=1;
            theHive->frames[selector]->honey-=1;
            }
          }
        }
        BEEselector->jelly=6;
        //theHive->jelly+=6;
        BEEselector->honey=0;
        theHive->honey-=15;
        BEEselector->frame=selector;
        for(int y=0;y<6;y++){
        selector=100;
        for(int i =0;i<10;i++){
          if(theHive->frames[i]->JellyCELL>0 && selector==100 && theHive->frames[i]->jelly % 1000 != 0){
            selector=i;
          }
        }
        if(selector!=100){
          CELLselector=theHive->frames[selector]->first;
          while((CELLselector->next!=NULL) && (strncmp(CELLselector->type,JELLY,10)!=0 || CELLselector->value == 1000)){
            CELLselector=CELLselector->next;
          }
          if(strncmp(CELLselector->type,JELLY,10)==0 && selector!=100){
            CELLselector->value+=1;
            theHive->jelly+=1;
            BEEselector->jelly-=1;
            theHive->frames[selector]->jelly+=1;
          }
        }else{
          for(int i =0;i<10;i++){
            if(theHive->frames[i]->EmptyCELL>0 && selector==100){
              selector=i;
            }
          }
        if(selector!=100){
          CELLselector=theHive->frames[selector]->first;
          while(CELLselector->next!=NULL && strncmp(CELLselector->type,EMPTY,10)!=0){
            CELLselector=CELLselector->next;
          }
          if(strncmp(CELLselector->type,EMPTY,10)==0 && selector!=100){
            strncpy(CELLselector->type,JELLY,10);
            CELLselector->value=1;
            theHive->jelly+=1;
            BEEselector->jelly-=1;
            theHive->frames[selector]->EmptyCELL-=1;
            theHive->frames[selector]->JellyCELL+=1;
            theHive->frames[selector]->jelly+=1;
          }
        }else{
          //printf("not enough space (empty) for the jelly\n");
        }
        }
        }
        }else{
          jellyerror+=1;
        }
      }
      }
    }
    
    BEEselector=BEEselector->next;
  }
  
  BEEselector=theHive->queen;
  while(BEEselector->next!=NULL){
    if(BEEselector->role[0]=='W'){
      if(strncmp(BEEselector->roleDuJour,CLEANER,10)==0){
        selector=100;
        for(int i =0;i<10;i++){
          if(theHive->frames[i]->DirtyCELL>0 && selector==100){
            selector=i;
          }
        }
        if(selector!=100){
          CELLselector=theHive->frames[selector]->first;
          while(CELLselector->next!=NULL && strncmp(CELLselector->type,DIRTY,10)!=0){
            CELLselector=CELLselector->next;
          }
          if(strncmp(CELLselector->type,DIRTY,10)==0 && selector!=100){
            strncpy(CELLselector->type,EMPTY,10);
            theHive->frames[selector]->DirtyCELL-=1;
            theHive->frames[selector]->EmptyCELL+=1;
          }
          BEEselector->frame=selector;
          selector=100;
        }
      }
      if(strncmp(BEEselector->roleDuJour,HONNEYMAKER,10)==0){
        selector=100;
        if(theHive->pollen>=15){
        for(int i = 0;i<15;i++){
          for(int i =0;i<10;i++){
              if(theHive->frames[i]->PollenCELL>0 && selector==100){
                selector=i;
              }
          }
          CELLselector=theHive->frames[selector]->first;
          while(CELLselector->next!=NULL && strncmp(CELLselector->type,POLLEN,10)!=0){
            CELLselector=CELLselector->next;
          }
          if(strncmp(CELLselector->type,POLLEN,10)==0 && selector!=100){
            if(CELLselector->value>=2){
              CELLselector->value-=1;
              BEEselector->pollen+=1;
              theHive->frames[selector]->pollen-=1;
            }else{
            strncpy(CELLselector->type,EMPTY,10);
            theHive->frames[selector]->PollenCELL-=1;
            theHive->frames[selector]->EmptyCELL+=1;
            CELLselector->value=0;
            BEEselector->pollen+=1;
            theHive->frames[selector]->pollen-=1;
            }
          }
        }
        BEEselector->honey=6;
        //theHive->honey+=6;
        BEEselector->pollen-=15;
        theHive->pollen-=15;
        BEEselector->frame=selector;
        for(int y=0;y<6;y++){
        selector=100;
        for(int i =0;i<10;i++){
          if(theHive->frames[i]->HoneyCELL>0 && selector==100 && theHive->frames[i]->honey % 1000 != 0){
            selector=i;
          }
        }
        if(selector!=100){
          CELLselector=theHive->frames[selector]->first;
          while((CELLselector->next!=NULL) && (strncmp(CELLselector->type,HONEY,10)!=0 || CELLselector->value == 1000)){
            CELLselector=CELLselector->next;
          }
          if(strncmp(CELLselector->type,HONEY,10)==0 && selector!=100){
            CELLselector->value+=1;
            theHive->honey+=1;
            BEEselector->honey-=1;
            theHive->frames[selector]->honey+=1;
          }
        }else{
          for(int i =0;i<10;i++){
            if(theHive->frames[i]->EmptyCELL>0 && selector==100){
              selector=i;
            }
          }
        if(selector!=100){
          CELLselector=theHive->frames[selector]->first;
          while(CELLselector->next!=NULL && strncmp(CELLselector->type,EMPTY,10)!=0){
            CELLselector=CELLselector->next;
          }
          if(strncmp(CELLselector->type,EMPTY,10)==0 && selector!=100){
            strncpy(CELLselector->type,HONEY,10);
            CELLselector->value=1;
            theHive->honey+=1;
            BEEselector->honey-=1;
            theHive->frames[selector]->EmptyCELL-=1;
            theHive->frames[selector]->HoneyCELL+=1;
            theHive->frames[selector]->honey+=1;
          }
        }else{
          //printf("not enough space (empty) for the honey\n");
        }
        }
        }
        }else{
          honeyerror+=1;
        }
      }
      if(strncmp(BEEselector->roleDuJour,WAXER,10)==0){
        selector=100;
        for(int i =0;i<10;i++){
          if(theHive->frames[i]->NotMadeCELL>0 && selector==100){
            selector=i;
          }
        }
        if(selector!=100){
          CELLselector=theHive->frames[selector]->first;
          while(CELLselector->next!=NULL && strncmp(CELLselector->type,NOTMADE,10)!=0){
            CELLselector=CELLselector->next;
          }
          if(strncmp(CELLselector->type,NOTMADE,10)==0 && selector!=100){
            strncpy(CELLselector->type,EMPTY,10);
            theHive->frames[selector]->NotMadeCELL-=1;
            theHive->frames[selector]->EmptyCELL+=1;
          }
          BEEselector->frame=selector;
        }else{
          //printf("not enough space (empty) for the wax\n");
        }
      }
    }
    BEEselector=BEEselector->next;
  }
  if(honeyerror!=0){
    //printf("not enough pollen for the honey x%d\n",honeyerror);
  }
}

void beesEat(HIVE* theHive){
  int selector=100,count=0;
  char  JELLY[10]="JELLY     ";
  char  HONEY[10]="HONEY     ";
  char    EGG[10]="EGG       ";
  char  DIRTY[10]="DIRTY     ";
  char LARVAE[10]="LARVAE    ";
  char  EMPTY[10]="EMPTY     ";
  char BROKEN[10]="BROKEN    ";
  char NOTMADE[10]="NOTMADE   ";
  char  POLLEN[10]="POLLEN    ";
  char BEEBREAD[10]="BEEBREAD  ";
  char CLEANER[20]="CLEANER             ";
  char NURSE[20]="NURSE               ";
  char WAXER[20]="WAXER               ";
  char HONNEYMAKER[20]="HONNEYMAKER         ";
  char GUARD[20]="GUARD               ";
  char VENTILLATOR[20]="VENTILLATOR         ";
  char FORAGER[20]="FORAGER             ";
  char WATERCARRIER[20]="WATERCARRIER        ";
  BEE* BEEselector=malloc(sizeof(BEE));
  BEE* BEEsave=malloc(sizeof(BEE));
  BEEselector=theHive->queen;
  frameCELL* CELLselector=malloc(sizeof(frameCELL));
  while(BEEselector->next!=NULL){
    if(BEEselector->role[0]=='Q'){
      selector=100;
      if(theHive->jelly>=10){
        theHive->jelly-=10;
        for(int y=0;y<10;y++){
          for(int i =0;i<10;i++){
            if(theHive->frames[i]->JellyCELL>0 && selector==100){
              selector=i;
            }
          }
          CELLselector=theHive->frames[selector]->first;
          while(CELLselector->next!=NULL && strncmp(CELLselector->type,JELLY,10)!=0){
            CELLselector=CELLselector->next;
          }
          if(strncmp(CELLselector->type,JELLY,10)==0 && selector!=100){
            if(CELLselector->value>=2){
              CELLselector->value-=1;
            }else{
            strncpy(CELLselector->type,EMPTY,10);
            theHive->frames[selector]->JellyCELL-=1;
            theHive->frames[selector]->EmptyCELL+=1;
            CELLselector->value=0;
            }
            theHive->frames[selector]->jelly-=1;
          }
        }
      }
    }
    if((BEEselector->age>=21&& BEEselector->role[0]!='Q') || (BEEselector->age>6 && BEEselector->age<=9 && BEEselector->role[0]!='Q')){
      selector=100;
      if(theHive->honey>=2){
        for(int i =0;i<10;i++){
          if(theHive->frames[i]->HoneyCELL>0 && selector==100){
            selector=i;
          }
        }
        CELLselector=theHive->frames[selector]->first;
        while(CELLselector->next!=NULL && strncmp(CELLselector->type,HONEY,10)!=0){
          CELLselector=CELLselector->next;
        }
        if(strncmp(CELLselector->type,HONEY,10)==0 && selector!=100){
          if(CELLselector->value>=2){
            CELLselector->value-=1;
          }else{
          strncpy(CELLselector->type,EMPTY,10);
          theHive->frames[selector]->HoneyCELL-=1;
          theHive->frames[selector]->EmptyCELL+=1;
          CELLselector->value=0;
          }
          theHive->frames[selector]->honey-=1;
          theHive->honey-=1;
        }
      }else{
        BEEselector->health-=10;
        if(BEEselector->health<=0){
          theHive->deathToday+=1;
          //theHive->nbBee-=1;
          printf("BEE %ld died of hunger\n",BEEselector->id);
        }
        BEEsave->next=BEEselector->next;
      }
    }
    if(BEEselector->age<=6 && BEEselector->age>3 && BEEselector->role[0]!='Q'){
      selector=100;
      if(BEEselector->role[0]=='M'){
        if(theHive->honey>=2){
        for(int i =0;i<10;i++){
          if(theHive->frames[i]->HoneyCELL>0 && selector==100){
            selector=i;
          }
        }
        CELLselector=theHive->frames[selector]->first;
        while(CELLselector->next!=NULL && strncmp(CELLselector->type,HONEY,10)!=0){
          CELLselector=CELLselector->next;
        }
        if(strncmp(CELLselector->type,HONEY,10)==0 && selector!=100){
          if(CELLselector->value>=2){
            CELLselector->value-=1;
          }else{
          strncpy(CELLselector->type,EMPTY,10);
          theHive->frames[selector]->HoneyCELL-=1;
          theHive->frames[selector]->EmptyCELL+=1;
          CELLselector->value=0;
          }
          theHive->frames[selector]->honey-=1;
          theHive->honey-=1;
        }
      }else{
        BEEselector->health-=10;
        if(BEEselector->health<=0){
          theHive->deathToday+=1;
          //theHive->nbBee-=1;
          printf("BEE %ld died of hunger\n",BEEselector->id);
        }
        BEEsave->next=BEEselector->next;
      }
      }else{
        if(BEEselector->role[0]=='W'){
        selector=100;
        if(theHive->jelly>=1){
          theHive->jelly-=1;
          for(int i =0;i<10;i++){
            if(theHive->frames[i]->JellyCELL>0 && selector==100){
              selector=i;
            }
          }
          CELLselector=theHive->frames[selector]->first;
          while(CELLselector->next!=NULL && strncmp(CELLselector->type,JELLY,10)!=0){
            CELLselector=CELLselector->next;
          }
          if(strncmp(CELLselector->type,JELLY,10)==0 && selector!=100){
            if(CELLselector->value>=2){
              CELLselector->value-=1;
            }else{
            strncpy(CELLselector->type,EMPTY,10);
            theHive->frames[selector]->JellyCELL-=1;
            theHive->frames[selector]->EmptyCELL+=1;
            CELLselector->value=0;
            }
            theHive->frames[selector]->jelly-=1;
          }else{
          BEEselector->health-=10;
          if(BEEselector->health<=0){
            theHive->deathToday+=1;
            //theHive->nbBee-=1;
            printf("BEE %ld died of hunger\n",BEEselector->id);
          }
          BEEsave->next=BEEselector->next;
          }
        }
      }
    }
    }
    BEEsave=BEEselector;
    BEEselector=BEEselector->next;
  }
}
void nextDay(HIVE* theHive){
  int wait=0;
  int count=0,count2=0;
  theHive->deathToday=0;
  char  JELLY[10]="JELLY     ";
  char  HONEY[10]="HONEY     ";
  char    EGG[10]="EGG       ";
  char  DIRTY[10]="DIRTY     ";
  char LARVAE[10]="LARVAE    ";
  char  EMPTY[10]="EMPTY     ";
  char BROKEN[10]="BROKEN    ";
  char NOTMADE[10]="NOTMADE   ";
  char  POLLEN[10]="POLLEN    ";
  char BEEBREAD[10]="BEEBREAD  ";
  char CLEANER[20]="CLEANER             ";
  char NURSE[20]="NURSE               ";
  char WAXER[20]="WAXER               ";
  char HONNEYMAKER[20]="HONNEYMAKER         ";
  char GUARD[20]="GUARD               ";
  char VENTILLATOR[20]="VENTILLATOR         ";
  char FORAGER[20]="FORAGER             ";
  char WATERCARRIER[20]="WATERCARRIER        ";
  BEE* BEEselector=malloc(sizeof(BEE));
  BEE* BEEsave=malloc(sizeof(BEE));
  BEEselector=theHive->queen;
  frameCELL* CELLselector=malloc(sizeof(frameCELL));
  do{
    count+=1;
    BEEselector->age+=1;
    if(BEEselector->role[0]=='W'){
      if(BEEselector->age>62){
        theHive->deathToday+=1;
        theHive->nbBee-=1;
        count2=1;
        count-=1;
        //printf("age %d ",BEEselector->age);
        if(BEEselector->next!=NULL){
          BEEsave->next=BEEselector->next;
          BEEselector=BEEselector->next;
        }else{
          BEEsave->next=NULL;
        }
      }
    }
    if(BEEselector->role[0]=='M'){
      if(BEEselector->age>115){
        theHive->deathToday+=1;
        theHive->nbBee-=1;
        count2=1;
        count-=1;
        //printf("age %d ",BEEselector->age);
        if(BEEselector->next!=NULL){
          BEEsave->next=BEEselector->next;
          BEEselector=BEEselector->next;
        }else{
          BEEsave->next=NULL;
        }
      }
    }
    
    count2 =0;
    BEEsave=BEEselector;
    BEEselector=BEEselector->next;
  }while(BEEselector->next!=NULL);  
}

void getOut(HIVE* theHive){
  int selector=100;
  char BROKEN[10]="BROKEN    ";
  char DIRTY[10]="DIRTY     ";
  char    EGG[10]="EGG       ";
  frameCELL* CELLselector=malloc(sizeof(frameCELL));
  for(int i =0;i<10;i++){
    CELLselector=theHive->frames[i]->first;
    while(CELLselector->next!=NULL){
        if(strncmp(CELLselector->type,EGG,10)==0){
        CELLselector->age+=1;
        if(CELLselector->age>=21){
          strncpy(CELLselector->type,DIRTY,10);
          theHive->frames[i]->EggCELL-=1;
          theHive->frames[i]->DirtyCELL+=1;
          theHive->frames[i]->nbEgg-=1;
          CELLselector->value=0;
          CELLselector->age=0;
          theHive->nbEgg-=1;
        }
      }
      CELLselector=CELLselector->next;
    }
  }
}

Node* createNode(int data) {
  Node* newNode = (Node*)malloc(sizeof(Node));
  newNode->data = data;
  newNode->left = NULL;
  newNode->right = NULL;
  return newNode;
}

Node* createBinaryTree(int depth) {
  if (depth <= 0) {
    return NULL;
  }
  int randomnumber = rand() % 100;//0=prairie, 1=forest, 2=champ de fleur,110=hive,4=nothing
  Node* root = createNode(randomnumber);
  root->left = createBinaryTree(depth - 1);
  root->right = createBinaryTree(depth - 1);

  return root;
}

int Findclosest2(Node* root,int deph,int maxdeph) {
  int i=0;
  if (deph>maxdeph) {
    return 100;
  }else{
    if(root->data==2){
      return deph;
    }
    if(Findclosest2(root->left,deph+1,maxdeph)!=100){
      return Findclosest2(root->left,deph+1,maxdeph);
    }
    if(Findclosest2(root->right,deph+1,maxdeph)!=100){
      return Findclosest2(root->right,deph+1,maxdeph);
    }
    
    
  }
}
int findpath(Node* root,int actualdeph,int maxdeph,char path[100]){
  if(actualdeph<=maxdeph){
    if(root->data==2){
      return actualdeph;
    }
    if(findpath(root->left,actualdeph+1,maxdeph,path)!=100){
      path[actualdeph]='l';
      return actualdeph;
    }
    if(findpath(root->right,actualdeph+1,maxdeph,path)!=100){
      path[actualdeph]='r';
      return actualdeph;
    }
    
  }
  return 100;
}

int affichage(HIVE* HIVE1){
  char wait;
  int atdeph=100;
  Node* tree;
  char* path=malloc(sizeof(char)*100);
  
  frameCELL* CELLalveole=malloc(sizeof(frameCELL));
  
    int randomNumber = 0;
    int count=0,count2=0,count3=0;
    //printf("hello there\n");
    
    BEE* mybee=createBEE(1,HIVE1,0);
    //printf("%s\n",mybee->role);
    //printf("hello there\n");
    BEE* newBEE=malloc(sizeof(BEE));


    // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("Error: Failed to initialize SDL\n");
    return 1;
  }

  // Create a window
  SDL_Window* window = SDL_CreateWindow("Projet", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1550, 650, 0);
  if (!window) {
    printf("Error: Failed to create window\n");
    return 1;
  }

  // Create a renderer
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    printf("Error: Failed to create renderer\n");
    return 1;
  }
  SDL_Rect rectangle;
    rectangle.x=10;
    rectangle.y=10;
    rectangle.w=20;
    rectangle.h=20;
    

    
    
    SDL_Surface* imageSurface = IMG_Load("white.png");
    if (imageSurface == NULL) {
        printf("Failed to load image: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_Surface* alveole = IMG_Load("hexagone.png");
    if (imageSurface == NULL) {
        printf("Failed to load image: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_Surface* alveoledirty = IMG_Load("hexagonedirty.png");
    if (imageSurface == NULL) {
        printf("Failed to load image: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_Surface* alveoleegg = IMG_Load("hexagoneegg.png");
    if (imageSurface == NULL) {
        printf("Failed to load image: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_Surface* alveolejelly = IMG_Load("hexagonejelly.png");
    if (imageSurface == NULL) {
        printf("Failed to load image: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_Surface* alveolemiel = IMG_Load("hexagonemiel.png");
    if (imageSurface == NULL) {
        printf("Failed to load image: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_Surface* alveolenotmade = IMG_Load("hexagonenotmade.png");
    if (imageSurface == NULL) {
        printf("Failed to load image: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_Surface* alveolepollen = IMG_Load("hexagonepollen.png");
    if (imageSurface == NULL) {
        printf("Failed to load image: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Create a texture from the image
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    SDL_FreeSurface(imageSurface);
    if (texture == NULL) {
        printf("Failed to create texture: %s\n", SDL_GetError());
        SDL_FreeSurface(imageSurface);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Texture* texturealveole = SDL_CreateTextureFromSurface(renderer, alveole);
    SDL_FreeSurface(alveole);
    if (texture == NULL) {
        printf("Failed to create texture: %s\n", SDL_GetError());
        SDL_FreeSurface(alveole);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_Texture* texturealveoledirty = SDL_CreateTextureFromSurface(renderer, alveoledirty);
    SDL_FreeSurface(alveoledirty);
    if (texture == NULL) {
        printf("Failed to create texture: %s\n", SDL_GetError());
        SDL_FreeSurface(alveoledirty);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_Texture* texturealveoleegg = SDL_CreateTextureFromSurface(renderer, alveoleegg);
    SDL_FreeSurface(alveoleegg);
    if (texture == NULL) {
        printf("Failed to create texture: %s\n", SDL_GetError());
        SDL_FreeSurface(alveoleegg);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_Texture* texturealveolejelly = SDL_CreateTextureFromSurface(renderer, alveolejelly);
    SDL_FreeSurface(alveolejelly);
    if (texture == NULL) {
        printf("Failed to create texture: %s\n", SDL_GetError());
        SDL_FreeSurface(alveolejelly);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_Texture* texturealveolemiel = SDL_CreateTextureFromSurface(renderer, alveolemiel);
    SDL_FreeSurface(alveolemiel);
    if (texture == NULL) {
        printf("Failed to create texture: %s\n", SDL_GetError());
        SDL_FreeSurface(alveolemiel);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_Texture* texturealveolenotmade = SDL_CreateTextureFromSurface(renderer, alveolenotmade);
    SDL_FreeSurface(alveolenotmade);
    if (texture == NULL) {
        printf("Failed to create texture: %s\n", SDL_GetError());
        SDL_FreeSurface(alveolenotmade);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_Texture* texturealveolepollen = SDL_CreateTextureFromSurface(renderer, alveolepollen);
    SDL_FreeSurface(alveolepollen);
    if (texture == NULL) {
        printf("Failed to create texture: %s\n", SDL_GetError());
        SDL_FreeSurface(alveolepollen);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    char  JELLY[10]="JELLY     ";
  char  HONEY[10]="HONEY     ";
  char    EGG[10]="EGG       ";
  char  DIRTY[10]="DIRTY     ";
  char LARVAE[10]="LARVAE    ";
  char  EMPTY[10]="EMPTY     ";
  char BROKEN[10]="BROKEN    ";
  char NOTMADE[10]="NOTMADE   ";
  char  POLLEN[10]="POLLEN    ";
  char BEEBREAD[10]="BEEBREAD  ";
  
    int truc=0;
    int close=0;
    int selector=0;
    while(!close){
      


    wait=0;
    selector=0;
    CELLalveole=HIVE1->frames[selector]->first;
    newBEE=HIVE1->queen;
    count2=0;
    count=0;
    //printf("nbworker:%d\n",count);
    //printf("nbbourdon:%d\n",count2);
    printf("Days : %d :\n",count3);
    queenLayEgg(HIVE1,500);
    putEggInCell(HIVE1,500);
    assignRoleForToday(HIVE1);
    doRoleFor1Period(HIVE1);
    doRoleFor1Period(HIVE1);
    doRoleFor1Period(HIVE1);
    doRoleForNight(HIVE1);//there is a problem here when honey is 0
    doRoleForNight(HIVE1);
    doRoleForNight(HIVE1);
    beesEat(HIVE1);
    nextDay(HIVE1);
    getOut(HIVE1);
    printf("number of cleaner : %d\n",HIVE1->cleaner);
    printf("number of honeyMaker : %d\n",HIVE1->honeyMaker);
    printf("number of waxer : %d\n",HIVE1->waxer);
    printf("number of guard : %d\n",HIVE1->guard);
    printf("number of ventillator : %d\n",HIVE1->ventillator);
    printf("number of forager : %d\n",HIVE1->forager);
    printf("number of waterCarrier : %d\n",HIVE1->waterCarrier);
    /*
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("%d\n",HIVE1->nbEgg);
    printf("%d\n",HIVE1->frames[0]->nbEgg);
    printf("%d\n",HIVE1->frames[9]->NotMadeCELL);
    printf("%d\n",HIVE1->frames[0]->EmptyCELL);
    printf("%d\n",HIVE1->frames[0]->DirtyCELL);
    */
  tree = createBinaryTree(10);//generate randomly the world ouside the hive
  tree->data=110;
  atdeph=100;
  for(int i=1;i<10;i++){
    if(Findclosest2(tree,0,i)!=100){
      if(atdeph>Findclosest2(tree,0,i)){
        atdeph=Findclosest2(tree,0,i);
      }
    }
  }
  findpath(tree,0,atdeph,path);//the tab path is filled with the path to the closest flowers from the hive

    printf("\n");
    HIVE1->deathToday=0;
    printf("number of bees : %d\n",HIVE1->nbBee);
    printf("honey in Hive : %d\n",HIVE1->honey);

    
    //printf("fhoney %d\n",ffhoney);
    printf("jelly in Hive : %d\n",HIVE1->jelly);
    //printf("fjelly%d\n",HIVE1->frames[0]->jelly);
    printf("pollen in Hive : %d\n",HIVE1->pollen);
    //printf("fpollen%d\n",HIVE1->frames[0]->pollen);
    printf("\n");
    
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    count3+=1;
    //scanf("%c",&wait);
    truc=0;

    SDL_RenderCopy(renderer, texture, NULL, NULL);
    
    for(int y =0;y<45;y++){
    for(int i =0;i<90;i++){
    if(y%2){
      truc=10;
    }else{
      truc=0;
    }
    rectangle.x=17*i + truc;
    rectangle.y=14*y;
    if(strncmp(CELLalveole->type,JELLY,10)==0){
      SDL_RenderCopy(renderer, texturealveolejelly, NULL, &rectangle);
    }
    if(strncmp(CELLalveole->type,HONEY,10)==0){
      SDL_RenderCopy(renderer, texturealveolemiel, NULL, &rectangle);
    }
    if(strncmp(CELLalveole->type,EGG,10)==0){
      SDL_RenderCopy(renderer, texturealveoleegg, NULL, &rectangle);
    }
    if(strncmp(CELLalveole->type,DIRTY,10)==0){
      SDL_RenderCopy(renderer, texturealveoledirty, NULL, &rectangle);
    }
    if(strncmp(CELLalveole->type,EMPTY,10)==0){
      SDL_RenderCopy(renderer, texturealveole, NULL, &rectangle);
    }
    if(strncmp(CELLalveole->type,NOTMADE,10)==0){
      SDL_RenderCopy(renderer, texturealveolenotmade, NULL, &rectangle);
    }
    if(strncmp(CELLalveole->type,POLLEN,10)==0){
      SDL_RenderCopy(renderer, texturealveolepollen, NULL, &rectangle);
    }
    if(CELLalveole->next!=NULL){
      CELLalveole=CELLalveole->next;
    }else{
      selector+=1;
      CELLalveole=HIVE1->frames[selector]->first;
    }
    
    
    }
    }
    

    // Update the screen
    
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);

    // Wait for user to close the window
    
    while(wait == 0 && close ==0){
    SDL_Event event;
      while(SDL_PollEvent(&event)){
        switch(event.type){
          case SDL_QUIT:
            close =1;
            break;
          
          default:
            break;
          
          case SDL_KEYDOWN:
            switch(event.key.keysym.sym){
              case SDLK_RIGHT:
                SDL_RenderCopy(renderer, texture, NULL, NULL);
    
    for(int y =0;y<45;y++){
    for(int i =0;i<90;i++){
    if(y%2){
      truc=10;
    }else{
      truc=0;
    }
    rectangle.x=10 + 17*i + truc;
    rectangle.y=10 + 14*y;
    if(strncmp(CELLalveole->type,JELLY,10)==0){
      SDL_RenderCopy(renderer, texturealveolejelly, NULL, &rectangle);
    }
    if(strncmp(CELLalveole->type,HONEY,10)==0){
      SDL_RenderCopy(renderer, texturealveolemiel, NULL, &rectangle);
    }
    if(strncmp(CELLalveole->type,EGG,10)==0){
      SDL_RenderCopy(renderer, texturealveoleegg, NULL, &rectangle);
    }
    if(strncmp(CELLalveole->type,DIRTY,10)==0){
      SDL_RenderCopy(renderer, texturealveoledirty, NULL, &rectangle);
    }
    if(strncmp(CELLalveole->type,EMPTY,10)==0){
      SDL_RenderCopy(renderer, texturealveole, NULL, &rectangle);
    }
    if(strncmp(CELLalveole->type,NOTMADE,10)==0){
      SDL_RenderCopy(renderer, texturealveolenotmade, NULL, &rectangle);
    }
    if(strncmp(CELLalveole->type,POLLEN,10)==0){
      SDL_RenderCopy(renderer, texturealveolepollen, NULL, &rectangle);
    }
    if(CELLalveole->next!=NULL){
      CELLalveole=CELLalveole->next;
    }else{
      if(selector<=8){
        selector+=1;
        CELLalveole=HIVE1->frames[selector]->first;
      }
    }
    
    
    }
    }
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
                //afficher next groupe of alveole
                break;
              case SDLK_TAB:
                wait=1;
                break;
              
              default:
                break;
              
            }
        }
      }
    }
    
    }

  


    // Clear the renderer
    //SDL_RenderClear(renderer);

    // Render the texture
    

    // Clean up resources
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(texturealveole);
    SDL_DestroyTexture(texturealveoledirty);
    SDL_DestroyTexture(texturealveoleegg);
    SDL_DestroyTexture(texturealveolejelly);
    SDL_DestroyTexture(texturealveolemiel);
    SDL_DestroyTexture(texturealveolenotmade);
    SDL_DestroyTexture(texturealveolepollen);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    
    return 0;
}
