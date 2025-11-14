#include <iostream>
#include "ContactBook.h"
#include "Contact.h"
#include "ConsoleUI.h"
#include "ContactBook.cpp"
#include "Contact.cpp"
#include "ConsoleUI.cpp"
using namespace std;

int main(){
    ContactBook contact_book;
    Contact test_contact("tim", "dvor", "timicoboy@gmail.com", {"+79184642985"}), tc1("van", "dvor", "ivankrd@gmail.ru", {"+79184664985"});

    //test_contact = contact_book.createContactByInput();
    contact_book.addContact(test_contact);
    contact_book.addContact(tc1);
    
    ConsoleUI consoleUI;

    consoleUI.run(contact_book);
    
    return 0;
}
