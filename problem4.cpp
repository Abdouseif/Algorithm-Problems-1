using namespace std;
#include <iostream>
#include <limits>
#include <fstream>
#include <string>
#include <cstdio>
#include <ctime>
#include <chrono>
#include <unordered_map>
#include <bits/stdc++.h>

void outTime(double t, string timefile)
{
    ofstream myfile(timefile, ios::out);
    if (myfile.is_open())
    {
        myfile << t << endl;
        myfile.close();
    }
    else
        cout << "Unable to open file";
}
struct arrayA
{
    int key;
    int value;
};
void mergekey(arrayA *arr, int p, int q, int r)
{

    int arr1 = q - p + 1;
    int arr2 = r - q;
    arrayA *l = new arrayA[arr1 + 2];
    arrayA *R = new arrayA[arr2 + 1];

    for (int i = 0; i < arr1; i++)
    {

        l[i].key = arr[p + i].key;
        l[i].value = arr[p + i].value;
    }

    for (int j = 0; j < arr2; j++)
    {
        R[j].key = arr[q + j + 1].key;
        R[j].value = arr[q + j + 1].value;
    }

    l[arr1].value = std::numeric_limits<int>::max();
    R[arr2].value = std::numeric_limits<int>::max();
    int i = 0;
    int j = 0;

    for (int x = p; x <= r; x++)
    {

        if (l[i].value < R[j].value)
        {
            arr[x].key = l[i].key;
            arr[x].value = l[i].value;

            i = i + 1;
        }
        else
        {
            arr[x].key = R[j].key;
            arr[x].value = R[j].value;

            j = j + 1;
        }
    }
    delete l;
    delete R;
}
void mergeSortArr(arrayA *arr, int p, int r)
{
    int q;

    if (p < r)
    {
        q = (p + r) / 2;
        mergeSortArr(arr, p, q);
        mergeSortArr(arr, q + 1, r);
        mergekey(arr, p, q, r);
    }
}

void algo(string inputFile, string outputFile, int k)
{
    ifstream myfile(inputFile, ios::in);
    // calcullate the size of the array
    int size = 0;
    arrayA *A;
    if (myfile.is_open())
    {
        while (true)
        {
            int x;
            myfile >> x;
            size++;
            if (myfile.eof())
                break;
        }
        size = size - 1;
        A = new arrayA[size];
        int i = 0;
        //read from the file and save in the array
        myfile.clear();
        myfile.seekg(0, ios::beg);
        while (true)
        {
            int x;
            myfile >> x;
            A[i].value = x;
            A[i].key = i;
            i++;
            if (myfile.eof())
                break;
        }
    }
    myfile.close();
    //sort the array A with index
    mergeSortArr(A, 0, size);
    int sizeB = size - k + 1;
    int *B = new int[sizeB];
    for (int i = 0; i < sizeB; i++)
    {
        B[i] = -1; // put values to array B to check when put value in it if the place is free or not
    }
    int counter = 0; // to exit the outer for loop if the array B is full
    for (int i = 0; i < sizeB; i++)
    {
        int index = A[i].key;

        for (int j = 0; j < k; j++)
        {

            if (index >= 0 && index <= sizeB)
            {
                if (B[index] == -1)
                {
                    B[index] = A[i].value;
                    counter++;
                }
            }

            index--;
        }

        if (counter == sizeB)
        {
            break; // to exit the outer for loop if the array B is full
        }
    }

    ofstream myfile1(outputFile, ios::out);

    if (myfile1.is_open())
    {

        for (int i = 0; i < (size - k + 1); i++)
        {

            myfile1 << B[i] << endl;
        }
        myfile1.close();
    }
    else
    {
        cout << "Unable to open file";
    }
    delete A;
    delete B;
}

int main(int argc, char **argv)
{
    double duration;
    auto start_time = std::chrono::high_resolution_clock::now();
    string kstr = argv[1];
    stringstream kk(kstr);
    int k = 0;
    kk >> k;
    string inputFile = argv[2];
    string outputFile = argv[3];
    string runningTimeFile = argv[4];
    algo(inputFile, outputFile, k);
    auto end_time = std::chrono::high_resolution_clock::now();
    auto time = end_time - start_time;
    duration = (std::chrono::duration_cast<std::chrono::milliseconds>(time).count());
    outTime(duration, runningTimeFile);
}