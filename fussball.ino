#include <TM1638lite.h>

TM1638lite tm(4, 7, 8);
int sensorA = 9;
int sensorB = 10;

int a = 0;
int b = 0;
unsigned long lastDebounceTimeA = 0;
unsigned long lastDebounceTimeB = 0;
unsigned long debounceDelay = 50;

void setup() {
    Serial.begin(9600);
    tm.reset();
    tm.displayText("00000000");
    delay(3000);
    pinMode(sensorA, INPUT);
    pinMode(sensorB, INPUT);
    doLEDs(0xFF, "a");
    doLEDs(0xFF, "b");
}

void loop() {
    lerSensores();
    atualizarDisplay();
    final();
    delay(10);
}



void final(){
  if(a + b >= 9 ){
    a= 0;
    b=0;
  }
}

void lerSensores() {
    int leituraA = digitalRead(sensorA);
    int leituraB = digitalRead(sensorB);



    if (leituraA == LOW) {
        a++;
        
        piscarLeds("a");
    }

    if (leituraB == LOW) {
        b++;
        lastDebounceTimeB = millis();
        piscarLeds("b");
    }
}

void atualizarDisplay() {
    char displayBuffer[8]; 
    sprintf(displayBuffer, "%03d%04d", a, b); 
    tm.displayText(displayBuffer); 
}

void piscarLeds(String local) {
    for (int i = 0; i < 3; i++) {
        doLEDs(0xFF, local);
        delay(200);
        doLEDs(0x00, local);
        delay(200);
        doLEDs(0xFF, local);
        
    }
}

void doLEDs(uint8_t value, String local) {
    if(local == "a"){
      for (uint8_t position = 0; position < 4; position++) {
        tm.setLED(position, value & 1);
        value = value >> 1;
    }
    }
    else{
      for (uint8_t position = 4; position < 8; position++) {
        tm.setLED(position, value & 1);
        value = value >> 1;
    
    }
    }
    
}


