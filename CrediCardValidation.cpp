/*
    Algorithm to validate a Credit Card Number;
    Camila Nori Dias Kubota
*/


#include <stdio.h>
#include <iostream>
#include<string>
#include<algorithm>
#include<ctime>
#include<sstream>
#include<iomanip>



using std::cout;
using std::cin;
using std::string;

bool isNumberString(const string& input) {
    return !input.empty() && std::all_of(input.begin(), input.end(), ::isdigit);
}


std::tm stringToDate(const std::string& dateString) {
    std::tm timeInfo = {};
    std::istringstream ss(dateString);
    char delimiter;
    ss >> std::get_time(&timeInfo, "%d/%m/%Y"); // Change according to your system Default
    if (ss.fail()) {
        std::cerr << "Failed to parse date string: " << dateString << std::endl;
    }
    return timeInfo;
}

bool isValid(const string& date) {
    std::time_t currentTime = std::time(nullptr);
    std::tm expDate = stringToDate(date);
    return std::mktime(&expDate) > currentTime;

}

bool creditCardValid(const string& number, const string& date) {
    bool numberValid = isNumberString(number);
    bool dateValid = isValid(date);
    bool valid = numberValid && dateValid;
    return valid;
}

int main() {
    string ccNumber;
    string date;

    cout << "This program uses the Luhn Algorigthm to validate a Credit Card number." << std::endl;
    cout << "You can enter 'exit' anytime to quit." << std::endl;

    while (true) {

        cout << "Please enter a Credit Card number to validate: ";
        cin >> ccNumber;

        if (ccNumber == "exit")
            break;

        cout << "Please enter the expiration date: ";
        cin >> date;
        if (date == "exit")
            break;

        else if (!creditCardValid(ccNumber, date)) {
            cout << "Bad input! ";
            continue;
        }

        int len = ccNumber.length();
        int doubleEvenSum = 0;

        /*
        Step 1 is to double every second digit, starting from the right.If it
        results in a two digit number, add both the digits to obtain a single
        digit number. Finally, sum all the answers to obtain 'doubleEvenSum'.
        */

        for (int i = len - 2; i >= 0; i = i - 2) {
            int dbl = ((ccNumber[i] - 48) * 2);
            if (dbl > 9) {
                dbl = (dbl / 10) + (dbl % 10);
            }
            doubleEvenSum += dbl;
        }

        /*
         Step 2 is to add every odd placed digit from the right to the value
         'doubleEvenSum'. A credit card number has, usually, 16 digits, but better to check out the lenght
         */

        if (len % 2 == 1) {
            for (int i = len; i >= 0; i = i - 2) {
                doubleEvenSum += (ccNumber[i] - 48);
            }
        }

        else {
            for (int i = len - 1; i >= 0; i = i - 2) {
                doubleEvenSum += (ccNumber[i] - 48);
            }
        }

        /*
        Step 3 is to check if the final 'doubleEvenSum' is a multiple of 10.
        If yes, it is a valid CC number. Otherwise, not.
        */


        cout << (doubleEvenSum % 10 == 0 ? "Valid!" : "Invalid!") << std::endl;

        continue;
    }

    return 0;
}
