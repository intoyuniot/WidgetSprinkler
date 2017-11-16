#ifndef WIDGET_SPRINKLER_H_
#define WIDGET_SPRINKLER_H_

#include "application.h"

class WidgetSprinkler: public WidgetBaseClass
{
    public:
        WidgetSprinkler(uint8_t ucItem = 0);
        ~WidgetSprinkler();
        void begin(void (*UserCallBack)(void) = NULL);
        void displaySoilHumidity(int soilHumidity);
        void displayWaterStatus(uint8_t status);
        uint8_t getWaterSwitch(void);
        int getWateringTime(void);
        void control(uint8_t pin,uint8_t status);

    private:
        char pCmdWaterTopic[64];
        char pDataSoilHumidityTopic[64];
        char pDataStatusTopic[64];
        uint8_t _switchKey = 0;
        uint8_t _Item=0;
        int _wateringTime;
        void (*_EventCb)(void);
        void widgetBaseCallBack(uint8_t *payload, uint32_t len);
};

#endif
