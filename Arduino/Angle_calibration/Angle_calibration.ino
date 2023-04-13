#include <Adafruit_SSD1306.h>
#include <SoftwareSerial.h>

#define nombreDePixelsEnLargeur 128         // Taille de l'écran OLED, en pixel, au niveau de sa largeur
#define nombreDePixelsEnHauteur 32          // Taille de l'écran OLED, en pixel, au niveau de sa hauteur
#define brocheResetOLED         -1          // Reset de l'OLED partagé avec l'Arduino (d'où la valeur à -1, et non un numéro de pin)
#define adresseI2CecranOLED     0x3C        // Adresse de "mon" écran OLED sur le bus i2c (généralement égal à 0x3C ou 0x3D)

#define pinSW 2
  
Adafruit_SSD1306 ecranOLED(nombreDePixelsEnLargeur, nombreDePixelsEnHauteur, &Wire, brocheResetOLED);


// ----------------------------
// CAPTEUR --------------------
// ----------------------------
float VADC = 0.0;
float VCC = 5.0;
float R1 = 100000.0;
float R2 = 390.0;
float R3 = 100000.0;
float R5 = 10000.0;
float RS = 0.0;

int analogPin = A0;

// ----------------------------
// ENCODEUR ROTATOIRE ---------
// ----------------------------
// Rotary Encoder Module connections
const int PinSW=2;   // Rotary Encoder Switch

// Variables to debounce Rotary Encoder Switch button 
long TimeOfLastDebounceSwitch = 0;
int DelayofDebounceSwitch = 500;

bool switch_button = false;
bool prev_switch_button = false;

long angle_flat = 0;
long angle_up = 0;

int switch_counter = 0;

long angle = 0;

void switched() {   // set boolean value if switch button has been pushed or not
  if ((millis() - TimeOfLastDebounceSwitch) > DelayofDebounceSwitch) {    // debouncing
    if (switch_button){
      switch_button = false;
    }
    else {
      switch_button = true;
    }
  }
  TimeOfLastDebounceSwitch = millis();
}

void main_panel() {   // display on OLED panel
  ecranOLED.clearDisplay();
  ecranOLED.setCursor(0,1);
  if (switch_counter < 3){
    ecranOLED.drawRect(0, 0, 128,32, WHITE);
  }

  if (switch_counter == 0){
    ecranOLED.setCursor(12,2);
    ecranOLED.println("Please, press the");
    ecranOLED.setCursor(20,12);
    ecranOLED.println("push button to");
    ecranOLED.setCursor(12,22);
    ecranOLED.println("start calibration");

  }

  if (switch_counter == 1) {
    ecranOLED.setCursor(12,2);
    ecranOLED.println("Place sensor flat");
    ecranOLED.setCursor(23,11);
    ecranOLED.print("press when OK");
    ecranOLED.setCursor(16,22);
    ecranOLED.print("R = ");
    ecranOLED.print(RS);
    ecranOLED.print(" M ohm");
    ecranOLED.drawRect(10, 20, 108, 12, WHITE);
    angle_flat = RS;
    
  }

  if (switch_counter == 2) {
    angle_up = RS;
    ecranOLED.setCursor(18,2);
    ecranOLED.println("Place sensor up");
    ecranOLED.setCursor(23,11);
    ecranOLED.print("press when OK");
    ecranOLED.setCursor(16,22);
    ecranOLED.print("R = ");
    ecranOLED.print(RS);
    ecranOLED.print(" M ohm");
    ecranOLED.drawRect(10, 20, 108, 12, WHITE);
  }

  if (switch_counter == 3) {
    ecranOLED.print(" R_flat : ");
    ecranOLED.print(angle_flat);
    ecranOLED.println(" M ohm");
    ecranOLED.print(" R_up   : ");
    ecranOLED.print(angle_up);
    ecranOLED.println(" M ohm");

    angle = (angle_flat - RS) / (angle_flat - angle_up) * 180;
    if (angle > 180){angle = 180;}

    ecranOLED.print(" Angle  : ");
    ecranOLED.print(angle);
    ecranOLED.println(" deg");

    ecranOLED.print(" Res : ");
    ecranOLED.print(RS);
    ecranOLED.print(" M ohm");
    
  }

  if (switch_counter == 4){
    switch_counter = 0;
  }
  
  ecranOLED.display();
}

void setup() {
  Serial.begin(9600);

  ecranOLED.begin(SSD1306_SWITCHCAPVCC, adresseI2CecranOLED);
  ecranOLED.clearDisplay();                 // Effaçage de l'intégralité du buffer
  ecranOLED.setTextSize(1);                 // Taille des caractères 
  ecranOLED.setCursor(0, 0);                // Déplacement du curseur en postion (0,0)
  ecranOLED.setTextColor(SSD1306_WHITE);
  ecranOLED.print("gezrgez");

  pinMode(pinSW, INPUT_PULLUP); // Set the Switch pin to use Arduino PULLUP resistors
  attachInterrupt(digitalPinToInterrupt(pinSW), switched, CHANGE);      // attach interrupt for switch button
}

void loop() {
  VADC = analogRead(analogPin)*0.004882814;
  
  RS = (((1 + (R3/R2))*R1*(VCC/VADC)) - R1 - R5) * 0.000001; // Resistance in M ohm
  
  main_panel();

  prev_switch_button = switch_button;
    
  delay(50);
}
