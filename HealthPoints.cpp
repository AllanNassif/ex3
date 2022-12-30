#include "HealthPoints.h"
#include <iostream>


HealthPoints::HealthPoints(int maxHP) {

    if(maxHP > 0){
        m_maxHP = maxHP;
        m_currentHP = maxHP;
    }
    else{
        throw InvalidArgument();
    }

}


void HealthPoints::handleHealthPointsEdge(){
    if(m_currentHP > m_maxHP){
        m_currentHP = m_maxHP;
    }
    if(m_currentHP < 0){
        m_currentHP = 0;
    }
}


HealthPoints& HealthPoints::operator+=(int hpToAdd){
    m_currentHP += hpToAdd;
    this->handleHealthPointsEdge();
    return *this;
}

HealthPoints& HealthPoints::operator-=(int hpToDecrease){
    m_currentHP -= hpToDecrease;
    this->handleHealthPointsEdge();
    return *this;
}

HealthPoints operator+(const HealthPoints& healthPoints, int hpToAdd){
    HealthPoints result = healthPoints;
    return (result += hpToAdd);
}

HealthPoints operator+(int hpToAdd, const HealthPoints& healthPoints){
    return healthPoints + hpToAdd;
}

HealthPoints operator-(const HealthPoints& healthPoints, int hpToDecrease){
    HealthPoints result = healthPoints;
    return (result -= hpToDecrease);
}

bool operator==(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2){
    return(healthPoints1.m_currentHP == healthPoints2.m_currentHP);
}
bool operator!=(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2){
    return !(healthPoints1 == healthPoints2);
}
bool operator<(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2){
    return(healthPoints1.m_currentHP < healthPoints2.m_currentHP);
}
bool operator<=(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2){
    return !(healthPoints1 > healthPoints2);
}
bool operator>(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2){
    return (healthPoints2 < healthPoints1);
}
bool operator>=(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2){
    return (healthPoints2 <= healthPoints1);
}


std::ostream& operator<<(std::ostream& stream , const HealthPoints& healthPoints){
    stream << healthPoints.m_currentHP << "(" << healthPoints.m_maxHP << ")";
    return stream;
    
}


