#pragma once

#include <stdexcept>
#include <vector>
#include "../entities/Predmet.h"

class PredmetManager {
private:
    std::vector<Predmet> predmetList;
public:
    void addPredmet(const Predmet& predmet) { predmetList.push_back(predmet); }

    const std::vector<Predmet>& getPredmets() const { return predmetList; }

    Predmet getPredmetByTitle(const std::string& title) const {
        for (const auto& predmet : predmetList) {
            if (predmet.getTitle() == title) {
                return predmet;
            }
        }
        throw std::runtime_error("Predmet not found");
    }

    Predmet getPredmetByCode(const std::string& code) const {
        for (const auto& predmet : predmetList) {
            if (predmet.getCode() == code) {
                return predmet;
            }
        }
        throw std::runtime_error("Predmet not found by code");
    }
};
