// Modified by Brent
//

#include "skiplist.h"
#include <iostream>
#include <sstream>

using namespace std;

int totalPassed = 0;
int totalTests = 0;

template <typename T> string isOK(const T& got, const T& expected) {
    ++totalTests;
    if (got == expected) {
        ++totalPassed;
        return "OK: ";
    }
    // Removed else statement due to warning in Linux Lab
    cout << "    Got   " << got << "\n expected " << expected << endl;
    return "ERR: ";
}

// Edited test02 expected output because of conversation on Discord
void test02() {
    SkipList skipList(3);
    stringstream ss;
    ss << skipList;
    cout << isOK(ss.str(), string("Level: 2 -- -2147483648, 2147483647, \n"
                                  "Level: 1 -- -2147483648, 2147483647, \n"
                                  "Level: 0 -- -2147483648, 2147483647, \n"))
                .c_str()
         << "Empty SkipList of Depth=3" << endl;
    srand(100);
    skipList.add(10);
    skipList.add(30);
    skipList.add(5);
    skipList.add(25);
    ss.str("");
    ss << skipList;
    cout << isOK(ss.str(),
                 string(
                     "Level: 2 -- -2147483648, 25, 30, 2147483647, \n"
                     "Level: 1 -- -2147483648, 25, 30, 2147483647, \n"
                     "Level: 0 -- -2147483648, 5, 10, 25, 30, 2147483647, \n"))
         << "SkipList of Depth=3 with 10, 30, 5, 25" << endl;
    cout << isOK(skipList.contains(10), true) << "Contains 10" << endl;
    cout << isOK(skipList.contains(30), true) << "Contains 30" << endl;
    cout << isOK(skipList.contains(71), false) << "Does not contain 71" << endl;
}

void test01() {
    SkipList skipList;
    stringstream ss;
    ss << skipList;
    cout << isOK(ss.str(), string("Level: 0 -- -2147483648, 2147483647, \n"))
         << "Empty SkipList" << endl;
    skipList.add(10);
    skipList.add(30);
    skipList.add(5);
    skipList.add(25);
    ss.str("");
    ss << skipList;
    cout << isOK(ss.str(),
                 string(
                     "Level: 0 -- -2147483648, 5, 10, 25, 30, 2147483647, \n"))
         << "Added 10, 30, 5, 25," << endl;
}

// Sample test from Assignment Instructions
void test04() {
    SkipList s(5);
    for (int i = 0; i < 20; i++) {
        int number = rand() % 100;
        s.add(number);
        cout << "After adding " << number << endl;
        cout << s << endl;
    }
}

// test 05
void test05() {
    SkipList sl1(6);
    for (int i = 30; i > 0; i--) {
        sl1.add(i);
        cout << "After adding " << i << endl;
        cout << sl1 << endl;
    }
    // Test remove
    cout << "\n\nRemoving 15\n";
    sl1.remove(15);
    cout << sl1;

    // Adding 15 back
    cout << "\n\nAdding 15 back to skiplist\n";
    sl1.add(15);
    cout << sl1;
}

//Testing default destructor (depth = 1)
void test06() {
    SkipList sl6;
    for (int i = 0; i < 75; i++) {
        int number = rand() % 1000;
        sl6.add(number);
    }
    cout << sl6;
}

int main() {
    cout << "Because of the random nature of SkipList, "
         << "the skip list levels may not match" << endl;
    // Set the random seed for easy debugging
    // NOLINTNEXTLINE
    srand(424242);
    test01();
    test02();
    cout << "Passed: " << totalPassed << "/" << totalTests << endl;

    // Sample test from Assignment Instructions
    cout << "\n\n**Running sample test04() from Assignment Instructions**\n";
    test04();

    // Test 05
    cout << "\n\n **Running Test 05**\n\n";
    test05();

    //Test 06 
    cout << "\n\n**Running Test 06**\n\n";
    test06();

    return 0;
}