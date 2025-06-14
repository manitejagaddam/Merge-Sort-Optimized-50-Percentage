#include <thread>
#include <iostream>
#include <vector>
#include <algorithm>
#include <atomic>
#include <random>
#include <chrono>
#include <future>
using namespace std;
using namespace chrono;




void merge(vector<int> & nums, int start, int mid, int end){
    vector<int> temp;
    
    int left = start;
    int right = mid + 1;

    while(left <= mid && right <= end){
        if(nums[left] < nums[right]) temp.push_back(nums[left++]);
        else temp.push_back(nums[right++]);
    }
    
    while(left <= mid)
        temp.push_back(nums[left++]);
    
    while(right <= end)
        temp.push_back(nums[right++]);


    for(int i = start ; i <= end ; i++){
        nums[i] = temp[i - start];
    }

}



void threadedMergeSort(vector<int> & nums, int start, int end, int depth = 0){
    if(start >= end) return;

    int mid = (start + end) / 2;
    
    if(depth <= 3){
        thread left_thread(threadedMergeSort, ref(nums), start, mid, depth + 1);
        thread right_thread(threadedMergeSort, ref(nums), mid + 1, end, depth + 1);
        left_thread.join();
        right_thread.join();
    }else{
        threadedMergeSort(nums, start, mid, depth + 1);
        threadedMergeSort(nums, mid + 1, end, depth + 1);
    }

    merge(nums, start, mid, end);

}

void futherMergeSort(vector<int> & nums, int start, int end, int depth = 0){
    if(start >= end) return;

    int mid = (start + end) / 2;

    if(depth <= 3){
        auto leftFuther = async(launch::async, futherMergeSort, ref(nums), start, mid, depth + 1);
        auto rightFuther = async(launch::async, futherMergeSort, ref(nums), mid + 1, end, depth + 1);

        leftFuther.get();
        rightFuther.get();
    }else{
        futherMergeSort(nums, start, mid, depth + 1);
        futherMergeSort(nums, mid + 1, end, depth + 1);
    }

    merge(nums, start, mid, end);
}


void normalMergeSort(vector<int> & nums, int start, int end){
    if(start >= end) return;

    int mid = (start + end) / 2;

    normalMergeSort(nums, start, mid);
    normalMergeSort(nums, mid + 1, end);

    merge(nums, start, mid, end);

}


int main(){
    int noe;
    cin >> noe;

    vector<int> nums1;
    vector<int> nums2;
    vector<int> nums3;
    vector<int> nums4;
    for(int idx = 0 ; idx < noe ; idx++){
        nums1.push_back(rand() % 1000);
        nums2.push_back(rand() % 1000);
        nums3.push_back(rand() % 1000);
        nums4.push_back(rand() % 1000);
    }
    // vector<int> nums2(nums1.begin(), nums1.end());

    // for(int i : nums) cout << i << " ";
    // cout << endl;


    auto start = high_resolution_clock::now();
    sort(nums1.begin(), nums1.end());
    auto end = high_resolution_clock::now();

    duration<double> time_taken = end - start;

    cout << "Time take for inbuilt sort : " << time_taken.count() << endl;


    start = high_resolution_clock::now();
    normalMergeSort(nums4, 0, noe - 1);
    end = high_resolution_clock::now();

    time_taken = end - start;

    cout << "Time taken for Normal Merge Sort : " << time_taken.count() << endl;


    start = high_resolution_clock::now();
    threadedMergeSort(nums2, 0, noe - 1);
    end = high_resolution_clock::now();
    time_taken = end - start;

    cout << "Time taken for Threaded Merge Sort : " << time_taken.count() << endl;


    start = high_resolution_clock::now();
    futherMergeSort(nums3, 0, noe - 1);
    end = high_resolution_clock::now();

    time_taken = end - start;

    cout << "Time taken for Futhre Threaded Merge Sort : " << time_taken.count() << endl;


    return 0;


}
