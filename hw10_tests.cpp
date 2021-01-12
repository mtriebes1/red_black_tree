//Matthew Triebes
//HW10 Tests -> hw10_tests.cpp

#include <iostream>
#include <string>
#include <algorithm> 
#include <gtest/gtest.h>
#include "rbt_collection.h"

using namespace std;


// Test 1
TEST (BasicCollectionTest, CorrectSize) {
RBTCollection <string, double> c ;
ASSERT_EQ (c.size(), 0);
c.insert ("a", 10.0);
ASSERT_EQ (c.size(), 1);
c.insert ("b", 20.0);
ASSERT_EQ (c.size(), 2);
}

// Test 2a
TEST (BasicCollectionTest, Insert_And_Find_Case1a) {
RBTCollection <string, double> c;
double v;
c.insert("b", v);
ASSERT_EQ (c.find ("b", v), true);
c.insert ("a", v);
ASSERT_EQ (c.find("a", v), true);
c.insert ("c", v);
ASSERT_EQ (c.find("c", v), true);
c.insert ("d", v);
ASSERT_EQ (c.find("d", v), true);
ASSERT_EQ (c.height(), 3);
}

//Test 2b
TEST (BasicCollectionTest, Insert_And_Find_Case1b) {
RBTCollection <string, double> c;
double v;
c.insert("c", v);
ASSERT_EQ (c.find ("c", v), true);
c.insert ("b", v);
ASSERT_EQ (c.find("b", v), true);
c.insert ("d", v);
ASSERT_EQ (c.find("d", v), true);
c.insert ("a", v);
ASSERT_EQ (c.find("a", v), true);
ASSERT_EQ (c.height(), 3);
}

//Test 2c
TEST (BasicCollectionTest, Insert_And_Find_Case1c) {
RBTCollection <string, double> c;
double v;
c.insert("c", v);
ASSERT_EQ (c.find ("c", v), true);
c.insert ("a", v);
ASSERT_EQ (c.find("a", v), true);
c.insert ("d", v);
ASSERT_EQ (c.find("d", v), true);
c.insert ("b", v);
ASSERT_EQ (c.find("b", v), true);
ASSERT_EQ (c.height(), 3);
}

//Test 2d
TEST (BasicCollectionTest, Insert_And_Find_Case1d) {
RBTCollection <string, double> c;
double v;
c.insert("c", v);
ASSERT_EQ (c.find ("c", v), true);
c.insert ("a", v);
ASSERT_EQ (c.find("a", v), true);
c.insert ("e", v);
ASSERT_EQ (c.find("e", v), true);
c.insert ("d", v);
ASSERT_EQ (c.find("d", v), true);
ASSERT_EQ (c.height(), 3);
}

// Test 3a
TEST (BasicCollectionTest, Insert_And_Find_Case2a) {
RBTCollection <string, double> c;
double v;
c.insert("a", v);
ASSERT_EQ (c.find ("a", v), true);
c.insert ("b", v);
ASSERT_EQ (c.find("b", v), true);
c.insert ("c", v);
ASSERT_EQ (c.find("c", v), true);
ASSERT_EQ(c.height(), 2);
}

// Test 3b
TEST (BasicCollectionTest, Insert_And_Find_Case2b) {
RBTCollection <string, double> c;
double v;
c.insert("c", v);
c.insert("b", v);
c.insert ("a", v);
ASSERT_EQ(c.find("a", v), true);
ASSERT_EQ(c.find("b", v), true);
ASSERT_EQ (c.find ("c", v), true);
ASSERT_EQ(c.height(), 2);
}

// Test 4a
TEST (BasicCollectionTest, Insert_And_Find_Case3a) {
RBTCollection <string, double> c;
double v;
c.insert("d", v);
c.insert("b", v);
c.insert("c", v);
ASSERT_EQ(c.find("d", v), true);
ASSERT_EQ(c.find("c", v), true);
ASSERT_EQ(c.find("b", v), true);
ASSERT_EQ(c.height(), 2);
}


// Test 4b
TEST (BasicCollectionTest, Insert_And_Find_Case3b) {
RBTCollection <string, double> c;
double v;
c.insert("e", v);
c.insert("g", v);
c.insert("f", v);
ASSERT_EQ(c.find("g", v), true);
ASSERT_EQ(c.find("f", v), true);
ASSERT_EQ(c.find("e", v), true);
ASSERT_EQ(c.height(), 2);
}
// Test 4
TEST (BasicCollectionTest, GetKeys) {
RBTCollection <string, double> c ;
c.insert("a", 10.0);
c.insert("b", 20.0);
c.insert("c", 30.0);
vector <string> ks;
c.keys(ks);
vector <string>:: iterator iter;
iter = find(ks.begin(), ks.end(), "a");
ASSERT_NE (iter, ks.end());
iter = find(ks.begin(), ks.end(), "b");
ASSERT_NE (iter, ks.end());
iter = find(ks.begin(), ks.end(), "c");
ASSERT_NE (iter, ks.end());
iter = find(ks.begin(), ks.end(), "d");
ASSERT_EQ (iter, ks.end());
}


// Test 5
TEST (BasicCollectionTest, GetKeyRange) {
RBTCollection <string, double> c;
c.insert("c", 10.0);
c.insert("b", 20.0);
c.insert("a", 30.0);
c.insert("d", 40.0);
c.insert("e", 50.0);
vector <string> ks;
c.find ("b", "d", ks);
vector <string>::iterator iter;
iter = find(ks.begin(), ks.end(), "b");
ASSERT_NE (iter, ks.end());
iter = find(ks.begin(), ks.end(), "c");
ASSERT_NE (iter, ks.end());
iter = find (ks.begin(), ks.end(), "d");
ASSERT_NE (iter, ks.end());
iter = find (ks.begin(), ks.end(), "a");
ASSERT_EQ (iter, ks.end());
iter = find (ks.begin(), ks.end(), "e");
ASSERT_EQ (iter, ks.end());
}

// Test 6
TEST (BasicCollectionTest, KeySort) {
RBTCollection <string, double> c;
c.insert("a", 10.0);
c.insert("e", 50.0);
c.insert("c", 30.0);
c.insert("b", 20.0);
c.insert("d", 40.0);
vector <string> sorted_ks;
c.sort(sorted_ks);
ASSERT_EQ (sorted_ks.size(), c.size());
    for (int i = 0; i < int (sorted_ks.size()) - 1; ++i) {
        //cout << "Sorted Order: " << sorted_ks.at(i) << endl;
        ASSERT_LE (sorted_ks[i], sorted_ks[i +1]);
    }
}

// Test 7
TEST (TreeCollectionTest, AssignOpTest) {
RBTCollection <string,int> c1;
c1.insert("a", 10);
c1.insert("b", 15);
c1.insert("c", 20);
c1.insert("d", 20);
RBTCollection <string, int> c2;
c2 = c1;
ASSERT_EQ (c1.size(), c2.size());
ASSERT_EQ (c1.height(), c2.height());
}

int main (int argc, char** argv)
{
    testing::InitGoogleTest (&argc, argv);
    return RUN_ALL_TESTS();
}