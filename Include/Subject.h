/**
 * @file Subject.h
 *
 * @brief Observer pattern
 *
 * @details Observer pattern is used to notify all observers about changes in subject.
 *
 * @author Jan Fojtik
 *
 * @year 2023
 **/

#ifndef ZPGPROJECT_SUBJECT_H
#define ZPGPROJECT_SUBJECT_H

#include <vector>
#include <algorithm>
#include "Event.h"

class Observer;
class Subject {
private:
    std::vector<Observer*> observers;
public:
    virtual ~Subject() = default;
    void attach(Observer* observer);
    void detach(Observer* observer);
    void notify(Event event);
};

#endif //ZPGPROJECT_SUBJECT_H
