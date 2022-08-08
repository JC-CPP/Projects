#include <vector>
#include <iostream>
#include <fstream>
#include <tuple>


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
    char YNuserChoice;
    bool loadAccounts = 0;
    std::vector<InfoStruct> AddressBook; // creates a vector for the addresses ( our address book ) for us to play with
    struct InfoStruct TempInfo; // This will hold info whilst we run a function, e.g. if we want to add a contact this will hold the new contact info then be forwarded into the addressbook
    std::string AccountLineHolder;

    //CHECKS IF THERE ARE ANY ACCOUNTS IN TXT FILE
    std::ifstream accountsFile; // variable to load the file into
    accountsFile.open("addressbook.txt", std::ios::in); // attempts to open the txt file with our account names in
    if(accountsFile.is_open()) // if it was able to open the file then ask the user if it wants to load the accounts in
    {
        while(1)
        {
            std::cout << "Accounts file found! Would you like to load the account in? (Y/N) ";
            std::cin >> YNuserChoice;
            YNuserChoice = std::tolower(YNuserChoice);
            if(YNuserChoice == 'n' || YNuserChoice == 'y')
            {
                break;
            }
            else
                std::cout << "\nBad input. Try again\n";
        }
        if(YNuserChoice == 'y')
        {
            loadAccounts = 1; // set accounts loaded to true
        }
    }
    else // else if the program wasn't able to open / make the file then tell the user
        std::cout << "\nAccounts file couldn't be created / opened.\n";

    if(loadAccounts == 1)
    {
        int Index = 0; // index for what part of the string we're extracting. (3 is max (name, number, email) ).
        std::string delimiter = ",";
        std::tuple<std::string, int, std::string> Account; // holds different parts of information per account to load into our vector
        std::string token; // holds the extracted piece of information from txt flie

        while(std::getline(accountsFile, AccountLineHolder))  // opens the file and puts each line into the string AccountLineHolder
        {
            size_t pos = 0; // holds position we're at in the string

            while ((pos = AccountLineHolder.find(delimiter)) != std::string::npos) // keeps us in the while loop until there's no more text no the line we're substringing
            {
                token = AccountLineHolder.substr(0, pos); // pulls a section from the line we took from the txt file
                if(Index == 0) // correlating to the index we're at, throws it into our tuple
                {
                    std::get<0>(Account) = token;
                }
                else if(Index == 1)
                {
                    std::get<1>(Account) = std::stoi(token);
                }
                else
                    std::get<2>(Account) = token;

                AccountLineHolder.erase(0, pos + delimiter.length()); // deletes the part of the string we just used
                ++Index;
            }
            TempInfo.Username = std::get<0>(Account);
            TempInfo.Number = std::get<1>(Account);
            TempInfo.Email = std::get<2>(Account);
            AddressBook.push_back(TempInfo); // loads our pulled account line from the txt file into our vector
            Index = 0; // resets the index var

        }
        accountsFile.close(); // close the file because we've finished loading it into our program
    }


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
            if(loadAccounts == 1)
            {
                std::cout << "\nWould you like to save the changes made to the account list? (Y/N) ";
                std::cin >> YNuserChoice;
                if(YNuserChoice == 'y')
                {
                    std::fstream AccountBookF; // Creates a new variable for the file that is used for writing
                    AccountBookF.open("addressbook.txt", std::ios::out); // opens the file as a writeable var
                    for(int i = 0; i < AddressBook.size(); ++i)
                    {
                        AccountBookF << AddressBook[i].Username << "," << AddressBook[i].Number << "," << AddressBook[i].Email << "," << std::endl;
                    }
                }
            }
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

