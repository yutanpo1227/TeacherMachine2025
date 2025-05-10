#ifndef IRSENSOR_H
#define IRSENSOR_H

class IRSensor {
    public:
        IRSensor(int startPin, int numSensors);
        int readAngle();
        int readDistance();
    private:
        int startPin;
        int numSensors;
};


#endif