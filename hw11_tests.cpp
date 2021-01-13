//Matthew Triebes
//HW11 Tests -> hw11_tests.cpp

#include <iostream>
#include <string>
#include <algorithm> 
#include <gtest/gtest.h>
#include "rbt_collection.h"

using namespace std;

// Test 1: Basic Insert Test
TEST (BasicCollectionTest, CorrectSize) {
RBTCollection <string, double> c ;
ASSERT_EQ (c.size(), 0);
c.insert ("a", 10.0);
ASSERT_EQ (c.size(), 1);
c.insert ("b", 20.0);
ASSERT_EQ (c.size(), 2);
}

// Test 2a: Find Test
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

//Test 2b: Insert & Height Check Test
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

//Test 2c: Insert and Find 
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

//Test 2d: Insert and Find
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

// Test 3a: Insert and Find
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

// Test 3b: Insert and Find
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

// Test 4a: Insert and Find
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


// Test 4b: Insert and Find
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

// Test 4: Insert and Find (Key Return)
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

// Test 5a: Remove Left Leaf
TEST (BasicCollectionTest, Remove_Leaf_Left) { 
RBTCollection <int, double> c;
double v;
c.insert(5, v);
c.insert(6, v);
c.insert(4, v);
ASSERT_EQ(c.height(), 2);
c.remove(4);
ASSERT_EQ(c.find(4, v), false);
ASSERT_EQ(c.height(), 2);
}

// Test 5b: Remove Right Leaf
TEST (BasicCollectionTest, Remove_Right_Left) { 
RBTCollection <int, double> c;
double v;
c.insert(5, v);
c.insert(6, v);
c.insert(4, v);
ASSERT_EQ(c.height(), 2);
c.remove(6);
ASSERT_EQ(c.find(6, v), false);
ASSERT_EQ(c.height(), 2);
}


// Test 5c: Remove Child Outside Left (Black)
TEST (BasicCollectionTest, Remove_Child_Outside_Left_Black) { 
RBTCollection <int, double> c;
double v;
c.insert(5, v);
c.insert(4, v);
c.insert(6, v);
c.insert(3, v);
ASSERT_EQ(c.height(), 3);
c.remove(4);
ASSERT_EQ(c.find(4, v), false);
ASSERT_EQ(c.height(), 2);
}


// Test 5ca: Remove Child Outside Left (Red)
TEST (BasicCollectionTest, Remove_Child_Outside_Left_Red) { 
RBTCollection <int, double> c;
double v;
c.insert(10, v);
c.insert(15, v);
c.insert(7, v);
c.insert(6, v);
c.insert(5, v);
c.remove(7);
ASSERT_EQ(c.find(7, v), false);
ASSERT_EQ(c.height(), 3);
}

// Test 5d: Remove Child Inside Right
TEST (BasicCollectionTest, Remove_Child_Inside_Right) { 
RBTCollection <int, double> c;
double v;
c.insert(5, v);
c.insert(3, v);
c.insert(6, v);
c.insert(4, v);
ASSERT_EQ(c.height(), 3);
c.remove(3);
ASSERT_EQ(c.find(3, v), false);
ASSERT_EQ(c.height(), 2);
}

// Test 5e: Remove Child Outside Right 
TEST (BasicCollectionTest, Remove_Child_Outside_Right) { 
RBTCollection <int, double> c;
double v;
c.insert(5, v);
c.insert(4, v);
c.insert(6, v);
c.insert(7, v);
ASSERT_EQ(c.height(), 3);
c.remove(6);
ASSERT_EQ(c.find(6, v), false);
ASSERT_EQ(c.height(), 2);
}

// Test 5f: Remove Child Inside Right
TEST (BasicCollectionTest, Remove_Child_Inside_Left) { 
RBTCollection <int, double> c;
double v;
c.insert(5, v);
c.insert(4, v);
c.insert(8, v);
c.insert(7, v);
ASSERT_EQ(c.height(), 3);
c.remove(8);
ASSERT_EQ(c.find(8, v), false);
ASSERT_EQ(c.height(), 2);
}

// Test 5g: Remove Child 2 Children (Left)
TEST (BasicCollectionTest, Remove_Child_Two_Children_Left) { 
RBTCollection <int, double> c;
double v;
c.insert(5, v);
c.insert(3, v);
c.insert(6, v);
c.insert(4, v);
c.insert(2, v);
ASSERT_EQ(c.height(), 3);
c.remove(3);
ASSERT_EQ(c.find(3, v), false);
ASSERT_EQ(c.height(), 3);
}

// Test 5h: Remove Child 2 Children (Right)
TEST (BasicCollectionTest, Remove_Child_Two_Children_Right) { 
RBTCollection <int, double> c;
double v;
c.insert(5, v);
c.insert(3, v);
c.insert(8, v);
c.insert(7, v);
c.insert(9, v);
ASSERT_EQ(c.height(), 3);
c.remove(8);
ASSERT_EQ(c.find(8, v), false);
ASSERT_EQ(c.height(), 3);
}

// Test 6: Range Test
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

// Test 7: Sort Test
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

// Test 8: Assign Operator Test
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


