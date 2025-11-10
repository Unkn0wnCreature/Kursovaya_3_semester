#pragma once
#include "Contact.h"
#include <vector>
#include <string>
using namespace std;

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
    bool addContact(const Contact& contact);
    bool deleteContact();
    bool updateContact();
    void searchContact();
};
