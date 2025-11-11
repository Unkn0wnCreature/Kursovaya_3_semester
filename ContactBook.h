#pragma once
#include "Contact.h"
#include <vector>
#include <string>
using namespace std;

enum SearchCriteria{FIRST_NAME = 1, SECOND_NAME, LAST_NAME, BIRTH_DATE, ADDRESS, EMAIL, PHONE_NUMBER};

class ContactBook {
    private:
    list<Contact> contactBook;
    //string filename;
    public:
    ContactBook(list<Contact> contactBook = {});
    ContactBook(const ContactBook& contact_book);
    ~ContactBook();

    void categoryInput(string category, string& inputString, string status = "compulsory");
    Contact createContactByInput();
    void showContacts();
    bool addContact(const Contact& contact);
    auto searchContact();
    void deleteContact(list<Contact>::iterator iter);
    void updateContact(list<Contact>::iterator iter);
};
