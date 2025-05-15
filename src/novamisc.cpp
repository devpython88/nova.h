#include "novamisc.h"

int NovaInteractPrompt::checkObjectAndDraw(NovaObject4 obj, NovaVec2 textPosition)
{
    if (CheckCollisionCircleRec(Vector2{pos.x + (detectionRadius * 2), pos.y}, detectionRadius, Rectangle{obj.x, obj.y, obj.width, obj.height})){
        NovaRenderDevice::uiLabel(message, textPosition, 20, BLACK);
        return 1;
    }

    return 0;
}

void NovaInteractPrompt::checkAndDraw(NovaVec2 textPosition, std::vector<NovaObject4> objectsToCheck)
{
    for (NovaObject4 obj : objectsToCheck){
        if (checkObjectAndDraw(obj, textPosition) == 1) return;
    }
}

void NovaVehicle::drive()
{
    handleVehicleVelocity();
    repositionVehicle();
}

float NovaVehicle::getValidSpeed()
{
    if (fabs(yVelocity) < 0.05f) return 0.0f;
    return yVelocity;
}


void NovaVehicle::handleAcceleration(){
    yVelocity += vehicleConfig.accelerationSpeed;
    if (yVelocity > vehicleConfig.topSpeed) yVelocity = vehicleConfig.topSpeed;
}

void NovaVehicle::handleDeceleration(){
    yVelocity -= vehicleConfig.decelerationSpeed;
    if (yVelocity < -vehicleConfig.maxDecelerationSpeed) yVelocity = -vehicleConfig.maxDecelerationSpeed;
}

void NovaVehicle::handleDamping(){
    if (fabs(yVelocity) < 0.05f) yVelocity = 0.0f;
    else if (yVelocity > 0.0f) yVelocity -= vehicleConfig.decelerationSpeed;
    else yVelocity += vehicleConfig.decelerationSpeed;
}

void NovaVehicle::handleVehicleVelocity(){
    // Accelerate
    if (NovaInputDevice::keyHeld(forwardKey)){
        handleAcceleration();
    }

    // Decellerate
    else if (NovaInputDevice::keyHeld(backwardKey)){
        handleDeceleration();
    }

    // Damping
    else {
        handleDamping();
    }
}

void NovaVehicle::repositionVehicle(){
    float rad = vehicleHost->rotation * DEG2RAD;
    


    // Turning
    if (NovaInputDevice::keyHeld(turnLeftKey)) vehicleHost->rotation -= vehicleConfig.turnSpeed;
    if (NovaInputDevice::keyHeld(turnRightKey)) vehicleHost->rotation += vehicleConfig.turnSpeed;


    vehicleHost->x += sin(rad) * yVelocity;
    vehicleHost->y += -cos(rad) * yVelocity;
}
