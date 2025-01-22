#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>
#include <limits>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

string strToLower(string s){
    transform(s.begin(), s.end(), s.begin(), [](unsigned char c) {
         return tolower(c);
    });
    return s;
}
int stringToInt(const std::string& str) {
    int value = 0;
    string lwr = strToLower(str);
    // Convert the string to a numeric value based on ASCII values
    for (char c : lwr) {
        value = value * 31 + c; // 31 is a small prime multiplier to create unique values
    }

    return value;
}

void swap(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}
void writeToFile(const std::string& filename, const std::string& content) {
    std::ofstream outFile(filename);  // Open the file in output mode (overwrites existing content)

    if (!outFile) {
        std::cerr << "Error opening file for writing!" << std::endl;
        return;
    }

    outFile << content;  // Write the string to the file
    outFile.close();     // Close the file after writing

    std::cout << "Content written to " << filename << std::endl;
}
std::vector<int> readNumbersFromFile(const std::string& filename) {
    std::ifstream inputFile(filename);  // Open the text file
    std::vector<int> numbers;  // Vector to hold numbers

    if (!inputFile) {
        std::cerr << "Error opening file!" << std::endl;
        return numbers;  // Return empty vector on failure
    }

    int num;
    while (inputFile >> num) {
        numbers.push_back(num);  // Add each number to the vector
        inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the newline character
    }

    inputFile.close();  // Close the file
    return numbers;  // Return the vector containing the numbers
}
std::vector<string> readWordsFromFile(const std::string& filename) {
    std::ifstream inputFile(filename);  // Open the text file
    std::vector<string> numbers;  // Vector to hold numbers

    if (!inputFile) {
        std::cerr << "Error opening file!" << std::endl;
        return numbers;  // Return empty vector on failure
    }

    string num;
    while (inputFile >> num) {
        numbers.push_back(num);  // Add each number to the vector
        inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the newline character
    }

    inputFile.close();  // Close the file
    return numbers;  // Return the vector containing the numbers
}
class Timer {
private:
    std::chrono::steady_clock::time_point start_time;
    std::chrono::steady_clock::time_point end_time;

public:
    void start() {
        start_time = std::chrono::steady_clock::now();  // Use steady_clock here
    }

    void stop() {
        end_time = std::chrono::steady_clock::now();  // Use steady_clock here
    }

    double getDuration() {
        std::chrono::duration<double> duration = end_time - start_time;
        return duration.count();  // Return the time in seconds
    }
};
void sort(std::vector<int>* arr){
    int n = arr->size();
    int outputInterval = 10000;
    for(int i = 0; i < n - 1; i++){
        int minIndex = i;
        for(int j = i + 1; j < n; j++){
            if((*arr)[j] < (*arr)[minIndex]){
                minIndex = j;
            }
        }
        swap((*arr)[i], (*arr)[minIndex]);
        if(i % outputInterval == 0 && i != 0){
            std::cout << i << "/" << n << "\n";
        }
    }
}
void sortStrings(std::vector<string>* arr){
    int n = arr->size();
    int outputInterval = 10000;
    for(int i = 0; i < n - 1; i++){
        int minIndex = i;
        for(int j = i + 1; j < n; j++){
            if(stringToInt((*arr)[j]) < stringToInt((*arr)[minIndex])){
                minIndex = j;
            }
        }
        swap((*arr)[i], (*arr)[minIndex]);
        if(i % outputInterval == 0 && i != 0){
            std::cout << i << "/" << n << "\n";
        }
    }
}void printArr(std::vector<int>* arr){
    for(int i = 0; i < arr->size(); i++){
        std::cout << arr->at(i) << " ";
    }
}
std::string arrToString(std::vector<int>* arr) {
    std::string res = "";
    for (int i = 0; i < arr->size(); i++) {
        res += std::to_string(arr->at(i)) + "\n";  // Convert integer to string and concatenate
    }
    return res;
}
std::string arrToString(std::vector<string>* arr) {
    std::string res = "";
    for (int i = 0; i < arr->size(); i++) {
        res += arr->at(i) + "\n";  // Convert integer to string and concatenate
    }
    return res;
}
int main(){
    
    Timer readTimer;
    readTimer.start();
    // std::vector<int> res = readNumbersFromFile("test.txt");
    // std::vector<int> res = readNumbersFromFile("input.txt");
    std::vector<string> res = readWordsFromFile("string.txt");
    if(!res.empty()){
        for(auto i = res.begin(); i != res.end(); i++){
        }
    } else { std::cout << "Vector is empty!";}
    readTimer.stop();
    Timer sortTimer;
    sortTimer.start();
    // sort(&res);
    sortStrings(&res);
    std::string sorted = arrToString(&res);

    sortStrings(&res);
    // printArr(&res);
    sortTimer.stop();
    std::string readFileTime = "Time taken to read the file: " + std::to_string(readTimer.getDuration()) + " seconds.\n";
    std::string sortFileTime = "Time taken to sort the file: " + std::to_string(sortTimer.getDuration()) + " seconds.\n";
    std::string totalTimeTaken = "Total time taken: " + std::to_string(sortTimer.getDuration()+readTimer.getDuration())+ " seconds.\n";
    writeToFile("output.txt", readFileTime + sortFileTime + totalTimeTaken);
    writeToFile("sortedArr.txt", sorted);

}