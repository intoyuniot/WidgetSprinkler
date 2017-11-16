#include "WidgetSprinkler.h"


WidgetSprinkler::WidgetSprinkler(uint8_t ucItem)
{
    _Item=ucItem;
    memset(pDataStatusTopic,0,sizeof(pDataStatusTopic));
    memset(pCmdWaterTopic,0,sizeof(pCmdWaterTopic));
    memset(pDataSoilHumidityTopic,0,sizeof(pDataSoilHumidityTopic));
    sprintf(pDataStatusTopic,"channel/sprinkler_%d/data/status",_Item);
    sprintf(pCmdWaterTopic,"channel/sprinkler_%d/cmd/watering",_Item);
    sprintf(pDataSoilHumidityTopic,"channel/sprinkler_%d/data/soilHumidity",_Item);

}

WidgetSprinkler::~WidgetSprinkler()
{
}

void WidgetSprinkler::begin(void (*UserCallBack)(void))
{
    _EventCb=UserCallBack;
    IntoRobot.subscribe(pCmdWaterTopic, NULL, this);
}

void WidgetSprinkler::displayWaterStatus(uint8_t status)
{
    IntoRobot.publish(pDataStatusTopic,status);
}


void WidgetSprinkler::displaySoilHumidity(int soilHumidity)
{
    IntoRobot.publish(pDataSoilHumidityTopic,soilHumidity);
}

uint8_t WidgetSprinkler::getWaterSwitch(void)
{
    return _switchKey;
}


int WidgetSprinkler:: getWateringTime(void)
{
    return _wateringTime;
}

void WidgetSprinkler::control(uint8_t pin,uint8_t status)
{
    pinMode(pin,OUTPUT);
    digitalWrite(pin,status);
    displayWaterStatus(status);
}

void WidgetSprinkler::widgetBaseCallBack(uint8_t *payload, uint32_t len)
{
    if(!jsonGetValue(payload, "status", _switchKey)) return;
    if(!jsonGetValue(payload, "time", _wateringTime)) return;
    _EventCb();
}







