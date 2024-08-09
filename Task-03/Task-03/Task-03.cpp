#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

struct Contact {
    string name;
    string phone;
    string email;
};

// Function prototypes
void addContact(vector<Contact>& contacts);
void viewContacts(const vector<Contact>& contacts);
void editContact(vector<Contact>& contacts);
void deleteContact(vector<Contact>& contacts);
void saveContacts(const vector<Contact>& contacts, const string& filename);
void loadContacts(vector<Contact>& contacts, const string& filename);

int main() {
    vector<Contact> contacts;
    string filename = "contacts.txt";

    loadContacts(contacts, filename);

    int choice;
    do {
        cout << "\nContact Management System\n";
        cout << "1. Add Contact\n";
        cout << "2. View Contacts\n";
        cout << "3. Edit Contact\n";
        cout << "4. Delete Contact\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addContact(contacts);
            break;
        case 2:
            viewContacts(contacts);
            break;
        case 3:
            editContact(contacts);
            break;
        case 4:
            deleteContact(contacts);
            break;
        case 5:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }

        if (choice == 5) {
            saveContacts(contacts, filename);
        }
    } while (choice != 5);

    return 0;
}

void addContact(vector<Contact>& contacts) {
    Contact newContact;

    cout << "Enter contact name: ";
    cin.ignore();
    getline(cin, newContact.name);

    while (true) {
        cout << "Enter phone number : ";
        getline(cin, newContact.phone);

        if (newContact.phone.length() == 13 && newContact.phone[0] == '+' &&
            all_of(newContact.phone.begin() + 1, newContact.phone.end(), ::isdigit)) {
            break;
        }
        else {
            cout << "Invalid phone number. Please try again.\n";
        }
    }

    while (true) {
        cout << "Enter email address : ";
        getline(cin, newContact.email);

        size_t atPosition = newContact.email.find('@');
        size_t dotPosition = newContact.email.rfind('.');

        if (atPosition != string::npos && dotPosition != string::npos &&
            atPosition < dotPosition && atPosition > 0 &&
            dotPosition < newContact.email.length() - 1) {
            break;
        }
        else {
            cout << "Invalid email address. Please try again.\n";
        }
    }

    contacts.push_back(newContact);
    cout << "Contact added successfully!\n";
}


void viewContacts(const vector<Contact>& contacts) {
    if (contacts.empty()) {
        cout << "No contacts found.\n";
        return;
    }

    cout << "\nContact List:\n";
    for (size_t i = 0; i < contacts.size(); i++) {
        cout << "Contact " << i + 1 << ":\n";
        cout << "Name: " << contacts[i].name << endl;
        cout << "Phone: " << contacts[i].phone << endl;
        cout << "Email: " << contacts[i].email << endl << endl;
    }
}

void editContact(vector<Contact>& contacts) {
    if (contacts.empty()) {
        cout << "No contacts found.\n";
        return;
    }

    viewContacts(contacts);

    int contactIndex;
    cout << "Enter the number of the contact to edit: ";
    cin >> contactIndex;

    if (contactIndex < 1 || contactIndex > contacts.size()) {
        cout << "Invalid contact number.\n";
        return;
    }

    cout << "Enter new name: ";
    cin.ignore();
    getline(cin, contacts[contactIndex - 1].name);

    cout << "Enter new phone number: ";
    getline(cin, contacts[contactIndex - 1].phone);

    cout << "Enter new email address: ";
    getline(cin, contacts[contactIndex - 1].email);

    cout << "Contact edited successfully!\n";
}

void deleteContact(vector<Contact>& contacts) {
    if (contacts.empty()) {
        cout << "No contacts found.\n";
        return;
    }

    viewContacts(contacts);

    int contactIndex;
    cout << "Enter the number of the contact to delete: ";
    cin >> contactIndex;

    if (contactIndex < 1 || contactIndex > contacts.size()) {
        cout << "Invalid contact number.\n";
        return;
    }

    contacts.erase(contacts.begin() + contactIndex - 1);
    cout << "Contact deleted successfully!\n";
}

void saveContacts(const vector<Contact>& contacts, const string& filename) {
    ofstream outfile(filename);
    if (!outfile.is_open()) {
        cout << "Error opening file for saving contacts.\n";
        return;
    }

    for (const Contact& contact : contacts) {
        outfile << contact.name << endl;
        outfile << contact.phone << endl;
        outfile << contact.email << endl;
    }

    outfile.close();
    cout << "Contacts saved to file successfully.\n";
}

void loadContacts(vector<Contact>& contacts, const string& filename) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        cout << "File not found or cannot be opened.\n";
        return;
    }

    string line;
    Contact contact;
    while (getline(infile, line)) {
        contact.name = line;
        getline(infile, line);
        contact.phone = line;
        getline(infile, line);
        contact.email = line;
        contacts.push_back(contact);
    }

    infile.close();
    cout << "Contacts loaded from file successfully.\n";
}