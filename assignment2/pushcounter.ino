#define b1 8 //LSB
#define b2 9
#define b3 10
#define b4 11 //MSB
#define INTR 12 //interrupt pin
int count = 0;
// the setup function runs once when you press reset or power the board
void setup() {
	// initialize digital pin LED_BUILTIN as an output.
	pinMode(b1, OUTPUT);
	pinMode(b2, OUTPUT);
	pinMode(b3, OUTPUT);
	pinMode(b4, OUTPUT);
	digitalWrite(b1, LOW);
	digitalWrite(b2, LOW);
	digitalWrite(b3, LOW);
	digitalWrite(b4, LOW);
}

// the loop function runs over and over again forever
void loop() {

	//should be low before sending data
	digitalWrite(INTR,LOW);

	if(count == 16){
		count = 0;
	}
	//which all bits need to be set for a particular count value
	if(count & (1 << 0)){
		digitalWrite(b1, HIGH);
	}else{
		digitalWrite(b1, LOW);
	}

	if(count & (1 << 1)){
		digitalWrite(b2, HIGH);
	}else{
		digitalWrite(b2, LOW);
	}

	if(count & (1 << 2)){
		digitalWrite(b3, HIGH);
	}else{
		digitalWrite(b3, LOW);
	}

	if(count & (1 << 3)){
		digitalWrite(b4, HIGH);
	}else{
		digitalWrite(b4, LOW);
	}
	count++;
	//should be high after sending data
	digitalWrite(INTR,HIGH);
	delay(1000);
}
