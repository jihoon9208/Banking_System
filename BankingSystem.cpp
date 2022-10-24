#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <iomanip>
#include <unistd.h>
#include <algorithm>

using namespace std;

string getFileContents(ifstream& File) {   
    
    string contents = "";                  
    
    if (File) {
        while (File.good ()){
            string tmp;
            getline (File , tmp);
            tmp += "\n";
            contents += tmp;
        }
	return contents;
    }

    else return "ERROR file does not exist.";
    
}

string readLine(string &filename, int n) {

    ifstream file(filename);
    string output;

    // Skip lines
    for (int i = 0; i < n; i++) {
        getline(file, output);
    }
    // Actual output
    getline(file, output);
    file.close();

    return output;
}

class Bank {
    public:
        // MENUS
        void mainMenu();
        void loginScreen();
        void registerScreen();
        void bankMenuScreen();
        void bankBalanceScreen();
        void bankWithdrawScreen();
        void bankDepositScreen();

        // OTHER FUNCTIONS
        bool createCount(const string username, const string password);
        bool authenticateNumber(const string usernameAttempt);
        bool authenticatePassword(const string usernameAttempt, const string passwordAttempt);
        bool withdraw(const string username, float amount);
        bool deposit(const string username, float amount);

    private:
        bool authenticated;
        string cnAttempt;
        string pwAttempt;
        
};

void Bank::mainMenu() {   
    int option;

    do {   
        system("clear"); // clear console.
        cout << "=================================" << endl;
        cout << "\n\n";
        cout << "   Please choose your option." << endl;
        cout << "   1 : LOGIN WITH CARD" << endl;
        cout << "   2 : REGISTER" << endl;
        cout << "   3 : QUIT" << endl;
        cout << "\n\n";
        cout << "=================================" << endl;
        cout << "\n\n";
        cout << "   Option : "; cin >> option;

        switch(option)
        {
            case 1:
                cout << "   LOGIN INITIALIZED...\n";
                sleep(0.5);
                loginScreen();
                break;

            case 2:
                cout << "   REGISTER INITIALIZED...\n";
                sleep(0.5);
                registerScreen();
                break;

            case 3:
                cout << "   QUIT INITIALIZED...\n";
                sleep(0.5);
                option = 4;
                exit(0);

            default:
                cout << "   INVALID OPTION.\n";
                cout << "   Please choose an option from 1 to 3.\n";
                sleep(0.5);
                mainMenu();
                break;
        }
    } while (option != 3);
}

void Bank::loginScreen() {       
    
    bool insertCard = true;
    cout << "\n\n";
    cout << "   Please insert your card. " << endl;
    
    if ( insertCard )
        cnAttempt = "1234-2345-4352-6859";
        cout << "   Current insert your card Number : "<< cnAttempt << endl;

    if (authenticateNumber(cnAttempt)) {

        cout << "   Please enter your password. " << endl << "  Password : "; cin >> pwAttempt;
        if (authenticatePassword(cnAttempt, pwAttempt)) {
            authenticated = true;
            cout << "   Login Successful!" << endl;
            cout << "\n\n";
            cout << "=================================" << endl;
            cout << "\n\n";
            sleep(0.5);
            bankMenuScreen();
        }

        else {
            cout << "   Wrong password. Please try another password." << endl;
            sleep(0.5);
            loginScreen();
        }
    }

    else {
        cout << "   This card not valid Number. Please insert another card." << endl;
        cout << "\n\n";
        
        sleep(0.5);
        mainMenu();
    }
}

void Bank::registerScreen() {

    system("clear");
    
    string cn, pw;
    cout << "\n\n";
    cout << "=================================" << endl;
    cout << "\n\n";
    cout << "   Please insert an unused user's card Number. " << endl << " user card Number : "; cin >> cn;
    cout << "   Please enter a password. " << endl << " Password : "; cin >> pw;

    if(createCount(cn, pw)) {
        cout << "   SUCCESS! Card Number " << cn << " registed.\n";
        sleep(0.5);
        mainMenu();
    }

    else{
        cout << "   Card Number already taken.\n";
        sleep(0.5);
        registerScreen();
    }
}


void Bank::bankMenuScreen() {

    system("clear");
    
    int option;

    while( true ) {
        cout << "\n\n";
        cout << "=================================" << endl;
        cout << "\n\n";
        cout << "   Please choose your option." << endl;
        cout << "   1 : BANK BALANCE" << endl;
        cout << "   2 : DEPOSIT MONEY" << endl;
        cout << "   3 : WITHDRAW MONEY" << endl;
        cout << "   4 : LOGOUT" << endl;
        cout << "\n\n";
        cout << "=================================" << endl;
        cout << "\n\n";
        cout << "   Option : "; cin >> option;

        switch(option) {
            case 1:
                cout << "   BANK BALANCE INITIALIZED...\n";
                sleep(0.5);
                bankBalanceScreen();
                break;

            case 2:
                cout << "   DEPOSIT MONEY INITIALIZED...\n";
                sleep(0.5);
                bankDepositScreen();
                break;
            
            case 3:
                cout << "   WITHDRAW MONEY INITIALIZED...\n";
                sleep(0.5);
                bankWithdrawScreen();
                break;
            
            case 4:
                cout << "   LOGOUT INITIALIZED...\n"; 
                sleep(0.5);
                mainMenu();
                break;

            default:
                cout << "   INVALID OPTION.\n";
                cout << "   Please choose an option from 1 to 4.\n";
                sleep(1);
                bankMenuScreen();
                break;   
        }
    }
}

void Bank::bankBalanceScreen() {
    
    system("clear");

    if (authenticated) {   
        string fileName = "data/" + cnAttempt + ".dat";
        string balance = readLine(fileName, 2);
        float Balance = stof(balance);

        stringstream stream;
        stream << fixed << setprecision(2) << Balance;
        balance = stream.str();

        cout << "\n\n";
        cout << "=================================" << endl;
        cout << "\n\n";

        cout << "   Bank Balance available : $" << balance;
        cout << "\n\n";

        sleep(2);

        bankMenuScreen();
    }
}

void Bank::bankWithdrawScreen() {

    system("clear");
    
    if (authenticated) {   
        string userInput;
        float balance;
        cout << "   Please key in your withdrawal amount: $"; cin >> userInput;
        cout << "\n\n";

        if (userInput.find_first_not_of("1234567890.") != string::npos )
        {
            cout << "   Invalid input: " << userInput << endl;
            cout << "\n\n";
            
            bankWithdrawScreen();
        }

        balance = stof(userInput);

        if (balance <= 0) {
            cout << "   Please key in only positive values.\n";
        }

        if (withdraw(cnAttempt, balance)) {
            cout << "   Successfully withdrawed $" << balance << " from account.\n";
            bankBalanceScreen();
            sleep(1);
            bankMenuScreen();
        }

        else {
            cout << "   Not enough money to withdraw from account. Please check your balance and try again.\n";
            
            bankMenuScreen();
        }
    }
}

void Bank::bankDepositScreen() {
    system("clear");
    
    if (authenticated) {  

        string userInput;
        float balance;

        cout << "\n\n";
        cout << "=================================" << endl;
        cout << "\n\n";

        cout << "   Please key in your deposit amount: $"; cin >> userInput;
        cout << "\n\n";

        if (userInput.find_first_not_of("1234567890.") != string::npos ) {
            cout << "   Invalid input: " << userInput << endl;           
            bankDepositScreen();
        }

        balance = stof(userInput);
        if (balance <= 0) {
            cout << "   Please key in only positive values.\n";
        }

        if (deposit(cnAttempt, balance)) {
            cout << "   Successfully deposited $" << balance << " from account.\n";
            bankBalanceScreen();
            sleep(1);
            bankMenuScreen();
        }
    }
}

bool Bank::withdraw(const string username, float amount) {   

    float initialBal;
    string fileName = "data/" + username + ".dat";
    initialBal = stof(readLine(fileName, 2)); 

    if (amount > initialBal) {   
        return false;
    }

    else {   
        string buffer;
        ifstream currentFile(fileName);
        string bufferName = "data/buffer.dat";
        ofstream bufferFile(bufferName);

        for (int i = 0; i < 2; i++) {
            getline(currentFile, buffer);
            bufferFile << buffer + '\n';
        }

        getline(currentFile, buffer); 

        float newBal = initialBal - amount;
        string printBal = to_string(newBal);

        bufferFile << printBal + '\n';

        currentFile.close();
        bufferFile.close();

        remove(fileName.c_str());
        rename("data/buffer.dat", fileName.c_str());
        
        return true;
    }
}

bool Bank::deposit(const string username, float amount) {

    float initialBal;
    string fileName = "data/" + username + ".dat";

    initialBal = stof(readLine(fileName, 2)); 

    string buffer;
    ifstream currentFile(fileName);
    string bufferName = "data/buffer.dat";
    ofstream bufferFile(bufferName);

    for (int i = 0; i < 2; i++) {
        getline(currentFile, buffer);
        bufferFile << buffer + '\n';
    }

    getline(currentFile, buffer); 

    float newBal = initialBal + amount;
    string printBal = to_string(newBal);

    bufferFile << printBal + '\n';

    currentFile.close();
    bufferFile.close();

    remove(fileName.c_str());
    rename("data/buffer.dat", fileName.c_str());
    
    return true;
}

bool Bank::createCount(const string cardNumber, const string password) {

    string fileName = cardNumber + ".dat";
    string pathName = "data/" + fileName;
    
    if (!ifstream(pathName)) {   
        ofstream file(pathName, ios::out);
        file << cardNumber << endl; // un
        file << password << endl; // pw
        file << 0 << endl; // balance
        
        file.close();

        return true; // SUCCESS.
    }

    else return false; 
    
}

bool Bank::authenticateNumber(const string cardNumberAttempt) {

    string fileName = cardNumberAttempt + ".dat";
    string pathName = "data/" + fileName;
    
    if (ifstream(pathName)) return true;
    else return false;
    
}

bool Bank::authenticatePassword(const string cardNumberAttempt, const string passwordAttempt) {

    string fileName = cardNumberAttempt + ".dat";
    string pathName = "data/" + fileName;
    string password = readLine(pathName, 1);

    if (password == passwordAttempt) return true;
    else return false;
    
}

int main () {

    Bank appBank;
    appBank.mainMenu();

    return 0;
}