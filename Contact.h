#pragma once
#include "PhoneNumber.h"
#include <string>
#include <list>
using namespace std;

class Contact {
    private:
    string firstName;
    string secondName;
    string lastName;
    string birthDate;
    string address;
    string email;
    list<string> list_of_phone_numbers;

    public:
    //Contact(string firstName = "", string secondName = "", string email = "", string phoneNumber = "");
    Contact(string firstName = "", string secondName = "", string email = "", list<string> list_of_phone_numbers = {}, string lastName = "", string birthDate = "", string address = "");
    Contact(const Contact &c);
    ~Contact();

    bool set_firstName(string& firstName);
    bool set_secondName(string& secondName);
    bool set_lastName(string& lastName);
    bool set_birthDate(string& birthDate);
    bool set_address(string& address);
    bool set_email(string& email);
    bool set_list_of_phones(list<string> list_of_phones);

    string get_firstName();
    string get_secondName();
    string get_lastName();
    string get_address();
    string get_email();
    list<string> get_list_of_phones();

    //Contact get_contact();

    bool isValidName(const string& name) const;
    bool isValidEmail(const string& email) const;
    bool isValidPhone(const string& phone) const;
    bool isValidDate(const string& date) const;
    bool isValidAddress(const string& address) const;

    
    string normalizePhoneNumber(const string& PhoneNumber);
    string trim(const string& string) const;
    bool addPhoneNumber(const string& PhoneNumber);

    void show();
};

