//Arduino Code - Rotary Encoder w push button

#include <BfButton.h>
#include <toshiba_ic.h>

#define STB_Pin 2 //Arduino板的Digital #2接TC9459F的STB（#13）接口
#define DATA_Pin 3 //Arduino板的Digital #3接TC9459F的DATA（#14）接口
#define CK_Pin 4 //Arduino板的Digital #4接TC9459F的CK（#12）接口
#define SW_Pin 5 //Arduino板的Digital #5接编码器的SW（按键开关）接口
#define DT_Pin 6 //Arduino板的Digital #6接编码器的DT（数据）接口
#define CLK_Pin 7 //Arduino板的Digital #7接编码器的CLK（时钟）接口

#define VOLUMECONTROLADDRESS 8 //定义TC9459F的地址为8

BfButton btn(BfButton::STANDALONE_DIGITAL, SW_Pin, true, LOW);

//定义TC9459F实例
TC9459 VolumControl(DATA_Pin,CK_Pin,STB_Pin,VOLUMECONTROLADDRESS);



int counter = 0;
int angle = 0; 
int aState;
int aLastState;  

//编码器下压按钮对应处理函数
void pressHandler (BfButton *btn, BfButton::press_pattern_t pattern) {
  switch (pattern) {
    case BfButton::SINGLE_PRESS:
      Serial.println("Single push");
      break;
      
    case BfButton::DOUBLE_PRESS:
      Serial.println("Double push");
      break;
      
    case BfButton::LONG_PRESS:
      Serial.println("Long push");
      break;
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println(angle);
  pinMode(CLK_Pin,INPUT_PULLUP);
  pinMode(DT_Pin,INPUT_PULLUP);
  aLastState = digitalRead(CLK_Pin);

  //Button settings
  btn.onPress(pressHandler)
  .onDoublePress(pressHandler) // default timeout
  .onPressFor(pressHandler, 1000); // custom timeout for 1 second
}

void loop() {
  // put your main code here, to run repeatedly:

  //Wait for button press to execute commands
  btn.read();
  
  aState = digitalRead(CLK_Pin);

  //Encoder rotation tracking
  if (aState != aLastState){     
     if (digitalRead(DT_Pin) != aState) 
     { 
       counter ++;
       angle ++;
     }
     else 
     {
       counter--;
       angle --;
     }
     if (counter >=100 ) 
     {
       counter =100;
     }
     if (counter <=-100 ) 
     {
       counter =-100;
     }
     Serial.println(counter); 
  }   
  aLastState = aState;
}
