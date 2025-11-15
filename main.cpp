#include <iostream>
#include "Contacts.h"
#include "Contact.h"
#include "Contacts.cpp"
#include "Contact.cpp"
using namespace std;

void showMenu();
void run_app(ContactBook& contact_book);

int main(){
    ContactBook contact_book;

    run_app(contact_book);
    
    return 0;
}

void showMenu(){
    cout<<"\nMENU\n"<<endl;
    cout<<"1. Show all."<<endl;
    cout<<"2. Add."<<endl;
    cout<<"3. Update."<<endl;
    cout<<"4. Delete."<<endl;
    cout<<"5. Sort."<<endl;
    cout<<"6. End"<<endl;
    cout<<"\nOption: ";
}

void run_app(ContactBook& contact_book){
    int option;

    showMenu();
    cin>>option;
    cin.ignore();

    while (option > 0 && option < 7){
        switch (option){
            case 1:
                contact_book.load();
                contact_book.showContacts();
                break;
            case 2:
                contact_book.load();
                contact_book.addContact(contact_book.createContact());
                contact_book.save(contact_book);
                break;
            case 3:
                contact_book.load();
                contact_book.update();
                contact_book.save(contact_book);
                break;
            case 4:
                contact_book.load();
                contact_book.delete_contact();
                contact_book.save(contact_book);
                break;
            case 5:
                contact_book.load();
                contact_book.sortContacts();
                contact_book.save(contact_book);
                break;
            case 6:
                contact_book.save(contact_book);
                return;
        }
        showMenu();
        cin>>option;
        cin.ignore();
    }
}

