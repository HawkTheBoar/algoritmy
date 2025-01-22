#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>
#include <limits>

using namespace std;
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
void swap(int* x, int* y){
    int temp = *x;
    *x = *y;
    *y = temp; 
}

std::string arrToString(std::vector<int>* arr) {
    std::string res = "";
    for (int i = 0; i < arr->size(); i++) {
        res += std::to_string(arr->at(i)) + "\n";  // Convert integer to string and concatenate
    }
    return res;
}

// A utility function to get maximum
// value in arr[]
int getMax(int arr[], int n)
{
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

// A function to do counting sort of arr[]
// according to the digit
// represented by exp.
void countSort(int arr[], int n, int exp)
{

    // Output array
    vector<int> output(n);
    int i, count[10] = { 0 };

    // Store count of occurrences
    // in count[]
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    // Change count[i] so that count[i]
    // now contains actual position
    // of this digit in output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // Copy the output array to arr[],
    // so that arr[] now contains sorted
    // numbers according to current digit
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

// The main function to that sorts arr[]
// of size n using Radix Sort
void radixsort(int arr[], int n)
{

    // Find the maximum number to
    // know number of digits
    int m = getMax(arr, n);

    // Do counting sort for every digit.
    // Note that instead of passing digit
    // number, exp is passed. exp is 10^i
    // where i is current digit number
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}

int main(){
    Timer readTimer;
    readTimer.start();
    // std::vector<int> res = readNumbersFromFile("test.txt");
    std::vector<int> res = readNumbersFromFile("input.txt");
    if(!res.empty()){
        for(auto i = res.begin(); i != res.end(); i++){
        }
    } else { std::cout << "Vector is empty!";}
    readTimer.stop();
    Timer sortTimer;
    sortTimer.start();
    // sort
    radixsort(res.data(), res.size());
    std::string sorted = arrToString(&res);
    sortTimer.stop();
    std::string readFileTime = "Time taken to read the file: " + std::to_string(readTimer.getDuration()) + " seconds.\n";
    std::string sortFileTime = "Time taken to sort the file: " + std::to_string(sortTimer.getDuration()) + " seconds.\n";
    std::string totalTimeTaken = "Total time taken: " + std::to_string(sortTimer.getDuration()+readTimer.getDuration())+ " seconds.\n";
    writeToFile("output.txt", readFileTime + sortFileTime + totalTimeTaken);
    writeToFile("sortedArr.txt", sorted);
    return 0;
}