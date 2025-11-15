#include "Contacts.h"
#include <algorithm>
#include <fstream>
#include <iostream>
using namespace std;

ContactBook::ContactBook(list<Contact> contactBook, string filename){
    this->contactBook = contactBook;
    this->filename = filename;
}

ContactBook::ContactBook(const ContactBook& contact_book){
    contactBook = contact_book.contactBook;
    filename = contact_book.filename;
}

ContactBook::~ContactBook(){}

void ContactBook::Input(string category, string& inputString, string status){
    cout<<"Enter "<< category <<" ("<< status <<"):"<<endl;
    getline(cin, inputString);
}

Contact ContactBook::createContact(){
    Contact contact;
    string firstName, secondName, lastName, birthDate, address, email, phone_number;

    Input("first name", firstName);
    while (firstName.empty()){
        Input("first name", firstName);
    }
    while (!contact.isValidName(firstName)){
        Input("first name", firstName);
    }
    contact.set_firstName(firstName);


    Input("second name", secondName);
    while (secondName.empty()){
        Input("second name", secondName);
    }
    while (!contact.isValidName(secondName)){
        Input("second name", secondName);
    }
    contact.set_secondName(secondName);

    Input("last name", lastName, "optional");
    while (!contact.isValidName(lastName)){
        Input("last name", lastName, "optional");
    }
    contact.set_lastName(lastName);

    Input("birth date", birthDate, "optional");
    while (!contact.isValidDate(birthDate)){
        Input("birth date", birthDate, "optional");
    }
    contact.set_birthDate(birthDate);

    Input("address", address, "optional");
    while (!contact.isValidAddress(address)){
        Input("address", address, "optional");
    }
    contact.set_address(address);

    Input("email", email);
    while (email.empty()){
        Input("email", email);
    }
    while (!contact.isValidEmail(email)){
        Input("email", email);
    }
    contact.set_email(email);

    Input("phone number", phone_number);
    while (phone_number.empty()){
        Input("phone number", phone_number);
    }
    while (!contact.isValidPhone(phone_number)){
        Input("phone number", phone_number);
    }
    contact.addPhoneNumber(phone_number);

    Input("phone number", phone_number, "keep empty to stop adding phone numbers");
    while (!phone_number.empty()){
        while (!contact.isValidPhone(phone_number)){
            Input("phone number", phone_number);
        }
        contact.addPhoneNumber(phone_number);
        Input("phone number", phone_number, "keep empty to stop adding phone numbers");
    }
    return contact;
}

void ContactBook::showContacts(){
    cout<<"\nLIST OF CONTACTS\n"<<endl;
    for (Contact contact : contactBook){
        contact.show();
        cout<<"*******************************"<<endl;
    }
}

bool ContactBook::addContact(const Contact& contact){
    contactBook.push_back(contact);
    return true;
}



void ContactBook::delete_contact(){
    list<Contact> list = search();
    char delete_all_status, status;
    for (Contact& contact_to_delete : list) {
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
                    break;
                } else {
                    ++it;
                }
            }
        }
    }
}

void ContactBook::update(){
    list<Contact> list = search();
    char opt;

    for (auto contact_to_update = contactBook.begin(); contact_to_update != contactBook.end(); contact_to_update++){
        for (Contact found_contact : list){
            if (*contact_to_update == found_contact){
                (*contact_to_update).show();
                cout<<"\nUpdate contact? (y/n)"<<endl;
                cin>>opt;
                cin.ignore();
                if (opt == 'y' || opt == 'Y'){
                    Contact temporary = createContact();
                    *contact_to_update = temporary;
                }
            }
        }
    }  
}

bool ContactBook::compareFirstName(const Contact& a, const Contact& b){
    return a.get_firstName() < b.get_firstName();
}

bool ContactBook::compareSecondName(const Contact& a, const Contact& b){
    return a.get_secondName() < b.get_secondName();
}

bool ContactBook::compareLastName(const Contact& a, const Contact& b){
    string lastName1 = (a.get_lastName().empty() ? "zzzzzzzzzz" : a.get_lastName());
    string lastName2 = (b.get_lastName().empty() ? "zzzzzzzzzz" : b.get_lastName());
    return lastName1 < lastName2;
}

bool ContactBook::compareBirthDate(const Contact& a, const Contact& b){
    string date1 = (a.get_birthDate().empty() ? "31-12-9999" : a.get_birthDate());
    string date2 = (b.get_birthDate().empty() ? "31-12-9999" : b.get_birthDate());
    return date1 < date2;
}

bool ContactBook::compareAddress(const Contact& a, const Contact& b){
    string address1 = (a.get_address().empty() ? "zzzzzzzzzz" : a.get_address());
    string address2 = (b.get_address().empty() ? "zzzzzzzzzz" : b.get_address());
    return address1 < address2;
}

bool ContactBook::compareEmail(const Contact& a, const Contact& b){
    return a.get_email() < b.get_email();
}

void ContactBook::sortContacts(){
    int criteria;
    
    cout<<"\nSORTING CRITERIAS\n"<<endl;
    cout << "1. First Name" << endl;
    cout << "2. Second Name" << endl;
    cout << "3. Last Name" << endl;
    cout << "4. Birth Date" << endl;
    cout << "5. Address" << endl;
    cout << "6. Email" << endl;
    cout << "7. Cancel" << endl;
    cout << "Choose sorting option: ";

    cin>>criteria;
    cin.ignore();

    switch (criteria)
    {
    case 1:
        contactBook.sort(compareFirstName);
        break;
    case 2:
        contactBook.sort(compareSecondName);
        break;
    case 3:
        contactBook.sort(compareLastName);
        break;
    case 4:
        contactBook.sort(compareBirthDate);
        break;
    case 5:
        contactBook.sort(compareAddress);
        break;
    case 6:
        contactBook.sort(compareEmail);
        break;
    case 7:
        break;
    default:
        cout<<"\nIncorrect criteria.\n"<<endl;
        return;
    }
}

void ContactBook::save(const ContactBook& contact_book){
    ofstream file(filename);

    if (!file.is_open()){return;}
    else{
        file<< contact_book.contactBook.size() <<endl;

        for (const Contact& contact : contact_book.contactBook){
            file<< contact.get_firstName() <<endl;
            file<< contact.get_secondName() <<endl;
            file<< contact.get_lastName() <<endl;
            file<< contact.get_birthDate() <<endl;
            file<< contact.get_address() <<endl;
            file<< contact.get_email() <<endl;

            list<string> phones = contact.get_list_of_phones();
            file<< phones.size() <<endl;

            for (const string& phone : phones){
                file<< phone <<endl;
            }
            file<<"+++++++++"<<endl;
        }
        file.close();
    }
}

void ContactBook::load(){
    list<Contact> contacts;
    ifstream file(filename);

    if (!file.is_open()){return;}
    else{
        size_t contact_count;
        file>>contact_count;
        file.ignore();

        for (size_t i = 0; i < contact_count; ++i){
            string first_name, second_name, last_name, birth_date, address, email;

            getline(file, first_name);
            getline(file, second_name);
            getline(file, last_name);
            getline(file, birth_date);
            getline(file, address);
            getline(file, email);

            size_t phone_count;
            file>>phone_count;
            file.ignore();

            list<string> phones;
            for (size_t j = 0; j < phone_count; ++j){
                string phone;
                getline(file, phone);
                phones.push_back(phone);
            }
            string separator;
            getline(file, separator);

            Contact contact(first_name, second_name, last_name, birth_date, address, email, phones);
            contacts.push_back(contact);
        }
        file.close();
    }
    contactBook = contacts;
}

list<Contact> ContactBook::search(){
    list<Contact> result;
    string find_parameters[8];
    string parametres[7] = {"first name", "second name", "last name", "birth date", "address", "email", "phone number"};
    char status;
    
    cout<<"\nDo you want find through all fields? (y/n)"<<endl;
    cin>>status;
    cin.ignore();
    if (status == 'y' || status == 'Y'){
        Input("string to find", find_parameters[7], "optional");
        for (Contact& contact : contactBook){
            if ((contact).findString(find_parameters[7])){
                result.push_back(contact);
            }
        }
    } else {
        for (int i = 0; i < 7; i++){
            Input(parametres[i], find_parameters[i], "optional");
        }

        for (Contact& contact : contactBook){
            bool flag = true;
            if (!find_parameters[0].empty() && !contact.findFirstName(find_parameters[0])) {flag = false;}
            if (!find_parameters[1].empty() && !contact.findSecondName(find_parameters[1])) {flag = false;}
            if (!find_parameters[2].empty() && !contact.findLastName(find_parameters[2])) {flag = false;}
            if (!find_parameters[3].empty() && !contact.findBirthDate(find_parameters[3])) {flag = false;}
            if (!find_parameters[4].empty() && !contact.findAddress(find_parameters[4])) {flag = false;}
            if (!find_parameters[5].empty() && !contact.findEmail(find_parameters[5])) {flag = false;}
            if (!find_parameters[6].empty() && !contact.findPhoneNumber(find_parameters[6])) {flag = false;}
            if (flag) {result.push_back(contact);}
        }
    }
    cout<<"Result: "<< result.size() <<" found.\n"<<endl;
    return result;
}