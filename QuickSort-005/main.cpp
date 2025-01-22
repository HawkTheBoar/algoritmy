#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>
#include <limits>

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
int partition(std::vector<int>* arr, int low, int high){
    int pivot = (*arr)[high];
    int i = low - 1;
    for(int j = low; j < high; j++){
        if((*arr)[j] <= pivot){
            i++;
            swap(&(*arr)[j], &(*arr)[i]);
        }
    }

    // swap pivot with last number bigger than pivot
    swap(&(*arr)[i+1], &(*arr)[high]);
    return i + 1;
}
std::string arrToString(std::vector<int>* arr) {
    std::string res = "";
    for (int i = 0; i < arr->size(); i++) {
        res += std::to_string(arr->at(i)) + "\n";  // Convert integer to string and concatenate
    }
    return res;
}
void quickSort(std::vector<int>* arr, int low, int high){
    if(low >= high)
        return;
    
    int pindex = partition(arr, low, high);

    quickSort(arr, low, pindex-1);
    quickSort(arr, pindex+1, high);

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
    quickSort(&res, 0, res.size()+1);
    std::string sorted = arrToString(&res);
    sortTimer.stop();
    std::string readFileTime = "Time taken to read the file: " + std::to_string(readTimer.getDuration()) + " seconds.\n";
    std::string sortFileTime = "Time taken to sort the file: " + std::to_string(sortTimer.getDuration()) + " seconds.\n";
    std::string totalTimeTaken = "Total time taken: " + std::to_string(sortTimer.getDuration()+readTimer.getDuration())+ " seconds.\n";
    writeToFile("output.txt", readFileTime + sortFileTime + totalTimeTaken);
    writeToFile("sortedArr.txt", sorted);
    return 0;
}