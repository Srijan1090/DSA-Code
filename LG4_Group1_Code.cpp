#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Function to generate N random integers
vector<int> generateRandomNumbers(int N) {
    vector<int> numbers;
    srand(time(0));
    for (int i = 0; i < N; i++) {
        numbers.push_back(rand() % 1000); // Random numbers between 0 and 999
    }
    return numbers;
}

// Selection Sort Algorithm
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

// Merge Sort Algorithm
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int i = 0; i < n2; i++) R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Binary Search Algorithm
int binarySearch(const vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

// Interpolation Search Algorithm
int interpolationSearch(const vector<int>& arr, int target) {
    int low = 0, high = arr.size() - 1;
    while (low <= high && target >= arr[low] && target <= arr[high]) {
        int pos = low + ((target - arr[low]) * (high - low)) / (arr[high] - arr[low]);
        if (arr[pos] == target) return pos;
        if (arr[pos] < target) low = pos + 1;
        else high = pos - 1;
    }
    return -1;
}

// Function to measure runtime of a function
template<typename Func>
long long measureTime(Func func) {
    auto start = high_resolution_clock::now();
    func();
    auto stop = high_resolution_clock::now();
    return duration_cast<milliseconds>(stop - start).count();
}

int main() {
    int N;
    cout << "Enter the number of random integers (N): ";
    cin >> N;

    // Generate N random integers
    vector<int> numbers = generateRandomNumbers(N);

    // Copy the array for sorting
    vector<int> selectionSorted = numbers;
    vector<int> mergeSorted = numbers;

    // Perform Selection Sort and measure time
    long long selectionTime = measureTime([&]() { selectionSort(selectionSorted); });
    cout << "Selection Sort completed in " << selectionTime << " ms." << endl;

    // Perform Merge Sort and measure time
    long long mergeTime = measureTime([&]() { mergeSort(mergeSorted, 0, mergeSorted.size() - 1); });
    cout << "Merge Sort completed in " << mergeTime << " ms." << endl;

    // Sort the mergeSorted array to prepare for ALL searches
    mergeSort(mergeSorted, 0, mergeSorted.size() - 1);

    // Display sorted arrays
    cout << "Selection Sorted Array: ";
    for (int num : selectionSorted) cout << num << " ";
    cout << endl;

    cout << "Merge Sorted Array: ";
    for (int num : mergeSorted) cout << num << " ";
    cout << endl;

    // Perform Binary Search
    int target;
    cout << "Enter the number to search: ";
    cin >> target;

    int binaryResult = binarySearch(mergeSorted, target);
    if (binaryResult != -1) {
        cout << "Binary Search: Element found at index " << binaryResult << endl;
    } else {
        cout << "Binary Search: Element not found." << endl;
    }

    // Perform Interpolation Search
    int interpolationResult = interpolationSearch(mergeSorted, target);
    if (interpolationResult != -1) {
        cout << "Interpolation Search: Element found at index " << interpolationResult << endl;
    } else {
        cout << "Interpolation Search: Element not found." << endl;
    }

    // Perform Binary Search and measure time
    target = numbers[rand() % N]; //search for a random number from the original array.
    long long binaryTime = measureTime([&]() { binarySearch(mergeSorted, target); });
    cout << "Binary Search completed in " << binaryTime << " ms." << endl;

    // Perform Interpolation Search and measure time
    long long interpolationTime = measureTime([&]() { interpolationSearch(mergeSorted, target); });
    cout << "Interpolation Search completed in " << interpolationTime << " ms." << endl;

    return 0;
}