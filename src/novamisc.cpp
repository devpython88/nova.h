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
















// Nova data device


void NovaDataDevice::saveData(std::string file, NovaJSON json){
    std::ofstream fs(file, std::ios::binary);

    if (!fs.is_open()){
        throw std::runtime_error("Could not create file for saving data: " + file);
    }
    
    // Get string json
    std::string data = json._nlJsonData.dump();

    uint32_t size = data.size();

    // Write binary
    fs.write(reinterpret_cast<char*>(&size), sizeof(size));
    fs.write(data.data(), size);

    fs.close();
}

void NovaDataDevice::saveData(std::string file, std::vector<NovaJSON> jsons){
    nlohmann::json j = nlohmann::json::array();

    // Convert jsons array into json
    for (const NovaJSON& it : jsons){
        j.push_back(it._nlJsonData);
    }

    // save file
    NovaJSON nJ;
    nJ._nlJsonData = j;
    saveData(file, nJ);
}

NovaJSON NovaDataDevice::loadData(std::string file){
    std::ifstream in(file, std::ios::binary);
    
    if (!in.is_open()){
        throw std::runtime_error("Could not load file for data reading: " + file);
    }

    uint32_t size; // size holder

    // Read size
    in.read(reinterpret_cast<char*>(&size), sizeof(size));

    // Read data
    std::string data(size, '\0');
    in.read(&data[0], size);

    // convert to json
    NovaJSON json;
    json._nlJsonData = nlohmann::json::parse(data);
    return json;
}

std::vector<NovaJSON> NovaDataDevice::loadDataEx(std::string file){
    NovaJSON json = loadData(file);
    auto arr = json._nlJsonData.get<std::vector<nlohmann::json>>();
    std::vector<NovaJSON> newArr;

    for (const auto& it : arr){
        NovaJSON j;
        j._nlJsonData = it;
        newArr.push_back(j);
    }

    return newArr;
}






// Nova object group


void NovaObjectGroup::refresh(){
    for (auto obj : objects){
        obj.obj->acceleration = globalAcceleration;
        obj.obj->velocity = globalVelocity;
    }
}

NovaList<NovaObject4*> NovaObjectGroup::getAll(std::string tag){
    NovaList<NovaObject4*> matches;

    for (auto obj : objects){
        if (obj.tag == tag) matches.push_back(obj.obj);    
    }

    return matches;
}

NovaObject4* NovaObjectGroup::get(int index){
    if (index >= objects.size()) throw std::runtime_error("Index out of bounds: " + index);

    return objects.at(index).obj;
}

void NovaObjectGroup::add(NovaObject4* obj, std::string tag){
    objects.push_back(GroupItem(obj, tag));
}

bool NovaObjectGroup::collidesWith(NovaObject4& other){
    for (auto obj : objects){
        if (NovaRenderDevice::checkCollision(*obj.obj, other)) return true;
    }

    return false;
}





// Notifyer

std::string NovaNotifier::currentMessage = "";
float NovaNotifier::maxTime = 2.5f;
float NovaNotifier::time = 0.0f;



void NovaNotifier::notify(std::string message){
    currentMessage = message;
    time = maxTime;
}

void NovaNotifier::clear(){
    currentMessage = "";
    time = 0.0f;
}

void NovaNotifier::show(){
    if (time > 0.0f){
        NovaRenderDevice::uiButton(currentMessage, NovaVec2(0, 0), BLACK, WHITE, 20);
        time -= GetFrameTime();
    }
}









// State manager



void NovaStateManager::unset(){
    currentState = "";
}

void NovaStateManager::set(std::string state){
    currentState = state;
}

int NovaStateManager::exec(){
    if (currentState == "") return 0;
    if (states.find(currentState) == states.end()) return 1;

    states[currentState]();
    return 0;
}
















std::vector<SchedulerTask> NovaScheduler::tasks = std::vector<SchedulerTask>();



void NovaScheduler::addTask(const SchedulerTask& task){
    tasks.push_back(task);
}

void NovaScheduler::update(){
    if (tasks.empty()) return;
    
    float frameTime = GetFrameTime();
    for (int i = tasks.size() - 1; i >= 0; i--){
        auto& task = tasks[i];

        if (task.duration > 0.0f){
            task.duration -= frameTime;
            continue;
        }
        
        task.callback();
        tasks.erase(tasks.begin() + i);
    }
}






std::map<std::string, NovaSound> NovaResourceManager::sounds = std::map<std::string, NovaSound>();
std::map<std::string, NovaRawTexture> NovaResourceManager::rawTextures = std::map<std::string, NovaRawTexture>();


void NovaResourceManager::loadSound(std::string name, std::string path){
    if (sounds.find(name) == sounds.end()){
        sounds.emplace(
            std::piecewise_construct,
            std::forward_as_tuple(name),
            std::forward_as_tuple(path)
        );
    }
}

void NovaResourceManager::playSound(std::string name, int volume){
    if (sounds.find(name) != sounds.end()){
        sounds[name].volume(volume);
        sounds[name].play();
    }
}

void NovaResourceManager::loadTexture(std::string name, std::string path){
    if (rawTextures.find(name) == rawTextures.end()){
        rawTextures.emplace(
            std::piecewise_construct,
            std::forward_as_tuple(name),
            std::forward_as_tuple(path)  
        );
    }
}

NovaRawTexture* NovaResourceManager::getTexture(std::string name){
    if (rawTextures.find(name) != rawTextures.end()){
        return &rawTextures[name];
    }

    return nullptr;
}

void NovaResourceManager::disposeAll(){
    for (auto pair : sounds){
        if (pair.second.loaded()) UnloadSound(pair.second.sound);
    }

    for (auto pair : rawTextures){
        if (pair.second.getTextureID() != 0) pair.second.dispose();
    }
}
