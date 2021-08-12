// upload this on the Arduino which gets cc

// for normal algorithms

// this Arduino only uses SoftwareSerial communication

// enable software serial communication with other Arduino
#include <SoftwareSerial.h>
SoftwareSerial button(12, 13); // SoftwareSerial pin

//save buttons' states
int state[10];

void setup()
{
    // set pins as buttons
    // init buttons' states
    for (int i = 0; i < 10; i++) {
        pinMode(i + 2, INPUT);
        state[i] = 1;
    }
    // begin SoftwareSerial communication, BPS:9600
    button.begin(9600);
}

void loop()
{
    //save button status
    int a;
    //data to send to the other Arduino and PC
    char data;

    for (int i = 0; i < 9; i++) {
        if (i == 0 || i == 2) {
            int a = digitalRead(i + 2);
            if (a && state[i]) {
                state[i] = 0;
                int counts = 0;
                while (a) {
                    // check the button pressed time
                    a = digitalRead(i + 2);
                    counts = counts + 1;
                    delay(100);
                }
                state[i] = 1;
                // send the data to the other Arduino
                char data;
                if (i == 0) {
                    if (counts < 5)
                        data = 'a';
                    else
                        data = 'b';
                } else {
                    if (counts < 5)
                        data = 'c';
                    else
                        data = 'd';
                }
                button.write(data);
            }
        } else {
            int a = digitalRead(i + 2); // save button status
            if (a && state[i]) {
                state[i] = 0;
                char data; // data to send to the other Arduino and PC
                switch (i) {
                case 1:
                    data = 'B';
                    break;
                case 3:
                    data = 'D';
                    break;
                case 4:
                    data = 'E';
                    break;
                case 5:
                    data = 'F';
                    break;
                case 6:
                    data = 'G';
                    break;
                case 7:
                    data = 'H';
                    break;
                case 8:
                    data = 'I';
                    break;
                case 9:
                    data = 'J';
                    break;
                default:
                    break;
                }
                button.write(data);
            }
            if (!a)
                state[i] = 1;
        }
    }
}