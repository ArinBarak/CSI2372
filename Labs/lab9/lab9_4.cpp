//Lab 9
//Exercice 4

#include <iostream>
#include <map>
#include <functional>
#include <memory>

class Sensor {
public:
    virtual ~Sensor() = default;
    virtual void handleEvent() const = 0;
};

class TemperatureSensor : public Sensor {
public:
    void handleEvent() const override {
        std::cout << "Handling Temperature Sensor event: Adjusting temperature threshold.\n";
    }
};

class PressureSensor : public Sensor {
public:
    void handleEvent() const override {
        std::cout << "Handling Pressure Sensor event: Checking pressure levels.\n";
    }
};

using EventHandler = void(Sensor::*)() const;

class SensorSystem {
private:
    std::map<int, std::unique_ptr<Sensor>> sensors;
    std::map<int, EventHandler> eventHandlers;

public:
    void addSensor(int id, std::unique_ptr<Sensor> sensor) {
        sensors[id] = std::move(sensor);
        eventHandlers[id] = &Sensor::handleEvent;
    }

    void triggerEvent(int id) {
        if (eventHandlers.find(id) != eventHandlers.end()) {
            (sensors[id].get()->*eventHandlers[id])();
        } else {
            std::cout << "No handler for sensor ID: " << id << "\n";
        }
    }

    void triggerAllEvents() {
        for (const auto& sensorPair : sensors) {
            triggerEvent(sensorPair.first);
        }
    }
};

int main() {
    SensorSystem system;

    system.addSensor(1, std::make_unique<TemperatureSensor>());
    system.addSensor(2, std::make_unique<PressureSensor>());

    std::cout << "Triggering events for individual sensors:\n";
    system.triggerEvent(1);
    system.triggerEvent(2);
}
