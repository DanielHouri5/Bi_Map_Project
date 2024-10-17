# include <iostream>
#include <fstream>
# include <string>
# include "BiMap.h"
#include "City.h"
#include "ExceptionCity.h"
#include "ExceptionRep.h"
void add_city(BiMap<City<long>,string>& myMap, fstream& inputFile, fstream& outputFile);
void add_name(BiMap<City<long>,string>& myMap, fstream& inputFile, fstream& outputFile);
void erase_by_city(BiMap<City<long>,string>& myMap, fstream& inputFile, fstream& outputFile);
void erase_by_name(BiMap<City<long>,string>& myMap, fstream& inputFile, fstream& outputFile);
void get_city(BiMap<City<long>,string>& myMap, fstream& inputFile, fstream& outputFile);
void get_name(BiMap<City<long>,string>& myMap, fstream& inputFile, fstream& outputFile);
void is_city(BiMap<City<long>,string>& myMap, fstream& inputFile, fstream& outputFile);
void is_name(BiMap<City<long>,string>& myMap, fstream& inputFile, fstream& outputFile);
bool checkName1(string& name);
bool checkName2(string& name);
bool checkTheFirstLetter(string& name, int &indexOfTav);
bool checkTheOtherLetter(string& name, int &startIndex, char endChar);
using namespace std;
typedef enum {addCity = 1, addName, eraseByCity, eraseByName, getCity, getName, isCity, isName, sortByCity, sortByName, Clean, Exit}options;
typedef BiMap<City<long>,string>biMapOfCityAndRep;
typedef BiMap<int, string> idNameBiMap;
int main()
{
    // Create an instance of BiMap with City<long> as the key and string as the value
    biMapOfCityAndRep myMap;

    int option;
    bool flag = true;

    fstream inputFile, outputFile;
    string inputFileName, outputFileName;

    // Read the input file name from the user
    cout << "Please enter the name of the input File:" << endl;
    cin >> inputFileName;
    // Read the output file name from the user
    cout << "Please enter the name of the output File:" << endl;
    cin >> outputFileName;
    // Open the input file for reading
    inputFile.open(inputFileName, ios::in);
    // Open the output file for writing
    outputFile.open(outputFileName, ios::out);

    if (!inputFile || !outputFile)
        // Display an error message if the file opening fails
        cout << "Error in open!" << endl;
    else
        while (flag)
        {
            // Read the option from the input file
            inputFile >> option;
            switch (option)
            {
                case addCity:
                    // Call the add_city function with the appropriate parameters
                    add_city(myMap, inputFile, outputFile);
                    break;
                case addName:
                    // Call the add_name function with the appropriate parameters
                    add_name(myMap, inputFile, outputFile);
                    break;
                case eraseByCity:
                    // Call the erase_by_city function with the appropriate parameters
                    erase_by_city(myMap, inputFile, outputFile);
                    break;
                case eraseByName:
                    // Call the erase_by_name function with the appropriate parameters
                    erase_by_name(myMap, inputFile, outputFile);
                    break;
                case getCity:
                    // Call the get_city function with the appropriate parameters
                    get_city(myMap, inputFile, outputFile);
                    break;
                case getName:
                    // Call the get_name function with the appropriate parameters
                    get_name(myMap, inputFile, outputFile);
                    break;
                case isCity:
                    // Call the is_city function with the appropriate parameters
                    is_city(myMap, inputFile, outputFile);
                    break;
                case isName:
                    // Call the is_name function with the appropriate parameters
                    is_name(myMap, inputFile, outputFile);
                    break;
                case sortByCity:
                    // Call the sortByCityAndPrint member function of myMap
                    myMap.sortByCityAndPrint(outputFile);
                    break;
                case sortByName:
                    // Call the sortByRepAndPrint member function of myMap
                    myMap.sortByRepAndPrint(outputFile);
                    break;
                case Clean:
                    // Call the clearMap member function of myMap
                    myMap.clearMap();
                    break;
                case Exit:
                    inputFile.close();// Close the input file
                    outputFile.close();// Close the output file
                    flag = false;//Changing the value of 'flag' to false so that the while loop ends.
                    break;
                default:
                    // Print "Not available" to the output file if the option is not recognized
                    outputFile << "Not available" << endl;
            }
        }
    return 0;
}

// This function adds a city and its representative name to the BiMap.
void add_city(BiMap<City<long>,string>& myMap, fstream& inputFile, fstream& outputFile)
{
    City<long>city;
    try {
        inputFile >> city;// Read city data from input file
        // Validate city name
        if (!city.nameIsValid(city.getName()) && !checkName1(city.getName()))
            throw ExceptionCity("The name of the city is not valid!", city.getName());
        // Validate city size
        if (city.getSize() < 0)
            throw ExceptionCity("The size of the city is not valid!", city.getName());
    }
    catch (ExceptionCity& exp)
    {
        outputFile << "error" << endl;
        exp.handel();
        return;
    }

    string repName;
    try {
        inputFile >> repName;// Read representative name from input file
        // Validate representative name
        if (!checkName1(repName) && !checkName2(repName))
            throw ExceptionRep("The name of the rep is not valid!", repName);
    }
    catch (ExceptionRep& exp)
    {
        outputFile << "error" << endl;
        exp.handel();
        return;
    }

    try {
        // Insert the city and representative name into the BiMap
        if (!myMap.insert(repName, city))
            throw ExceptionCity("The city is not unique!", city.getName());
    }
    catch (ExceptionCity& exp)
    {
        outputFile << "error" << endl;
        exp.handel();
    }
}

// This function adds a representative name and its associated city to the BiMap.
void add_name(BiMap<City<long>,string>& myMap, fstream& inputFile, fstream& outputFile)
{
    string repName;
    try {
        inputFile >> repName;// Read representative name from input file
        // Validate representative name
        if (!checkName1(repName) && !checkName2(repName))
            throw ExceptionRep("The name of the rep is not valid!", repName);
    }
    catch (ExceptionRep& exp)
    {
        outputFile << "error" << endl;
        exp.handel();
        return;
    }

    City<long>city;
    try {
        inputFile >> city;// Read city data from input file
        // Validate city name
        if (!city.nameIsValid(city.getName()) && !checkName1(city.getName()))
            throw ExceptionCity("The name of the city is not valid!", city.getName());
        // Validate city size
        if (city.getSize() < 0)
            throw ExceptionCity("The size of the city is not valid!", city.getName());
    }
    catch (ExceptionCity& exp)
    {
        outputFile << "error" << endl;
        exp.handel();
        return;
    }

    try{
        // Insert the city and representative name into the BiMap
        if (!myMap.insert(city, repName))
            throw ExceptionRep("The rep is not unique!", repName);
    }
    catch (ExceptionRep& exp)
    {
        outputFile << "error" << endl;
        exp.handel();
    }
}

// This function erases a city from the BiMap by its ID.
void erase_by_city(BiMap<City<long>,string>& myMap, fstream& inputFile, fstream& outputFile)
{
    long cityId;
    City<long> city;
    try {
        inputFile >> cityId;// Read city ID from input file
        city.setCityId(cityId);
        // Check if the city exists in the map
        if (!myMap.find(city))
            throw ExceptionCity("There is no city in the map with the inputted id!", city.getName());
    }
    catch (ExceptionCity& exp)
    {
        outputFile << "error" << endl;
        exp.handel();
        return;
    }
    try
    {
        // Erase the city from the BiMap
        if (!myMap.erase(city))
            throw ExceptionCity("The city in not exist in the map!", city.getName());
    }
    catch (ExceptionCity& exp)
    {
        outputFile << "error" << endl;
        exp.handel();
    }
}

// This function erases a representative name from the BiMap.
void erase_by_name(BiMap<City<long>,string>& myMap, fstream& inputFile, fstream& outputFile)
{
    string repName;
    try {
        inputFile >> repName;// Read representative name from input file
        // Validate representative name
        if (!checkName1(repName) && !checkName2(repName))
            throw ExceptionRep("The name of the rep is not valid!", repName);
    }
    catch (ExceptionRep& exp)
    {
        outputFile << "error" << endl;
        exp.handel();
        return;
    }

    try {
        // Erase the representative from the BiMap
        if (!myMap.erase(repName))
            throw ExceptionRep("The rep is not exist in the map!", repName);
    }
    catch (ExceptionRep& exp)
    {
        outputFile << "error" << endl;
        exp.handel();
    }
}

// This function retrieves the city associated with a representative name from the BiMap.
void get_city(BiMap<City<long>,string>& myMap, fstream& inputFile, fstream& outputFile)
{
    string repName;
    try {
        inputFile >> repName;// Read representative name from input file
        // Validate representative name
        if (!checkName1(repName) && !checkName2(repName))
            throw ExceptionRep("The name of the rep is not valid!", repName);
    }
    catch (ExceptionRep& exp)
    {
        outputFile << "error" << endl;
        exp.handel();
        return;
    }
    try {
        // Check if the representative exists in the map
        if (!myMap.find(repName))
            throw ExceptionRep("The rep is not unique!", repName);
        // Output the city associated with the representative
        outputFile << myMap[repName];
    }
    catch (ExceptionRep& exp)
    {
        outputFile << "error" << endl;
        exp.handel();
    }
}

// This function retrieves the representative name associated with a city ID from the BiMap.
void get_name(BiMap<City<long>,string>& myMap, fstream& inputFile, fstream& outputFile)
{
    long cityId;
    City<long> city;
    try {
        inputFile >> cityId;// Read city ID from input file
        city.setCityId(cityId);
        // Check if the city exists in the map
        if (!myMap.find(city))
            throw ExceptionCity("There is no city in the map with the inputted id!", city.getName());
    }
    catch (ExceptionCity& exp)
    {
        outputFile << "error" << endl;
        exp.handel();
        return;
    }

    try {
        // Find the representative associated with the city and output it
        for (BiMap<City<long>,string>::iteratorS i = myMap.beginS(); i != myMap.endS(); ++i)
            if (city == i.getFirst())
            {
                outputFile << myMap[i.getFirst()] << endl;
                return;
            }
        throw ExceptionCity("The city is not exist!", city.getName());
    }
    catch (ExceptionCity& exp)
    {
        outputFile << "error" << endl;
        exp.handel();
    }
}

// This function checks if a city with a given ID exists in the BiMap.
void is_city(BiMap<City<long>,string>& myMap, fstream& inputFile, fstream& outputFile)
{
    long cityId;
    City<long> city;
    inputFile >> cityId;// Read city ID from input file
    city.setCityId(cityId);
    // Check if the city exists in the map and output result
    if (myMap.find(city))
        outputFile << "Yes" << endl;
    else
        outputFile << "No" << endl;
}

// This function checks if a representative name exists in the BiMap.
void is_name(BiMap<City<long>,string>& myMap, fstream& inputFile, fstream& outputFile)
{
    string repName;
    try {
        inputFile >> repName;// Read representative name from input file
        // Validate representative name
        if (!checkName1(repName) && !checkName2(repName))
            throw ExceptionRep("The name of the rep is not valid!", repName);
    }
    catch (ExceptionRep& exp)
    {
        outputFile << "error" << endl;
        exp.handel();
        return;
    }

    // Check if the representative exists in the map and output result
    if (myMap.find(repName))
        outputFile << "Yes" << endl;
    else
        outputFile << "No" << endl;
}

// This function checks if the given name follows the first name - hyphen - last name format.
bool checkName1(string& name)
{
    // Set the index to 0 and check the first letter of the name
    int i = 0;
    if (!checkTheFirstLetter(name, i))
        return false;

    // Move to the next index and check for a space character
    ++i;
    if (!checkTheOtherLetter(name, i, HYPHEN))
        return false;

    // Move to the next index and check the first letter of the last name
    ++i;
    if (!checkTheFirstLetter(name, i))
        return false;
    return checkTheOtherLetter(name, i, '\0');
}

// This function checks if the given name follows the first name format without a hyphen.
bool checkName2(string& name)
{
    int i = 0;
    if (!checkTheFirstLetter(name, i))
        return false;

    // Move to the next index and check for a space character
    ++i;
    return checkTheOtherLetter(name, i, '\0');
}

// This function checks if the first letter of the name is an uppercase letter.
bool checkTheFirstLetter(string& name, int &indexOfTav)
{
    // Check if the first letter is a lowercase letter
    if (name[indexOfTav] >= MIN_LOWER_CASE_LETTER && name[indexOfTav] <= MAX_LOWER_CASE_LETTER)
        // If it is, convert it to uppercase
        name[indexOfTav] -= MIN_LOWER_CASE_LETTER - MIN_UPPER_CASE_LETTER;
    // Check if the first letter is now an uppercase letter
    return name[indexOfTav] >= MIN_UPPER_CASE_LETTER && name[indexOfTav] <= MAX_UPPER_CASE_LETTER;
}

// This function checks if the characters between startIndex and endChar are all lowercase letters.
bool checkTheOtherLetter(string& name, int &startIndex, char endChar)
{
    // Loop through the string until the end character is reached
    while (name[startIndex] != endChar)
    {
        // If the current character is an uppercase letter, convert it to lowercase
        if (name[startIndex] >= MIN_UPPER_CASE_LETTER && name[startIndex] <= MAX_UPPER_CASE_LETTER)
            name[startIndex] += MIN_LOWER_CASE_LETTER - MIN_UPPER_CASE_LETTER;
        // Check if the current character is a lowercase letter
        if (name[startIndex] < MIN_LOWER_CASE_LETTER || name[startIndex] > MAX_LOWER_CASE_LETTER)
            // If it's not, return false
            return false;
        // Move to the next character in the string
        ++startIndex;
    }
    // If all characters between the first and end character are lowercase letters, return true
    return true;
}