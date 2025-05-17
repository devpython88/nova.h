#include "novamisc.h"

void NovaVehicle::drive()
{
    float rad = vehicleHost->rotation * DEG2RAD;
    
    if (driving){
        if (NovaInputDevice::keyHeld(forwardKey)){
            yVelocity += vehicleConfig.accelerationSpeed;
            if (yVelocity > vehicleConfig.topSpeed) yVelocity = vehicleConfig.topSpeed;
        }

        // Decellerate
        else if (NovaInputDevice::keyHeld(backwardKey)){
            yVelocity -= vehicleConfig.decelerationSpeed;
            if (yVelocity < -vehicleConfig.maxDecelerationSpeed) yVelocity = -vehicleConfig.maxDecelerationSpeed;
        }
    }
    // Damping
    else {
        if (fabs(yVelocity) < 0.05f) yVelocity = 0.0f;
        else if (yVelocity > 0.0f) yVelocity -= vehicleConfig.decelerationSpeed;
        else yVelocity += vehicleConfig.decelerationSpeed;
    }

    // Turning
    if (driving) {
        if (NovaInputDevice::keyHeld(turnLeftKey)) vehicleHost->rotation -= vehicleConfig.turnSpeed;
        if (NovaInputDevice::keyHeld(turnRightKey)) vehicleHost->rotation += vehicleConfig.turnSpeed;
    }

    vehicleHost->x += sin(rad) * yVelocity;
    vehicleHost->y += -cos(rad) * yVelocity;
}

float NovaVehicle::getValidSpeed()
{
    if (fabs(yVelocity) < 0.05f) return 0.0f;
    return yVelocity;
}
