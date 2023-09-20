#include <iostream>
#include <vector>
#include <string>
#include <limits>
using namespace std;
int choices;
int order;
void input(vector<int>& arr)
{
    string input;
    cout << "Nhap lien tiep cac phan tu cua mang, nhap 'end' de stop! \n" ;
    while (1)
    {
        if (cin >> input && input != "end"){
            arr.push_back(stoi(input));
        }else break;
    }
}

void output(vector<int>& arr)
{
    for (int i = 0; i < arr.size(); i++) 
        cout << arr[i] << " " ;
    cout << endl;
}

void swap(int& a,int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

const bool ascending(int a, int b)
{
    return a > b;
}
const bool descending(int a, int b)
{
    return a < b;
}


void selectionSort(vector<int>& arr,const bool p(int, int))
{
    for (int i = 0; i < arr.size()-1; i++)
    {
        for (int j = i+1; j < arr.size(); j++)
            if (p(arr[i], arr[j])) 
                swap(arr[i], arr[j]);
    }
    cout << "Selection Sort: ";
    output(arr);
}

void insertionSort(vector<int>& arr,const bool p(int, int))
{
    for (int i = 0; i<arr.size(); i++)
    {
        for (int j = i; j > 0; j--)
        {
            if (!p(arr[j], arr[j-1]))
            {
                swap(arr[j], arr[j-1]);
            }
        }
    }
    cout << "Insertion Sort: ";
    output(arr);
}

void bubbleSort(vector<int>& arr,const bool p(int, int))
{
    for (int i = 0; i < arr.size()-1; i++)
    {
        for (int j =arr.size()-1; j > i; j--)
        {
            if (!p(arr[j], arr[j-1]))
                swap(arr[j-1], arr[j]);
        }
    }
    cout << "Bubble Sort: ";
    output(arr);
}

int partition(vector<int>& arr, int low, int high,const bool p(int, int)) {
    int x = arr[low]; // pivot
    int i = low;
    int j = high;
    int temp1=0, temp2=1;
    while (true) {
        if (p(temp1, temp2))
        {
            while (arr[i] > x) i++; 
            while (arr[j] < x) j--;
        }else
            {
                while (arr[i] < x) i++;
                while (arr[j] > x) j--;
            }

        if (i < j) {
            swap(arr[i], arr[j]);
        } else {
            return j;
        }
    }
}
void quickSort(vector<int>& arr, int low, int high, const bool p(int, int)) {
    if (low < high) {
        int q = partition(arr, low, high, p);
        quickSort(arr, low, q, p);
        quickSort(arr, q + 1, high, p);
    }
    
}


void doquickSort(vector<int>& arr,const bool p(int, int)){
    quickSort(arr, 0, arr.size()-1, p);
    cout << "Quick Sort: ";
    output(arr);
}

void shellSort(vector<int>& arr,const bool p(int, int)) {
    for (int interval = arr.size() / 2; interval > 0; interval /= 2)
    {
        for (int i = interval; i < arr.size(); i += 1)
        {
            int temp = arr[i];
            int j;
            for (j = i; j >= interval && p(arr[j - interval], temp); j -= interval) 
            {
                arr[j] = arr[j - interval];
            }
            arr[j] = temp;
        }
    }
    cout << "Quick Sort: ";
    output(arr);
}

void Heapify(vector<int>& arr,int length, int i, const bool p(int, int))
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < length && p(arr[left], arr[largest]))
        largest = left;
    if (right < length && p(arr[right], arr[largest]))
        largest = right;
    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        Heapify(arr, length, largest, p);
    }
}

void heapSort(vector<int>& arr, const bool p(int, int))
{
    for (int i = arr.size()/2 - 1; i >= 0; i--)
        Heapify(arr, arr.size(), i, p);
    for (int i = arr.size()-1; i >= 0; i--){
        swap(arr[0], arr[i]);
        Heapify(arr, i, 0, p);
    }
    cout << "Heap Sort: ";
    output(arr);
}


void radixSort (vector<int>& arr, const bool p(int, int))
{
    int temp1=0, temp2=1;
    int i, m = 0, exp = 1, b[100];
    for (i = 0; i < arr.size(); i++)
    {
        if (arr[i] > m)
            m = arr[i];
    } 
    while (m / exp>0)
    {
        int bucket[10] = {0};
        if (!p(temp1, temp2))
        {
            for (i = 0; i < arr.size(); i++)
                bucket[arr[i]/exp%10]++;
            for (i = 1; i < 10; i++)
                bucket[i] += bucket[i-1];
            for (i = arr.size()-1; i >= 0; i--)
                b[--bucket[arr[i]/exp%10]] = arr[i];
            for (i = 0; i < arr.size();i++)
                arr[i]=b[i];
        }else
        {
            for (i = 0; i < arr.size(); i++)
                bucket[9-arr[i]/exp%10]++;
            for (i = 1; i < 10; i++)
                bucket[i] += bucket[i-1];
            for (i = arr.size()-1; i >= 0; i--)
                b[--bucket[9-arr[i]/exp%10]] = arr[i];
            for (i = 0; i < arr.size(); i++)
                arr[i]=b[i];
        }
        
        exp *= 10;
    }
    cout << "Radix Sort: ";
    output(arr);
}



void sort(vector<int>& arr)
{
    cout << "Chon thuat toan sap xep:\n (1)selectionSort (2)insertionSort (3)bubbleSort (4)quickSort\n (5)shellSort (6)heapSort (7)radixSort \n";
    cout << "(1..7)--> ";
    cin >> choices; 
    cout << "Chon cach sap xep:\n (1)tang (2)giam\n";
    cout << "(1..2)--> ";
    cin >> order;
    void (*func[])(vector<int>&,const bool p(int, int)) = {selectionSort, insertionSort, bubbleSort, doquickSort, shellSort, heapSort, radixSort};
    
    switch(order)
    {
        case 1:
            func[choices-1](arr, ascending);
            break;
        case 2:
            func[choices-1](arr, descending);
            break;
        default:
            break;
    }
}

void linearSearch(vector<int>& arr, const int k)
{
    for (int i = 0; i < arr.size(); i++)
    {    
        if (arr[i] == k)
        {
            cout << "Phan tu " << k << " o vi tri " << i + 1;
            return; 
        }
    }
    cout << "Khong ton tai phan tu " << k << " trong mang";
}

void binarySearch(vector<int>& arr, const int k)
{
    int left = 0, right = arr.size()-1;
    while (left <=right)
    {
        int temp = (left + right) /2;
        if (arr[temp] == k)
        {
            cout << "Phan tu " << k << " o vi tri " << temp + 1;
            return;
        }
        if (arr[temp] > k)
            right = temp - 1;
        else
            left = temp + 1;
    }
    cout << "Khong ton tai phan tu " << k << " trong mang";
}

void interpolationSearch(vector<int>& arr, const int k)
{
    int left = 0;
    int right = arr.size() - 1;
    while (left <= right && k >= arr[left] && k <= arr[right])
    {
        int val1 = (k-arr[left]) / (arr[right] - arr[left]);
        int val2 = right - left;
        int pos = left + val1 * val2;
        if (arr[pos] == k)
        {
            cout << "Phan tu " << k << " o vi tri " << pos + 1;
            return;
        }
        if (arr[pos] < k)
            left = pos + 1;
        else    
            right = pos - 1;
    }
    cout << "Khong ton tai phan tu " << k << " trong mang";
}

void search(vector<int>& arr)
{
    int k;
    cout << "nhap phan tu muon tim: ";
    cin >> k;
    cout << "chon thuat toan sap xep:\n (1)linearSearch (2)binarySearch (3)interpolationSearch\n";
    cout << "(1..3)--> ";
    cin >> choices;
    void(*func2[])(vector<int>&, const int) = {linearSearch, binarySearch, interpolationSearch};
    func2[choices-1](arr, k);

}

int main()
{
    vector<int> arr;
    input(arr);
    cout << "Mang co cac phan tu: "; 
    output(arr);
    cout << "Mang co " << arr.size() << " phan tu." << endl; 
    sort(arr);
    search(arr);
    return 0;
}
