//
// Created by Honza Fojtík on 12.10.2023.
//

#include "../Include/Observer.h"

void Subject::attach(Observer* observer) {
    this->observers.push_back(observer);
}

void Subject::detach(Observer* observer) {
    this->observers.erase(std::remove(this->observers.begin(), this->observers.end(), observer));
}

void Subject::notify() {
    fprintf(stdout, "[DEBUG] Notifying observers\n");
    for (auto observer : this->observers) {
        observer->update(this);
    }
}