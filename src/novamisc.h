#pragma
#include "nova.h"
#include <string>



class NovaVehicleConfig {
    public:
    float topSpeed;
    float decelerationSpeed;
    float accelerationSpeed;
    float turnSpeed;
    float maxDecelerationSpeed;

    NovaVehicleConfig() = default;
    NovaVehicleConfig(float topSpeed, float decelerationSpeed, float accelerationSpeed, float turnSpeed, float maxDecelerationSpeed)
        : topSpeed(topSpeed), decelerationSpeed(decelerationSpeed), accelerationSpeed(accelerationSpeed), turnSpeed(turnSpeed), maxDecelerationSpeed(maxDecelerationSpeed) {}
};


class NovaVehicle {
    public:
    float yVelocity;
    NovaVehicleConfig vehicleConfig;
    int forwardKey, backwardKey, turnLeftKey, turnRightKey;
    NovaObject4* vehicleHost;
    bool driving;

    NovaVehicle() = default;
    NovaVehicle(NovaObject4* vehicleHost, const NovaVehicleConfig& config, int forwardKey, int backwardKey, int turnLeftKey, int turnRightKey)
        : vehicleHost(vehicleHost), yVelocity(0.0f), vehicleConfig(config), forwardKey(forwardKey), backwardKey(backwardKey), turnLeftKey(turnLeftKey), turnRightKey(turnRightKey) {}

    void drive();
    float getValidSpeed();
};



