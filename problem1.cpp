using namespace std;
#include <iostream>
#include <limits>
#include <fstream>
#include <string>
#include <cstdio>
#include <ctime>
#include <chrono>

struct node
{
    node *next;
    int data;
};
typedef struct node node;

void addnode(node *&head, int x)
{
    node *y = new node;
    y->next = NULL;
    y->data = x;
    node *current = head;
    if (head == NULL)
    {
        head = y;
    }

    else
    {
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = y;
    }
}

void createList(node *&head, string inputfile)
{
    ifstream myfile(inputfile, ios::in);
    if (myfile.is_open())
    {
        while (true)
        {
            int x;
            myfile >> x;
            addnode(head, x);
            if (myfile.eof())
                break;
        }
    }
}

void reverseList(node *&head)
{
    if (head == NULL)
    {
        return;
    }
    node *prev = head;
    node *current = head->next;
    node *next = current->next;
    prev->next = NULL;
    while (next != NULL)
    {
        current->next = prev;
        prev = current;
        current = next;
        next = next->next;
    }
    current->next = prev;
    prev = current;
    head = prev;
}

void outList(node *&head, string outputfile)
{
    node *current = head;
    ofstream myfile(outputfile, ios::out);
    if (myfile.is_open())
    {
        while (current != NULL)
        {

            myfile << (current->data) << endl;
            current = current->next;
        }

        myfile.close();
    }
    else
        cout << "Unable to open file";
}

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

int main(int argc, char **argv)
{
    double duration;
    auto start_time = std::chrono::high_resolution_clock::now();

    string inputFile = argv[1];
    string outputFile = argv[2];
    string runningTimeFile = argv[3];

    node *head = new node;
    head = NULL;
    createList(head, inputFile);
    reverseList(head);
    outList(head, outputFile);

    auto end_time = std::chrono::high_resolution_clock::now();
    auto time = end_time - start_time;
    duration = (std::chrono::duration_cast<std::chrono::milliseconds>(time).count());
    outTime(duration, runningTimeFile);
    node *current = head;
    node *temp;
    while (current != NULL)
    {
        temp = current;
        current = current->next;
        delete temp;
    }
}
