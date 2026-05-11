#ifndef EXAM_H
#define EXAM_H

#include "GradedItem.h"

class Exam : public GradedItem {
    string name;
    float pointsEarned;
    float pointsPossible;
public:
    Exam(const string& name, float earned, float possible)
        : name(name), pointsEarned(earned), pointsPossible(possible) {}
    string getName() const override { return name; }
    string getCategory() const override { return "Exam"; }
    float getPointsEarned() const override { return pointsEarned; }
    float getPointsPossible() const override { return pointsPossible; }
    float getPercentage() const override {
        return (pointsPossible > 0) ? (pointsEarned / pointsPossible) * 100 : 0;
    }
};

#endif
