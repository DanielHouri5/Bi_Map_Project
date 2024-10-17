//
// Created by hdani on 14/06/2023.
//

#ifndef SEMESTERB_TASK5_CITY_H
#define SEMESTERB_TASK5_CITY_H
#include <iostream>
#define MIN_DIGIT_OF_ID '0'
#define MAX_DIGIT_OF_ID '9'
#define HYPHEN '-'
#define SPACE ' '
#define MIN_LOWER_CASE_LETTER 'a'
#define MAX_LOWER_CASE_LETTER 'z'
#define MIN_UPPER_CASE_LETTER 'A'
#define MAX_UPPER_CASE_LETTER 'Z'
using namespace std;

template <class T>
class City
{
public:
    // Constructor for City class
    explicit City(const T& cityId = '\0', const string& name = "UnknownCity", const int& citySize = 0);
    // Copy constructor for City class
    City(const City& other);
    // Destructor for City class
    ~City(){;}

    // Check if the name of the city is valid
    bool nameIsValid(basic_string<char> name);
    // Getter for the city name
    string& getName(){return m_name;}
    // Getter for the city size
    int& getSize(){return m_citySize;}
    // Setter for the city ID
    void setCityId(const T& cityId){m_cityId = cityId;}

    // Equality operator
    bool operator==(const City& other)const;
    // Inequality operator
    bool operator!=(const City& other)const;
    // Less than operator
    bool operator<(const City& other)const;
    // Greater than operator
    bool operator>(const City& other)const;

    // Assignment operator
    City<T>& operator=(const City& other);

    // Friend function to overload the input stream operator for City class
    friend std::istream& operator>>(std::istream& input, City<T>& thisCity)
    {
        // Read the city ID from the input stream
        input >> thisCity.m_cityId;
        // Read the city name from the input stream
        input >> thisCity.m_name;
        // Read the city size from the input stream
        input >> thisCity.m_citySize;
        return input;
    }
    // Friend function to overload the output stream operator for City class
    friend std::ostream& operator<<(std::ostream& output, const City<T>& thisCity)
    {
        // Write the city ID to the output stream
        output << "[" << thisCity.m_cityId << "]" << SPACE;
        // Write the city name to the output stream
        output << thisCity.m_name << SPACE;
        // Write the city size to the output stream
        output << thisCity.m_citySize << endl;
        return output;
    }

private:
    string m_name;// Member variable to store the name of the city
    int m_citySize;// Member variable to store the size of the city
    T m_cityId;// Member variable to store the ID of the city
};

// Constructor for City class
template<class T>
City<T>::City(const T &cityId, const string& name, const int &citySize)
{
    // Assign the name parameter to the member variable m_name
    m_name = name;
    // Assign the citySize parameter to the member variable m_citySize
    m_citySize = citySize;
    // Assign the cityId parameter to the member variable m_cityId
    m_cityId = cityId;
}

// Copy constructor for City class
template<class T>
City<T>::City(const City &other)
{
    // Copy the name from the other City object to m_name
    m_name = other.m_name;
    // Copy the city size from the other City object to m_citySize
    m_citySize = other.m_citySize;
    // Copy the city ID from the other City object to m_cityId
    m_cityId = other.m_cityId;
}

template<class T>
bool City<T>::nameIsValid(basic_string<char> name)
{
    // Set the index to 0 and check the first letter of the name
    int i = 0;
    if (name[i] < MIN_UPPER_CASE_LETTER || name[i] > MAX_UPPER_CASE_LETTER)
        return false;

    // Move to the next index and check for a space character
    ++i;
    while (name[i] != '\0')
    {
        // Check if the current character is a lowercase letter
        if (name[i] < MIN_LOWER_CASE_LETTER || name[i] > MAX_LOWER_CASE_LETTER)
            // If it's not, return false
            return false;
        // Move to the next character in the string
        ++i;
    }
    return true;
}

// Equality operator
template<class T>
bool City<T>::operator==(const City &other) const
{
    // Check if the city IDs are equal
    return m_cityId == other.m_cityId;
}

// Inequality operator
template<class T>
bool City<T>::operator!=(const City &other) const
{
    // Check if the city IDs are not equal
    return m_cityId != other.m_cityId;
}

// Less than operator
template<class T>
bool City<T>::operator<(const City &other) const
{
    // Check if the city ID is less than the other city's ID
    return m_cityId < other.m_cityId;
}

// Greater than operator
template<class T>
bool City<T>::operator>(const City &other) const
{
    // Check if the city ID is greater than the other city's ID
    return m_cityId > other.m_cityId;
}

// Assignment operator
template<class T>
City<T> &City<T>::operator=(const City &other)
{
    // If the name of the other city is not valid, assign "UnknownCity" to m_name
    if (!nameIsValid(other.m_name))
        m_name = "UnknownCity";
    else
        // Otherwise, copy the name from the other city to m_name
        m_name = other.m_name;
    // If the city size of the other city is negative, assign 0 to m_citySize
    if (other.m_citySize < 0)
        m_citySize = 0;
    else
        // Otherwise, copy the city size from the other city to m_citySize
        m_citySize = other.m_citySize;
    // Copy the city ID from the other city to m_cityId
    m_cityId = other.m_cityId;
    // Return the current City object
    return *this;
}

#endif //SEMESTERB_TASK5_CITY_H
