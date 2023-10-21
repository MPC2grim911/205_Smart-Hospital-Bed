
/*********************************************************************************************
                        WELCOME TO THE SMARTEST "SMART BED"!
                        The Revolution happening in numerous hospitals worldwide
*********************************************************************************************/

#define Ppin 26   //Analog input of pulsioximeter
#define LED 12    //LED pin
int pulse;       //Sensor output. Range: (0,1024)
#define thr 2777  //If higher, BEAT
int BPM;         //Beats per minute
#define W 10        //Window for LP filter
int pulses[W];   //Last W readings
int n=0;         //Reading index


/*                        SET-UP
*********************************************************************************************/
void setup() {
  
   //PINOUT SET-UP
   pinMode(LED,OUTPUT);         
   Serial.begin(9600); 
   Serial.println(n);
   for(int i=0; i<W; i++){
      pulses[i]=0;
      //Serial.print(pulses[i]);Serial.print(" | ");
   }
   //Serial.println("");
}




/*                        MAIN LOOP
*********************************************************************************************/
void loop() {
  
  /* PULSE SENOR READING
  --------------------------------------*/
  pulse = analogRead(Ppin);  
  
   if(pulse > thr){                        
     digitalWrite(LED,HIGH); // BEAT!
   } else {
     digitalWrite(LED,LOW);  //BACJGROUND NOISE              
   }


  /* SMOOTHING FILTER
   *  Takes into account a window of [W] values
  --------------------------------------*/
   pulses[n%10]=pulse;
   //Serial.println("");Serial.println(n);
   int pulse_smooth=0;
   for(int i=0; i<W; i++){
      //Serial.print(pulses[i]);Serial.print(" | ");
      pulse_smooth+=pulses[i];
   }
   n++;
   
   delay(10);

   pulse_smooth=pulse_smooth/W;
   //Serial.print(">> Pulse reading: ");
   Serial.println(pulse_smooth);   
                       
}
