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

void merge(vector<int>& arr, int left, 
                     int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temp vectors
    vector<int> L(n1), R(n2);

    // Copy data to temp vectors L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    // Merge the temp vectors back 
    // into arr[left..right]
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], 
    // if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], 
    // if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
void mergeSort(vector<int>& arr, int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr,  mid+ 1, right);
    merge(arr, left, mid, right);
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
    mergeSort(res, 0, res.size() - 1);
    std::string sorted = arrToString(&res);
    sortTimer.stop();
    std::string readFileTime = "Time taken to read the file: " + std::to_string(readTimer.getDuration()) + " seconds.\n";
    std::string sortFileTime = "Time taken to sort the file: " + std::to_string(sortTimer.getDuration()) + " seconds.\n";
    std::string totalTimeTaken = "Total time taken: " + std::to_string(sortTimer.getDuration()+readTimer.getDuration())+ " seconds.\n";
    writeToFile("output.txt", readFileTime + sortFileTime + totalTimeTaken);
    writeToFile("sortedArr.txt", sorted);
    return 0;
}