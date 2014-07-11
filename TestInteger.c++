// --------------------------------
// projects/integer/TestInteger.c++
// Copyright (C) 2014
// Glenn P. Downing
// --------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

/*
Google Test Libraries:
    % ls -al /usr/include/gtest/
    ...
    gtest.h
    ...

    % locate libgtest.a
    /usr/lib/libgtest.a

    % locate libpthread.a
    /usr/lib/x86_64-linux-gnu/libpthread.a
    /usr/lib32/libpthread.a

    % locate libgtest_main.a
    /usr/lib/libgtest_main.a

To compile the test:
    % g++-4.7 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Integer.c++ TestInteger.c++ -o TestInteger -lgtest -lgtest_main -lpthread

To run the test:
    % valgrind TestInteger

To obtain coverage of the test:
    % gcov-4.7 -b Integer.c++ TestInteger.c++
*/

// --------
// includes
// --------

#include <algorithm> // equal
#include <cstring>   // strcmp
#include <sstream>   // ostringstream
#include <stdexcept> // invalid_argument
#include <string>    // ==

#include "gtest/gtest.h"

#include "Integer.h"

// -----------
// TestInteger
// -----------

// -----------------
// shift_left_digits
// -----------------

TEST(Integer, shift_left_digits_1) {
    const int a[] = {2, 3, 4};
    const int b[] = {0, 2, 3, 4};
          int x[10];
    const int* p = shift_left_digits(a, a + 3, 1, x);
    ASSERT_EQ(4, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, b));}

TEST(Integer, shift_left_digits_2) {
    const int a[] = {2, 3, 4};
    const int b[] = {0, 0, 0, 2, 3, 4};
          int x[10];
    const int* p = shift_left_digits(a, a + 3, 3, x);
    ASSERT_EQ(6, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, b));}

TEST(Integer, shift_left_digits_3) {
    const int a[] = {2, 3, 4};
    const int b[] = {0, 0, 2, 3, 4};
          int x[10];
    const int* p = shift_left_digits(a, a + 3, 2, x);
    ASSERT_EQ(5, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, b));}

// ------------------
// shift_right_digits
// ------------------

TEST(Integer, shift_right_digits_1) {
    const int a[] = {2, 3, 4};
    const int b[] = {4};
          int x[10];
    const int* p = shift_right_digits(a, a + 3, 2, x);
    ASSERT_EQ(1, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, b));}

TEST(Integer, shift_right_digits_2) {
    const int a[] = {2, 3, 4};
    const int b[] = {3, 4};
          int x[10];
    const int* p = shift_right_digits(a, a + 3, 1, x);
    ASSERT_EQ(2, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, b));}

TEST(Integer, shift_right_digits_3) {
    const int a[] = {2, 3, 4, 5, 6};
    const int b[] = {5, 6};
          int x[10];
    const int* p = shift_right_digits(a, a + 5, 3, x);
    ASSERT_EQ(2, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, b));}

// -----------
// plus_digits
// -----------

TEST(Integer, plus_digits_1) {
    const int a[] = {0, 0, 1};
    const int b[] = {9, 9, 1};
    const int c[] = {9, 9, 2};
          int x[10];
    const int* p = plus_digits(a, a + 3, b, b + 3, x);
    ASSERT_EQ(3, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}

TEST(Integer, plus_digits_2) {
    const int a[] = {1};
    const int b[] = {5, 6, 7};
    const int c[] = {6, 6, 7};
          int x[10];
    const int* p = plus_digits(a, a + 1, b, b + 3, x);
    ASSERT_EQ(3, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}

TEST(Integer, plus_digits_3) {
    const int a[] = {5, 6, 7};
    const int b[] = {2, 3, 4};
    const int c[] = {7, 9, 1, 1};
          int x[10];
    const int* p = plus_digits(a, a + 3, b, b + 3, x);
    ASSERT_EQ(4, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}


// ------------
// minus_digits
// ------------

TEST(Integer, minus_digits) {
    const int a[] = {5, 4, 3, 2, 1};
    const int b[] = {0, 4, 3, 2, 1};
    const int c[] = {5};
          int x[10];
    const int* p = minus_digits(b, b + 5, a, a + 5, x);
    ASSERT_EQ(1, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}

TEST(Integer, minus_digitsII) {
    const int a[] = {1, 0, 8};
    const int b[] = {7, 6, 5};
    const int c[] = {4, 3, 2};
          int x[10];
    const int* p = minus_digits(a, a + 3, b, b + 3, x);
    ASSERT_EQ(3, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}
    
TEST(Integer, minus_digitsIII) {
    const int a[] = {7, 1, 5};
    const int b[] = {1, 2};
    const int c[] = {6, 9, 4};
          int x[10];
    const int* p = minus_digits(a, a + 3, b, b + 2, x);
    ASSERT_EQ(3, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}
    
// -----------------
// multiplies_digits
// -----------------

TEST(Integer, multiplies_digits_1) {
    const int a[] = {2, 3, 4};
    const int b[] = {5, 6, 7};
    const int c[] = {0, 8, 4, 0, 3, 3};
          int x[10];
    //cout << "1";
    const int* p = multiplies_digits(a, a + 3, b, b + 3, x);
    //cout << "2";
    ASSERT_EQ(6, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}

TEST(Integer, multiplies_digits_2) {
    const int a[] = {1, 2, 3, 4, 5};
    const int b[] = {3, 4, 5, 6, 7};
    const int c[] = {3, 0, 3, 2, 9, 8, 7, 5, 1, 4};
          int x[10];
    const int* p = multiplies_digits(a, a + 5, b, b + 5, x);
    ASSERT_EQ(10, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}

TEST(Integer, multiplies_digits_3) {
    const int a[] = {2,};
    const int b[] = {5};
    const int c[] = {0, 1};
          int x[10];
    const int* p = multiplies_digits(a, a + 1, b, b + 1, x);
    ASSERT_EQ(2, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}

// --------------
// divides_digits
// --------------

TEST(Integer, divides_digits_1) {
    const int a[] = {0, 8, 4, 0, 3, 3};
    const int b[] = {5, 6, 7};
    const int c[] = {2, 3, 4};
          int x[10];
    const int* p = divides_digits(a, a + 6, b, b + 3, x);
    ASSERT_EQ(3, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}

TEST(Integer, divides_digits_2) {
    const int a[] = {0, 8, 4};
    const int b[] = {1};
    const int c[] = {0, 8, 4};
          int x[10];
    const int* p = divides_digits(a, a + 3, b, b + 1, x);
    ASSERT_EQ(3, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}

TEST(Integer, divides_digits_3) {
    const int a[] = {1, 2};
    const int b[] = {2};
    const int c[] = {0, 1};
          int x[10];
    const int* p = divides_digits(a, a + 2, b, b + 1, x);
    ASSERT_EQ(2, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}

// -----------
// constructor
// -----------

TEST(Integer, constructor_1) {
    try {
        const Integer<int> x("abc");
        ASSERT_TRUE(false);}
    catch (std::invalid_argument& e) {
        ASSERT_STREQ("Integer::Integer()", e.what());}}

TEST(Integer, constructor_2) {
    try {
        const Integer<int> x("-2");}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, constructor_3) {
    try {
        const Integer<int> x(2);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

// ---
// abs
// ---

TEST(Integer, abs_1) {
    try {
        Integer<int>  x = -98765;
        Integer<int>& y = x.abs();
        ASSERT_EQ(98765, x);
        ASSERT_EQ(&x,    &y);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, abs_2) {
    try {
        const Integer<int> x = -98765;
        const Integer<int> y = abs(x);
        ASSERT_EQ(-98765, x);
        ASSERT_EQ( 98765, y);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, abs_3) {
    try {
        const Integer<int> x = 98765;
        const Integer<int> y = abs(x);
        ASSERT_EQ( 98765, x);
        ASSERT_EQ( 98765, y);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

// --------
// equal_to
// --------

TEST(Integer, equal_to_1) {
    try {
        const Integer<int> x = 98765;
        const Integer<int> y = 98765;
        ASSERT_EQ(      x, y);
        ASSERT_EQ(      x, 98765);
        ASSERT_EQ(  98765, x);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, equal_to_2) {
    try {
        const Integer<int> x = 0;
        const Integer<int> y = 0;
        ASSERT_EQ(      x, y);
        ASSERT_EQ(      x, 0);
        ASSERT_EQ(  0, x);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, equal_to_3) {
    try {
        const Integer<int> x = 1;
        const Integer<int> y = 1;
        ASSERT_EQ(      x, y);
        ASSERT_EQ(      x, 1);
        ASSERT_EQ(  1, x);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

// --------
// negation
// --------

TEST(Integer, negation_1) {
    try {
        const Integer<int> x = 98765;
        const Integer<int> y = -x;
        ASSERT_EQ(-98765, y);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, negation_2) {
    try {
        const Integer<int> x = 1;
        const Integer<int> y = -x;
        ASSERT_EQ(-1, y);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, negation_3) {
    try {
        const Integer<int> x = 2;
        const Integer<int> y = -x;
        ASSERT_EQ(-2, y);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

// ------
// output
// ------

TEST(Integer, output_1) {
    try {
        const Integer<int> x = 98765;
        std::ostringstream out;
        out << x;
        ASSERT_EQ("98765", out.str());}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, output_2) {
    try {
        const Integer<int> x = 0;
        std::ostringstream out;
        out << x;
        ASSERT_EQ("0", out.str());}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, output_3) {
    try {
        const Integer<int> x = 1;
        std::ostringstream out;
        out << x;
        ASSERT_EQ("1", out.str());}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

// ---
// pow
// ---

TEST(Integer, pow_1) {
    try {
        Integer<int>       x = 2;
        const int          e = 2;
        Integer<int>&      y = x.pow(e);
        ASSERT_EQ(4,  x);
        ASSERT_EQ(2,  e);
        ASSERT_EQ(&x, &y);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, pow_2) {
    try {
        const Integer<int> x = 12;
        const int          e =  2;
        const Integer<int> y = pow(x, e);
        ASSERT_EQ(12, x);
        ASSERT_EQ(2, e);
        ASSERT_EQ(144, y);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, pow_3) {
    try {
        const Integer<int> x = 10;
        const int          e =  3;
        const Integer<int> y = pow(x, e);
        ASSERT_EQ(10, x);
        ASSERT_EQ(3, e);
        ASSERT_EQ(1000, y);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}


// ----------
// operator <
// ----------

TEST(Integer, less_than_1) {
    try {
        const Integer<int> x = 0;
        const Integer<int> y = 0;
        ASSERT_EQ(      x<y, false);} 
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, less_than_2) {
    try {
        const Integer<int> x = 201;
        const Integer<int> y = 102;
        ASSERT_EQ(      x<y, false);} 
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, less_than_3) {
    try {
        const Integer<int> x = -1;
        const Integer<int> y = -2;
        ASSERT_EQ(      x<y, false);} 
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

// -----------
// operator +=
// -----------

TEST(Integer, plus_equals_1) {
        Integer<int> x("199"); 
        const Integer<int> y("100"); 
        x += y;
        Integer<int> sum("299");
        ASSERT_EQ(      x, sum);}

TEST(Integer, plus_equals_2) {
        Integer<int> x("-987654321987654321"); 
        const Integer<int> y("-987654321987654321"); 
        x += y;
        Integer<int> sum("-1975308643975308642");
        ASSERT_EQ(      x, sum);}

TEST(Integer, plus_equals_3) {
        Integer<int> x("987654321987654321"); 
        const Integer<int> y("-1975308643975308642"); 
        x += y;
        Integer<int> sum("-987654321987654321");
        ASSERT_EQ(      x, sum);}

// -----------
// operator -=
// -----------
TEST(Integer, minus_equals_1) {
        Integer<int> x("-987654321987654321"); 
        const Integer<int> y("0"); 
        x -= y;
        Integer<int> difference("-987654321987654321");
        ASSERT_EQ(      x, difference);}

TEST(Integer, minus_equals_2) {
        Integer<int> x("987654321987654321"); 
        const Integer<int> y("76543217654321"); 
        x -= y;
        Integer<int> difference("987577778770000000");
        ASSERT_EQ(      x, difference);}

TEST(Integer, minus_equals_3) {
        Integer<int> x("-987654321987654321"); 
        const Integer<int> y("-76543217654321"); 
        x -= y;
        Integer<int> difference("-987577778770000000");
        ASSERT_EQ(      x, difference);}

TEST(Integer, minus_equals_4) {
        Integer<int> x(12345); 
        const Integer<int> y(12340); 
        x -= y;
        Integer<int> difference(5);
        ASSERT_EQ(      x, difference);}

// -----------
// operator *=
// -----------

//first positive second positive
TEST(Integer, times_equals_1) {
        Integer<int> x("987654321987654321"); 
        const Integer<int> y("76543217654321"); 
        x *= y;
        Integer<int> product("75598239735131859630574619971041");
        ASSERT_EQ(      x, product);}

//first positive second zero
TEST(Integer, times_equals_2) {
        Integer<int> x("987654321987654321"); 
        const Integer<int> y("0"); 
        x *= y;
        Integer<int> product("0");
        ASSERT_EQ(      x, product);}



//first positive second negative
TEST(Integer, times_equals_3) {
        Integer<int> x("2342341235"); 
        const Integer<int> y("-42157978692456234"); 
        x *= y;
        Integer<int> product("-98748371875591620331008990");
        ASSERT_EQ(      x, product);}

// -----------
// operator /=
// -----------

TEST(Integer, divide_equals_1) {
    try {
        Integer<int> x = -12345;
        x /= -20;
        ASSERT_EQ(617, x);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, divide_equals_2) {
    try {
        Integer<int> x = 0;
        x /= 3;
        ASSERT_EQ(0, x);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, divide_equals_3) {
    try {
        Integer<int> x = 12345;
        x /= 20;
        ASSERT_EQ(617, x);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

// -----------
// operator %=
// -----------

// modulo of negative and negative
TEST(Integer, modulo_equals_1) {
    try {
        Integer<int> x = -12345;
        const Integer<int> y = -20;
        x %= y;
        ASSERT_TRUE(false);}
    catch (std::invalid_argument& e) {
        }}

// modulo of 0 is 0
TEST(Integer, modulo_equals_2) {
    try {
        Integer<int> x = 0;
        const Integer<int> y = 3;
        x %= y;
        ASSERT_EQ(0, x);}
    catch (std::invalid_argument& e) {
        cout <<"here3\n";
        ASSERT_TRUE(false);}}

// modulo of positive and positive
TEST(Integer, modulo_equals_3) {
    try {
        Integer<int> x = 12345;
        x %= 20;
        ASSERT_EQ(5, x);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

// ------------
// operator <<=
// ------------

TEST(Integer, shift_left_equals_1) {
    try {
        Integer<int> x = 12345;
        x <<= 2;
        ASSERT_EQ(1234500, x);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, shift_left_equals_2) {
    try {
        Integer<int> x = 0;
        x <<= 3;
        ASSERT_EQ(0, x);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, shift_left_equals_3) {
    try {
        Integer<int> x = 12345;
        x <<= 7;
        ASSERT_EQ(Integer<int>("123450000000"), x);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}


// ------------
// operator >>=
// ------------

TEST(Integer, shift_right_equals_1) {
    try {
        Integer<int> x = 12345;
        x >>= 2;
        ASSERT_EQ(123, x);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, shift_right_equals_2) {
    try {
        Integer<int> x = 0;
        x >>= 3;
        ASSERT_TRUE(false);}
    catch (std::invalid_argument& e) {
        }}

TEST(Integer, shift_right_equals_3) {
    try {
        Integer<int> x = 12345;
        x >>= 7;
        ASSERT_TRUE(false);}
    catch (std::invalid_argument& e) {
        }}

//------------
//greater_than
//------------

TEST(Integer, greater_than_1) {
    std::vector<int> v1{1, 2, 3};
    std::vector<int> v2{1, 2, 3};
    int x = greater_than(v1, v2);
    ASSERT_EQ(0, x);    
}

TEST(Integer, greater_than_2) {
    std::vector<int> v1{1, 2, 3};
    std::vector<int> v2{1, 2, 2};
    int x = greater_than(v1, v2);
    ASSERT_EQ(1, x);    
}

TEST(Integer, greater_than_3) {
    std::vector<int> v1{1, 2, 3};
    std::vector<int> v2{1, 2, 4};
    int x = greater_than(v1, v2);
    ASSERT_EQ(-1, x);    
}