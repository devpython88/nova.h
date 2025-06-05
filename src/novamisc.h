#pragma
#include "nova.h"
#include <string>
#include "novajson.h"



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














class NovaMath {
    public:

    static float roundTo(float val, float step);

    static float normalize(float value);
    static NovaVec2 normalize2(NovaVec2 vec);
    static NovaVec3 normalize3(NovaVec3 vec);
    static NovaVec4 normalize4(NovaVec4 vec);
};












template <typename T>
class NovaList : public std::vector<T> {
    public:


    NovaList(): std::vector<T>(){}

    void pop_index(int index){
        this->erase(this->begin() + index);
    }


    bool has_item(auto item){
        for (auto& it : *this){
            if (it == item) return true;
        }
        return false;
    }
    

    void fill(int amount, auto genFunc){
        for (size_t i = 0; i < amount; i++){
            this->push_back(genFunc(i));
        }
    }
};












// Data device


class NovaDataDevice {
    public:
    static void saveData(std::string file, NovaJSON json);
    static void saveData(std::string file, std::vector<NovaJSON> jsons);
    static NovaJSON loadData(std::string file);
    static std::vector<NovaJSON> loadDataEx(std::string file);
};








// Object Group



class GroupItem {
    public:
    NovaObject4* obj;
    std::string tag;

    GroupItem(NovaObject4* obj, std::string tag): obj(obj), tag(tag){}
};




class NovaObjectGroup {

    private:
    NovaList<GroupItem> objects;

    public:
    NovaVec2 globalVelocity, globalAcceleration;


    NovaObjectGroup(): globalVelocity(0.0f, 0.0f), globalAcceleration(.1f, .1f){}


    void refresh();
    NovaList<NovaObject4*> getAll(std::string tag);
    NovaObject4* get(int index);
    void add(NovaObject4* obj, std::string tag);
    bool collidesWith(NovaObject4& other);


    template <typename Func>
    void forEach(Func&& logic){
        for (int i = 0; i < objects.size(); i++){
            logic(i, objects[i]);
        }
    }
};












// Notifyer


class NovaNotifier {
    private:
    static std::string currentMessage;
    static float maxTime;
    static float time;

    public:

    static void notify(std::string message);
    static void clear();
    static void show();
};