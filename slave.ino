/* -SLAVE-
 * This program recieves strings of length MSG_SIZE from the master to slave.
 * Enable new line ending on master device
 * connect RX of hc05 to pin 11 of the arduino and TX of hc05 to pin 10 of the arduino
 */

#include <SoftwareSerial.h>
#define TERMINATE '\n'
#define MSG_SIZE 255
#define RX 10
#define TX 11

SoftwareSerial BTserial(RX,TX); //makes pin 10 and 11 behave as RX and TX respectively

int code;
char message[MSG_SIZE + 1]; //+1 to include '\0'

void setup() {
        BTserial.begin(38400);
        Serial.begin(9600);
        pinMode(RX, INPUT);
        pinMode(TX, OUTPUT);
}

void loop() {
        code_reader();
}

void code_reader() {
        //this code converts single char into a string which terminates only with '\n'
        code = 0;
        int count = 0; //the position of the letter in the string used to store the code
        while (count < MSG_SIZE + 1) {
                if (BTserial.available()) { //prints char sent from master device
                        code = BTserial.read();
                        if (code == TERMINATE) {
                                break;
                        }
                        message[count] = code;
                        //Serial.println(code); //uncomment to see actual letter code sent
                        count += 1;
                }
        }
        message[count] = 0; //terminates string with '\0'
        Serial.println(message);
        check_message(); //to trigger commands ie: digitalwrite-HIGH
}

void check_message() {
        //this block executes commands once the message is a match to certain keywords
        char match1[] = {"hello"};//keyword that triggers command
        if (message_match(match1, message)) {
                //command to be executed
                Serial.println("MESSAGE IS A MATCH");
        }
}

bool message_match(char msg1[], char msg2[]) {
        //this function returns true only if 2 strings are identical
        int i;
        for (i = 0; msg1[i] != 0 || msg2[i] != 0; i += 1) {
                if (msg1[i] != msg2[i]) {
                        return false;
                }
        }
        return (msg1[i] == 0 && msg2[i] == 0); //only returns true if '\0' is at same position in both strings
}
