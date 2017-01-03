/*
 * Head's Up game for Tiva C
 * Sidak Manchanda
 * Veljko Dimic
 * SE101 project
 */

#include <delay.h>
#include <FillPat.h>
#include <LaunchPad.h>
#include <OrbitBoosterPackDefs.h>
#include <OrbitOled.h>
#include <OrbitOledChar.h>
#include <OrbitOledGrph.h>
#include <Wire.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#define Address 0x1D

//Change Settings
const unsigned long transitionTime =10000;
const unsigned long timeT = 30000;
const int minPlayers = 2;
const int maxPlayers = 5;

//Functions for Accelerometer 
void WireStart();
void WireRequestArray(int Addressess, uint8_t* buffer, uint8_t amount);
void WireWriteRegister(int Addressess, uint8_t reg, uint8_t value);
void accelVal(int val[]);

//Functions for OLED
void printInterface(int players, int isEdit);
void printPass(int player);
void printWin(int win[], int players);
void printPoint(int player);
void printNext(int player);
void OrbitSetOled();
void formattedWrite(const char s[]);
char *itoa(int i);

//Button pins
const int buttonLeft = PUSH1;
const int buttonRight = PUSH2;

const char *list[]={"ping pong", "snowball", "roof", "fly", "fang", "bicycle", "bear", "cape", "puppet", "piano", "lipstick", "salute", "hula hoop", "penguin", "banana peel", "whisper", "popsicle", "Frankenstein", "earthquake", "yo-yo", "road", "rain", "alarm clock", "dog", "leash", "chop", "pajamas", "slam", "dunk", "fiddle", "seashell", "jog", "seesaw", "nap", "cheerleader", "blind", "beg", "shopping", "cart", "Michael Jackson", "limbo", "newspaper", "twist", "rhinoceros", "cow", "tickle", "fetch", "violin", "cage", "cello", "braid", "skateboard", "stairs", "trumpet", "mop", "shovel", "money", "soap", "saddle", "wink", "tree", "Spider Man", "think", "peck", "windmill", "party", "dentist", "lawn mower", "softball", "wig", "stain", "cuff", "sunburn", "funny", "sheet", "hair", "dryer", "nightmare", "iPad", "shadow", "wax", "fog", "sip", "bathroom", "scale", "taxi", "pizza", "sand", "huddle", "cowboy", "ticket", "doghouse", "stiff", "knot", "president", "owl", "wrench", "story", "whisk", "quicksand", "spine", "chess", "artist", "vest", "gingerbread man", "spider", "web", "bobsled", "lung", "washing machine", "oar", "torch", "eraser", "mini", "blinds", "mouse trap", "swordfish", "jar", "cramp", "flamingo", "cast", "honk", "mirror", "business trip", "chalk", "gym", "volcano", "doorbell", "witch", "bats", "costume", "autumn", "skeleton", "sweets", "afraid", "scarecrow", "candy", "Frankenstein", "candy", "corn", "hay", "ride", "boo", "lollipop", "dark", "ghost", "trick or treat", "naruto", "scary", "jack-o-lantern", "haunted", "house", "ghost", "story", "spider", "werewolf", "scary", "movies", "graveyard", "spells", "pumpkin", "vampire", "marshmallow", "zombie", "secret", "lab", "mad", "scientist", "monster", "chocolate", "spider", "web", "black", "Dracula", "spooks", "grave", "creepy", "Monster", "Mash", "corn", "maze", "candle", "crypt", "apple", "cider", "frightened", "fortune", "teller", "Igor", "pumpkin", "seeds", "horror", "goody", "bag", "ghoul", "coffin", "nighttime", "Ghostbusters", "goblin", "spooky", "lantern", "gypsy", "family", "cornucopia", "harvest", "football", "pie", "cooking", "eating", "corn", "table", "setting", "green", "bean", "casserole", "gravy", "cranberry", "tablecloth", "food", "drives", "gratitude", "candlesticks", "setting", "table", "sweet", "corn", "pilgrims", "apple", "pie", "squash", "thankful", "Plymouth", "blessings", "festival", "parades", "pecan", "pie", "resting", "praise", "grateful", "holiday", "survive", "winter", "New", "England", "mashed", "potatoes", "celebration", "rolls", "baking", "Thanksgiving", "dinner", "sweet", "potatoes", "stuffing", "football", "games", "creamed", "corn", "turkey", "pardoning", "turkey", "Thursday", "pumpkin", "pie", "dumplings", "Macy's", "Day", "Parade", "watching", "TV", "Native", "American", "Turkey", "Bowl", "thanks", "winter", "squash", "venison", "rejoice", "parade", "floats", "cranberry", "sauce", "travel", "yams", "scarecrow", "sweater", "corn", "November", "quarterback", "crunching", "leaves", "jacket", "colds", "frost", "migration", "football", "yellow", "candy", "changing", "colors", "raking", "leaves", "apple", "cider", "orange", "crisp", "autumn", "school", "supplies", "scarves", "cool", "soup", "leaves", "hiking", "soccer", "foliage", "rake", "back", "school", "hot", "chocolate", "backpack", "sweatshirts", "harvest", "pumpkin", "apple", "pie", "apples", "hayride", "colored", "leaves", "chicken", "noodle", "soup", "chill", "wind", "lunch", "box", "crow", "maple", "syrup", "decorations", "September", "candy", "corn", "bonfire", "Egypt", "skiing", "Bahamas", "luggage", "Europe", "beach", "house", "packing", "camping", "rainforest", "Colorado", "river", "airport", "summer", "Canada", "sunscreen", "Disneyland", "passport", "Arizona", "Aruba", "sightseeing", "resort", "water", "park", "customs", "America", "Africa", "tourist", "island", "lake", "sunny", "weather", "airport", "security", "cruise", "ship", "Mexico", "sleeping", "bag", "hotel", "mountain", "biking", "Paris", "road", "trip", "Bermuda", "Jamaica", "Spain", "snowboarding", "map", "trains", "Alaska", "camera", "theme", "park", "national", "park", "tour", "guide", "relax", "Delaware", "airplane", "bug", "spray", "scenery", "layover", "Are", "we", "there", "yet?", "fanny", "pack", "river", "rafting", "beach", "ball", "kayak", "movies", "hiking", "stroll", "surfboard", "time", "off", "swimming", "pool", "bird", "watching", "Broadway", "Universal", "Studios", "binoculars", "shopping", "Rome", "Maine", "bicycle", "snow", "cone", "vacation", "day", "boardwalk", "Six", "Flags", "airline", "lazy", "river", "Florida", "Texas", "South", "Dakota", "Istanbul", "Grand", "Canyon", "June", "holiday", "safari", "Las", "Vegas", "suitcase", "Turkey", "hang", "glider", "first", "class", "condo", "honeymoon", "scuba", "diving", "China", "Africa", "Italy", "Hawaii", "family", "reunion", "Scottland", "London", "Four", "Corners", "backpacking", "Ireland", "California", "Switzerland", "July", "Tokyo", "Mount", "Rushmore", "coral", "reef", "summer", "France", "San", "Francisco", "Athens", "Vienna", "England", "Washington", "D.C.", "money", "belt", "Los", "Angeles", "Boston", "party", "Egypt", "skiing", "Bahamas", "luggage", "Europe", "beach", "house", "packing", "camping", "rainforest", "Colorado", "river", "airport", "summer", "Canada", "sunscreen", "Disneyland", "passport", "Arizona", "Aruba", "sightseeing", "resort", "water", "park", "customs", "America", "Africa", "tourist", "island", "lake", "sunny", "weather", "airport", "security", "cruise", "ship", "Mexico", "sleeping", "bag", "hotel", "mountain", "biking", "Paris", "road", "trip", "Bermuda", "Jamaica", "Spain", "snowboarding", "map", "trains", "Alaska", "camera", "theme", "park", "national", "park", "tour", "guide", "relax", "Delaware", "airplane", "bug", "spray", "scenery", "layover", "Are", "we", "there", "yet?", "fanny", "pack", "river", "rafting", "beach", "ball", "kayak", "movies", "hiking", "stroll", "surfboard", "time", "off", "swimming", "pool", "bird", "watching", "Broadway", "Universal", "Studios", "binoculars", "shopping", "Rome", "Maine", "bicycle", "snow", "cone", "vacation", "day", "boardwalk", "Six Flags", "airline", "lazy", "river", "Florida", "Texas", "South", "Istanbul", "Grand Canyon", "June", "holiday", "safari", "Las", "Vegas", "suitcase", "Turkey", "hang", "glider", "first", "class", "condo", "honeymoon", "scuba", "diving", "China", "Africa", "Italy", "Hawaii", "family", "reunion", "Scottland", "London", "Four Corners", "backpacking", "Ireland", "California", "Switzerland", "July", "Tokyo", "Mount Rushmore", "coral", "reef", "summer", "France", "San Francisco", "Athens", "Vienna", "England", "Washington D.C.", "money", "belt", "Los Angeles", "Boston", "party"};

struct player{
  int score;  
};

/*
 * On startup of board initiate all settings
 */
void setup() {
  periphEnable();
  buttonConfig();
  switchConfig();
  LEDConfig();
  boosterConfig();
  accelerometerConfig();
  buttonSet(buttonLeft);
  buttonSet(buttonRight);
  OrbitOledInit();

  OrbitOledClear();
  OrbitOledMoveTo(0,0);
  OrbitOledSetCursor(0,0);
    
  Serial.begin(9600);
}

/*
 * Repeat the game
 */
void loop() { 
  newGame(interface());
}

/*
 * Create a new game
 * players: number of players
 */
void newGame(int players){ 
  struct player p[players];
  for (int i = 0; i < players; i ++){
    p[i].score = 0;
  }
  for(int x =0; x< players; x++){ 
    unsigned long ST = millis();//get the time  
    while ((millis()-ST)<timeT){
      int windex = newWord();
      int tag = listen(ST,windex);
      if(tag ==1){
        addPoint(p,x);
      }
      if(tag == -1){
        printPass(x+1);
        continue;
      }
    }
    if(x != (players-1)){//if not after last player has gone
      transition(x+2); //gives time for transition to users
    }
    
  }
  winner(p, players);  
}

/*
 * Generate a random index for the word to be chosen
 */
int newWord(){
  srand(millis());
  int randc = rand() % 665;
  return randc;
}

/*
 * Interface to choose the number of players and start the game
 * returns: number of players
 */
int interface(){//fill in with code for the interface 
  int p = minPlayers;
  int first = 1;

  printInterface(p, first--);
  
  while (digitalRead(buttonRight) == HIGH){
    if (digitalRead(buttonLeft) == LOW){
      if (p == maxPlayers){
        p = minPlayers;
      }
      else{
        p++;
      }
      printInterface(p, first);
      delay(300);
    }
  }
  OrbitOledClear();
  return p;
}

/*
 * Listens for an accelerometer action for a pass or point
 * ST: Start time
 * windex: index of the word currently chosen
 * 
 * returns: -1 for a pass, 1 for a correct
 */
int listen(unsigned long ST, int windex){
  formattedWrite(list[windex]);
  
  int correct =0;
  while((millis()-ST)<timeT){//make sure not gone overtime
      delay(300);
      int val[] = {0,0,0};
      accelVal(val);
      char l = Serial.read();

      if(val[0] < -200 || val[0]>200){//replace with corect == -1 (if the user passes) after
        delay(1000);
        return -1;
      }
      if(val[1]<0){//replace with corect ==1 after
        delay(1000);
        return 1;
      }  
  }
  return 0;
}

/*
 * adds point to player x
 * p: array of player scores
 * x: player to receive point
 */
void addPoint(struct player p[], int x){
  p[x].score+=1;
  printPoint(x+1);
}

/*
 * Transitions to next player
 * p: player to transition to
 */
void transition(int p){
  printNext(p);
  delay(transitionTime);//give 10 seconds for the transition
  
}

/*
 * Display the results of the game
 * p: array of player scores
 * players: number of players
 */
void winner(struct player p[], int players){
  int top = p[0].score;
  int win[players];
  clearWin(win,players);  
  win[0]=1;
  for(int x =1; x< players; x++){
    if(p[x].score > top){
      clearWin(win,players);
      top= p[x].score;
      win[x] = 1;
      continue;
    }
    if(p[x].score == top){
      win[x]=1;
    } 
    
  }
  printWin(win, players);
  delay(25000);
}

/*
 * Reset winners
 * win: array of winners
 * players: number of players
 */
void clearWin(int win[], int players){
  for(int x =0; x<players; x++){
    win[x]=0;
  }
}


/*
 * Initialization functions
 */
 
void periphEnable(){
  SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOA );
  SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOB );
  SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOC );
  SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOD );
  SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOE );
  SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOF );
}

void switchConfig(){
  GPIOPadConfigSet(SWTPort, SWT1 | SWT2, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);
  GPIOPinTypeGPIOInput(SWTPort, SWT1 | SWT2);
}

void buttonConfig(){
  GPIOPadConfigSet(BTN1Port, BTN1, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);
  GPIOPadConfigSet(BTN2Port, BTN2, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);

  GPIOPinTypeGPIOInput(BTN1Port, BTN1);
  GPIOPinTypeGPIOInput(BTN2Port, BTN2);
}

void LEDConfig(){
  GPIOPadConfigSet(LED1Port, LED1, GPIO_STRENGTH_8MA_SC, GPIO_PIN_TYPE_STD);
  GPIOPadConfigSet(LED2Port, LED2, GPIO_STRENGTH_8MA_SC, GPIO_PIN_TYPE_STD);
  GPIOPadConfigSet(LED3Port, LED3, GPIO_STRENGTH_8MA_SC, GPIO_PIN_TYPE_STD);
  GPIOPadConfigSet(LED4Port, LED4, GPIO_STRENGTH_8MA_SC, GPIO_PIN_TYPE_STD);
  GPIOPinTypeGPIOOutput(LED1Port, LED1);
  GPIOPinTypeGPIOOutput(LED2Port, LED2);
  GPIOPinTypeGPIOOutput(LED3Port, LED3);
  GPIOPinTypeGPIOOutput(LED4Port, LED4);
  
}

void boosterConfig(){
  SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
  GPIOPinTypeADC(AINPort, AIN);
  ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);
  ADCSequenceStepConfigure(ADC0_BASE, 0, 0, ADC_CTL_IE | ADC_CTL_END | ADC_CTL_CH0);
  ADCSequenceEnable(ADC0_BASE, 0);
}

void accelerometerConfig(){
  WireStart();
  WireWriteRegister(Address, 0x2C, 0x0A);  
  WireWriteRegister(Address, 0x2D, 0x08);  
  WireWriteRegister(Address, 0x31, 0x08);
}

void buttonSet(const int b){
  pinMode(b, INPUT_PULLUP);
}
