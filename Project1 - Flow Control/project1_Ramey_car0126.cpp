// File Name   : project1_Ramey_car0126.cpp
// Author      : Clay Ramey (car0126)
// Version     : 02/01/2024
// Description : comp 2710 - Software Construction Project 1
// Resources   : I used the following resources to help me complete this project:
// Citation 1  - https://www.geeksforgeeks.org/program-check-input-integer-string-cpp/
// Citation 2  - https://www.geeksforgeeks.org/converting-strings-numbers-cc/
// Citation 3  - https://stackoverflow.com/questions/14903198/function-stof-could-not-be-resolved
// Citation 4  - https://www.w3schools.com/cpp/default.asp - any syntax questions
// Extra resource -  GTA office hours Wed 1/31/24 from 2:30pm-4pm
// Compile     : g++ -std=c++11 project1_Ramey_car0126.cpp -o proj1
// Run         : ./proj1

#include <iostream>
using namespace std;

bool check_number(string str) {
   for (int i = 0; i < str.length(); i++)
   if (isdigit(str[i]) == false)
      return false;
      return true;
}

int main() {
	// Format for Currency
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);

	// initialize variables
	float loan = -1;
	float interest = -1;
	float payments = -1;

	//  while loop for calculations
	while (loan <= 0) {
		cout << "\nLoan Amount: ";
		std::string x;
		cin >> x;
   		if (check_number(x)) {
			loan = stof(x);
   		}
   		else {
      		cout<< "Warning: Invalid loan"<<endl;
			loan = -1;
   		}
	}

	while (interest <= -1) {
		cout << "Interest Rate (% per year): ";
		
		std::string x;
		cin >> x;
   		if (check_number(x)) {
			interest = stof(x);
   		}
   		else {
      		cout<< "Warning: Invalid interest rate\n"<<endl;
			interest = -1;
   		}
	}

	float interest_rate = interest / 12 / 100;
	while (payments <= 0 || payments <= loan * interest_rate) {
		cout << "Monthly Payments: ";
		std::string x;
		cin >> x;
   		if (check_number(x)) {
			payments = stof(x);
   		}
   		else {
			payments = -1;
   		}
		if (payments <= loan * interest_rate) {
			cout << "Warning: Insufficient payment\n" <<endl;
			payments = -1;
		}
	}
	cout << endl;

	// AMORTIZATION TABLE
	cout << "*****************************************************************\n"
	     << "\tAmortization Table\n"
	     << "*****************************************************************\n"
	     << "Month\tBalance\t  Payment\tRate\tInterest\tPrincipal\n";

	int cur_month = 0;
	float interest_total = 0;

	while (loan > 0) {
		if (cur_month == 0) {
			cout << cur_month++ << "\t$" << loan;
			if (loan < 1000) cout << "\t";
			cout << "  N/A\t\tN/A\tN/A\t\tN/A\n";
		}
		else {
			float interest_payment = loan * interest_rate;
			float principal_payment = payments - interest_payment;
			loan -= principal_payment;
			interest_total += interest_payment;

			if (loan < 0) {
				principal_payment += loan;
				payments += loan;
				loan = 0;
			}

			cout << cur_month++ << "\t$" << loan;
			if (loan < 1000) cout << "\t";
			cout << "  $" << payments << "\t" << interest_rate * 100 << "\t$" << interest_payment << "\t\t$" << principal_payment << "\n"; 
		}
	}

	cout << "****************************************************************\n";
	cout << "\nIt takes " << --cur_month << " months to pay off "
	     << "the loan.\n"
	     << "Total interest paid is: $" << interest_total;
	cout << endl << endl;

	return 0;
}
