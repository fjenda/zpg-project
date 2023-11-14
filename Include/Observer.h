/**
 * @file Observer.h
 *
 * @brief Observer pattern
 *
 * @details Observer pattern is used to notify all observers about changes in subject.
 *
 * @author Jan Fojtik
 *
 * @year 2023
 **/

#ifndef ZPGPROJECT_OBSERVER_H
#define ZPGPROJECT_OBSERVER_H

#include <vector>
#include <algorithm>
#include "Event.h"

class Subject;
class Observer {
public:
    virtual void update(Event event) = 0;
    virtual ~Observer() = default;
};

#endif //ZPGPROJECT_OBSERVER_H
