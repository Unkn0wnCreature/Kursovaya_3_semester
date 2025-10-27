#pragma once
#include <string>
using namespace std;

class PhoneNumber {
    private:
    string phoneNumber;

    public:
    PhoneNumber(string PhoneNumber);
    PhoneNumber(const PhoneNumber &p);
    ~PhoneNumber();

    string normalizePhoneNumber(const string& phoneNumber);

    ///int isValid();
};
