//
// Created by hdani on 14/06/2023.
//

#ifndef SEMESTERB_TASK5_EXCEPTIONCITY_H
#define SEMESTERB_TASK5_EXCEPTIONCITY_H
#include "Exception.h"

class ExceptionCity : public Exception
{
    public:
        // Constructor for ExceptionCity class
        // Set the value of the member variable "m_problem" to the provided problem string
        // Set the value of the member variable "m_name" to the provided city name
        explicit ExceptionCity(const string& problem = "Unknown problem!", const string& cityName = "UnknownCity"){m_problem = problem, m_name = cityName;}
        // Handler method to handle the exception
        // Print the exception information
        // Display the problem description of the exception
        virtual void handel(){cout << "Exception in City <" << m_name << ">" << endl << m_problem << endl;}
    private:
        string m_name;// Member variable to store the name of the city where the exception occurred
};


#endif //SEMESTERB_TASK5_EXCEPTIONCITY_H
