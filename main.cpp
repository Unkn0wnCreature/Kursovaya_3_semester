#include <iostream>
#include "ContactBook.h"
#include "Contact.h"
#include "ContactBook.cpp"
#include "Contact.cpp"
using namespace std;

int main(){
    ContactBook contact_book;
    Contact test_contact("btim", "dvor", "timicoboy@gmail.com", {"+79184642985"}), tc1("avan", "dvor", "ivankrd@gmail.ru", {"+79184664985"});

    //test_contact = contact_book.createContactByInput();
    contact_book.addContact(test_contact);
    contact_book.addContact(tc1);

    //contact_book.deleteContact();
    contact_book.sortContacts();
    contact_book.showContacts();
    return 0;
}
