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

struct valueOccurance
{
    int key;
    int numberOfOccurance;
};
void mergekey(valueOccurance *arr, int p, int q, int r)
{

    int arr1 = q - p + 1;
    int arr2 = r - q;
    valueOccurance *l = new valueOccurance[arr1 + 2];
    valueOccurance *R = new valueOccurance[arr2 + 1];

    for (int i = 0; i < arr1; i++)
    {

        l[i].key = arr[p + i].key;
        l[i].numberOfOccurance = arr[p + i].numberOfOccurance;
    }

    for (int j = 0; j < arr2; j++)
    {
        R[j].key = arr[q + j + 1].key;
        R[j].numberOfOccurance = arr[q + j + 1].numberOfOccurance;
    }

    l[arr1].key = std::numeric_limits<int>::max();
    R[arr2].key = std::numeric_limits<int>::max();
    int i = 0;
    int j = 0;

    for (int x = p; x <= r; x++)
    {

        if (l[i].key < R[j].key)
        {
            arr[x].key = l[i].key;
            arr[x].numberOfOccurance = l[i].numberOfOccurance;

            i = i + 1;
        }
        else
        {
            arr[x].key = R[j].key;
            arr[x].numberOfOccurance = R[j].numberOfOccurance;

            j = j + 1;
        }
    }
    delete l;
    delete R;
}
void mergeSortKey(valueOccurance *arr, int p, int r)
{
    int q;

    if (p < r)
    {
        q = (p + r) / 2;
        mergeSortKey(arr, p, q);
        mergeSortKey(arr, q + 1, r);
        mergekey(arr, p, q, r);
    }
}
void mergeoccurance(valueOccurance *arr, int p, int q, int r)
{

    int arr1 = q - p + 1;
    int arr2 = r - q;
    valueOccurance *l = new valueOccurance[arr1 + 2];
    valueOccurance *R = new valueOccurance[arr2 + 1];

    for (int i = 0; i < arr1; i++)
    {
        l[i].numberOfOccurance = arr[p + i].numberOfOccurance;
        l[i].key = arr[p + i].key;
    }
    for (int j = 0; j < arr2; j++)
    {
        R[j].numberOfOccurance = arr[q + j + 1].numberOfOccurance;
        R[j].key = arr[q + j + 1].key;
    }

    l[arr1].numberOfOccurance = 0;
    R[arr2].numberOfOccurance = 0;
    int i = 0;
    int j = 0;

    for (int x = p; x <= r; x++)
    {
        if (l[i].numberOfOccurance >= R[j].numberOfOccurance)
        {
            arr[x].key = l[i].key;
            arr[x].numberOfOccurance = l[i].numberOfOccurance;
            i = i + 1;
        }
        else
        {
            arr[x].key = R[j].key;
            arr[x].numberOfOccurance = R[j].numberOfOccurance;
            j = j + 1;
        }
    }
    delete l;
    delete R;
}
void mergeSortOccurance(valueOccurance *arr, int p, int r)
{
    int q;

    if (p < r)
    {
        q = (p + r) / 2;
        mergeSortOccurance(arr, p, q);
        mergeSortOccurance(arr, q + 1, r);
        mergeoccurance(arr, p, q, r);
    }
}
void createUmap(string inputFile, string outputFile)
{

    unordered_map<int, int> umap;
    ifstream myfile(inputFile, ios::in);
    if (myfile.is_open())
    {

        while (true)
        {

            int key;
            myfile >> key;

            while (true)
            {
                //if the key is not found
                if (umap.find(key) == umap.end())
                {
                    umap[key] = 1;
                    break;
                }
                // If the key is found
                else
                    umap[key] = (umap[key]) + 1;
                break;
            }

            if (myfile.eof())
                break;
        }
        myfile.close();
    }

    int S = umap.size();
    cout << "the size of the array is  " << S << endl;
    valueOccurance *arr = new valueOccurance[S];
    int i = 0;
    // now i have a map (umap) with key=Number & value = #occurances
    for (auto x : umap)
    {
        cout << x.first << " " << x.second << endl;
        arr[i].key = x.first;
        arr[i].numberOfOccurance = x.second;
        i++;
    }
    cout << "-----------------------------------" << endl;

    // now we will sort the array according to value first then according to nummber of occurance;

    mergeSortKey(arr, 0, S - 1);
    mergeSortOccurance(arr, 0, S - 1);

    ofstream myfile1(outputFile, ios::out);
    if (myfile1.is_open())
    {
        for (int j = 0; j < S; j++)
        {
            cout << arr[j].key << " " << arr[j].numberOfOccurance << endl;
            for (int i = 0; i < arr[j].numberOfOccurance; i++)
            {
                myfile1 << (arr[j].key) << endl;
            }
        }
    }
    else
        cout << "Unable to open file";

    myfile1.close();
    delete arr;
}

int main(int argc, char **argv)
{
    double duration;
    auto start_time = std::chrono::high_resolution_clock::now();

    string inputFile = argv[1];
    string outputFile = argv[2];
    string runningTimeFile = argv[3];
    createUmap(inputFile, outputFile);
    auto end_time = std::chrono::high_resolution_clock::now();
    auto time = end_time - start_time;
    duration = (std::chrono::duration_cast<std::chrono::milliseconds>(time).count());
    outTime(duration, runningTimeFile);
}