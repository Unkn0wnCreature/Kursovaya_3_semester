#include "PhoneNumber.h"
#include <regex>
#include <stdexcept>

PhoneNumber::PhoneNumber(string phoneNumber){
    this->phoneNumber = normalizePhoneNumber(phoneNumber);
}

PhoneNumber::PhoneNumber(const PhoneNumber &p){
    phoneNumber = normalizePhoneNumber(p.phoneNumber);
}

PhoneNumber::~PhoneNumber(){}

string PhoneNumber::normalizePhoneNumber(const string& phoneNumber){
    string digits;
    for (char c : phoneNumber){
        if (isdigit(c) || c == '+'){
            digits += c;
        }
    }

    if (!digits.empty() && digits[0] == '7' && digits.find('+')){
        digits = '+' + digits;
    }

    if (digits.substr(0, 2) != "+7" && digits.size() >= 11){
        digits = "+7" + digits.substr(digits.size() - 10);
    }

    return digits;
}

///int PhoneNumber::isValid(){if {this->phoneNumber.size() < 10}}