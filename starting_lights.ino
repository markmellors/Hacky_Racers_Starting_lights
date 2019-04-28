
 
int inByte = 0;         // incoming serial byte
int inChar = 0;
bool one = false;
bool two = false;
bool three = false;
bool four = false;
bool five = false;


// the setup function runs once when you press reset or power the board
void setup() {
  randomSeed(analogRead(0));
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  for (int pin = 2; pin < 7; pin++) {
    digitalWrite(pin, HIGH);
  } 
    // initialize serial:
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  if (Serial.available() > 0) {
    // get incoming byte:
    inByte = Serial.read();
    inChar = char(inByte);
    switch (inChar) {
      case 49: //ascii 1
        one = false;
        break;
      case 81: //ascii Q
        one = true;
        break;
      case 50: //ascii 2
        two = false;
        break;
      case 87: //ascii W
        two = true;
        break;
      case 51: //ascii 3
        three = false;
        start_sequence();
        break;
      case 69: //ascii E
        three = true;
        break;
      case 52: //ascii 4
        four = false;
        break;
      case 82: //ascii R
        four = true;
        break;
      case 39: //ascii ' (quote)
        flash_all(2);
        Serial.println("R");
        delay(2000);
        break;
      case 85: //ascii U
        blink(2);
        blink(3);
        blink(4);
        blink(5);
        blink(6);
        delay(2000);
        break;
      case 89: //ascii Y
        blink(6);
        blink(5);
        blink(4);
        blink(3);
        blink(2);
        delay(2000);
        break;
      default:
        int decades = inChar % 10;
        flash_all(decades);
        delay(1000);
        int units = inChar-decades*10;
        flash_all(units);
        delay(1000);
        break;
    }
    set_light(2, one);
    set_light(3, two);
    set_light(4, three);
    set_light(5, four);
  }
}

void set_light(int pin, bool state){
  if (state){
    digitalWrite(pin, true);
  }
  else{
      digitalWrite(pin, false);
  }
}

void flash_all(int times){
  for (int loop = 0; loop<times; loop++){
    for (int pin = 2; pin < 7; pin++) {
      digitalWrite(pin, LOW);
    }
    delay(200); 
    for (int pin = 2; pin < 7; pin++) {
      digitalWrite(pin, HIGH);
    }
    delay(200);
  }
}

void blink(int pin){
  digitalWrite(pin, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(200);              // wait for a second
  digitalWrite(pin, HIGH);    // turn the LED off by making the voltage LOW
} 

void start_sequence(){
  bool timing_started = false;
  one = true;
  two = true;
  three = true;
  four = true;
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(2, LOW);
  if (not timing_started){
    timing_started = clear_buffer(); 
  }
  delay(1000);
  if (not timing_started){
    timing_started = clear_buffer(); 
  }
  digitalWrite(3, LOW);
  delay(1000);
  if (not timing_started){
    timing_started = clear_buffer(); 
  }
  digitalWrite(4, LOW);
  delay(1000);
  if (not timing_started){
    timing_started = clear_buffer(); 
  }
  digitalWrite(5, LOW);
  delay(1000);
  if (not timing_started){
    timing_started = clear_buffer(); 
  }
  digitalWrite(6, LOW);
  delay(1000);
  if (not timing_started){
    timing_started = clear_buffer(); 
  }
  delay(random(1));
  while (not timing_started){
    timing_started = clear_buffer();
  }
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  delay(1000);
  clear_buffer();
}

bool clear_buffer(){
    bool start_received = false;
    while (Serial.available() > 0) {
    inByte = Serial.read();
    if (char(inByte) == 39){
      Serial.println("R");
    } else if (char(inByte) == 49){
      start_received = true;
    }
  }
  return start_received;
}
