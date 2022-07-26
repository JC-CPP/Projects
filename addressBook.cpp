#include <vector>
#include <iostream>
#include <random>
#include <chrono>



struct InfoStruct // the data type to hold account information (address book)
{
    std::string Username;
    int Number;
    std::string Email; // all the possible values in our data type that we can fill out
};

struct InfoStruct AddContact(); // declaring the function to add contacts into our book
std::vector<InfoStruct> RemoveContact(std::vector<InfoStruct> AddressBook);
void PrintAddressBook(std::vector<InfoStruct> AddressBook); // prints out contents of the address book

int main()
{
    int UserChoice;
    std::vector<InfoStruct> AddressBook; // creates a vector for the addresses ( our address book ) for us to play with
    struct InfoStruct TempInfo; // This will hold info whilst we run a function, e.g. if we want to add a contact this will hold the new contact info then be forwarded into the addressbook
    while(1)
    {
        while(1)
        {
            std::cout << "Pick what you would like to do with your address book:\n(0) Add contact\n(1) Remove contact\n(2) Print Contacts\n(3) Quit\nEnter your choice: ";
            std::cin >> UserChoice;
            if(UserChoice > 4 || UserChoice < 0)
            {
                std::cout << "\nBad input. Try again\n";
            }
            else
                break;
        }
        if(UserChoice == 0)
        {
            TempInfo = AddContact();
            AddressBook.push_back(TempInfo);
        }
        else if(UserChoice == 1)
        {
            AddressBook = RemoveContact(AddressBook);
        }
        else if(UserChoice == 2)
        {
            PrintAddressBook(AddressBook);
        }
        else if(UserChoice == 3)
        {
            break;
        }
    }
    return 0;
}


struct InfoStruct AddContact()
{
    struct InfoStruct ReturnStruct;
    std::string InputString;
    int InputInt;
    bool ValidInput = 0;


    while(ValidInput == 0)
    {
        std::cout << "Enter the name of the contact you want to add: ";
        std::cin >> InputString;
        ReturnStruct.Username = InputString;

        std::cout << "Enter the E-Mail of the contact you want to add: ";
        std::cin >> InputString;
        ReturnStruct.Email = InputString;

        try
        {
            std::cout << "Enter the number of the contact you want to add: ";
            std::cin >> InputInt;
            ReturnStruct.Number = InputInt;
            ValidInput = 1;
        }
        catch(int InputInt)
        {
            std::cout << "Invalid input, try again.\n";
        }
    }

    return ReturnStruct;
};

std::vector<InfoStruct> RemoveContact(std::vector<InfoStruct> AddressBook)
{
    int AccountSearchMethodInput = 5;
    char RemoveFromBookInput = 'e';
    std::string UserInputString;
    bool DeletingContacts = 0, RemoveConfirmation = 0;

//    for(int i = 0; i < AddressBook.size(); ++i)
//    {
//        std::cout << AddressBook[i].Username << " | ";
//    }
//    std::cout << "\n";

    while(DeletingContacts == 0)
    {
        while(AccountSearchMethodInput > 2 || AccountSearchMethodInput < 0)
        {
            std::cout << "How would you like to search the contacts?\n(0) By name\n(1) By number\n(2) By email\nEnter input: ";
            std::cin >> AccountSearchMethodInput;
        }
        if(AccountSearchMethodInput == 0)
        {
            std::cout << "Please enter the name of the contact you want to search for: ";
            std::cin >> UserInputString;
            for(int i = 0; i < AddressBook.size(); ++i)
            {
                if(AddressBook[i].Username.find(UserInputString) != std::string::npos)
                {
                    std::cout << "Account found: " << AddressBook[i].Username << " | " << AddressBook[i].Email << " | " << AddressBook[i].Number << "\nRemove from book? (Y/N) : ";
                    std::cin >> RemoveFromBookInput;
                    tolower(RemoveFromBookInput);
                    if(RemoveFromBookInput == 'y')
                    {
                        AddressBook.erase(AddressBook.begin() + i);
                    }
                }
            }
        }
        else if(AccountSearchMethodInput == 1)
        {
            int SearchNumber;
            std::cout << "Please enter the number of the contact you want to search for: ";
            std::cin >> SearchNumber;
            for(int i = 0; i < AddressBook.size(); ++i)
            {
                if(AddressBook[i].Number == SearchNumber)
                {
                    std::cout << "Account found: " << AddressBook[i].Username << " | " << AddressBook[i].Email << " | " << AddressBook[i].Number << "\nRemove from book? (Y/N) : ";
                    std::cin >> RemoveFromBookInput;
                    tolower(RemoveFromBookInput);
                    if(RemoveFromBookInput == 'y')
                    {
                        AddressBook.erase(AddressBook.begin() + i);
                    }
                }
            }
        }
        else if(AccountSearchMethodInput == 2)
        {
            std::cout << "Please enter the email of the contact you want to search for: ";
            std::cin >> UserInputString;
            for(int i = 0; i < AddressBook.size(); ++i)
            {
                if(AddressBook[i].Email.find(UserInputString) != std::string::npos)
                {
                    std::cout << "Account found: " << AddressBook[i].Username << " | " << AddressBook[i].Email << " | " << AddressBook[i].Number << "\nRemove from book? (Y/N) : ";
                    std::cin >> RemoveFromBookInput;
                    tolower(RemoveFromBookInput);
                    if(RemoveFromBookInput == 'y')
                    {
                        AddressBook.erase(AddressBook.begin() + i);
                    }
                }
            }
        }
        std::cout << "\nAll accounts searched.";
        std::cout << "\nWould you like to search again? (y/n) ";
        std::cin >> UserInputString;
        if(UserInputString == "n")
        {
            DeletingContacts = 1;
        }
    }

    return AddressBook;


};

void PrintAddressBook(std::vector<InfoStruct> AddressBook)
{
    for(int i = 0; i < AddressBook.size(); ++i)
    {
        std::cout << "(" << i << ") " << AddressBook[i].Username << " | " << AddressBook[i].Email << " | " << AddressBook[i].Number << "\n";
    }
}

