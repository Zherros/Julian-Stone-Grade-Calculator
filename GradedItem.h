#ifndef GRADEDITEM_H
#define GRADEDITEM_H

#include <string>
using namespace std;

class GradedItem {
public:
    virtual ~GradedItem() = default;
    virtual string getName() const = 0;
    virtual string getCategory() const = 0;
    virtual float getPointsEarned() const = 0;
    virtual float getPointsPossible() const = 0;
    virtual float getPercentage() const = 0;
};

#endif
