#include "novamisc.h"

void NovaVehicle::drive()
{
    float rad = vehicleHost->rotation * DEG2RAD;
    bool moved = false;

    if (driving)
    {
        if (NovaInputDevice::keyHeld(forwardKey))
        {
            moved = true;
            yVelocity += vehicleConfig.accelerationSpeed;
            if (yVelocity > vehicleConfig.topSpeed)
                yVelocity = vehicleConfig.topSpeed;
        }

        // Decellerate
        else if (NovaInputDevice::keyHeld(backwardKey))
        {
            moved = true;
            yVelocity -= vehicleConfig.decelerationSpeed;
            if (yVelocity < -vehicleConfig.maxDecelerationSpeed)
                yVelocity = -vehicleConfig.maxDecelerationSpeed;
        }
    }
    // Damping
    if (!moved)
    {
        if (fabs(yVelocity) < 0.05f)
            yVelocity = 0.0f;
        else if (yVelocity > 0.0f)
            yVelocity -= vehicleConfig.decelerationSpeed;
        else
            yVelocity += vehicleConfig.decelerationSpeed;
    }
    // Turning
    if (driving)
    {
        if (NovaInputDevice::keyHeld(turnLeftKey))
            vehicleHost->rotation -= vehicleConfig.turnSpeed;
        if (NovaInputDevice::keyHeld(turnRightKey))
            vehicleHost->rotation += vehicleConfig.turnSpeed;
    }

    vehicleHost->x += sin(rad) * yVelocity;
    vehicleHost->y += -cos(rad) * yVelocity;
}

float NovaVehicle::getValidSpeed()
{
    if (fabs(yVelocity) < 0.05f)
        return 0.0f;
    return yVelocity;
}





// Math

float NovaMath::roundTo(float val, float step){
    return round(val / step) * step;
}


float NovaMath::normalize(float value) {
    if (value == 0) return 0;
    return (value > 0) ? 1.0f : -1.0f;
}


NovaVec2 NovaMath::normalize2(NovaVec2 vec) {
    float mag = std::sqrt(vec.x * vec.x + vec.y * vec.y);
    if (mag == 0) return NovaVec2(0, 0);
    return NovaVec2(vec.x / mag, vec.y / mag);
}

NovaVec3 NovaMath::normalize3(NovaVec3 vec){
    float mag = std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
    if (mag == 0) return NovaVec3(0, 0, 0);
    return NovaVec3(vec.x / mag, vec.y / mag, vec.z / mag);
}

NovaVec4 NovaMath::normalize4(NovaVec4 vec){
    float mag = std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w);
    if (mag == 0) return NovaVec4(0, 0, 0, 0);
    return NovaVec4(vec.x / mag, vec.y / mag, vec.z / mag, vec.w / mag);
}



