/*

  Monitor Master Clock from input ByteStream...

  NOT WORKING: as 
    ?
    MIDI device not receiving
    
    TRY something with MIDI library.

*/


// define I/O pins
int pin_sensor   = 10;
int pin_led      = 13;


// define basic clock MESSAGE Bytes:
byte midi_start     = 0xfa;
byte midi_stop      = 0xfc;
byte midi_clock     = 0xf8;
byte midi_continue  = 0xfb;

// initlize MIDI control variables

// define timing variables
int baud = 31250; 


unsigned int bpm = 120;

unsigned int n_ppQ = 24;              // "frames" or "pulses" per "Beat"

//unsigned long ms_tB = 1000;            // time period of beat
unsigned long ms_tB   = 60*1000 / bpm;
unsigned long ms_tP = ms_tB / n_ppQ;   // time period per "frame"/"pulse"

int i_pulse = 0;

unsigned long ms_prev = 0;
unsigned long ms_now = millis(); // start checking time.


// DEFINE Functions:
int syncPulseHandler(int i){
  
  // send midi CLOCK TICK
  Serial.write(midi_clock);
  
  // HANDLE index of pulse w/in Quarter note BEAT
  if(i < n_ppQ / 2){
    //light high
    digitalWrite(pin_led, HIGH);
    
  }else{
    //light low
    digitalWrite(pin_led, LOW);
  }
  i++;    // iterate and reset:
  if(i > n_ppQ-1){
    i = 0;
  }
  
  return i;
}



// SETUP
void setup() { // put your setup code here, to run once:
  pinMode(pin_sensor, INPUT);
  pinMode(pin_sensor, OUTPUT);
  pinMode(pin_led, OUTPUT);
  Serial.begin(baud); // MIDI baud rate for 24 PPQ
  
  delay(500);
  Serial.write(midi_stop);
  delay(500);
  Serial.write(midi_start);
  
}




// MAIN LOOP
void loop() {
   // track time and react
  ms_now = millis();
  
  if(ms_now - ms_prev > ms_tP){
    ms_prev = ms_now;
  
   i_pulse = syncPulseHandler( i_pulse );   
  }

}// end MAIN Loop

