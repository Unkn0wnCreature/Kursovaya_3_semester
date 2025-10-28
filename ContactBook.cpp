#include "ContactBook.h"
#include <algorithm>
#include <iostream>
using namespace std;

ContactBook::ContactBook(list<Contact> contactBook){
    this->contactBook = contactBook;
}

ContactBook::ContactBook(const ContactBook& contact_book){
    contactBook = contact_book.contactBook;
}

ContactBook::~ContactBook(){};

bool ContactBook::createContactByInput(){
    Contact contact;
    string firstName, secondName, lastName, birthDate, address, email;

    cout<<"Enter first name: "<<endl;
    getline(cin, firstName);
    if (!firstName.empty()){
        while (!contact.isValidName(firstName)){
            cout<<"Enter first name again: "<<endl;
            getline(cin, firstName);
        }
        if (!contact.set_firstName(firstName)){cout<<"Ошибка присвоения имени."<<endl;}
        //contact.set_firstName(firstName);
    }
    

    cout<<"Enter second name: "<<endl;
    getline(cin, secondName);
    if (!secondName.empty()){
        while (!contact.isValidName(secondName)){
            cout<<"Enter second name again: "<<endl;
            getline(cin, secondName);
        }
        if (!contact.set_secondName(secondName)){cout<<"Ошибка присвоения фамилии."<<endl;}
        //contact.set_secondName(secondName);
    }

    cout<<"Enter last name (optional): "<<endl;
    getline(cin, lastName);
    while (!contact.isValidName(lastName)){
        cout<<"Enter last name again (optional): "<<endl;
        getline(cin, lastName);
    }
    if (!contact.set_lastName(lastName)){cout<<"Ошибка присвоения отчества."<<endl;}
    //contact.set_lastName(lastName);

    cout<<"Enter birth date (optional): "<<endl;
    getline(cin, birthDate);
    while (!contact.isValidDate(birthDate)){
        cout<<"Enter birth date again (optional): "<<endl;
        getline(cin, birthDate);
    }
    if (!contact.set_birthDate(birthDate)){cout<<"Ошибка присвоения даты рождения."<<endl;}

    cout<<"Enter address (optional): "<<endl;
    getline(cin, address);
    while (!contact.isValidAddress(address)){
        cout<<"Enter address again (optional): "<<endl;
        getline(cin, address);
    }
    if (!contact.set_address(address)){cout<<"Ошибка присвоения адреса."<<endl;}

    cout<<"Enter email: "<<endl;
    getline(cin, email);
    if (!email.empty()){
        while (!contact.isValidEmail(email)){
            cout<<"Enter email again: "<<endl;
            getline(cin, email);
        }
        if (!contact.set_email(email)){cout<<"Ошибка присвоения email."<<endl;}
    }

}

bool ContactBook::addContact(const Contact& contact){
    contactBook.push_back(contact);
    return true;
}