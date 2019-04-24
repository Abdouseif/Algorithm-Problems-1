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

void merge(int *arr, int p, int q, int r)
{

    int arr1 = q - p + 1;
    int arr2 = r - q;
    int *l = new int[arr1 + 2];
    int *R = new int[arr2 + 1];

    for (int i = 0; i < arr1; i++)
    {

        l[i] = arr[p + i];
    }

    for (int j = 0; j < arr2; j++)
    {
        R[j] = arr[q + j + 1];
    }

    l[arr1] = std::numeric_limits<int>::max();
    R[arr2] = std::numeric_limits<int>::max();
    int i = 0;
    int j = 0;

    for (int x = p; x <= r; x++)
    {

        if (l[i] < R[j])
        {
            arr[x] = l[i];

            i = i + 1;
        }
        else
        {
            arr[x] = R[j];

            j = j + 1;
        }
    }
    delete l;
    delete R;
}

void mergesort(string inputFile, string outputFile)
{
    ifstream myfile(inputFile, ios::in);
    // calcullate the size of the array
    int size = 0;
    int *A;
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
        A = new int[size];
        int i = 0;
        //read from the file and save in the array
        myfile.clear();
        myfile.seekg(0, ios::beg);
        while (true)
        {
            int x;
            myfile >> x;
            A[i] = x;
            i++;
            if (myfile.eof())
                break;
        }
    }
    myfile.close();
    int h;
    for (int i = 1; i < size; i = i + i)
    {
        for (int j = 0; j < (size - i); j = j + i + i)
        {
            if ((j + i + i - 1) > (size - 1))
            {
                h = size - 1;
            }
            else
            {
                h = j + i + i - 1;
            }
            merge(A, j, j + i - 1, h);
        }
    }

    ofstream myfile1(outputFile, ios::out);

    if (myfile1.is_open())
    {

        for (int i = 0; i < size; i++)
        {
            myfile1 << A[i] << endl;
        }
        myfile1.close();
    }
    else
    {
        cout << "Unable to open file";
    }
    delete A;
}

int main(int argc, char **argv)
{
    double duration;
    auto start_time = std::chrono::high_resolution_clock::now();

    string inputFile = argv[1];
    string outputFile = argv[2];
    string runningTimeFile = argv[3];
    mergesort(inputFile, outputFile);
    auto end_time = std::chrono::high_resolution_clock::now();
    auto time = end_time - start_time;
    duration = (std::chrono::duration_cast<std::chrono::milliseconds>(time).count());
    outTime(duration, runningTimeFile);
}