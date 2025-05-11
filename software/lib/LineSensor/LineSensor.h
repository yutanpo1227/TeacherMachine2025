#ifndef LINESENSOR_H
#define LINESENSOR_H

class LineSensor {
    public:
        LineSensor(int startPin, int numSensors, const int* thresholds);
        int readAngle();
        bool checkOnLine();
        void setMode(bool mode);
    private:
        int startPin;
        int numSensors;
        const int* thresholds;
        bool mode;
};
#endif
