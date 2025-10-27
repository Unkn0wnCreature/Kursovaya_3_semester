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

bool ContactBook::addContact(const Contact& contact){
    contactBook.push_back(contact);
    return true;
}