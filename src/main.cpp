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

using namespace std;
using namespace Utility;
using namespace Utility::Mth;

//using Vec3 = Utility::Mth::Vec3;

///int argc, char * argv[]



    Bank myBank = Bank("Standard");


    int main()
    {

        Vec2 mousePosition = Vec2(2, 2);

        std::cout << mousePosition.getX();

        myBank.addAccount("John Paul", 10.0);
        myBank.addAccount("Jane Smith", 12.0);
        myBank.addAccount("Alice Johnson", 20.0);

        BankAccount& account = myBank.getAccount(1000);
        BankAccount& account2 = myBank.getAccount(1001);
        BankAccount& account3 = myBank.getAccount(1002);


        myBank.transfer(account, account2, 4);
        myBank.transfer(account2, account3, 460);

        account.withdraw(2);



        myBank.generateReport();



        return 0;
    }

