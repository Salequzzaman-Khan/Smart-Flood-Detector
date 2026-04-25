// include the library code: 
#include <LiquidCrystal_I2C.h>

//initialise the library with the numbers of the interface pins
 
LiquidCrystal_I2C lcd(0x27, 16, 2); 
#include <Adafruit_BMP085.h>

int value = 0;  // holds the value of water sensor

const  int trigger=6; // Ultrasonic Sensor pin
const  int echo=7; // Ultrasonic Sensor  pin
float  distance; // Ultrasonic Sensor 
float dist_inches; // Ultrasonic Sensor 


int buzzer = 8; // buzzer pin

// Use it as bmp
Adafruit_BMP085 bmp;


void setup() {
  

  // lcd initial
  lcd.init();
  lcd.backlight();
  
  
  // set up the LCD's number of columns and rows: 
  Serial.begin(9600);
  lcd.begin(16, 2); 

  pinMode(trigger,OUTPUT);
  pinMode(echo,INPUT);

  // buzzer output
  pinMode(8, OUTPUT); 


  //check BmP starts or not
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP180 sensor, check wiring!");
    while (1) {}
    }
  } 
  
void loop() {
  
    
     
  //Read data from analog pin and store it to resval variable from water Sensor
  value = analogRead(A0); 
  
  // Clears the trigPin condition 
  digitalWrite(trigger,LOW);
  delayMicroseconds(5);
  
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigger,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger,LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  distance=pulseIn(echo,HIGH);
  
  // Calculating the distance
  distance=distance*0.0001657;
  dist_inches=distance*39.37;
  Serial.println(dist_inches);

  // water sensor measure start  
  if (value<=37){
    lcd.setCursor(0,0);   
    lcd.print("   No Flood     ");
    lcd.setCursor(0, 1);
    lcd.print("                     ");
    delay(2000);
  }
  else if (value >50 && value<=650){ 
    Serial.println(value);
    lcd.setCursor(0,0);   
    lcd.print("   WaterLevel   ");
    lcd.setCursor(0, 1);
    lcd.print("     Rising       ");
    delay(2000);
    
    
  }
  
  else if (value>650){ 
    Serial.println(value);
    if (dist_inches<8){
      
      digitalWrite(buzzer, HIGH); 
      delay(1000);
     
      noTone(buzzer);     // Stop sound...
      delay(100);}
     
    
    Serial.print("Distance: ");
    Serial.print(dist_inches);
    
    //Serial.println(" inch");
    lcd.setCursor(0, 0); 
    lcd.print("    Warning !    ");
    lcd.setCursor(0, 1);
    lcd.print("Flood Detect");
    delay(2000);
    
     
  }

   

  
  
  // for monitoring  perpouse
  Serial.print("Temperature = ");
  Serial.print(bmp.readTemperature());
  Serial.println(" *C");
    
  Serial.print("Pressure = ");
  Serial.print(bmp.readPressure());
  Serial.println(" Pa");
  //------------------------------ 
    


  Serial.println();
  delay(1000);

  // BMP working starts
  if (bmp.readPressure()>100850){
    lcd.setCursor(0,0);
    lcd.print("Heavy Rainfall");
    lcd.setCursor(0,1);
    lcd.print("     Alert!       ");
    delay(3000);}
}
