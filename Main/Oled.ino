/*
 * OLED display functions for Head's Up game
 */
#include <FillPat.h>
#include <LaunchPad.h>
#include <OrbitBoosterPackDefs.h>
#include <OrbitOled.h>
#include <OrbitOledChar.h>
#include <OrbitOledGrph.h>
#include <string.h>
#include <stdlib.h>


/*
 * Prints the interface
 * players: number of players
 * isEdit: Checks if the interface has not been displayed yet or if it is being edited
 */
void printInterface(int players, int isNew){
  if (isNew){
    OrbitOledClear();
    OrbitOledSetCursor(0,0);
    OrbitOledPutString("Players:");
  
    OrbitOledSetCursor(9,0);
    OrbitOledPutString(itoa(players));
  
    OrbitOledSetCursor(0,1);
    OrbitOledPutString("Change");
  
    OrbitOledSetCursor(11,1);
    OrbitOledPutString("Begin");
  
    OrbitOledSetCursor(0,3);
    OrbitOledPutString("V");
  
    OrbitOledSetCursor(15,3);
    OrbitOledPutString("V");
  }
  else{
    OrbitOledSetCursor(9,0);
    OrbitOledPutString(itoa(players));
    
  }
}

/*
 * prints the pass screen
 * player: The player that is next
 */
void printPass(int player){
  OrbitOledClear();
  OrbitOledSetCursor(0,0);
  OrbitOledPutString("Player   passed");
  OrbitOledSetCursor(7,0);
  OrbitOledPutString(itoa(player));
  
  Serial.print("Player ");
  Serial.print(player);
  Serial.print(" passed\n");
}

/*
 * prints winners
 * win: Array of winners
 * players: number of players
 */
void printWin(int win[], int players){
  OrbitOledClear();
  OrbitOledSetCursor(0,0);
  OrbitOledPutString("Player(s) ");
  Serial.print("Player(s) ");
  for(int x =0; x< players; x++){
    if(win[x] ==1){
      OrbitOledPutString(itoa(x+1));
      OrbitOledPutString(" ");
      Serial.print(x+1);
      Serial.print(" ");
    }
  }
  OrbitOledSetCursor(0,1);
  OrbitOledPutString("Won!");
  Serial.print("Won");
}

/*
 * prints an increase in points
 * player: player who received a point
 */
void printPoint(int player){
  OrbitOledClear();
  OrbitOledSetCursor(0,0);
  OrbitOledPutString("Player   got a");
  OrbitOledSetCursor(0,1);
  OrbitOledPutString("point");
  OrbitOledSetCursor(7,0);
  OrbitOledPutString(itoa(player));
  
  Serial.print("Player ");
  Serial.print(player);
  Serial.print(" got a point\n");
}

/*
 * prints the next player up
 * player: next player up
 */
void printNext(int player){
  OrbitOledClear();
  OrbitOledSetCursor(0,0);
  OrbitOledPutString("Player   is next");
  OrbitOledSetCursor(7,0);
  OrbitOledPutString(itoa(player));
  
  Serial.print("Player ");
  Serial.print(player);
  Serial.print(" is next\n");
}


/*
 * Prints generated words to the OLED screen
 * s: word to be printed
 */
void formattedWrite(const char s[]){
  int spaceIndex = 0;
  for (int i = 0; i < strlen(s); i ++){
    if (s[i] == ' '){
      spaceIndex = i;
      break;
    }
  }
  if (spaceIndex>0){
    char line1[spaceIndex+1];
    char line2[strlen(s)-spaceIndex];
    for (int j = 0; j < spaceIndex; j++){
      line1[j] = s[j];
    }
    line1[spaceIndex+1] = '\0';
    for (int j = 0; j < strlen(s)-spaceIndex-1; j++){
      line2[j] = s[spaceIndex + 1 + j];
    }
    line2[strlen(s)-spaceIndex] = '\0';

    OrbitOledSetCursor(0,2);
    OrbitOledPutString(line1);
    OrbitOledSetCursor(0,3);
    OrbitOledPutString(line2);
  }
  else{
    char temp[strlen(s)+1];
    strcpy(temp, s);
    OrbitOledSetCursor(0,3);
    OrbitOledPutString(temp);
  }
  Serial.print(s);
  Serial.print("\n");
}


/*
 * Converts integer to string
 * i: number to be converted
 * returns: string of converted integer
 */
char *itoa(int i){
  char *numbers = "0123456789";
  char *ret;
  int l = 0;
  int remainder = i;
  while (remainder >0){
    l++;
    remainder /= 10;
  }
  ret = (char*)malloc(sizeof(char)*(l+1));
  remainder = i;
  for (int j = l - 1; j >= 0; j --){
    ret[j] = numbers[remainder%10];
    remainder /= 10;
  }
  ret[l] = '\0';
  return ret;
}
