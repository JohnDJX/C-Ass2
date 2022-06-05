#include "PatientFileLoader.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "Patient.h"
#include "Vitals.h"

using namespace std;


std::vector<Patient*> PatientFileLoader::loadPatientFile(const std::string& file)

{
	vector<Patient*> patients{};

    std::ifstream inFile(file);

    string strLine;

    std::tm t{ };
    std::istringstream ss("18-02-1980");
    ss >> std::get_time(&t, "%d-%m-%Y");

    if (inFile.is_open()) {
        // TODO: load your file here
        // print the file
        char c = inFile.get();
        while (getline(inFile, strLine)) {
            stringstream ss(strLine);
            string strTmp;
            int i = 0;
            string uid, firstname, lastname;
            string birthday;
            string disease;
            while (getline(ss, strTmp, '|')) {
                if (i == 0)uid = strTmp;
                else if (i == 1)firstname = strTmp;
                else if (i == 2)birthday = strTmp;
                else if (i == 3)disease = strTmp;
                i++;
            }
            Patient* p = new Patient(uid, firstname, t);  
            patients.push_back(p);
        }  
    }
    else {
        //show erroe message
        std::cout << "Error opening ";
    }

    return patients;

}
