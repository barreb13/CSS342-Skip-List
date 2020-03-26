// skiplist.cpp
// Created by <Brent> on <2/15/2020>.

#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>

#include "skiplist.h"

using namespace std;

// Constructor for SNode struct. Set data. Set all pointers to nullptr
SkipList::SNode::SNode(int data)
    : Data{data}, Next{nullptr}, Prev{nullptr}, UpLevel{nullptr},
      DownLevel{nullptr} {}

// Dynamically allocate frontGuards and rearGuards arrays
// Create the special SNode* objects as guards
// Tie all the SNode objects together (both prev-next and up-down)
SkipList::SkipList(int depth) : depth{depth} {
    // Create dynamically allocated front and rear guard arrays
    frontGuards = new SNode*[depth];
    rearGuards = new SNode*[depth];

    for (int i = 0; i < depth; i++) {
        frontGuards[i] = new SNode(INT_MIN);
        rearGuards[i] = new SNode(INT_MAX);
    }

    // Tie SNode objects together
    for (int i = 0; i < depth; i++) {
        // If at level 0, can NOT tie any SNodes below
        // If depth > 0, tie to nodes below
        if (i > 0) {
            frontGuards[i]->DownLevel = frontGuards[i - 1];
            rearGuards[i]->DownLevel = rearGuards[i - 1];
        }
        // If higher than depth, can NOT tie any SNodes above
        if (i < depth - 1) {
            frontGuards[i]->UpLevel = frontGuards[i + 1];
            rearGuards[i]->UpLevel = rearGuards[i + 1];
        }
        // Always able to SNode objects together horizontally
        frontGuards[i]->Next = rearGuards[i];
        rearGuards[i]->Prev = frontGuards[i];
    }
}

// return true approx. 50% of time,
// each node has a 50% chance of being at higher level
bool SkipList::alsoHigher() const {
   /* if (rand() % 2 == 1) {
        return true;
    }
    return false;*/
    return rand() % 2 == 1;
}

// Add data to Skip List. Return false if given value already in level 0
// return true if successfully added, no duplicates
bool SkipList::add(int data) {
    SNode* nextNode;
    SNode* newNode;
    int level = 1;

    // Set nextNode and start walking through level 0
    nextNode = frontGuards[0]->Next;
    //As long as nextNode->next is not null & nextNode-> data is less than data, keep moving right
    while (nextNode->Next != nullptr && nextNode->Data < data) {
        nextNode = nextNode->Next;
    }
    // If the data is already in the list, return false due to no duplicates
    if (nextNode->Data == data) {
        cout << "Duplicates Not Allowed" << endl;
        return false;
    }
    // If data is NOT found in the list, create new node with data
    newNode = new SNode(data);

    // Call addBefore to add into list and connect pointers horizontally
    addBefore(newNode, nextNode);

    // After inserting into level 0, toss a coin to check if it
    // should be inserted at higher level
    while (alsoHigher() && level < depth) {
        auto newUpper = new SNode(data);
        // Connect newNode and newUpper(up-down)
        newNode->UpLevel = newUpper;
        newUpper->DownLevel = newNode;

        // Go back towards INT_MIN until find a node which upLevel != nullptr
        SNode* tempPtr = newNode->Prev;
        while (tempPtr->UpLevel == nullptr) {
            tempPtr = tempPtr->Prev;
        }
        tempPtr = tempPtr->UpLevel;

        // Now go right towards INT_MAX
        while (tempPtr->Next != nullptr && tempPtr->Data < data) {
            tempPtr = tempPtr->Next;
        }
        //Call addBefore to insert newUpper to come before node you just got to
        addBefore(newUpper, tempPtr);
        newNode = newUpper;
        // Increment level for while loop
        level++;
    }
    return true;
}

// given a SNode, place it before the given NextNode
void SkipList::addBefore(SNode* newNode, SNode* nextNode) {
    assert(newNode != nullptr && nextNode != nullptr &&
           newNode->Data < nextNode->Data);
    SNode* tempPtr = nextNode->Prev;
    newNode->Prev = tempPtr;
    tempPtr->Next = newNode;
    newNode->Next = nextNode;
    nextNode->Prev = newNode;
}

// Destructor that needs to delete SNodes and give memory back
SkipList::~SkipList() {
    //cout << "Destructor called!" << endl;
    clearSkipList();
}

// given data, removes SNode
// return true if successfully removed, false if not removed
bool SkipList::remove(int data) {
    // Use contains to test for data in Skip List first
    if (contains(data)) {
        // Create tempPtr and set to frontGuard at top of list
        SNode* currentPtr = frontGuards[depth - 1];
        SNode* nodeToDelete;

        // Start at top left of list and walk through
        while (currentPtr != nullptr) {
            // If the current nodes getNext node's data is < data move right
            if (currentPtr->Next->Data < data) {
                currentPtr = currentPtr->Next;
            }
            // Found data match. Start deleting
            else if (currentPtr->Next->Data == data) {
                currentPtr = currentPtr->Next;
                while (currentPtr != nullptr) {
                    // Point nodeToDelete to current so you can delete
                    nodeToDelete = currentPtr;
                    // Move pointers in preparation of deleting node
                    currentPtr->Next->Prev = currentPtr->Prev;
                    currentPtr->Prev->Next = currentPtr->Next;
                    currentPtr = currentPtr->DownLevel;
                    delete nodeToDelete;
                }
                return true;
            } else {
                currentPtr = currentPtr->DownLevel;
            }
        }
    }
    return false;
}

// return true if found in SkipList
bool SkipList::contains(int data) {
    // Start at the top to achieve maximum efficiency
    for (int i = depth - 1; i >= 0; i--) {
        // Create a Ptr to walk through each level of Skip List
        SNode* currentPtr = frontGuards[i]->Next;
        while (currentPtr != nullptr) {
            if (currentPtr->Data == data) {
                return true;
            }
            // Keep walking through list
            currentPtr = currentPtr->Next;
        }
    }
    //Value was not found so return false
    return false;
}

// Friend function used to display all the elements of SkipList
ostream& operator<<(ostream& out, const SkipList& skipList) {
    // Create an SNode pointer to access top left of list
    SkipList::SNode* currentPtr;
    for (int i = skipList.depth - 1; i >= 0; i--) {
        out << "Level: " << i << " -- ";
        currentPtr = skipList.frontGuards[i];
        while (currentPtr != nullptr) {
            out << currentPtr->Data << ", ";
            currentPtr = currentPtr->Next;
        }
        out << endl;
    }
    return out;
}

// Private method to clear the skip list
void SkipList::clearSkipList() {
    SNode* currentPtr;
    SNode* temp;
    // Delete SNodes starting from the top
    for (int i = depth - 1; i >= 0; i--) {
        currentPtr = frontGuards[i];
        while (currentPtr != nullptr) {
            //cout << "Deleting SNode!\n";
            temp = currentPtr;
            currentPtr = currentPtr->Next;
            delete temp;
        }
    }
    // Delete array
    delete[] frontGuards;
    delete[] rearGuards;
}
