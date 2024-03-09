#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class CountSort {
private:
    vector <int> inputArray;
    vector <int> implementation() {
        int N = inputArray.size();
        int M = inputArray[0];
        for(int i = 0 ; i<inputArray.size();i++)
            if(inputArray[i]>M)
                M = inputArray[i];

//        int M = *max_element(inputArray.begin(),inputArray.end());
        vector <int> countArray(M+1,0);

        for(int i = 0 ; i<N ; i++)
            countArray[inputArray[i]]++;

        for(int i = 1 ; i<= M ; i++)
            countArray[i] += countArray[i-1];

        vector <int> outputArray(N);


        for(int i = N-1 ; i>=0 ; i--){
            outputArray[countArray[inputArray[i]]-1] = inputArray[i];
            countArray[inputArray[i]]--;
        }

        return outputArray;

    }

public:
    CountSort(const vector<int>& inputArray) : inputArray(inputArray) {}
    vector<int> sort() {
        return implementation();
    }
};

class RadixSort {
private:
    // A utility function to get the maximum value in arr[]
    int getMax(int arr[], int n) {
        int mx = arr[0];
        for (int i = 1; i < n; i++)
            if (arr[i] > mx)
                mx = arr[i];
        return mx;
    }

    // A function to do counting sort of arr[] according to the digit represented by exp
    void countSort(int arr[], int n, int exp) {
        int output[n]; // Output array
        int i, count[10] = { 0 };

        // Store count of occurrences in count[]
        for (i = 0; i < n; i++)
            count[(arr[i] / exp) % 10]++;

        // Change count[i] so that count[i] now contains actual position of this digit in output[]
        for (i = 1; i < 10; i++)
            count[i] += count[i - 1];

        // Build the output array
        for (i = n - 1; i >= 0; i--) {
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
        }

        // Copy the output array to arr[], so that arr[] now contains sorted numbers according to the current digit
        for (i = 0; i < n; i++)
            arr[i] = output[i];
    }

public:
    // The main function that sorts arr[] of size n using Radix Sort
    void radixsort(int arr[], int n) {
        // Find the maximum number to know the number of digits
        int m = getMax(arr, n);

        // Do counting sort for every digit. Note that instead of passing digit number, exp is passed. exp is 10^i where i is the current digit number
        for (int exp = 1; m / exp > 0; exp *= 10)
            countSort(arr, n, exp);
    }
};





int main() {
    vector<int> inputArray = { 4, 3, 12, 1, 5, 5, 3, 9 };
    CountSort countSort(inputArray);
    vector<int> outputArray = countSort.sort();

    for (int i = 0; i < inputArray.size(); i++)
        cout << outputArray[i] << " ";

    cout<<endl;

    int arr[] = { 543, 986, 217, 765, 329 };
    int n = sizeof(arr) / sizeof(arr[0]);

    RadixSort radixSort;

    radixSort.radixsort(arr, n);



    for(int i = 0 ; i <n ;i++)
        cout<<arr[i]<<" ";



    return 0;
}

