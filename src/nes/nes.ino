// Refer to this document page 53 for int/key correspondance :
// http://www.usb.org/developers/devclass_docs/Hut1_11.pdf

const int AKey = 27;         // X
const int BKey = 6;          // C
const int SELECTKey = 25;    // V
const int STARTKey = 40;     // ENTER
const int UPKey = 82;        // UP ARROW
const int DOWNKey = 81;      // DOWN ARROW
const int LEFTKey = 80;      // LEFT ARROW
const int RIGHTKey = 79;     // RIGHT ARROW

///////////////////////////////

const int latch = 2;
const int clock = 3;
const int data = 4;

uint8_t buf[8] = {
  0 }; 	/* Keyboard report buffer */

boolean A, B, SELECT, START, UP, DOWN, LEFT, RIGHT;
boolean APressed, AReleased;
boolean BPressed, BReleased;
boolean SELECTPressed, SELECTReleased;
boolean STARTPressed, STARTReleased;
boolean UPPressed, UPReleased;
boolean DOWNPressed, DOWNReleased;
boolean LEFTPressed, LEFTReleased;
boolean RIGHTPressed, RIGHTReleased;

int ASlot = 1;
int BSlot = 1;
int SELECTSlot = 1;
int STARTSlot = 1;
int UPSlot = 1;
int DOWNSlot = 1;
int LEFTSlot = 1;
int RIGHTSlot = 1;

void setup() {
  A = B = SELECT = START = UP = DOWN = LEFT = RIGHT = false;
  
  Serial.begin(9600);
  pinMode(latch, OUTPUT);
  pinMode(clock, OUTPUT);
  pinMode(data, INPUT);
  
  digitalWrite(latch,HIGH);
  digitalWrite(clock,HIGH);
}

byte controllerRead() {
  byte controller_data = 0;
  digitalWrite(latch,LOW);
  digitalWrite(clock,LOW);
  
  digitalWrite(latch,HIGH);
  delayMicroseconds(2);
  digitalWrite(latch,LOW);
  
  controller_data = digitalRead(data);
  for (int i = 1; i <= 7; i++) {
    digitalWrite(clock, HIGH);
    delayMicroseconds(2);
    controller_data = controller_data << 1;
    controller_data = controller_data + digitalRead(data);
    delayMicroseconds(4);
    digitalWrite(clock, LOW);
  }
  return 255 - controller_data;
}

void updateControllerVars(byte controller_data) {
  
  APressed = AReleased = false;
  BPressed = BReleased = false;
  SELECTPressed = SELECTReleased = false;
  STARTPressed = STARTReleased = false;
  UPPressed = UPReleased = false;
  DOWNPressed = DOWNReleased = false;
  LEFTPressed = LEFTReleased = false;
  RIGHTPressed = RIGHTReleased = false;
  
  if (controller_data & B10000000) {
    if (!A) APressed = true;
    A = true;
  } else {
    if (A) AReleased = true;
    A = false;
  }
  
  if (controller_data & B01000000) {
    if (!B) BPressed = true;
    B = true;
  } else {
    if (B) BReleased = true;
    B = false;
  }
  
  if (controller_data & B00100000) {
    if (!SELECT) SELECTPressed = true;
    SELECT = true;
  } else {
    if (SELECT) SELECTReleased = true;
    SELECT = false;
  }
  
  if (controller_data & B00010000) {
    if (!START) STARTPressed = true;
    START = true;
  } else {
    if (START) STARTReleased = true;
    START = false;
  }
  
  if (controller_data & B00001000 ) {
    if (!UP) UPPressed = true;
    UP = true;
  } else {
    if (UP) UPReleased = true;
    UP = false;
  }
  
  if (controller_data & B00000100 ) {
    if (!DOWN) DOWNPressed = true;
    DOWN = true;
  } else {
    if (DOWN) DOWNReleased = true;
    DOWN = false;
  }
  
  if (controller_data & B00000010 ) {
    if (!LEFT) LEFTPressed = true;
    LEFT = true;
  } else {
    if (LEFT) LEFTReleased = true;
    LEFT = false;
  }
  
  if (controller_data & B00000001 ) {
    if (!RIGHT) RIGHTPressed = true;
    RIGHT = true;
  } else {
    if (RIGHT) RIGHTReleased = true;
    RIGHT = false;
  }
}



void loop() {
  byte controller_data = controllerRead();
  updateControllerVars(controller_data);
  
  // A ======
  if (APressed) {
    ASlot = getFreeSlot();
    buf[ASlot] = AKey;  
    Serial.write(buf, 8);	// Send keypress
  }
  
  if (AReleased) {
    buf[ASlot] = 0;
    Serial.write(buf, 8);	// Send keyrelease
  }
  
  // B ======
  if (BPressed) {
    BSlot = getFreeSlot();
    buf[BSlot] = BKey;  
    Serial.write(buf, 8);	// Send keypress
  }
  
  if (BReleased) {
    buf[BSlot] = 0;
    Serial.write(buf, 8);	// Send keyrelease
  }
  
  // SELECT ======
  if (SELECTPressed) {
    SELECTSlot = getFreeSlot();
    buf[SELECTSlot] = SELECTKey;  
    Serial.write(buf, 8);	// Send keypress
  }
  
  if (SELECTReleased) {
    buf[SELECTSlot] = 0;
    Serial.write(buf, 8);	// Send keyrelease
  }
  
  // START ======
  if (STARTPressed) {
    STARTSlot = getFreeSlot();
    buf[STARTSlot] = STARTKey;  
    Serial.write(buf, 8);	// Send keypress
  }
  
  if (STARTReleased) {
    buf[STARTSlot] = 0;
    Serial.write(buf, 8);	// Send keyrelease
  }
  
  // UP ======
  if (UPPressed) {
    UPSlot = getFreeSlot();
    buf[UPSlot] = UPKey;  
    Serial.write(buf, 8);	// Send keypress
  }
  
  if (UPReleased) {
    buf[UPSlot] = 0;
    Serial.write(buf, 8);	// Send keyrelease
  }
  
  // DOWN ======
  if (DOWNPressed) {
    DOWNSlot = getFreeSlot();
    buf[DOWNSlot] = DOWNKey;  
    Serial.write(buf, 8);	// Send keypress
  }
  
  if (DOWNReleased) {
    buf[DOWNSlot] = 0;
    Serial.write(buf, 8);	// Send keyrelease
  }
  
  // LEFT ======
  if (LEFTPressed) {
    LEFTSlot = getFreeSlot();
    buf[LEFTSlot] = LEFTKey;  
    Serial.write(buf, 8);	// Send keypress
  }
  
  if (LEFTReleased) {
    buf[LEFTSlot] = 0;
    Serial.write(buf, 8);	// Send keyrelease
  }
  
  // RIGHT ======
  if (RIGHTPressed) {
    RIGHTSlot = getFreeSlot();
    buf[RIGHTSlot] = RIGHTKey;  
    Serial.write(buf, 8);	// Send keypress
  }
  
  if (RIGHTReleased) {
    buf[RIGHTSlot] = 0;
    Serial.write(buf, 8);	// Send keyrelease
  }
}

int getFreeSlot() {
  for (int i = 2; i < 9; i++) {
    if (buf[i] == 0) return i;
  }
}
