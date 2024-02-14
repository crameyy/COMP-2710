// File Name   : project2_Ramey_car0126.cpp
// Author      : Clay Ramey (car0126)
// Version     : 02/12/2024
// Description : Comp 2710 - Software Construction Project 2
// Resources   : I used the following resources to help me complete this project:
// Citation 1  - https://www.w3schools.com/cpp/cpp_functions.asp
// Citation 2  - https://www.geeksforgeeks.org/rand-and-srand-in-ccpp/
// Citation 3  - https://www.geeksforgeeks.org/assert-h-in-cpp/
// Citation 4  - https://www.softwaretestinghelp.com/assert-in-cpp/
// Compile     : g++ -std=c++11 project2_Ramey_car0126.cpp -o proj2
// Run         : ./proj2

# include <iostream>
# include <stdlib.h>
# include <assert.h>
# include <ctime>
using namespace std;

bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive) {
    if (A_alive && B_alive || A_alive && C_alive || B_alive && C_alive) {
        return true;
    }
    else {
        return false;
    }
}

// Accuracy constant
const float aaron_acc = 1.0 / 3.0;
const float bob_acc = 1.0 / 2.0;
const float charlie_acc = 1.0;

bool shoot(float accuracy) {
    float random_num = rand() % 100;
    if (random_num <= accuracy * 100) {
        return true;
    }
    else {
        return false;
    }
}


// Arrons first shooting strategy
int Aaron_shoots1(bool& B_alive, bool& C_alive) {
    if (C_alive) {
        bool shot = shoot(aaron_acc);
        if (shot) {
            C_alive = false;
        }
    return 2;
    }
    else if (B_alive) {
        bool shot = shoot(aaron_acc);
        if (shot) {
            B_alive = false;
        }
    return 1;
    }
    return 0;
}

// Bob shooting chances
int Bob_shoots(bool& A_alive, bool& C_alive) {
    if (C_alive) {
        bool shot = shoot(bob_acc);
        if (shot) {
            C_alive = false;
        }
    return 2;
    }
    else if (A_alive) {
        bool shot = shoot(bob_acc);
        if (shot) {
            A_alive = false;
        }
    return 1;
    }
    return 0;
}

// Charlie shooting chances
int Charlie_shoots(bool& A_alive, bool& B_alive) {
    if (B_alive) {
        bool shot = shoot(charlie_acc);
        if (shot) {
            B_alive = false;
        }
    return 2;
    }
    else if (A_alive) {
        bool shot = shoot(charlie_acc);
        if (shot) {
            A_alive = false;
        }
    return 1;
    }
    return 0;
}

// Aarons second strategy
int Aaron_shoots2(bool& B_alive, bool& C_alive) {
    if (B_alive && C_alive) {
        // don't shoot
        return -1;
    }
    else {
        return Aaron_shoots1(B_alive, C_alive);
    }
}

//initialize vars
int A_wins = 0;
int B_wins = 0;
int C_wins = 0;

void strat_1() {
    bool A_alive = true;
    bool B_alive = true;
    bool C_alive = true;
    while (at_least_two_alive(A_alive, B_alive, C_alive)) {
        if (A_alive) {
            Aaron_shoots1(B_alive, C_alive);
        }
        if (B_alive) {
            Bob_shoots(A_alive, C_alive);
        }
        if (C_alive) {
            Charlie_shoots(A_alive, B_alive);
        }
    }
    if (A_alive) {
        A_wins++;
    }
    if (B_alive) {
        B_wins++;
    }
    else {
        C_wins++;
    }
}

void strat_2() {
    bool A_alive = true;
    bool B_alive = true;
    bool C_alive = true;
    while (at_least_two_alive(A_alive, B_alive, C_alive)) {
        if (A_alive) {
            Aaron_shoots2(B_alive, C_alive);
        }
        if (B_alive) {
            Bob_shoots(A_alive, C_alive);
        }
        if (C_alive) {
            Charlie_shoots(A_alive, B_alive);
        }
    }
    if (A_alive) {
        A_wins++;
    }
    if (B_alive) {
        B_wins++;
    }
    else {
        C_wins++;
    }
}

void press_any_key() {
    cout << "Press any key to continue...";
    cin.ignore().get(); // pause command for linux terminal
}

void test_at_least_two_alive(void) {
    cout << "Unit Testing 1: Function - at_least_two_alive()\n";
    cout << "\tCase 1: Aaron alive, Bob alive, Charlie alive\n";
    assert(true == at_least_two_alive(true, true, true));
    cout << "\tCase passed ...\n";

    cout << "\tCase 2: Aaron dead, Bob alive, Charlie alive\n";
    assert(true == at_least_two_alive(false, true, true));
    cout << "\tCase passed ...\n";

    cout << "\tCase 3: Aaron alive, Bob dead, Charlie alive\n";
    assert(true == at_least_two_alive(true, false, true));
    cout << "\tCase passed ...\n";

    cout << "\tCase 4: Aaron alive, Bob alive, Charlie dead\n";
    assert(true == at_least_two_alive(true, true, false));
    cout << "\tCase passed ...\n";

    cout << "\tCase 5: Aaron dead, Bob dead, Charlie alive\n";
    assert(false == at_least_two_alive(false, false, true));
    cout << "\tCase passed ...\n";

    cout << "\tCase 6: Aaron dead, Bob alive, Charlie dead\n";
    assert(false == at_least_two_alive(false, true, false));
    cout << "\tCase passed ...\n";

    cout << "\tCase 7: Aaron alive, Bob dead, Charlie dead\n";
    assert(false == at_least_two_alive(true, false, false));
    cout << "\tCase passed ...\n";

    cout << "\tCase 8: Aaron dead, Bob dead, Charlie dead\n";
    assert(false == at_least_two_alive(false, false, false));
    cout << "\tCase passed ...\n";
}

void test_Aaron_shoots1(void) {
    cout << "Unit Testing 2: Function Aaron_shoots1(Bob_alive, Charlie_alive)\n";
    bool B = true; bool C = true;
    cout << "\tCase 1: Bob alive, Charlie alive\n\t\tAaron is shooting at Charlie\n";
    assert(2 == Aaron_shoots1(B, C));

    B = false; C = true;
    cout << "\tCase 2: Bob dead, Charlie alive\n\t\tAaron is shooting at Charlie\n";
    assert(2 == Aaron_shoots1(B, C));

    B = true; C = false;
    cout << "\tCase 3: Bob alive, Charlie dead\n\t\tAaron is shooting at Bob\n";
    assert(1 == Aaron_shoots1(B, C));
}

void test_Bob_shoots(void) {
    cout << "Unit Testing 3: Function Bob_shoots(Aaron_alive, Charlie_alive)\n";
    bool A = true; bool C = true;
    cout << "\tCase 1: Aaron alive, Charlie alive\n\t\tBob is shooting at Charlie\n";
    assert(2 == Bob_shoots(A, C));

    A = false; C = true;
    cout << "\tCase 2: Aaron dead, Charlie alive\n\t\tBob is shooting at Charlie\n";
    assert(2 == Bob_shoots(A, C));

    A = true; C = false;
    cout << "\tCase 3: Aaron alive, Charlie dead\n\t\tBob is shooting at Aaron\n";
    assert(1 == Bob_shoots(A, C));
}

void test_Charlie_shoots(void) {
    cout << "Unit Testing 4: Function Charlie_shoots(Aaron_alive, Bob_alive)\n";
    bool A = true; bool B = true;
    cout << "\tCase 1: Aaron alive, Bob alive\n\t\tCharlie is shooting at Bob\n";
    assert(2 == Charlie_shoots(A, B));

    A = false; B = true;
    cout << "\tCase 2: Aaron dead, Bob alive\n\t\tCharlie is shooting at Bob\n";
    assert(2 == Charlie_shoots(A, B));

    A = true; B = false;
    cout << "\tCase 3: Aaron alive, Bob dead\n\t\tCharlie is shooting at Aaron\n";
    assert(1 == Charlie_shoots(A, B));
}

void test_Aaron_shoots2(void) {
    cout << "Unit Testing 5: Function Aaron_shoots2(Bob_alive, Charlie_alive)\n";
    bool B = true; bool C = true;
    cout << "\tCase 1: Bob alive, Charlie alive\n\t\tAaron intentionally misses his first shot\n";
    cout << "\t\tBoth Bob and Charlie are alive.\n";
    assert(-1 == Aaron_shoots2(B, C));

    B = false; C = true;
    cout << "\tCase 2: Bob dead, Charlie alive\n\t\tAaron is shooting at Charlie\n";
    assert(2 == Aaron_shoots2(B, C));

    B = true; C = false;
    cout << "\tCase 3: Bob alive, Charlie dead\n\t\tAaron is shooting at Bob\n";
    assert(1 == Aaron_shoots2(B, C));
}


int main()
{
    //initialize vars for last print
    int A_wins_strat1 = 0;
    int A_wins_strat2 = 0;
    
    cout << "*** Welcome to Ramey's Duel Simulator ***\n";

    // call all testing methods
    srand(time(0));
    test_at_least_two_alive();
    press_any_key();
    test_Aaron_shoots1();
    press_any_key();
    test_Bob_shoots();
    press_any_key();
    test_Charlie_shoots();
    press_any_key();
    test_Aaron_shoots2();
    press_any_key();

    cout << "Ready to test strategy 1 (run 10000 times):\n";
    press_any_key();
    for (int i = 0; i < 10000; i++) {
        strat_1();
    }
    A_wins_strat1 = A_wins;
    cout << "Aaron won " << A_wins << "/10000 duels or " << (A_wins / 10000.0) * 100 << "%\n";
    cout << "Bob won " << B_wins << "/10000 duels or " << (B_wins / 10000.0) * 100 << "%\n";
    cout << "Charlie won " << C_wins << "/10000 duels or " << (C_wins / 10000.0) * 100 << "%\n";
    press_any_key();
    cout << "Ready to test strategy 2 (run 10000 times):\n";
    press_any_key();
    for (int i = 0; i < 10000; i++) {
        strat_2();
    }
    A_wins_strat2 = A_wins;
    cout << "Aaron won " << A_wins << "/10000 duels or " << (A_wins / 10000.0) * 100 << "%\n";
    cout << "Bob won " << B_wins << "/10000 duels or " << (B_wins / 10000.0) * 100 << "%\n";
    cout << "Charlie won " << C_wins << "/10000 duels or " << (C_wins / 10000.0) * 100 << "%\n";
    press_any_key();

    if (A_wins_strat2 > A_wins_strat1) {
        cout << "Strategy 2 is better than strategy 1.\n";
    }
    else {
        cout << "Strategy 1 is better than strategy 2.\n";
    }
    return 0;
}