#pragma once

#define _CRT_SECURE_NO_WARNINGS
using namespace std;
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <fstream>


class Interface {

public:
	virtual void Output() const = 0;
	virtual void Input() = 0;
	virtual ~Interface() { };
	virtual std::string Name() = 0;
	virtual void Serialize(std::fstream& f) = 0;
	virtual void Deserialize(std::fstream& f) = 0;
};


class Employee : public Interface {
private:
	int salary, experience;

protected:
	char* job_title;


public:
	char* company;
	char* Full_name;

	Employee(const char* Full_name_ = "None", const char* company_ = "None", \
		const char* job_title_ = "None", int salary_ = 30000, int experience_ = 5);
	Employee(const Employee* obj);
	virtual ~Employee();

	virtual std::string Name() { return "Employee"; };
	virtual void Input();
	virtual void Output() const;
	virtual void Serialize(std::fstream& f);
	virtual void Deserialize(std::fstream& f);
};

//самозанятый
class Self_Employeed : public Employee {

	int duration_work;

public:

	Self_Employeed(int duration_work, const char* Full_name_ = "None", const char* company_ = "None", \
		const char* job_title_ = "None", int salary_ = 30000, int experience_ = 5);
	virtual ~Self_Employeed();

	virtual std::string Name() { return "Self_Employeed"; };
	virtual void Input();
	virtual void Output() const;
	virtual void Serialize(std::fstream& f);
	virtual void Deserialize(std::fstream& f);
};

class Businessman : public Self_Employeed {

	//название бизнеса
	char* business;

public:

	Businessman(const char* business, int duration_work, const char* Full_name_ = "None", const char* company_ = "None", \
		const char* job_title_ = "None", int salary_ = 30000, int experience_ = 5);
	virtual ~Businessman();
	
	virtual std::string Name() { return "Businessman"; };
	virtual void Input();
	virtual void Output() const;
	virtual void Serialize(std::fstream& f);
	virtual void Deserialize(std::fstream& f);

	char* get_business() const { return business; };

	int operator || (const char* str);
	int operator || (const Businessman* obj);

	void operator - (const char* str);
	void operator - (const Businessman* obj);
};


class Translator : public Employee {

	char* language;

public:

	Translator(const char* language, const char* Full_name_ = "None", const char* company_ = "None", \
		const char* job_title_ = "None", int salary_ = 30000, int experience_ = 5);

	virtual ~Translator();

	virtual std::string Name() { return "Translator"; };
	virtual void Input();
	virtual void Output() const;
	virtual void Serialize(std::fstream& f);
	virtual void Deserialize(std::fstream& f);
}; 
