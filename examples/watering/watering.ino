/*
 ************************************************************************
 * 作者:  IntoRobot Team
 * 版本:  V1.0.0
 * 日期:  03-30-15
 ************************************************************************
 功能描述：
 浇灌器：具有土壤湿度检测功能的浇花控制器

 所需器件:
 1. YL38 土壤湿度传感器
 2. 电磁阀
 */

#include <yl38.h>
#include <WidgetSprinkler.h>

#define SPRINKLER_SWITCH_PIN    D0   //定义浇水开关引脚
#define YL38_PIN    A0
YL38 yl38 = YL38(YL38_PIN);
WidgetSprinkler sprinkler = WidgetSprinkler();

uint8_t   wateringDelay;  //浇水时间
uint8_t   wateringFlag;   //浇水标志
uint32_t  wateringTimer;  //浇水定时器

void wateringCb(void)
{
    wateringDelay = sprinkler.getWateringTime();

    if(sprinkler.getWaterSwitch())
    {
        sprinkler.control(SPRINKLER_SWITCH_PIN,1);//打开浇水

        if(wateringDelay != 0)
        {
            wateringFlag = 1;
            wateringTimer = timerGetId();
        }
        else
        {
            wateringFlag = 0;
        }
    }
    else
    {
        sprinkler.control(SPRINKLER_SWITCH_PIN,0); //关闭浇水
        wateringFlag = 0;
    }
}

void setup()
{
    //初始化
    yl38.begin();
    //接收浇水控制
    sprinkler.begin(wateringCb);
}

void loop()
{
    sprinkler.displaySoilHumidity(yl38.CalculateHumidity());  //上送土壤湿度

    if(wateringFlag && timerIsEnd(wateringTimer,wateringDelay*60000))
    {
        sprinkler.control(SPRINKLER_SWITCH_PIN,0); //浇水时间到，关闭浇水
        wateringFlag = 0;
    }

    delay(3000);
}
