/*
   使用Arduino UNO控制TOSHIBA TC9459F电子音量芯片
   使用Jerry Long的TC9459库
   By Jerry Long， 10 Feb 2024

   TC9459芯片SPI接线：
      STB(14#)——>SDL——>D10(SS)
      Clock(12#)——>SCL——>D13(SCK)
      Data(13#) ——>SDA——>D11(MOSI)

   TC9459芯片模拟供电：
      外接±15V电源，地A_GND
*/
#include <TC9459.h>

//定义TC9459芯片的地址（根据CS1-#9和CS2-#16脚位的高低电平）
static const byte TC9459_ADDRESS = 0b10000000;

//根据上述芯片地址创建TC9459对象
static TC9459 TC9459L(TC9459_ADDRESS);

//定义默认音量，当前音量，最大和最小音量
static TC9459::volume_t defaultVolume = 30; //重启后的默认音量--44dB
static TC9459::volume_t currentVolume = 20; //当前音量，-20dB开始
int MaxVolume = 0; //最大音量0dB
int MinVolume = 89; //最小音量-89dB

void setup() {
  //设置串口波特率
  Serial.begin(115200);
  
  //初始化TC9459
  TC9459L.begin();  
  
  //设置TC9459是否启用响度状态
  TC9459L.turnOnLoudness(false); //不使用响度

  //启动时设置为默认音量
  TC9459L.setVolume(defaultVolume, defaultVolume);

}

void loop() {
  // put your main code here, to run repeatedly:

  for(int i = MaxVolume; i<MinVolume; i++)
  {
    currentVolume = i;
    Serial.print("currentVolume = ");
    Serial.println(currentVolume);
    TC9459L.setVolume(currentVolume, currentVolume);
    delay(30);
  }

  for (int i = MinVolume; i>MaxVolume; i--)
  {
    currentVolume = i;
    Serial.print("currentVolume = ");
    Serial.println(currentVolume);
    TC9459L.setVolume(currentVolume, currentVolume);
    delay(30);
  }
  
  // You can continue with the rest of your loop code here.
  delay(100);
}
