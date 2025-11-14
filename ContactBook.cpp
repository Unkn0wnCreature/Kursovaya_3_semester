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

/*
auto ContactBook::searchContact(){
    string string_to_find;

    categoryInput("string for searching", string_to_find, "enter as much as you can, to search better");
    for (auto iter = contactBook.begin(); iter != contactBook.end(); iter++){
        if ((*iter).findByString(string_to_find)){return iter;}
    }
    return contactBook.end();
}
*/

list<Contact> ContactBook::searchContact(){
    list<Contact> result;
    string find_parameters[8];
    string parametres[7] = {"first name", "second name", "last name", "birth date", "address", "email", "phone number"};
    char status;
    
    cout<<"Do you want find through all fields? (y/n)"<<endl;
    cin>>status;
    cin.ignore();
    if (status == 'y' || status == 'Y'){
        categoryInput("string to find", find_parameters[7]);
        for (Contact& contact : contactBook){
            if ((contact).findByString(find_parameters[7])){
                result.push_back(contact);
            }
        }
    } else {
        for (int i = 0; i < 7; i++){
            categoryInput(parametres[i], find_parameters[i], "optional");
        }

        for (Contact& contact : contactBook){
            bool matches = true;
            // Проверяем каждое поле только если указан поисковый запрос
            if (!find_parameters[0].empty() && !contact.findByFirstName(find_parameters[0])) {
                matches = false;
            }
            if (!find_parameters[1].empty() && !contact.findBySecondName(find_parameters[1])) {
                matches = false;
            }
            if (!find_parameters[2].empty() && !contact.findByLastName(find_parameters[2])) {
                matches = false;
            }
            if (!find_parameters[3].empty() && !contact.findByBirthDate(find_parameters[3])) {
                matches = false;
            }
            if (!find_parameters[4].empty() && !contact.findByAddress(find_parameters[4])) {
                matches = false;
            }
            if (!find_parameters[5].empty() && !contact.findByEmail(find_parameters[5])) {
                matches = false;
            }
            if (!find_parameters[6].empty() && !contact.findByPhoneNumber(find_parameters[6])) {
                matches = false;
            }
            
            if (matches) {
                result.push_back(contact);
            }
        }
    }
    cout<<"Found "<< result.size() <<" contact(s).\n"<<endl;
    return result;
}

void ContactBook::deleteContact(){
    list<Contact> list_to_delete = searchContact();
    char delete_all_status, status;

    cout<<"\nWant to delete all? (y/n)"<<endl;
        cin>>delete_all_status;
        cin.ignore();
    if (delete_all_status == 'y' || delete_all_status == 'Y'){
        for (Contact& contact_to_delete : list_to_delete) {
            for (auto it = contactBook.begin(); it != contactBook.end(); ) {
                if (*it == contact_to_delete) {
                    it = contactBook.erase(it);
                    cout << "Contact deleted." << endl;
                    break;
                } else {
                    ++it;
                }
            }
        }
    }else {
        for (Contact& contact_to_delete : list_to_delete) {
            contact_to_delete.show();
            
            char status;
            cout << "\nWant to delete this contact? (y/n)" << endl;
            cin >> status;
            cin.ignore();
            
            if (status == 'y' || status == 'Y'){
                // Находим и удаляем конкретный контакт
                for (auto it = contactBook.begin(); it != contactBook.end(); ) {
                    if (*it == contact_to_delete) {
                        it = contactBook.erase(it);
                        cout << "Contact deleted." << endl;
                        break;
                    } else {
                        ++it;
                    }
                }
            }
        }
    }
}

void ContactBook::updateContact(){
    list<Contact> list_to_update = searchContact();
    char status;

    for (auto contact_to_update = contactBook.begin(); contact_to_update != contactBook.end(); contact_to_update++){
        for (Contact found_contact : list_to_update){
            if (*contact_to_update == found_contact){
                (*contact_to_update).show();
                cout<<"\nWant to update contact? (y/n)"<<endl;
                cin>>status;
                cin.ignore();
                if (status == 'y' || status == 'Y'){
                    Contact temporary_contact = createContactByInput();
                    *contact_to_update = temporary_contact;
                }
            }
        }
    }
    
    
}