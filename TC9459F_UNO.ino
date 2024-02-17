/* 
    电子音量IC（TC9459F）功能测试代码，2024年2月
*/
#include <SPI.h>

//TC9459F与Arduino UNO连接
#define STB_Pin 10 //Arduino板的Digital #10接TC9459F的STB（#14）接口
#define DATA_Pin 11 //Arduino板的Digital #11接TC9459F的DATA（#13）接口
#define CK_Pin 13 //Arduino板的Digital #13接TC9459F的CK（#12）接口


//定义TC9459F的地址，和是否启用响度
const uint8_t Addr_Loudness = 0b10000000; //不启用响度，CS1和CS2都接地

uint8_t Volume = 0;//用于控制音量大小，根据TC9459F数据手册，最大音量为0dB，对应的寄存器写入值为0b0000000，最小音量为-89dB，对应的寄存器写入值为0b1001101
const uint8_t defaultVolume = 30;//默认音量，-30dB
void setup() {


  //设置CS脚位
  pinMode(STB_Pin, OUTPUT);
  digitalWrite(STB_Pin, HIGH);

  //初始化SPI
  SPI.begin();
  SPI.beginTransaction(SPISettings(250000, LSBFIRST, SPI_MODE0));//根据数据手册，芯片工作频率为0~1MHz，寄存器数据写入顺序为LSB

   
  Serial.begin(115200);  // output
}

void loop() 
{ 
/*
    for (Volume = 0; Volume < 50; Volume++) //控制音量衰减由小到大（音量从大到小变化），衰减控制数值从0（0dB）增加到89（-89dB）
    {
       TC9459Write(Volume, Volume);
       Serial.print("Volume=");
       Serial.println(Volume);
       delay(10);
    }

    for (Volume = 50; Volume > 0; Volume--) //控制音量衰减由大到小（音量从小到大变化），衰减控制数值从89（-89dB）减小到0（0dB）
    {
       TC9459Write(Volume, Volume);
       Serial.print("Volume=");
       Serial.println(Volume);
       delay(10);
    }
*/
    TC9459Write(defaultVolume, defaultVolume);
    //Serial.print("Volume=");
    //Serial.println(defaultVolume);
      
}


//TC9459F写入函数
void TC9459Write(uint8_t leftAttenuation, uint8_t rightAttenuation)
{

    //拉低CS脚电位，准备写入
    digitalWrite(STB_Pin, LOW);
    delayMicroseconds(1);
    
    //写入数据
    SPI.transfer(leftAttenuation);
    SPI.transfer(rightAttenuation);
    SPI.transfer(Addr_Loudness);

    //拉高CS脚电位，完成写入
    delayMicroseconds(1);
    digitalWrite(STB_Pin, HIGH);
    SPI.endTransaction();

}
