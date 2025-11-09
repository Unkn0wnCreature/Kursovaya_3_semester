#include <iostream>
#include "ContactBook.h"
#include "Contact.h"
#include "ContactBook.cpp"
#include "Contact.cpp"
using namespace std;

int main(){
    ContactBook contact_book;
    Contact test_contact;

    test_contact = contact_book.createContactByInput();
    contact_book.addContact(test_contact);

    test_contact.showContact();

    return 0;
}
