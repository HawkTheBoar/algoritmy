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

void heapify(vector<int>& arr, int n, int i){

    // Initialize largest as root
    int largest = i;

    // left index = 2*i + 1
    int l = 2 * i + 1;

    // right index = 2*i + 2
    int r = 2 * i + 2;

    // If left child is larger than root
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// Main function to do heap sort
void heapSort(vector<int>& arr){
    int n = arr.size();

    // Build heap (rearrange vector)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {

        // Move current root to end
        swap(arr[0], arr[i]);

        // Call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
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
    heapSort(res);
    std::string sorted = arrToString(&res);
    sortTimer.stop();
    std::string readFileTime = "Time taken to read the file: " + std::to_string(readTimer.getDuration()) + " seconds.\n";
    std::string sortFileTime = "Time taken to sort the file: " + std::to_string(sortTimer.getDuration()) + " seconds.\n";
    std::string totalTimeTaken = "Total time taken: " + std::to_string(sortTimer.getDuration()+readTimer.getDuration())+ " seconds.\n";
    writeToFile("output.txt", readFileTime + sortFileTime + totalTimeTaken);
    writeToFile("sortedArr.txt", sorted);
    return 0;
}