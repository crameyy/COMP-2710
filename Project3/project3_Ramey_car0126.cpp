// File Name   : project3_Ramey_car0126.cpp
// Author      : Clay Ramey (car0126)
// Version     : 03/10/2024
// Description : Comp 2710 - Software Construction Project 3
// Resources   : I used the following resources to help me complete this project:
// Citation 1  - https://www.geeksforgeeks.org/selection-sort/
// Citation 2  - https://cplusplus.com/doc/tutorial/files/
// Compile     : g++ -std=c++11 project3_Ramey_car0126.cpp -o Project3
// Run         : ./Project3

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int arr_size(string file) {

    // gets size of array
    int count = 0;
    int i;
    ifstream fin;
    fin.open(file); //.txt file
    while(fin >> i) {
        count++;
    }
    fin.close();
    return count;
}


int* read_file(int count, string file_name) {

    //puts data into array
    ifstream iFile;
    iFile.open(file_name);
    int n = 0;
    int* num = new int[count];
    for (int i = 0; i < count; i++) {
        iFile >> num[i];
        cout << num[i] << "\n";
    }
    iFile.close();
    return num;
}

int* merge_and_sort(int* arr1, int* arr2, int size1, int size2) {

    // new vars needed for the following algorthim and combine
    int new_size = size1 + size2;
    int size_difference = new_size - size2;
    int* new_arr = new int[new_size];

    //combines arr1 and arr2
    for (int i = 0; i < new_size; i++) {
        if (i < size1) {
            new_arr[i] = arr1[i];
        }
        else {
            new_arr[i] = arr2[i-size1];
        }
    }

    cout << "\nThe sorted list of " << new_size << " numbers is: ";

    // ALGORITHM USED > selection sort
    // vars used in sort
    int i, j, min_idx; 
    // One by one move boundary of unsorted subarray 
    for (i = 0; i < new_size; i++) { 
  
        // Find the minimum element in 
        // unsorted array 
        min_idx = i; 
        for (j = i + 1; j < new_size; j++) { 
            if (new_arr[j] < new_arr[min_idx]) {
                min_idx = j; 
            }
        }

        // Swap the found minimum element 
        // with the first element 
        if (min_idx != i) {
            swap(new_arr[min_idx], new_arr[i]); 
        }
        cout << new_arr[i] << " ";
    }
    return new_arr;
} 

void write_file(int* arr, int arr_size) {
    
    // takes sorted array and arrays size as input
    // outputs new file with this information
    string output_filename;
    cout << "\nEnter the output file name: ";
    cin >> output_filename;
    ofstream oFile;
    oFile.open (output_filename);
    for (int i = 0; i < arr_size; i++) {
        oFile << arr[i] << "\n";
    }
    oFile.close();

    cout << "*** Please check the new file - " << output_filename << " ***" <<
        "\n*** Goodbye. ***" << endl;
}

bool check_file(string file_name) {
    // checks if file is a real and valid file
    bool valid_file = false;
    ifstream instream;
    instream.open((char*)file_name.c_str());
    valid_file = instream.good();
    if (!valid_file) {
        cout << "Error: Invalid filename, please try again\n";
        cout << endl;
        return false;
    }
    else {
        return true;
    }
}

int main() {

    // takes user input to get file name
    string file_name1;
    string file_name2;

    cout << "*** Welcome to Ramey's sorting program ***\n" <<
        "Enter the first input file name: ";
    cin >> file_name1;

    bool file_check1 = check_file(file_name1);
    // while loop for file check1
    while (file_check1 == false) {
        cout << "Enter the first input file name: ";
        cin >> file_name1;
        file_check1 = check_file(file_name1);
    }
    int count1 = arr_size(file_name1);
    cout << "The list of " << count1 << " numbers in file " <<
        file_name1 << " is:\n";
    int * arr_1 = read_file(count1, file_name1);  // input txt file #1

    cout << "\nEnter the second input file name: ";
    cin >> file_name2;

    bool file_check2 = check_file(file_name2);
    // while loop for file check2
    while (file_check2 == false) {
        cout << "Enter the second input file name: ";
        cin >> file_name2;
        file_check2 = check_file(file_name2);
    }
    int count2 = arr_size(file_name2);
    cout << "The list of " << count2 << " numbers in file " <<
        file_name2 << " is:\n";
    int * arr_2 = read_file(count2, file_name2);  // input txt file #2

    int * sorted_arr = merge_and_sort(arr_1, arr_2, count1, count2);

    int count3 = count1 + count2;
    write_file(sorted_arr, count3);

    return 0;
}