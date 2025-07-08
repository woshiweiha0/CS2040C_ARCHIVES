#include "food.h"
#include <iostream>
using namespace std;

Food Food:: operator+(const Food& rhs) const
{
    string combinedName = m_name + " " + rhs.name();
    float combinedCalories = m_calories + rhs.calories();
    return Food(combinedName, combinedCalories);
}


bool Food:: operator<(const Food& rhs) const
{
    return true;
}

bool Food:: operator==(const Food& rhs) const
{
    return true;
}
