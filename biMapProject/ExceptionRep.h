//
// Created by hdani on 14/06/2023.
//

#ifndef SEMESTERB_TASK5_EXCEPTIONREP_H
#define SEMESTERB_TASK5_EXCEPTIONREP_H
#include "Exception.h"

class ExceptionRep : public Exception
{
    public:
        // Constructor for ExceptionRep class
        // Set the value of the member variable "m_problem" to the provided problem string
        // Set the value of the member variable "m_repName" to the provided rep name
        explicit ExceptionRep(const string& problem = "Unknown problem!", const string& repName = "Unknown rep"){m_problem = problem, m_repName = repName;}
        // Handler method to handle the exception
        // Print the exception information
        // Display the problem description of the exception
        virtual void handel(){cout << m_problem << endl << "This exception in regarding <" << m_repName << ">" << endl;}
    private:
        string m_repName;// Member variable to store the name of the representative related to the exception
};


#endif //SEMESTERB_TASK5_EXCEPTIONREP_H
