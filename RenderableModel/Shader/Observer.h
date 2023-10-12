//
// Created by Honza Fojtík on 12.10.2023.
//

#ifndef ZPGPROJECT_OBSERVER_H
#define ZPGPROJECT_OBSERVER_H

#include <vector>
#include <algorithm>

class Subject;
class Observer {
public:
    virtual void update(Subject* subject) = 0;
    virtual ~Observer() = default;
};

class Subject {
private:
    std::vector<Observer*> observers;
public:
    virtual ~Subject() = default;
    void attach(Observer* observer);
    void detach(Observer* observer);
    void notify();
};


#endif //ZPGPROJECT_OBSERVER_H
