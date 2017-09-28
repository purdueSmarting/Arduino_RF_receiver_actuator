#include <VirtualWire.h>

#include <VirtualWire.h>
 #include <string.h>
 
  byte message[VW_MAX_MESSAGE_LEN];          //받은 메세지 저장할 임시변수 선언           
  byte messageLength = VW_MAX_MESSAGE_LEN; 
 
 int ledPin = 10;
 
  void setup() {
    vw_setup(2000);
    vw_set_rx_pin(2);            //수신 핀 설정
    vw_rx_start();               //수신 시작
    pinMode(ledPin, OUTPUT);
  }
 
  void loop() {
    if (vw_get_message(message, &messageLength)) {       //메세지 읽어옴
       int command = processResponse((char*)message, 1); //메세지에서 command만 분리
       if (command) {
         switch (command) {
          case 1:                         //명령어가 1이면
            digitalWrite(ledPin, HIGH);   //LED ON
            break;
          case 2:                         //명령어가 2이면
            digitalWrite(ledPin, LOW);    //LED OFF
            break;
        }
       }  
    }
  }
 
 //메세지에서 command만 분리하는 함수
  int processResponse(char* message, int pinCode) {
      char *p = message;
      char *buf;
      int o = 0;
      int pin;
      int command;
 
      while ((buf = strtok_r(p, ".", &p)) != NULL)  {  //메세지 분리 후 buf에 저장
         if (o == 0) {                                 //o가 0이면
           pin = atoi(buf);                            //핀 코드 부분 정수로 변환
         } else {
           command = atoi(buf);                        //명령어 정수로 변환
         }
         o++;
      }
 
      if (pinCode == pin && command > 0) {             //명령어만 반환      
          return command;
      } else {
         return 0; 
      }
  }
