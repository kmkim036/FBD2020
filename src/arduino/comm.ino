// upload this on the Arduino which connects with PC by Serial communication

// this Arduino uses all communication (I2C, SoftwareSerial, Hardware Serial)

// enable i2c communication with other Arduino
#include <Wire.h>
// I2C address
#define Slave 0x10

// enable software serial communication with other Arduino
#include <SoftwareSerial.h>
SoftwareSerial button(12, 13); // SoftwareSerial pin

// save buttons' states
int state[2];

void setup()
{
    // set pins as buttons
    // init buttons' states
    for (int i = 0; i < 2; i++) {
        pinMode(i + 2, INPUT);
        state[i] = 1;
    }
    // begin I2C communication as I2C slave
    Wire.begin(Slave);
    // function for I2C call from master
    Wire.onReceive(receiveFromMaster);
    // begin SoftwareSerial communication, BPS:9600
    button.begin(9600);
    // begin Serial communication, BPS: 9600
    Serial.begin(9600);
}

void loop()
{
    // if there is a button input with SoftwareSerial communication
    if (button.available() > 0) {
        // data from other Arduino by SoftwareSerial communication
        char data_serial;
        // read the data by SoftwareSerial communication
        data_serial = button.read();
        // send the data to PC
        Serial.println(data_serial);
    }

    for (int i = 0; i < 2; i++) {
        int a = digitalRead(i + 2); // save button status
        char data; // data to send to PC
        if (a && state[i])
            state[i] = 0;
        else if (!a && !state[i])
            state[i] = 1;
        else
            continue;
        switch (i) {
        case 0:
            data = 'W';
            break;
        case 1:
            data = 'X';
            break;
        }
        // send the data to the PC
        Serial.println(data);
    }
}

//if there is a call from I2C master device
void receiveFromMaster(int nByteNum)
{
    // data from other Arduino by I2C communication
    char data_i2c;
    // read the data by I2C communication
    for (int i = 0; i < nByteNum; i++)
        data_i2c = Wire.read();
    // send the data to PC
    Serial.println(data_i2c);
}
