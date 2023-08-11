// Queue.h - Specification of Queue ADT (Pointer-based)
#pragma once
#include<string>
#include<iostream>
using namespace std;

typedef char ItemType;

class Queue
{
private:
    struct Node
    {
        ItemType item;	// item
        Node* next;	// pointer pointing to next item
    };

    Node* frontNode;	// point to the first item
    Node* backNode;	// point to the first item


public:
    //// constructor
    //Queue();
    //~Queue();

    bool checkUserLogin(string username, string password);

    void registerUser(string username, string password);

    void addFoodItems(int itemId, string itemName, double price);

    void displayFoodItems();
};

