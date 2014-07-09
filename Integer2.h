// --------------------------
// projects/integer/Integer.h
// Copyright (C) 2014
// Glenn P. Downing
// --------------------------

#ifndef Integer_h
#define Integer_h
using namespace std;

// --------
// includes
// --------

#include <cassert>   // assert
#include <iostream>  // ostream
#include <stdexcept> // invalid_argument
#include <string>    // string
#include <vector>    // vector
#include <stdlib.h>  // abs

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
template <typename II, typename OI>
OI shift_left_digits (II b, II e, int n, OI x) {

    OI y = copy(b,e,x);
    fill(y,y+n,0);
	advance(y,n);
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
template <typename II, typename OI>
OI shift_right_digits (II b, II e, int n, OI x) {
    
    OI y = copy(b,e-n,x);
    return y;}

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
template <typename II1, typename II2, typename OI>
OI plus_digits (II1 b1, II1 e1, II2 b2, II2 e2, OI x) {
   	
   	int result;
   	int carry = 0;
   	OI xb = x;
   	
   	// compute the values from right to left and fill into x
   	while(b1 != e1 && b2 != e2){
   	
   		--e1; -- e2;
   		result = *e1 + *e2 + carry;
   		carry = 0;
   		*x = result;
   		
   		// if theres an overflow keep track
   		if(result > 9){
   		
   			*x = result % 10;
   			carry = 1;
   		} 
   		if(b1 != e1 && b2 != e2) ++x;
   	}
   	
   	// assuming II1 is larger
   	while(b1 != e1){
   	
   		result = *e1 + carry;
   		carry = 0;
   		e1--;
   		if(result > 9)
   			*x = result % 10;
   		else if(b1 != e1) ++x;	
   	}
   	
   	// assuming II2 is larger
   	while(b2 != e2){
   	
   		result = *e2 + carry;
   		carry = 0;
   		e2--;
   		if(result > 9)
   			*x = result % 10;
   		else if(b2 != e2) ++x;	
   	}
   	
   	// check if any overflow at end
   	if(carry == 1){
   		++x;
   		*x = 1;
   	}
   	++x;
   	reverse(xb,x);
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
template <typename II1, typename II2, typename OI>
OI minus_digits (II1 b1, II1 e1, II2 b2, II2 e2, OI x) {
    
    OI xb = x;
    
    // get max to determine subtacter and subtract-ee
    bool b1_is_max = true;
    II1 a = b1;
    II2 b = b2;
    if((e1 - b1) > (e2 - b2))
    	b1_is_max = true;
    else if((e1-b1) < (e2-b2))
    	b1_is_max = false;
    else{
    	b1_is_max = true;
    	// if same length find first difference and return max
    	while(a != e1){
    		if(*a > *b){
    			break;
    		}
    		else if(*a < *b){
    			b1_is_max = false;
    			break;
    		}
    		++a; ++b;
    	}
    }
    
    if(b1_is_max){
    
		// go through the iterators backwards and place answer in x
    	while(b1 != e1 && b2 != e2){
    		--e1; --e2;
    	
    		// if the current place value of the max is less than the min
    		if(*e1 < *e2){
    			// distribute value from higher digits
    			*x = (10 + *e1) - *e2;
    			--e1; --e2; ++x;
    		
    			while(*e1 == 0){
    				
    				*x = 9 - *e2;
    				--e1; --e2; ++x;
    			}
    			
    			if(e2 >= b2)
    				*x = *e1 - *e2 - 1;
    			else
    				*x = *e1 -1;
    			++x;
    		} else {
    			*x = *e1 - *e2;
    			++x;
    		}
    	}
    
    	while(e1 != b1){
    		*x = *e1;
    		--e1;
    		if(e1 != b1)
    			++x;
    	}
    } else {

    	// go through the iterators backwards and place answer in x
    	while(b1 != e1 && b2 != e2){
    		--e1; --e2;
    	
    		// if the current place value of the max is less than the min
    		if(*e2 < *e1){
    			// distribute value from higher digits
    			*x = (10 + *e2) - *e1;
				--e1; --e2; ++x;
    		
    			while(*e2 == 0){
    				*x = 9 - *e1;
    				--e1; --e2; ++x;
    			}
    			
    			if(e1 >= b1)
    				*x = *e2 - *e1 - 1;
    			else
    				*x = *e2 -1;
    			++x;
    		} else {
    			*x = *e2 - *e1;
    			++x;
    		}
    	}
    
    	while(e2 != b2){
    		*x = *e2;
    		--e2;
    		if(e2 != b2)
    			++x;
    	}
    }
    
    // get rid of leading zeros
    while(xb != (x-1) && *(x-1) == 0)
    	--x;
    
    reverse(xb,x); 	
    return x;}

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
template <typename II1, typename II2, typename OI>
OI multiplies_digits (II1 b1, II1 e1, II2 b2, II2 e2, OI x) {
    
    OI xb = x;
    II2 e2c = e2;
    int count1 = 0;
    while(e1 != b1){
    	--e1;
    	
    	int count2 = 0;
    	e2 = e2c;
    	while(e2 != b2){
    		--e2;
    		
    		if(count1 == 0 || e2 == b2)
    			*(xb + count1 + count2) = *e1 * *e2;
			else
    			*(xb + count1 + count2) += *e1 * *e2;
    		++count2;
    	}
    	x = xb + count1 + count2;
    	++count1;
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
	
    reverse(xb,x);
    return x;}

// --------------
// divides_digits
// --------------

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
template <typename II1, typename II2, typename OI>
OI divides_digits (II1 b1, II1 e1, II2 b2, II2 e2, OI x) {
    // <your code>
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

        C _x; // the backing container
        // <your data>
        int is_negative = false;

    private:
        // -----
        // valid
        // -----

        bool valid () const { // class invariant
            return 1;}//all_of(this->_x.begin(), this->_x.end(), ::isdigit);}

    public:
        // ------------
        // constructors
        // ------------

        /**
         * <your documentation>
         */
        Integer (int value) {
            
            if(value < 0)
                this->is_negative = true;
            value = ::abs(value);
            do {
                int to_insert = value % 10;
                value /= 10;
                typename C::iterator it = this->_x.begin();
                this->_x.insert(it,to_insert);
                cout << *this->_x.begin() << endl;
            } while(value != 0);
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
            if((this->is_negative == false && rhs->is_negative == false) || 
                (this->is_negative == true && rhs->is_negative == true))
                this->is_negative = false;
            else
                this->is_negative = true;

            // still shit to do
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
            C copy = this->_x;
            //int i;
            //for(i = 0; i < e; ++i)
                //this->_x *= copy;
            return *this;}};

#endif // Integer_h
