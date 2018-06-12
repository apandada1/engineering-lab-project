const int serial_out = 2;
const int clk = 4;
const int enable = 7;
int i=0;
int p=0; //This is for stopping the racing of clock

int a[8] = {LOW,HIGH,LOW,HIGH,LOW,LOW,HIGH,LOW};//{Dummy,Dummy,Dummy,front left,front right,back left,back right,Dummy} 
//Motion of wheels - LOW is backward, HIGH is forward
int forward[8] = {LOW,LOW,LOW,HIGH,HIGH,HIGH,HIGH,LOW};
int backward[8] = {LOW,LOW,LOW,LOW,LOW,LOW,LOW};
int right[8] = {LOW,LOW,LOW,HIGH,LOW,HIGH,LOW,LOW};
int left[8] = {LOW,LOW,LOW,LOW,HIGH,LOW,HIGH,LOW};
unsigned long previousTime = 0; //time of previous change
unsigned long currentTime;
long interval = 10; //time period of clock

void setup()
{
  Serial.begin(9600);
  pinMode(serial_out, OUTPUT);
  pinMode(clk, OUTPUT);
  pinMode(enable, OUTPUT);
  digitalWrite(clk, HIGH); //Initially clock should be high due to positive edge triggered IC
  //copy(a,backward,8); //This is temporary. Later we will change this dynamically with Raspberry Pi
}

void alterValue (int pin)
{
	if (digitalRead(pin) == HIGH)
	{
		digitalWrite(pin, LOW);
	}
	else
	{
		digitalWrite(pin, HIGH);
	}
}
void loop()
{
  currentTime = millis(); //current time
  if((currentTime - previousTime) > interval)
  {
  	if (i == 0)
  	{
  		digitalWrite(enable, LOW);
  	}
    previousTime = currentTime;
  	digitalWrite(serial_out, a[i]);
    Serial.print(i);
    Serial.print("  ");
    Serial.println(a[i]);
  	i++;
  	if(i == 8)
  	{
  		digitalWrite(enable, HIGH);
  		i = 0;
  	}
    alterValue(clk);
    p = 0;
  }
  else if (currentTime - previousTime >= (interval/2) && p == 0)
  {
  	alterValue(clk);
    p = 1;
  }
}

void copy(int destination[], int source[], int count)
{
	int k;
	for (k = 0; k < count; ++k)
	{
		destination[k] = source[k];
	}
}
