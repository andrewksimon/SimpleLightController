//This code was written by Andrew. 
//This project utilizes a relay board to control some sort of load. In this case, it is a 12v LED Strips. 
//This code was originally intended to run on an Arduino Nano. 
//Change

//Preprocessor directives.
#include <Arduino.h>

//Variable Declarations. 
int opt1 = 2;
int opt2 = 4;//3
int opt3 = 5;//4
int opt4 = 3;//5
int relay1 = 7;
int relay2 = 12;
//int relay1 = 10; //Optional 
//int relay2 = 11; //Optional

//This array will store the previous state values. 
bool opt[4];

//Main Driver function. 
void setup() {

	Serial.begin(9600);
	//Defines the output pins and input pins. These may vary. 
	//opt is the input on the input pad. 
	//Relay is the corresponding Relay that we are controlling. 
	pinMode(opt1, INPUT); 
	pinMode(opt2, INPUT); 
	pinMode(opt3, INPUT); 
	pinMode(opt4, INPUT); 
	pinMode(relay1, OUTPUT); 
	pinMode(relay2, OUTPUT); 
	//pinMode(relay3, OUTPUT); //Optional
	//pinMode(relay4, OUTPUT); //Optional 

	//Loops through each individual state and initializes them to false. 
	for(int i = 0; i < 4; i++){
		opt[i] = false;
		relay[i] = false;
	}

	//Test the one relay by changing a state. 
	//Because of code below, this is NOT a permanant state and will change in 500ms.
	digitalWrite(relay1, HIGH);

}

void loop() {

	//Getting input over a period of time to de-bounce the input. 
	//Define an 2D boolean. 1D will hold the ID of the relay, and the other will hold it's current state. 
	bool tempOpt[4][2];

	//Check the status of the input pad twice w/ a 500ms interval in between.
	//If the button is has the same state of high, switch the corresponding relay's state. 
	//This effectively de-bounces the input and ensures that the user wants a change of state. 
	for(int i = 0; i < 2; i++){
		tempOpt[0][i] = digitalRead(opt1);
		tempOpt[1][i] = digitalRead(opt2);
		tempOpt[2][i] = digitalRead(opt3);
		tempOpt[3][i] = digitalRead(opt4);
		delay(500);
  }

	//IF there is a state between the 500ms interval, INVERT the state of the relay.
	for(int i = 0; i < 4; i++){
		if(tempOpt[i][0] == 1 && tempOpt[i][1] == 1){
			opt[i] = !bool(opt[i]);
		}
	} 

	//Write or Sets the relay states to the correct pins. 
	digitalWrite(relay1, opt[0]);
	digitalWrite(relay2, opt[1]);
	//digitalWrite(relay1, opt[2]); //Optional
	//digitalWrite(relay2, opt[3]); //Optional 

	//Prints out the states via Serial. For debugging purposes.
	for(int i = 0; i < 4; i++){
		Serial.println(opt[i]);
	}
	Serial.println("");

	//Wait 100ms. 
	delay(100);

}
