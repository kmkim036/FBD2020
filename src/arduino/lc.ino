// upload this on the Arduino which gets lc

// this Arduino only uses I2C communication

// enable i2c communication with other Arduino
#include <Wire.h>
// I2C address
#define I2C_SLAVE_ADDR 0x10

// save buttons' states
int state[12];

void setup()
{
    // set pins as buttons
    // init buttons' states
    for (int i = 0; i < 12; i++) {
        pinMode(i + 2, INPUT);
        state[i] = 1;
    }
    // begin I2C communication as I2C master
    Wire.begin();
}

void loop()
{
    for (int i = 0; i < 12; i++) {
        int a = digitalRead(i + 2); // save button status
        if (a && state[i]) {
            state[i] = 0;
            char data; // data to send to the other Arduino and PC
            switch (i) {
            case 0:
                data = 'K';
                break;
            case 1:
                data = 'L';
                break;
            case 2:
                data = 'M';
                break;
            case 3:
                data = 'N';
                break;
            case 4:
                data = 'O';
                break;
            case 5:
                data = 'P';
                break;
            case 6:
                data = 'Q';
                break;
            case 7:
                data = 'R';
                break;
            case 8:
                data = 'S';
                break;
            case 9:
                data = 'T';
                break;
            case 10:
                data = 'U';
                break;
            case 11:
                data = 'V';
                break;
            default:
                break;
            }
            Wire.beginTransmission(I2C_SLAVE_ADDR);
            Wire.write(data);
            Wire.endTransmission();
        }
        if (!a)
            state[i] = 1;
    }
}
