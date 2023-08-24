#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;

const int MAX_YEARS = 100; // Maximum number of years to support

// Define a structure to store interest and inflation data for a year
struct YearData {
    int year;
    double interestRate;
    double inflationRate;
};

// Function to read interest and inflation rates from a CSV file into an array of structures
int readData(const string& fileName, YearData data[]) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << fileName << endl;
        exit(1);
    }
    string line;
    getline(file, line); // Skip header line
    int count = 0;
    while (getline(file, line) && count < MAX_YEARS) {
        istringstream ss(line);
        ss >> data[count].year >> data[count].interestRate >> data[count].inflationRate;
        count++;
        
    }
    file.close();
    return count;
}

// Function to calculate the value of money invested at a given year
double calculateValue(const YearData data[], double amount, int investYear, int targetYear, int dataCount) {
    // double value = amount;

    for (int year = investYear; year < targetYear; year++) {
        double interestRate = 0.0;
        double inflationRate = 0.0;
        
        // Find the data for the current year
        for (int i = 0; i < dataCount; i++) {
            if (data[i].year == year) {
                interestRate = data[i].interestRate;
                inflationRate = data[i].inflationRate;
                break;
            }
        }

        
         double amount = amount * ((interestRate) / 100 )+ 1;
        // value *= effectiveRate;
    }
    return amount;
    // return round(value * 100) / 100; // Round to the nearest paisa
}

int main() {
    string fileName = "india_data.csv"; // Replace with your CSV file name
    YearData data[MAX_YEARS];
    int dataCount = readData(fileName, data);

    double amount;
    int investYear, targetYear;

    cout << "Enter the amount of investment: ";
    cin >> amount;

    cout << "Enter the year in which it was invested: ";
    cin >> investYear;

    cout << "Enter the year for which you want to estimate the value: ";
    cin >> targetYear;

    double futureValue = calculateValue(data, amount, investYear, targetYear, dataCount);

    cout << fixed << setprecision(2);
    cout << "The estimated value in " << targetYear << " is " << futureValue << " INR" << endl;

    return 0;
}
