#include <VirtualWire.h>
#include <string.h>
 
byte message[VW_MAX_MESSAGE_LEN];          //받은 메세지 저장할 임시변수 선언           
byte messageLength = VW_MAX_MESSAGE_LEN; 
int ledPin = 10;

void setup() {
  vw_setup(2000);
  vw_set_rx_pin(2); // 수신 핀 설정
  vw_rx_start(); // 수신 시작
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if(vw_get_message(message, &messageLength)) {
    int command = processResponse((char*)message, 1);
    if(command) {
      switch(command) {
        case 1:
        digitalWrite(ledPin, HIGH);
        break;
        case 2:
        digitalWrite(ledPin, LOW);
        break;
      }
    }
  }
}

int processResponse(char* message, int pinCode) {
  char *p = message;
  char *buf;
  int o = 0;
  int pin, command;

  while((buf = strtok_r(p, ".", &p)) != NULL) {
    if(o == 0) {
      pin = atoi(buf);
    } else {
      command = atoi(buf);
    }
    o++;
  }

  if(pinCode == pin && command > 0) {
    return command;
  } else {
    return 0;
  }
}
