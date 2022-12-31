// set pin numbers
const int buttonPin1 = 15;  // the number of the pushbutton pin 
const int buttonPin2 = 2;
const int buttonPin3 = 4;
const int ledPin1 =  5;    // the number of the LED pin
const int ledPin2 =  18;
const int ledPin3 =  19;
int button1, button2, button3;
// variable for storing the pushbutton status 
int buttonState = 0;
void setup() {
Serial.begin(115200);  
// initialize the pushbutton pin as an input 
pinMode(buttonPin1, INPUT);
pinMode(buttonPin2, INPUT);
pinMode(buttonPin3, INPUT);
// initialize the LED pin as an output 
pinMode(ledPin1, OUTPUT);
pinMode(ledPin2, OUTPUT);
pinMode(ledPin3, OUTPUT);
}
void loop() {
// read the state of the pushbutton value 
button1 = digitalRead(buttonPin1); 
button2 = digitalRead(buttonPin2); 
button3 = digitalRead(buttonPin3); 
// check if the pushbutton is pressed. 
// if it is, the buttonState is HIGH 
if (button1 == HIGH) {
    digitalWrite(ledPin1, HIGH);
}  else if (button2 == HIGH){
    digitalWrite(ledPin2, HIGH);
    delay(500);
    digitalWrite(ledPin2, LOW);
    delay(500);
} else if (button3 == HIGH) {
    digitalWrite(ledPin1, HIGH);
    delay(500);
    digitalWrite(ledPin1, LOW);
    delay(500);
    digitalWrite(ledPin2, HIGH);
    delay(500);
    digitalWrite(ledPin2, LOW);
    delay(500);
    digitalWrite(ledPin3, HIGH);
    delay(500);
    digitalWrite(ledPin3, LOW);
    delay(500);
}
}
