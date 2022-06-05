#include "Patient.h"

#include <iomanip>
#include <iostream>
#include <sstream>

#include "Vitals.h"


using namespace std;

const std::string Diagnosis::SIMIAN_FLU = "SimianFlu";
const std::string Diagnosis::GREYSCALE = "Greyscale";
const std::string Diagnosis::BONEITIS = "Boneitis";


Patient::Patient(const std::string& firstName, const std::string& lastName, std::tm birthday) :
	Person(firstName, lastName, birthday),
	_alertLevel(AlertLevel::Green)
{
}

int Patient::age() const
{	
	// an inaccurate age estimate but fine for assignment purposes
	return 2022 - (1900 + _birthday.tm_year);
}

std::string Patient::uid() const
{
	std::stringstream ss;
	ss << (char)std::tolower(_lastName.at(0)) 
	   << (char)std::tolower(_firstName.at(0))
	   << std::setfill('0') << std::setw(2) << (_birthday.tm_mon + 1) 
	   << _birthday.tm_year;
	return ss.str();
}

std::string Patient::humanReadableID() const
{
	return "" + _lastName + ", " + _firstName + " (" + uid() + ")";
}

std::ostream& operator<<(std::ostream& os, const Patient& p)
{
	os << p.uid() << "|" << p._lastName << "," << p._firstName << "|" << std::put_time(&p._birthday, "%d-%m-%Y") << "|" << p.primaryDiagnosis();
	
	os << "|";
	for (int i = 0; i < p.vitals().size(); ++i) {
		auto v = p.vitals()[i];
		os << *v;
		if (i != p.vitals().size() - 1) {
			os << ";";
		}
	}
	return os;
}

void Patient::addDiagnosis(const std::string& diagnosis)
{
	_diagnosis.push_back(diagnosis);
}

const std::string& Patient::primaryDiagnosis() const
{
	return _diagnosis.front();
}

void Patient::addVitals(const Vitals* v)
{
	_vitals.push_back(v);
	auto disease = primaryDiagnosis();
	// TODO: calculate alert levels
	if (disease == Diagnosis::SIMIAN_FLU)
	{
		auto BP = v->BP();
		if (BP > 140) setAlertLevel(AlertLevel::Red);
		else if (BP > 130) setAlertLevel(AlertLevel::Orange);
		else if (BP > 110) setAlertLevel(AlertLevel::Yellow);
		else setAlertLevel(AlertLevel::Green);
	}
	else if (disease == Diagnosis::GREYSCALE)
	{
		auto patientAge = age();
		auto HR = v->HR();
		if (patientAge < 12 && HR > 120) setAlertLevel(AlertLevel::Red);
		else if(patientAge >= 12 && HR > 100) setAlertLevel(AlertLevel::Red);
		else setAlertLevel(AlertLevel::Green);
	}
	else if (disease == Diagnosis::BONEITIS)
	{
		auto RR = v->RR();
		if (RR > 40) setAlertLevel(AlertLevel::Red);
		else if (RR > 30) setAlertLevel(AlertLevel::Orange);
		else if (RR > 30) setAlertLevel(AlertLevel::Yellow);
		else setAlertLevel(AlertLevel::Green);
	}
}

const std::vector<const Vitals*> Patient::vitals() const
{
	return _vitals;
}

void Patient::setAlertLevel(AlertLevel level)
{
	_alertLevel = level;

	if (_alertLevel > AlertLevel::Green) {
		cout << "Patient: " << humanReadableID() << "has an alert level: ";
		switch (_alertLevel) {
		case AlertLevel::Yellow:
			cout << "Yellow";
			break;
		case AlertLevel::Orange:
			cout << "Orange";
			break;
		case AlertLevel::Red:
			cout << "Red";
			break;
		}
		cout << endl;
	}
}
