#pragma
#include "nova.h"
#include <string>


class NovaInteractPrompt {
    private:
    int checkObjectAndDraw(NovaObject4 obj, NovaVec2 textPosition);

    public:
    float detectionRadius;
    std::string message;
    int triggerKey;
    NovaVec2 pos;


    NovaInteractPrompt() = default;
    NovaInteractPrompt(std::string message, NovaVec2 pos, int triggerKey, float detectionRange):
    message(message), triggerKey(triggerKey), detectionRadius(detectionRange), pos(pos){}

    void checkAndDraw(NovaVec2 textPosition, std::vector<NovaObject4> objectsToCheck);
};



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

    NovaVehicle() = default;
    NovaVehicle(NovaObject4* vehicleHost, const NovaVehicleConfig& config, int forwardKey, int backwardKey, int turnLeftKey, int turnRightKey)
        : vehicleHost(vehicleHost), yVelocity(0.0f), vehicleConfig(config), forwardKey(forwardKey), backwardKey(backwardKey), turnLeftKey(turnLeftKey), turnRightKey(turnRightKey) {}

    void drive();
    float getValidSpeed();



    protected:
    void handleAcceleration();
    void handleDeceleration();
    void handleDamping();

    void handleVehicleVelocity();
    void repositionVehicle();
};



