#ifndef OBSERVER_H_
#define OBSERVER_H_

#include <algorithm>
#include <vector>

class Observer {
public:
    virtual void update() = 0;
    virtual ~Observer() {};
};

class Observable {
private:
    std::vector<Observer* > observers;
public:
    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }
    void removeObserver(Observer* observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }
    void notify() {
        for (Observer* observer : observers) {
            observer->update();
        }
    }
    virtual ~Observable() {};

};

#endif /* OBSERVER_H_ */
