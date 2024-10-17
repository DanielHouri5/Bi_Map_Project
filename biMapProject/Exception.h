//
// Created by hdani on 14/06/2023.
//

#ifndef SEMESTERB_TASK5_EXCEPTION_H
#define SEMESTERB_TASK5_EXCEPTION_H
#include <iostream>
using namespace std;
class Exception
{
    public:
        // Constructor for the Exception class
        // Set the value of the member variable "m_problem" to the provided problem string
        explicit Exception(const string& problem = "Unknown problem!"){m_problem = problem;}
        // Virtual destructor for the Exception class
        virtual ~Exception(){;}
        // Pure virtual function to handle the exception (needs to be implemented by derived classes)
        virtual void handel() = 0;
    protected:
        string m_problem;// Member variable to store the problem description of the exception
};


#endif //SEMESTERB_TASK5_EXCEPTION_H
