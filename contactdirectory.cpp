
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <limits>
using namespace std;

class Contact
{
private:
    string name, phone, email;

public:

    void addContact()
    {
        cout << "\nEnter Name: ";
        getline(cin, name);

        cout << "Enter Phone: ";
        getline(cin, phone);

        cout << "Enter Email: ";
        getline(cin, email);
    }

    void displayContact()
    {
        cout << "\nName: " << name;
        cout << "\nPhone: " << phone;
        cout << "\nEmail: " << email;
        cout << "\n----------------------\n";
    }

    void loadDetails(string n, string p, string e)
    {
        name = n;
        phone = p;
        email = e;
    }

    string getName()
    {
        return name;
    }

    string getPhone()
    {
        return phone;
    }

    string getEmail()
    {
        return email;
    }

    void updateContact()
    {
        cout << "\nEnter New Name: ";
        getline(cin, name);

        cout << "Enter New Phone: ";
        getline(cin, phone);

        cout << "Enter New Email: ";
        getline(cin, email);
    }
};

vector<Contact> loadContacts()
{
    vector<Contact> contacts;
    ifstream file("contacts.txt");

    string n, p, e;

    while (getline(file, n))
    {
        if (!getline(file, p)) break;
        if (!getline(file, e)) break;

        Contact c;
        c.loadDetails(n, p, e);
        contacts.push_back(c);
    }

    file.close();
    return contacts;
}

void saveContacts(vector<Contact> contacts)
{
    ofstream file("contacts.txt");

    for (int i = 0; i < contacts.size(); i++)
    {
        file << contacts[i].getName() << endl;
        file << contacts[i].getPhone() << endl;
        file << contacts[i].getEmail() << endl;
    }

    file.close();
}

int main()
{
    vector<Contact> contacts = loadContacts();
    int choice;

    do
    {
        cout << "\n===== CONTACT DIRECTORY =====";
        cout << "\n1. Add Contact";
        cout << "\n2. Display Contacts";
        cout << "\n3. Search Contact";
        cout << "\n4. Update Contact";
        cout << "\n5. Delete Contact";
        cout << "\n6. Exit";

        cout << "\nEnter your choice: ";

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input!";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1)
        {
            Contact c;
            c.addContact();
            contacts.push_back(c);
            saveContacts(contacts);

            cout << "\nContact added successfully!";
        }

        else if (choice == 2)
        {
            if (contacts.empty())
                cout << "\nNo contacts found!";

            for (int i = 0; i < contacts.size(); i++)
                contacts[i].displayContact();
        }

        else if (choice == 3)
        {
            string phone;
            bool found = false;

            cout << "\nEnter phone to search: ";
            getline(cin, phone);

            for (int i = 0; i < contacts.size(); i++)
            {
                if (contacts[i].getPhone() == phone)
                {
                    contacts[i].displayContact();
                    found = true;
                    break;
                }
            }

            if (!found)
                cout << "\nContact not found!";
        }

        else if (choice == 4)
        {
            string phone;
            bool found = false;

            cout << "\nEnter phone to update: ";
            getline(cin, phone);

            for (int i = 0; i < contacts.size(); i++)
            {
                if (contacts[i].getPhone() == phone)
                {
                    contacts[i].updateContact();
                    saveContacts(contacts);

                    cout << "\nContact updated successfully!";
                    found = true;
                    break;
                }
            }

            if (!found)
                cout << "\nContact not found!";
        }

        else if (choice == 5)
        {
            string phone;
            bool found = false;

            cout << "\nEnter phone to delete: ";
            getline(cin, phone);

            for (int i = 0; i < contacts.size(); i++)
            {
                if (contacts[i].getPhone() == phone)
                {
                    contacts.erase(contacts.begin() + i);
                    saveContacts(contacts);

                    cout << "\nContact deleted successfully!";
                    found = true;
                    break;
                }
            }

            if (!found)
                cout << "\nContact not found!";
        }

        else if (choice == 6)
        {
            cout << "\nThank you for using Contact Directory!";
        }

        else
        {
            cout << "\nInvalid choice!";
        }

    } while (choice != 6);

    return 0;
}
;