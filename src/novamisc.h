#pragma
#include "nova.h"
#include <string>
#include <iomanip>
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






















// State manager



class NovaStateManager {
    protected:
    std::map<std::string, std::function<void(void)>> states;
    
    public:
    std::string currentState;

    NovaStateManager(): states(), currentState(""){}

    void unset();
    void set(std::string state);
    int exec();


    template <typename Func>
    void add(std::string name, Func&& callback){ states[name] = std::function<void(void)>(callback); }
};















class SchedulerTask {
    public:
    std::string name;
    float duration;
    std::function<void(void)> callback;

    SchedulerTask() = default;
    SchedulerTask(const std::string& name, float duration, std::function<void(void)> callback)
        : name(name), duration(duration), callback(callback) {}
};






class NovaScheduler {
    private:
    static std::vector<SchedulerTask> tasks;

    public:

    static void addTask(const SchedulerTask& task);
    
    static void update();


    template <typename Func>
    static void addTask(const std::string& name, float duration, Func&& callback){
        tasks.push_back(SchedulerTask(name, duration, callback));
    }
};


































class NovaResourceManager {
    private:
    static std::map<std::string, NovaSound> sounds;
    static std::map<std::string, NovaRawTexture> rawTextures;

    public:

    static void loadSound(std::string name, std::string path);
    static void playSound(std::string name, int volume);

    static void loadTexture(std::string name, std::string path);
    static NovaRawTexture* getTexture(std::string name);
    
    static void disposeAll();
};













typedef struct {
    NovaObject4* object;
    std::string tag;
} TaggedObject;


class NovaTagDevice {
    private:
    static std::vector<TaggedObject> objects;

    public:

    static void addObject(std::string tag, NovaObject4* object);
    static NovaObject4* getFirst(std::string tag);
    static NovaList<NovaObject4*> getAll(std::string tag);
    static NovaList<NovaObject4*> getMax(std::string tag, int maxCount);

    static void removeFirst(std::string tag);
    static void removeAll(std::string tag);
    static void removeMax(std::string tag, int maxCount);
    
};



































// Shaders

typedef int ShaderLoc;
typedef int ShaderUniformType;



class NovaShader {
    private:
    RenderTexture2D shaderTex;
    RenderTexture2D drawTex;

    public:
    Shader rShader;
    Color background;



    NovaShader(std::string fragmentShader, std::string vertexShader): rShader(LoadShader(vertexShader.c_str(), fragmentShader.c_str())),
    shaderTex(LoadRenderTexture(GetScreenWidth(), GetScreenHeight())),
    drawTex(LoadRenderTexture(GetScreenWidth(), GetScreenHeight())),
    background(BLANK){}
    NovaShader() = default;



    ShaderLoc getLocation(std::string uniformName);

    template <typename T>
    void setValue(ShaderLoc loc, T* value, ShaderUniformType uniformType){
        SetShaderValue(rShader, loc, value, uniformType);
    }


    void startShader();
    void endShaderAndApply(float x = 0.0f, float y = 0.0f);

    bool loaded(){ return rShader.id != 0; }
    void dispose(){ if (loaded()) UnloadShader(rShader); }
};