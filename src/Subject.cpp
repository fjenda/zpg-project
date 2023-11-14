//
// Created by Honza Fojtík on 5.11.2023.
//

#include "../Include/Subject.h"
#include "../Include/Observer.h"

void Subject::attach(Observer* observer) {
    this->observers.push_back(observer);
}

void Subject::detach(Observer* observer) {
    this->observers.erase(std::remove(this->observers.begin(), this->observers.end(), observer));
}

void Subject::notify(Event event) {
    for (auto observer : this->observers) {
        observer->update(event);
    }
}