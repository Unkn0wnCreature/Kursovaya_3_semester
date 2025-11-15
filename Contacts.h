#pragma once
#include "Contact.h"
#include <string>
using namespace std;

class ContactBook {
    private:
    list<Contact> contactBook;
    string filename;
    public:
    ContactBook(list<Contact> contactBook = {}, string filename = "save.txt");
    ContactBook(const ContactBook& contact_book);
    ~ContactBook();
    static bool compareFirstName(const Contact& a, const Contact& b);
    static bool compareSecondName(const Contact& a, const Contact& b);
    static bool compareLastName(const Contact& a, const Contact& b);
    static bool compareBirthDate(const Contact& a, const Contact& b);
    static bool compareAddress(const Contact& a, const Contact& b);
    static bool compareEmail(const Contact& a, const Contact& b);
    Contact createContact();
    void showContacts();
    bool addContact(const Contact& contact);
    list<Contact> search();
    void delete_contact();
    void update();
    void sortContacts();
    void save(const ContactBook& contact_book);
    void load();
    void Input(string category, string& inputString, string status = "compulsory");
};


