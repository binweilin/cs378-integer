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
    FI xb = x;
    
    // get max to determine subtacter and subtract-ee
    bool b1_is_max = true;
    II1 a = e1;
    II2 b = e2;
    if((e1 - b1) > (e2 - b2))
        b1_is_max = true;
    else if((e1-b1) < (e2-b2))
        b1_is_max = false;
    else{
        b1_is_max = true;
        // if same length find first difference and return max
        while(a > b1){
             --a; --b;
            if(*a > *b){

                break;
            }
            else if(*a < *b){
                b1_is_max = false;
                break;
            }
        }
    }
    
    if(b1_is_max){
        // go through the iterators backwards and place answer in x
        int carry = 0;
        while(b2 != e2){
            int value = *b1 - *b2 - carry;
            if(value < 0){
                *x = value+10;
                carry = 1;
            } 
            else {

                *x = value;
                carry = 0;
            }
            ++b1; ++b2;++x;
        }
    
        while(e1 != b1){
            if(carry >0){
                *x = *b1 - carry;
                carry = 0;
            }
            else
                *x = *b1;
            ++b1;
            ++x;
        }
    } else {
        int carry = 0;
        // go through the iterators backwards and place answer in x
        while(b1 != e1){
            int value = *b2 - *b1 - carry;
        
        if(value < 0){
                *x = value+10;
                carry = 1;
            } 
            else {
                
                *x = value;
                carry = 0;
            }
            ++b1; ++b2;++x;
        }
    
        while(e2 != b2){
            if(carry >0){
                *x = *b2 + carry;
                carry = 0;
            }
            else
                *x = *b2;
            ++b2;
            ++x;
         }
    }
    
    // get rid of leading zeros
    while(xb != (x-1) && *(x-1) == 0)
        --x; 
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
    FI xb = x;
    II2 b2c = b2;
    int count1 = 0;
    while(e1 > b1){
        
        int count2 = 0;
        b2 = b2c;
        while(e2 > b2){           
            if(count1 == 0 || e2-1 == b2)
                *(xb + count1 + count2) = *b1 * *b2;
            else
                *(xb + count1 + count2) += *b1 * *b2;
            ++count2; ++b2;
        }
        x = xb + count1 + count2;
        ++count1; ++b1;
    }

    int i = 0;
    while((xb + i) != x){      
        if( *(xb + i) >= 10){
            if((xb + i + 1) == x){
                *(xb + i + 1) = *(xb+i) / 10;
                ++x;
            } else
                *(xb + i + 1) += *(xb + i) / 10;
            *(xb + i) %= 10;
        }
        ++i;
    }

    return x;}

// --------------
// divides_digits
// --------------

int greater_than(vector<int> t1, vector<int> t2){
    if(t1.size() < t2.size())
        return -1;
    if(t1.size() == t2.size()){
        for(unsigned int i = 0; i < t1.size(); i++){
            if(t1[i] < t2[i]){
                return -1;
            }
            else if(t1[i] > t2[i]){
                break;
            }
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
    if(l2 == 1 && *b2 == 1){
        for(II1 i = b1; i < e1;i++){
            *x = *i;
            x++;
        }
        return x;
    }
    reverse(v1.begin(), v1.end());
    reverse(v2.begin(), v2.end());
    int i = 0;
    bool first = true;
    vector<int> temp;
    while(i < l1){
        int counter = 0;
        if(greater_than(temp, v2) == 0){
            result.push_back(1);
            i++;
        }

        while(greater_than(temp, v2) == -1 && i < l1){
            temp.push_back(v1[i]);
            i++;
            counter++;
            if(!first &&counter == 2){
                result.push_back(0);
                counter = 0;
                cout<<"push 0"<<endl;
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
        cout<<"push " << count<<endl;
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
        if(lhs.is_negative == rhs.is_negative  &&
            lhs._x.size() == rhs._x.size()){
            for(unsigned int i = 0; i < lhs._x.size(); i++){
                if(!(lhs._x[i] == rhs._x[i]))
                    return false;
            }
            return true;
        }
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
        Integer l = lhs;
        Integer r = rhs;
        
        if(l.is_negative != r.is_negative){
            if(l.is_negative == true)
                return true;
        }
        else if(l.is_negative == false){
            if(l._x.size() < r._x.size())
                return true;
            else if(l._x.size() == r._x.size()){
                unsigned int s = l._x.size()-1;
                while(s >= 0){
                    if(l._x[s] > r._x[s])
                        return false;
                }
                return true;
            }
        }
        else{
            if(l._x.size() > r._x.size())
                return true;
            else if(l._x.size() == r._x.size()){
                unsigned int s = l._x.size()-1;
                while(s >= 0){
                    if(l._x[s] < r._x[s])
                        return false;
                }
                return true;
            }
        }
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
        if(rhs.is_negative == true)
            lhs << '-';
        typename C::const_iterator b = rhs._x.begin();
        typename C::const_iterator e = rhs._x.end();
        e--;
        while(b!=e+1){
            lhs << *e;
            e--;
        }

        return lhs;}

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
      
        bool is_negative = false;
        C _x; // the backing container

    private:
        // -----
        // valid
        // -----

        bool valid () const { // class invariant
            for(unsigned int i = 0; i < this->_x.size(); i++){
                if(!(this->_x[i] >= 0 && this->_x[i] <= 9))
                    return false;
            }
            return true;}

    public:
        // ------------
        // constructors
        // ------------

        /**
         * <your documentation>
         */
        Integer(){
            Integer(0);
        }

        Integer (int value) {

            if(value < 0)
                this->is_negative = true;
            value = ::abs(value);
            do {
                int to_insert = value % 10;
                value /= 10;
                this->_x.push_back(to_insert);
            } while(value != 0);
            assert(valid());}

        /**
         * <your documentation>
         * @throws invalid_argument if value is not a valid representation of an Integer
         */
        explicit Integer (const std::string& value) {
            
            unsigned int i = 0;
            if(value[0] == '-'){
                this->is_negative = true;
                i++;
            }
            while(i < value.size()){
                T digit = int(value[i] - 48);
                if(!(digit>=0 && digit<=9)){
                    throw std::invalid_argument("Integer::Integer()");
                }
                this->_x.insert(this->_x.begin(), digit);
                i++;
            }

            if (!valid()){
                throw std::invalid_argument("Integer::Integer()");;}}

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
            Integer x = *this;
            x.is_negative = !(x.is_negative);
            return x;}

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
           
           bool flag;
            Integer l = *this;
            Integer result;
            typename C::iterator b1 = l._x.begin();
            typename C::iterator e1 = l._x.end();
            typename C::iterator b2 = rhs._x.begin();
            typename C::iterator e2 = rhs._x.end();
            typename C::iterator x = result._x.begin();
            if(rhs.is_negative == this.is_negative)
                flag = true;
            else
                flag = false;

            if(flag == true){
                plus_digits(b1,e1,b2,e2,x);
                result.is_negative = rhs.is_negative;
            }
            else{
                minus_digits(b1,e1,b2,e2,x);
                if(l > rhs)
                    result.is_negative = l.is_negative;
                else
                    result.is_negative = rhs.is_negative;
            }
            *this = result;

            return *this;}

        // -----------
        // operator -=
        // -----------

        /**
         * <your documentation>
         */
        Integer& operator -= (const Integer& rhs) {
            
            bool flag;
            Integer l = *this;
            Integer s = rhs;
            C result (l._x.size(), 0);
            typename C::iterator b1 = l._x.begin();
            typename C::iterator e1 = l._x.end();
            typename C::iterator b2 = s._x.begin();
            typename C::iterator e2 = s._x.end();
            typename C::iterator x = result.begin();
            typename C::iterator p;
            if(rhs.is_negative == this->is_negative)
                flag = false;
            else
                flag = true;

            if(flag == true){
                p = plus_digits(b1,e1,b2,e2,x);
                this->is_negative = l.is_negative;
            }
            else{
                p = minus_digits(b1,e1,b2,e2,x);
                if(l > rhs && l.is_negative == false)
                    this->is_negative = false;
                else if(l < rhs && l.is_negative == false)
                    this->is_negative = true;
                else if(l < rhs && l.is_negative == true)
                    this->is_negative = false;
                else if(l < rhs && l.is_negative == true)
                    this->is_negative = true;
            }
            C v = C(x,p);
            this->_x = v;
            return *this;}

        // -----------
        // operator *=
        // -----------

        /**
         * <your documentation>
         */
        Integer& operator *= (const Integer& rhs) {
           
           if(this->is_negative ==  rhs.is_negative)
                this->is_negative = false;
            else
                this->is_negative = true;

            Integer l = *this;
            Integer s = rhs;
            C result (l._x.size() + s._x.size()+1, 0);
            //Integer result;
            typename C::iterator b1 = l._x.begin();
            typename C::iterator e1 = l._x.end();
            typename C::iterator b2 = s._x.begin();
            typename C::iterator e2 = s._x.end();
            typename C::iterator x = result.begin();

            typename C::iterator p = multiplies_digits(b1,e1,b2,e2,x);
            C v = C(x,p);
            this->_x = v;

            return *this;}

        // -----------
        // operator /=
        // -----------

        /**
         * <your documentation>
         * @throws invalid_argument if (rhs == 0)
         */
        Integer& operator /= (const Integer& rhs) {
            if(rhs == 0)
                throw std::invalid_argument("Integer::Integer()");
            
            if(this->is_negative ==  rhs->is_negative)
                this->is_negative = false;
            else
                this->is_negative = true;

            Integer l = *this;
            Integer result;
            typename C::iterator b1 = l._x.begin();
            typename C::iterator e1 = l._x.end();
            typename C::iterator b2 = rhs._x.begin();
            typename C::iterator e2 = rhs._x.end();
            typename C::iterator x = result._x.begin();

            divide_digits(b1,e1,b2,e1,x);
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
            if(rhs <= 0)
                throw std::invalid_argument("rhs <= 0");

            typename C::iterator b2 = rhs._x.begin();
            typename C::iterator e2 = rhs._x.end();
            Integer result;
            result = *this / rhs;
            result = rhs * result;
            result = *this - result;
            *this = result;            
            return *this;}

        // ------------
        // operator <<=
        // ------------

        /**
         * <your documentation>
         */
        Integer& operator <<= (int n) {
            
            typename C::iterator b = this._x.begin();
            typename C::iterator e = this._x.end();
            shift_left_digits(b, e, n);
            return *this;}

        // ------------
        // operator >>=
        // ------------

        /**
         * <your documentation>
         */
        Integer& operator >>= (int n) {
            
            typename C::iterator b = this._x.begin();
            typename C::iterator e = this._x.end();
            shift_right_digits(b, e, n);
            return *this;}

        // ---
        // abs
        // ---

        /**
         * absolute value
         * <your documentation>
         */
        Integer& abs () {
            this->is_negative = false;
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
            if(*this == 0)
                throw::invalid_argument("Integer::Integer()");
            if(e < 0)
                throw::invalid_argument("Integer::Integer()");
            if (e == 0){
                *this = 1;
                return *this;
            }

            Integer n = *this;
            Integer result = 1;

            if(e > 1)
                result = n.pow(e/2); 

            if(!(e & 1) )       // even
                result *= result;
            else{       // odd
                result *= result;
                result *= *this;
            }


            *this = result;
            return *this;
        }
    };

#endif // Integer_h
