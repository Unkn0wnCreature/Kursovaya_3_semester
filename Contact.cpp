#include "Contact.h"
#include <regex>
#include <stdexcept>
#include <ctime>

Contact::Contact(string firstName, string secondName, string email, string phoneNumber){
    this->firstName = firstName;
    this->secondName = secondName;
    this->email = email;
    this->list_of_phone_numbers.emplace_back(phoneNumber);
}
/*
Contact::Contact(string firstName, string secondName, string lastName, string birthDate = "", string address = "", string email, list<string> list_of_phone_numbers){
    this->firstName = firstName;
    this->secondName = secondName;
    this->lastName = lastName;
    this->birthDate = birthDate;
    this->address = address;
    this->email = email;
    this->list_of_phone_numbers = list_of_phone_numbers;
}
*/
Contact::Contact(const Contact& c){
    firstName = c.firstName;
    secondName = c.secondName;
    lastName = c.lastName;
    address = c.address;
    email = c.email;
    list_of_phone_numbers = c.list_of_phone_numbers;
}

Contact::~Contact(){}

bool Contact::set_firstName(string& firstName){
    string trimmed = trim(firstName);
    if (!isValidName(trimmed)){return false;}
    this->firstName = trimmed;
    return true;

}

bool Contact::set_secondName(string& secondName){
    string trimmed = trim(secondName);
    if (!isValidName(trimmed)){return false;}
    this->secondName = trimmed;
    return true;
}

bool Contact::set_lastName(string& lastName){
    string trimmed = trim(lastName);
    if (!isValidName(trimmed)){return false;}
    this->lastName = trimmed;
    return true;
}

bool Contact::set_address(string& address){
    this->address = trim(address);
    return true;
}

bool Contact::set_email(string& email){
    string trimmed = trim(email);
    if (!isValidEmail(trimmed)){return false;}
    this->email = trimmed;
    return true;
}

bool Contact::set_list_of_phones(list<string> list_of_phones){
    list<string> temp_list_of_phones;
    for (string str : list_of_phones){
        string trimmed = trim(str);
        if (!isValidPhone(trimmed)){return false;}
        
        temp_list_of_phones.emplace_back(trimmed);
    }

    this->list_of_phone_numbers = temp_list_of_phones;

    return true;
}

string Contact::get_firstName(){return firstName;}
string Contact::get_secondName(){return secondName;};
string Contact::get_lastName(){return lastName;};
string Contact::get_address(){return address;};
string Contact::get_email(){return email;};
list<string> Contact::get_list_of_phones(){return list_of_phone_numbers;};

bool Contact::isValidName(const string& name) const {
    if (name.empty()) return true; // Отчество может быть пустым
    
    regex pattern("^[a-zA-Zа-яА-Я][a-zA-Zа-яА-Я0-9\\-\\s]*[a-zA-Zа-яА-Я0-9]$");
        return regex_match(name, pattern);
}

bool Contact::isValidEmail(const string& email) const {
    regex pattern("^[a-zA-Z0-9]+@[a-zA-Z0-9]+\\.[a-zA-Z0-9]+$");
    return regex_match(email, pattern);
}

bool Contact::isValidPhone(const std::string& phoneNumber) const {
    // Убираем все нецифровые символы кроме + для проверки
    string cleanPhone = phoneNumber;
    cleanPhone.erase(remove_if(cleanPhone.begin(), cleanPhone.end(),
                     [](char c) { return !isdigit(c) && c != '+'; }), cleanPhone.end());
    
    // Проверяем различные форматы номеров
    regex pattern("^(\\+7|8)?[0-9]{10}$");
    return regex_match(cleanPhone, pattern);
}

bool Contact::isValidDate(const string& date) const {
    // Формат: DD-MM-YYYY
    if (date.length() != 10) return false;
    if (date[2] != '-' || date[5] != '-') return false;
    int year, month, day;
    try {
        day = stoi(date.substr(0, 2));
        month = stoi(date.substr(3, 2));
        year = stoi(date.substr(6, 4));
    } catch (...) {
        return false;
    }
    // Проверка диапазонов
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;
    // Проверка високосного года и количества дней в месяце
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        daysInMonth[1] = 29; // Февраль в високосный год
    }
    if (day > daysInMonth[month - 1]) return false;
    // Проверка что дата не в будущем
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    int currentYear = now->tm_year + 1900;
    int currentMonth = now->tm_mon + 1;
    int currentDay = now->tm_mday;
    if (year > currentYear) return false;
    if (year == currentYear && month > currentMonth) return false;
    if (year == currentYear && month == currentMonth && day > currentDay) return false;
    return true;
}

string Contact::trim(const string& string) const{
    size_t start = string.find_first_not_of(" \t\n\r");
    size_t end = string.find_last_not_of(" \t\n\r");
    if (start == string::npos){return "";}
    return string.substr(start, end - start + 1);
}

string Contact::normalizePhoneNumber(const string& phoneNumber){
    string result;
    for (char c : phoneNumber) {
        if (std::isdigit(c) || c == '+') {
            result += c;
        }
    }
    
    // Приводим к формату +7XXXXXXXXXX
    if (result.length() == 11 && result[0] == '8') {
        result[0] = '7';
        result = "+" + result;
    } else if (result.length() == 10) {
        result = "+7" + result;
    }
    
    return result;
}

bool Contact::addPhoneNumber(const string& phoneNumber){
    if (!isValidPhone(phoneNumber)){return false;}
    this->list_of_phone_numbers.push_back(phoneNumber);
    return true;
}