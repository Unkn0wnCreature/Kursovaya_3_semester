#include "ContactBook.h"
#include <algorithm>
#include <iostream>
using namespace std;
string specialNoneString = "None";

ContactBook::ContactBook(list<Contact> contactBook){
    this->contactBook = contactBook;
}

ContactBook::ContactBook(const ContactBook& contact_book){
    contactBook = contact_book.contactBook;
}

ContactBook::~ContactBook(){};

void ContactBook::categoryInput(string category, string& inputString, string status){
    cout<<"Enter "<< category <<" ("<< status <<"):"<<endl;
    getline(cin, inputString);
}

Contact ContactBook::createContactByInput(){
    Contact contact;
    string firstName, secondName, lastName, birthDate, address, email, phone_number;

    categoryInput("first name", firstName);
    while (firstName.empty()){categoryInput("first name", firstName);}
    while (!contact.isValidName(firstName)){categoryInput("first name", firstName);}
    if (!contact.set_firstName(firstName)){cout<<"Ошибка присвоения имени."<<endl;}


    categoryInput("second name", secondName);
    while (secondName.empty()){categoryInput("second name", secondName);}
    while (!contact.isValidName(secondName)){categoryInput("second name", secondName);}
    if (!contact.set_secondName(secondName)){cout<<"Ошибка присвоения фамилии."<<endl;}

    categoryInput("last name", lastName, "optional");
    while (!contact.isValidName(lastName)){categoryInput("last name", lastName, "optional");}
    if (!contact.set_lastName(lastName)){cout<<"Ошибка присвоения отчества."<<endl;}

    categoryInput("birth date", birthDate, "optional");
    while (!contact.isValidDate(birthDate)){categoryInput("birth date", birthDate, "optional");}
    if (!contact.set_birthDate(birthDate)){cout<<"Ошибка присвоения даты рождения."<<endl;}

    categoryInput("address", address, "optional");
    while (!contact.isValidAddress(address)){categoryInput("address", address, "optional");}
    if (!contact.set_address(address)){cout<<"Ошибка присвоения даты адреса."<<endl;}

    categoryInput("email", email);
    while (email.empty()){categoryInput("email", email);}
    while (!contact.isValidEmail(email)){categoryInput("email", email);}
    if (!contact.set_email(email)){cout<<"Ошибка присвоения email."<<endl;}

    categoryInput("phone number", phone_number);
    while (phone_number.empty()){categoryInput("phone number", phone_number);}
    while (!contact.isValidPhone(phone_number)){categoryInput("phone number", phone_number);}
    if (!contact.addPhoneNumber(phone_number)){cout<<"Ошибка присвоения номера телефона."<<endl;}

    categoryInput("phone number", phone_number, "keep empty to stop adding phone numbers");
    while (!phone_number.empty()){
        while (!contact.isValidPhone(phone_number)){categoryInput("phone number", phone_number);}
        if (!contact.addPhoneNumber(phone_number)){cout<<"Ошибка присвоения фамилии."<<endl;}
        categoryInput("phone number", phone_number, "keep empty to stop adding phone numbers");
    }

    return contact;
}

void ContactBook::showContacts(){
    cout<<"\n-------LIST OF CONTACTS-------\n"<<endl;
    for (Contact contact : contactBook){
        contact.show();
        cout<<endl;
    }
}

bool ContactBook::addContact(const Contact& contact){
    contactBook.push_back(contact);
    return true;
}

auto ContactBook::searchContact(){
    string string_to_find;

    categoryInput("string for searching", string_to_find, "enter as much as you can, to search better");
    for (auto iter = contactBook.begin(); iter != contactBook.end(); iter++){
        if ((*iter).findByString(string_to_find)){return iter;}
    }
    return contactBook.end();
}

void ContactBook::deleteContact(list<Contact>::iterator iter){
    this->contactBook.erase(iter);
}

void ContactBook::updateContact(list<Contact>::iterator iter){
    Contact temporary_contact = createContactByInput();
    
    deleteContact(iter);
    contactBook.insert(--iter, temporary_contact);
}