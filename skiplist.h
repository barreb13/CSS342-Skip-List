/**skiplist.h
 * Created by <Brent> on <2/15/2020>.
 *
 * SkipList https://en.wikipedia.org/wiki/Skip_list
 *
 * SkipList with a depth of 1 is similar to a doubly-linked list
 * Each item has a p percent chance of being at the next level up
 * For our implementation p = 50%
 * All elements are inserted at the lowest Depth (1)
 * 50% of the elements inserted in Depth = 2
 * 50% of 50%, or 25% of the elements inserted in Depth = 3
 * and so on
 *
 * If a Skip List has only 1 level, such as p = 0%
 * Insert O(n), Search O(n)
 * For Depth > 1
 * Insert O(log n), Search O(log n)
 * Modifying p allows us to trade off search speed and storage cost
 */

#pragma once
#include <iostream>

using namespace std;

class SkipList {
    // display with level
    friend ostream& operator<<(ostream& out, const SkipList& skipList);

  public:
    // default SkipList has Depth of 1, just one doubly-linked list
    explicit SkipList(int depth = 1);

    // destructor
    virtual ~SkipList();

    // return true if successfully added, no duplicates
    bool add(int data);

    // return true if successfully removed
    bool remove(int data);

    // return true if found in SkipList
    bool contains(int data);

  private:
    // SNode
    // defined in .cpp as SkipList::SNode::SNode(int data) ...
    struct SNode 
    {
        explicit SNode(int data);
        int Data;
        // link to Next SNode
        SNode* Next;
        // link to Prev SNode
        SNode* Prev;
        // link to up one level
        SNode* UpLevel;
        // link to down one level
        SNode* DownLevel;
    };

    // Depth of SkipList, levels are 0 to depth-1
    int depth;

    // array of Depth SNode* objects as FrontGuards linking levels
    // if depth = 2, we'd have frontGuards[0] and frontGuards[1]
    SNode** frontGuards;

    // array of Depth SNode* objects as RearGuards linking levels
    // Same as above for the rearGuards (rearGuards[0] and rearguards[1]) for depth of 2
    SNode** rearGuards;

    // given a SNode, place it before the given NextNode
    void addBefore(SNode* newNode, SNode* nextNode);

    // return true 50% of time,
    // each node has a 50% chance of being at higher level
    bool alsoHigher() const;

    //Private method to clear the skip list
    void clearSkipList();
};
