// --------------------------
// projects/integer/Integer.h
// Copyright (C) 2014
// Glenn P. Downing
// --------------------------

#ifndef Integer_h
#define Integer_h

// --------
// includes
// --------

#include <cassert>   // assert
#include <iostream>  // ostream
#include <stdexcept> // invalid_argument
#include <string>    // string
#include <vector>    // vector
using namespace std;
// -----------------
// shift_left_digits
// -----------------

/**
 * @param b an iterator to the beginning of an input  sequence (inclusive)
 * @param e an iterator to the end       of an input  sequence (exclusive)
 * @param x an iterator to the beginning of an output sequence (inclusive)
 * @return  an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the shift left of the input sequence into the output sequence
 * ([b, e) << n) => x
 */
template <typename II, typename FI>
FI shift_left_digits (II b, II e, int n, FI x) {
    // <your code>
    x = copy(b, e, x);
    FI y = x;
    advance(y, n);
    fill(x, y, typename iterator_traits<II>::value_type());
    return y;}

// ------------------
// shift_right_digits
// ------------------

/**
 * @param b an iterator to the beginning of an input  sequence (inclusive)
 * @param e an iterator to the end       of an input  sequence (exclusive)
 * @param x an iterator to the beginning of an output sequence (inclusive)
 * @return  an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the shift right of the input sequence into the output sequence
 * ([b, e) >> n) => x
 */
template <typename II, typename FI>
FI shift_right_digits (II b, II e, int n, FI x) {
    // <your code>
    while(n){
        e--;
        n--;
    }

    while(b != e){
        *x = *b;
        x++;
        b++;
    }
    return x;}

// -----------
// plus_digits
// -----------

/**
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param b2 an iterator to the beginning of an input  sequence (inclusive)
 * @param e2 an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive)
 * @return   an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the sum of the two input sequences into the output sequence
 * ([b1, e1) + [b2, e2)) => x
 */
template <typename II1, typename II2, typename FI>
FI plus_digits (II1 b1, II1 e1, II2 b2, II2 e2, FI x) {
    // <your code>
    int carry = 0;
    int l = 0;
    int max = 0;
    if(e1-b1 > e2-b2){
        l = e2-b2;
        max = 1;
    }
    else if(e1-b1 < e2-b2){
        l = e1-b1;
        max = 2;
    }
    else{
        l = e1-b1;
        max = 3;
    }

    while(l--){
        int value = *b1 + *b2 + carry;
        if(value >= 10){
            value -= 10;
            *x = value;
            carry = 1;
        }
        else{
            *x = value;
            carry = 0;
        }
        b1++;
        b2++;
        x++;
    }
    if(max == 3){
        if(carry == 1){           
            *x = 1;
            carry = 0;
        }
        x++;
    }
    else if(max == 1){
        while(b1 != e1){ 
            if(carry == 1){
                *x = *b1 + 1;
                carry = 0;
            }
            else
                *x = *b1;
            x++;
            b1++;
        }
    }
    else{
        while(b2 != e2){
            if(carry == 1){
                *x = *b2 + 1;
                carry = 0;
            }
            else
                *x = *b2;
            x++;
            b2++;
        }
    }    
    return x;}

// ------------
// minus_digits
// ------------

/**
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param b2 an iterator to the beginning of an input  sequence (inclusive)
 * @param e2 an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive)
 * @return   an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the difference of the two input sequences into the output sequence
 * ([b1, e1) - [b2, e2)) => x
 */
template <typename II1, typename II2, typename FI>
FI minus_digits (II1 b1, II1 e1, II2 b2, II2 e2, FI x) {
    // <your code>
    bool borrow = false;
    int l = 0;
    int max = 0;
    // II1 s1;
    // II1 f1;
    // II2 s2;
    // II2 f2;
    if(e1-b1 > e2-b2){
        l = e2-b2;
        max = 1;
        // s1 = b1;
        // f1 = e1;
        // s2 = b2;
        // f2 = e2;
    }
    else {
        // s1 = b2;
        // f1 = e2;
        // s2 = b1;
        // f2 = e2;
        l = e1-b1;
        max = 2;
    }
    // else{
    //     if(*(e1-1) > *(e2-1)){
    //         s1 = b1;
    //         f1 = e1;
    //         s2 = b2;
    //         f2 = e2;
    //     }
    //     else{
    //         s1 = b2;
    //         f1 = e2;
    //         s2 = b1;
    //         f2 = e2;
    //     }
    // }

    while(l--){
        int c = *b1;
        if(borrow){
            if(c == 0)
                c = 9;
            else{
                c--;
                borrow = false;
            }
        }
        if(c < *b2){
            *x = c + 10 - *b2;
            borrow = true;
        }
        else
            *x = c - *b2;
        b1++;
        b2++;
        x++;
    }
    
    if(max == 1){
        if(borrow){
            *x = *b1--;
            x++;
            b1++;
            borrow = false; 
        }
        while(b1 != e1){
            *x = *b1;
            x++;
            b1++;
        }
    }
    else{
        if(borrow){
            *x = *b2--;
            x++;
            b2++;
            borrow = false; 
        }
        while(b2 != e2){
            *x = *b2;
            x++;
            b2++;
        }
    }

    while(*(x-1) == 0)
        x--;

    return x;
}

// -----------------
// multiplies_digits
// -----------------

/**
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param b2 an iterator to the beginning of an input  sequence (inclusive)
 * @param e2 an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive)
 * @return   an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the product of the two input sequences into the output sequence
 * ([b1, e1) * [b2, e2)) => x
 */
template <typename II1, typename II2, typename FI>
FI multiplies_digits (II1 b1, II1 e1, II2 b2, II2 e2, FI x) {
    // <your code>
    if(b1+1 == e1 && *b1 == 0){
        *x = 0;
        x++;
        return x;
    }
    if(b2+1 == e2 && *b2 == 0){
        *x = 0;
        x++;
        return x;
    }

    vector<int> result;
    
    int i = 0;
    II2 begin = b2;  
    while(b1 != e1){
        b2 = begin;
        int carry = 0;
        vector<int> temp;
        for(int j = i; j > 0; j--)
                temp.push_back(0);
       
        while(b2 != e2){
            int value = *b1 * *b2 + carry;
            if(value >= 10){
                temp.push_back(value%10);
                carry = value/10;
            }
            else{
                temp.push_back(value);
                carry = 0;
            }           
            b2++;
        }
        if(carry != 0){
            temp.push_back(carry);
            carry = 0;
        }
        
        int c = 0;
        for(unsigned int k = 0; k < result.size(); k++){           
            int value = result[k] + temp[k] + c;
            if(value >= 10){
                result[k] = value%10;
                c = value/10;
            }
            else{
                result[k] = value;
                c = 0;
            }
        }
        if(c != 0){
            result.push_back(c);
        }

        for(unsigned int l = result.size(); l < temp.size(); l++){
            result.push_back(temp[l]);
        }
        i++;
        b1++;
    }

    for(unsigned int m = 0; m < result.size(); m++){

        *x = result[m];
        x++;
    }

    // FI begin = x;
    // int* y;
    // x = multiple_helper(b1, b2, e2, y);
    // b1++;
    // b2++;
    // for(; b1 != e1; b1++){             
    //     FI end = multiple_helper(b1, b2, e2, y);
    //     x = plus_digits(begin, x, y, end, x);
    // }

    return x;
}

// --------------
// divides_digits
// --------------

int greater_than(vector<int> t1, vector<int> t2){
    if(t1.size() < t2.size())
        return -1;
    if(t1.size() == t2.size()){
        for(unsigned int i = 0; i < t1.size(); i++){
            if(t1[i] < t2[i])
                return -1;
        }
        if(equal(t1.begin(), t1.begin() + t1.size(), t2.begin()))
            return 0;
    }
    return 1;
}

/**
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param b2 an iterator to the beginning of an input  sequence (inclusive)
 * @param e2 an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive)
 * @return   an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the division of the two input sequences into the output sequence
 * ([b1, e1) / [b2, e2)) => x
 */
template <typename II1, typename II2, typename FI>
FI divides_digits (II1 b1, II1 e1, II2 b2, II2 e2, FI x) {
    // <your code>    
    vector<int> result;
    vector<int> v1;
    vector<int> v2;  
    int l1 = 0;
    int l2 = 0;
    for(II1 i = b1; i < e1; i++){
        v1.push_back(*i);       
        l1++;
    }
    for(II2 i = b2; i < e2; i++){
        v2.push_back(*i);
        l2++;
    }
    if(l1 < l2){
        *x = 0;
        x++;
        return x;
    }
    if(l1 == l2){
        if(v1[l1-1] < v2[l2-1]){
            *x = 0;
            x++;
            return x;
        }
    }
    reverse(v1.begin(), v1.end());
    reverse(v2.begin(), v2.end());
    int i = 0;
    bool first = true;
    vector<int> temp;
    while(i < l1){
        int counter = 0;    
        while(greater_than(temp, v2) == -1 && i < l1){
            temp.push_back(v1[i]);
            i++;
            counter++;
            if(!first &&counter == 2){
                result.push_back(0);
                counter = 0;
            }            
        }
        first = false;

        int count = 0;
        while(greater_than(temp, v2) == 1){
            count++;
            int borrow = 0;
            vector<int> sub;
            vector<int> t1 = temp;
            vector<int> t2 = v2;
            reverse(t1.begin(), t1.end());
            reverse(t2.begin(), t2.end());

            for(unsigned int j = 0; j < t2.size(); j++){
                int value = t1[j] - borrow - t2[j];
                if(value < 0){
                    value += 10;
                    borrow = 1;
                    sub.push_back(value);
                }
                else{
                    sub.push_back(value);
                    borrow = 0;
                }
            }
            if(borrow != 0 && t1.size() > t2.size())
                t1[t2.size()] -= borrow;
            for(unsigned int j = t2.size(); j < t1.size(); j++){
                sub.push_back(t1[j]);
            }
            reverse(sub.begin(), sub.end());
            while(sub[0] == 0){
                for(unsigned int k = 0; k < sub.size()-1; k++)
                    sub[k] = sub[k+1];
                sub.pop_back();
            }
            temp.clear();
            temp = sub;

            if(greater_than(temp, v2) == 0){
                count++;
                break;
            }
        }
        result.push_back(count);
    }
    for(int s = result.size()-1; s >= 0; s--){
        *x = result[s];
        x++;
    }
    while(*(x-1) == 0)
        x--;

    return x;}

// -------
// Integer
// -------

template < typename T, typename C = std::vector<T> >
class Integer {
    // -----------
    // operator ==
    // -----------

    /**
     * <your documentation>
     */
    friend bool operator == (const Integer& lhs, const Integer& rhs) {
        // <your code>
        return false;}

    // -----------
    // operator !=
    // -----------

    /**
     * <your documentation>
     */
    friend bool operator != (const Integer& lhs, const Integer& rhs) {
        return !(lhs == rhs);}

    // ----------
    // operator <
    // ----------

    /**
     * <your documentation>
     */
    friend bool operator < (const Integer& lhs, const Integer& rhs) {
        // <your code>
        return false;}

    // -----------
    // operator <=
    // -----------

    /**
     * <your documentation>
     */
    friend bool operator <= (const Integer& lhs, const Integer& rhs) {
        return !(rhs < lhs);}

    // ----------
    // operator >
    // ----------

    /**
     * <your documentation>
     */
    friend bool operator > (const Integer& lhs, const Integer& rhs) {
        return (rhs < lhs);}

    // -----------
    // operator >=
    // -----------

    /**
     * <your documentation>
     */
    friend bool operator >= (const Integer& lhs, const Integer& rhs) {
        return !(lhs < rhs);}

    // ----------
    // operator +
    // ----------

    /**
     * <your documentation>
     */
    friend Integer operator + (Integer lhs, const Integer& rhs) {
        return lhs += rhs;}

    // ----------
    // operator -
    // ----------

    /**
     * <your documentation>
     */
    friend Integer operator - (Integer lhs, const Integer& rhs) {
        return lhs -= rhs;}

    // ----------
    // operator *
    // ----------

    /**
     * <your documentation>
     */
    friend Integer operator * (Integer lhs, const Integer& rhs) {
        return lhs *= rhs;}

    // ----------
    // operator /
    // ----------

    /**
     * <your documentation>
     * @throws invalid_argument if (rhs == 0)
     */
    friend Integer operator / (Integer lhs, const Integer& rhs) {
        return lhs /= rhs;}

    // ----------
    // operator %
    // ----------

    /**
     * <your documentation>
     * @throws invalid_argument if (rhs <= 0)
     */
    friend Integer operator % (Integer lhs, const Integer& rhs) {
        return lhs %= rhs;}

    // -----------
    // operator <<
    // -----------

    /**
     * <your documentation>
     * @throws invalid_argument if (rhs < 0)
     */
    friend Integer operator << (Integer lhs, int rhs) {
        return lhs <<= rhs;}

    // -----------
    // operator >>
    // -----------

    /**
     * <your documentation>
     * @throws invalid_argument if (rhs < 0)
     */
    friend Integer operator >> (Integer lhs, int rhs) {
        return lhs >>= rhs;}

    // -----------
    // operator <<
    // -----------

    /**
     * <your documentation>
     */
    friend std::ostream& operator << (std::ostream& lhs, const Integer& rhs) {
        // <your code>
        return lhs << "0";}

    // ---
    // abs
    // ---

    /**
     * absolute value
     * <your documentation>
     */
    friend Integer abs (Integer x) {
        return x.abs();}

    // ---
    // pow
    // ---

    /**
     * power
     * <your documentation>
     * @throws invalid_argument if ((x == 0) && (e == 0)) || (e < 0)
     */
    friend Integer pow (Integer x, int e) {
        return x.pow(e);}

    private:
        // ----
        // data
        // ----
        int number;
        bool negative;
        C _x; // the backing container
        // <your data>

    private:
        // -----
        // valid
        // -----

        bool valid () const { // class invariant
            // <your code>
            return true;}

    public:
        // ------------
        // constructors
        // ------------

        /**
         * <your documentation>
         */
        Integer (int value) {
            // <your code>
            assert(valid());}

        /**
         * <your documentation>
         * @throws invalid_argument if value is not a valid representation of an Integer
         */
        explicit Integer (const std::string& value) {
            // <your code>
            if (!valid())
                throw std::invalid_argument("Integer::Integer()");}

        // Default copy, destructor, and copy assignment.
        // Integer (const Integer&);
        // ~Integer ();
        // Integer& operator = (const Integer&);

        // ----------
        // operator -
        // ----------

        /**
         * <your documentation>
         */
        Integer operator - () const {
            // <your code>
            return Integer(0);}

        // -----------
        // operator ++
        // -----------

        /**
         * <your documentation>
         */
        Integer& operator ++ () {
            *this += 1;
            return *this;}

        /**
         * <your documentation>
         */
        Integer operator ++ (int) {
            Integer x = *this;
            ++(*this);
            return x;}

        // -----------
        // operator --
        // -----------

        /**
         * <your documentation>
         */
        Integer& operator -- () {
            *this -= 1;
            return *this;}

        /**
         * <your documentation>
         */
        Integer operator -- (int) {
            Integer x = *this;
            --(*this);
            return x;}

        // -----------
        // operator +=
        // -----------

        /**
         * <your documentation>
         */
        Integer& operator += (const Integer& rhs) {
            // <your code>
            return *this;}

        // -----------
        // operator -=
        // -----------

        /**
         * <your documentation>
         */
        Integer& operator -= (const Integer& rhs) {
            // <your code>
            return *this;}

        // -----------
        // operator *=
        // -----------

        /**
         * <your documentation>
         */
        Integer& operator *= (const Integer& rhs) {
            // <your code>
            return *this;}

        // -----------
        // operator /=
        // -----------

        /**
         * <your documentation>
         * @throws invalid_argument if (rhs == 0)
         */
        Integer& operator /= (const Integer& rhs) {
            // <your code>
            return *this;}

        // -----------
        // operator %=
        // -----------

        /**
         * <your documentation>
         * @throws invalid_argument if (rhs <= 0)
         */
        Integer& operator %= (const Integer& rhs) {
            // <your code>
            return *this;}

        // ------------
        // operator <<=
        // ------------

        /**
         * <your documentation>
         */
        Integer& operator <<= (int n) {
            // <your code>
            return *this;}

        // ------------
        // operator >>=
        // ------------

        /**
         * <your documentation>
         */
        Integer& operator >>= (int n) {
            // <your code>
            return *this;}

        // ---
        // abs
        // ---

        /**
         * absolute value
         * <your documentation>
         */
        Integer& abs () {
            // <your code>
            return *this;}

        // ---
        // pow
        // ---

        /**
         * power
         * <your documentation>
         * @throws invalid_argument if ((this == 0) && (e == 0)) or (e < 0)
         */
        Integer& pow (int e) {
            // <your code>
            return *this;}};

#endif // Integer_h
