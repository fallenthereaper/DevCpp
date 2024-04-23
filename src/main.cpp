// main.cpp : Defines the entry point for the application.
//

#include "main.h"
#include "utility.h"
#include "containers.h"
#include <vector>
#include "practice.h"
#include "bank.h"
#include "bank_account.h"
#include "tictac_game.h"
#include <sstream>
#include <iomanip>

using namespace std;
using namespace Utility;
using namespace Utility::Mth;

//using Vec3 = Utility::Mth::Vec3;

///int argc, char * argv[]

unsigned long long hexToDecimal(const std::string& hexString) {
    unsigned long long decimalValue;
    std::stringstream ss;
    ss << std::hex << hexString;
    ss >> decimalValue;
    return decimalValue;
}

// Function to convert a decimal integer to a hexadecimal string
std::string decimalToHex(unsigned long long decimalValue) {
    std::stringstream ss;
    ss << std::hex << std::uppercase << decimalValue;
    return ss.str();
}


    Bank myBank = Bank("Standard");


    int main()
    {

        Vec2 mousePosition = Vec2(2, 2);



        myBank.addAccount("John Paul", 10.0);
        myBank.addAccount("Jane Smith", 10.0);
        myBank.addAccount("Alice Johnson", 10.0);

        BankAccount account = myBank.getAccount(1000);
        BankAccount account2 = myBank.getAccount(1001);
        BankAccount account3 = myBank.getAccount(1002);



        std::cout << "Pointer of account 1:  " << &account << '\n';
        std::cout << "Pointer of account 2:  " << &account2 << '\n';
        std::cout << "Pointer of account 3:  " << &account3 << '\n';

        std::cout << "Size of account:  " << sizeof(BankAccount) << '\n';

  

      //  myBank.transfer(account, account2, 4);
       // myBank.transfer(account2, account3, 460);

        account.withdraw(2);



      ///  myBank.generateReport();



        return 0;
    }

