#include <iostream>
#include <vector>
#include <memory>


class Observer {
public:
    virtual void update(float temperature) = 0;
    virtual ~Observer() = default;
};

class Subject {
public:
    virtual void addObserver(Observer* observer) = 0;
    virtual void removeObserver(Observer* observer) = 0;
    virtual void notifyObservers() = 0;
    virtual ~Subject() = default;
};


class WeatherStation : public Subject {
private:
    std::vector<Observer*> observers;
    float temperature;

public:
    void setTemperature(float temp) {
        temperature = temp;
        notifyObservers();
    }

    void addObserver(Observer* observer) override {
        observers.push_back(observer);
    }

    void removeObserver(Observer* observer) override {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notifyObservers() override {
        for (Observer* observer : observers) {
            observer->update(temperature);
        }
    }
};

class PhoneDisplay : public Observer {
private:
    std::string owner;

public:
    explicit PhoneDisplay(const std::string& owner) : owner(owner) {}

    void update(float temperature) override {
        std::cout << "Телефон " << owner << ": нова температура: " << temperature << "°C" << std::endl;
    }
};

class LEDPanel : public Observer {
public:
    void update(float temperature) override {
        std::cout << "LED-панель: температура зараз: " << temperature << "°C" << std::endl;
    }
};


int main() {
    WeatherStation station;

    PhoneDisplay phone1("Андрій");
    PhoneDisplay phone2("Марія");
    LEDPanel ledPanel;

    station.addObserver(&phone1);
    station.addObserver(&phone2);
    station.addObserver(&ledPanel);

    station.setTemperature(25.0f);
    station.setTemperature(30.0f);

    station.removeObserver(&phone2);
    station.setTemperature(20.0f);

    return 0;
}
