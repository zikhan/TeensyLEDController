/*
 Name:		arduinoStuff.ino
 Created:	4/12/2017 9:51:37 PM
 Author:	Zovin
*/

#define Bluetooth Serial1

int red = 23;
int green = 22;
int blue = 21;

int mic = 16;

int rgb[3] = {0, 0, 0};

// the setup function runs once when you press reset or power the board
void setup() {
    Serial.begin(9600);
    Bluetooth.begin(9600);

    pinMode(red, OUTPUT);
    pinMode(green, OUTPUT);
    pinMode(blue, OUTPUT);

    pinMode(mic, INPUT);
}

// the loop function runs over and over again until power down or reset
void loop() {
    analogWrite(red, rgb[0]);
    analogWrite(green, rgb[1]);
    analogWrite(blue, rgb[2]);

    if (Bluetooth.available()) {
        String incoming = Bluetooth.readString();
        Serial.println("Bluetooth: " + incoming);
        setRGB(incoming);
    }
    if (Serial.available()) {
        String incoming = Serial.readString();
        Serial.println("Serial: " + incoming);
        setRGB(incoming);
        Bluetooth.write(incoming.c_str());
    }

    int val = analogRead(mic);
    Serial.println(val);
    delay(100);
}

void setRGB(String rgbVals) {
    rgbVals.remove(0,1);
    rgbVals.remove(rgbVals.indexOf(')'),1);
    int comma = rgbVals.indexOf(',');
    rgb[0] = rgbVals.substring(0, comma).toInt();

    int lastComma = rgbVals.lastIndexOf(',');
    rgb[1] = rgbVals.substring(comma + 1, lastComma).toInt();

    rgb[2] = rgbVals.substring(lastComma + 1).toInt();
}
