

#ifndef HEALTH_POINTS_H
#define HEALTH_POINTS_H

#include <iostream>

class HealthPoints{
 
public:


    /*
     * C'tor for HealthPoints class.
     * 
     * @param maxHP - Max health points.
     * @return
     * A new instance of HealthPoints if maxHP is positive integer,
     * else throws an exception: InvalidArgument.
    */
    HealthPoints(int maxHP = DEFAULT_MAX_HP);

    

    /*
     * operator+=
     * 
     * @param hpToAdd - The amount of hp to add.
     * @return
     * The instance of HealthPoints the operator has been used on,
     * after adding the amount of hp given by the parameter.
    */
    HealthPoints& operator+=(int hpToAdd);

    /*
     * operator-=
     * 
     * @param hpToDecrease - The amount of hp to decrease.
     * @return
     * The instance of HealthPoints the operator has been used on,
     * after decreasing the amount of hp given by the parameter.
    */
    HealthPoints& operator-=(int hpToDecrease);


    /*
     * Here we are explicitly telling the compiler to use the default methods.
    */
    ~HealthPoints() = default;
    HealthPoints& operator=(const HealthPoints& otherHealthPoints) = default;
    HealthPoints(const HealthPoints& healthPoints) = default;

    /*
    * InvalidArgument - Exception of invalid argument.
    */
    class InvalidArgument {};

private:

    int m_maxHP;
    int m_currentHP;

    /*The default max hp of a HealthPoints instance*/
    static const int DEFAULT_MAX_HP = 100;

    /*
     * handleHealthPointsEdge - checks if the HP is higher of maxHP or lower than 0 and fix accordingly.
     * 
    */
    void handleHealthPointsEdge();

    /*
    * operator==
    * 
    * @param healthPoints1 - The first object for comparison.
    * @param healthPoints2 - The second object for comparison.
    * @return
    * Returns true if the objects has the same current hp, else false.
    */  
    friend bool operator==(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2);

    /*
    * operator<
    * 
    * @param healthPoints1 - The first object for comparison.
    * @param healthPoints2 - The second object for comparison.
    * @return
    * Returns true if the first object has lower current hp than the second object, else false.
    */  
    friend bool operator<(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2);

    /*
    * operator<< - prints the healthPoints object in the format <currentValue>(<maxValue>)
    * 
    * @param stream - output stream.
    * @param healthPoints - instance of HealthPoints to print.
    * @return
    * Returns the output stream that has been used.
    */  
    friend std::ostream& operator<<(std::ostream& stream , const HealthPoints& healthPoints);

};

/*
* operator+
* 
* @param healthPoints - instance of HealthPoints.
* @param hpToAdd - The amount of hp to add.
* @return
* Returns a instance of HealthPoints, after adding hp to healthPoints object.
*/  
HealthPoints operator+(const HealthPoints& healthPoints, int hpToAdd);

/*
* operator+
* 
* @param hpToAdd - The amount of hp to add.
* @param healthPoints - instance of HealthPoints.
* @return
* Returns a instance of HealthPoints, after adding hp to healthPoints object.
*/  
HealthPoints operator+(int hpToAdd, const HealthPoints& healthPoints);

/*
* operator-
* 
* @param hpToDecrease - The amount of hp to decrease.
* @param healthPoints - instance of HealthPoints.
* @return
* Returns a instance of HealthPoints, after decreasing hp to healthPoints object.
*/  
HealthPoints operator-(const HealthPoints& healthPoints, int hpToDecrease);



/*
* operator!=
* 
* @param healthPoints1 - The first object for comparison.
* @param healthPoints2 - The second object for comparison.
* @return
* Returns true if the objects does not have the same current hp, else false.
*/  
bool operator!=(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2);



/*
* operator<=
* 
* @param healthPoints1 - The first object for comparison.
* @param healthPoints2 - The second object for comparison.
* @return
* Returns true if the first object has lower or equal current hp than the second object, else false.
*/  
bool operator<=(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2);

/*
* operator>
* 
* @param healthPoints1 - The first object for comparison.
* @param healthPoints2 - The second object for comparison.
* @return
* Returns true if the first object has more current hp than the second object, else false.
*/  
bool operator>(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2);

/*
* operator>=
* 
* @param healthPoints1 - The first object for comparison.
* @param healthPoints2 - The second object for comparison.
* @return
* Returns true if the first object has more or equal current hp than the second object, else false.
*/  
bool operator>=(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2);


#endif