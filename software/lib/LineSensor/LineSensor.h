#ifndef LINESENSOR_H
#define LINESENSOR_H

class LineSensor {
    public:
        LineSensor(int startPin, int numSensors, int* thresholds);
        int readAngle();
    private:
        int startPin;
        int numSensors;
        int* thresholds;
};
#endif
