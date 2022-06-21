#include "bigint.h"
#include <iostream>
#include <string>
#include <climits>
#include <cmath>
using namespace std;


//START OF THE CONSTRUCTORS SECTION


// Create a default BigInt with base 10.

BigInt::BigInt(){
  base = 10;
  isPositive = true;
}


// Create a BigInt with a specified base.

BigInt::BigInt(int setbase){
    if(setbase < 2 || setbase > 36){
        throw InvalidBaseException();
    }
    base = setbase;
    isPositive = true;
}


// Destructure. 

BigInt::~BigInt(){}


//  Create a BigInt from string.

BigInt::BigInt(const string &s, int setbase){
    if(setbase < 2 || setbase > 36){
        throw InvalidBaseException();
    }
    //place holder
    //sign of number
    base = setbase;
    int temp;
    //iterate through to string and add each value to vetor as int
    isPositive = true;
    for(int i  = s.length()-1; i >=0;i--){
        //perfrom artihmitic on string and push int value to vec
      if(s[i] == '-' && i == 0 ){
        isPositive = false;
        continue;
      }
      if(int(s[i])> 57)
      {
        //Match -55 for letters 
        temp = s[i]- 55;
        vec.push_back(temp);
      }
      else
      {
        temp = s[i]- 48;
        vec.push_back(temp);
      }
    }
}



//  Create a BigInt from int (base 10).

BigInt::BigInt(int input,int setbase){
    if(setbase < 2 || setbase > 36){
        throw InvalidBaseException();
    }

//set base
base  = setbase;
long long int rem;

if(input < 0 ){
  isPositive = false;
}
else{
  isPositive= true;
}
input = abs(input);
if(input == 0){
  vec.push_back(input);
}

while(input > 0)
{
  rem = input%base;
  vec.push_back(rem);
  input = input/base;
}
}


//  Create a BigInt from another BigInt.

BigInt::BigInt(const BigInt &b){

 *this = b;
}


//  Assignment operator. (i.e., BigInt a = b;)
//       - vec
//       - isPositive
//       - base

BigInt & BigInt::operator = (const BigInt &b){

    //this->vec
  (*this).vec = b.vec;
  (*this).isPositive = b.isPositive;
  (*this).base = b.base;

  return *this; 
}

//******************************************************************
//END OF THE CONSTRUCTORS SECTION
//******************************************************************

//******************************************************************
//START OF THE DISPLAYS SECTION
//******************************************************************


// Convert to string and return the string
// Display it in its corresponding base

string BigInt::to_string(){

string temp = "";
char current;

for( int i = vec.size()-1; i >= 0; i--){
  //check for base 16 letters
  if(vec[i] >= 10){
    current = char(vec[i]+55);
    temp += current;
  }
  else{
    current = (char)(vec[i]+48);
    temp += current;
  }
  //cout << vec[i];
}
if(isPositive == false){
  temp ='-'+temp;
}

  return temp;//for now
}


//  Convert BigInt to integer base 10 and return that int

int BigInt::to_int() const{
    
int size = (*this).vec.size();
long long int val = 0;
for(int i = 0; i < size; i++){
  val += vec[i]* pow(((*this).base),i);
   if(val >= INT_MAX){
    break;
  }
}
// INT_MIN = -2147483648
// INT_MAX = 2147483647
if(isPositive){
  if(val >= INT_MAX){
    return INT_MAX;
  } 
}
else{
  if(val > INT_MAX){
    return INT_MIN;
  }
  else{
    val *= -1;
  }
}
  return val;
}
//******************************************************************
//END OF THE DISPLAYS SECTION
//******************************************************************

//******************************************************************
//START OF THE EQUALITY CHECK OPERATORS SECTION
//******************************************************************


//  Compare a and b.
//     If a = b, return 0.
//     If a < b, return -1.
//     If a > b, return 1.

int BigInt::compare(const BigInt &b) const{
    if(base != b.base){
        cout <<"COMPAREEXCEPTION" << endl;
        cout << base << endl;
        cout << b.base << endl;
        throw DiffBaseException();
    }
    
    //First let's compare the signs
    //    - if the signs aren't the same,
    //              how do you know which one is larger?

    //If they have the same sign, let's compare their vec sizes 
    //    - what if both are positive, but a's vec is larger (a or b is larger?)
    //    - other cases?
    
    //If they have the same vec size, let's compare their digits one by one
    // Starting from the most-significant digits. --> in what vector position?
    
    if((*this).isPositive != b.isPositive){
      if(b.isPositive){
        return -1;
      }
      else{
        return 1;
      }
    }
    
    if(((*this).vec.size() != b.vec.size())){
        
        if(b.isPositive || isPositive){
        if(((*this).vec.size() > b.vec.size())){
          return 1;
        }
        else{
          return -1;
        }
        }
        else{
          if(((*this).vec.size() < b.vec.size())){
          return 1;
        }
        else{
          return -1;
          }
        }
      }
    for(int i = ((*this).vec.size()-1); i >= 0;i--){
          //if first digit is greater than that numver is larger
          if(b.isPositive){
            if((*this).vec[i] > b.vec[i]){
            return 1;
            }
            else if((*this).vec[i] < b.vec[i]){
              return -1;
              }
          }
          else{
            if((*this).vec[i] < b.vec[i]){
            return 1;
            }
            else if((*this).vec[i] > b.vec[i]){
              return -1;
              }
          }
          
        } 
    return 0;
}


//Call the compare function above to check if a == b
bool operator == (const BigInt &a, const BigInt &b){

  int result = a.compare(b);
  if(result == 0){
    return true;
  }
 return false;//for now
}

//Call the compare function above to check if a != b
bool operator != (const BigInt &a, const BigInt &b){

  int result = a.compare(b);
  if(result != 0){
    return true;
  }
  return false;//for now
}

//Call the compare function above to check if a <= b
bool operator <= (const BigInt &a, const BigInt &b){
  
  int result = a.compare(b);
  if(result == 0 || result == -1){
    return true;
  }
  return false;//for now
}

//Call the compare function above to check if a >= b
bool operator >= (const BigInt &a, const BigInt &b){
   
 int result = a.compare(b);
  if(result == 0 || result == 1){
    return true;
  }
  return false;//for now
}

//Call the compare function above to check if a > b
bool operator > (const BigInt &a, const BigInt &b){
  int result = a.compare(b);
  if(result == 1){
    return true;
  }
  return false;//for now
}

//Call the compare function above to check if a < b
bool operator < (const BigInt &a, const BigInt &b){
  int result = a.compare(b);
  if(result == -1){
    return true;
  }
  return false;//for now
}

//******************************************************************
//END OF THE EQUALITY CHECK OPERATORS SECTION
//******************************************************************

//******************************************************************
//START OF THE ARITHMETIC OPERATORS SECTION
//******************************************************************

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call += operator on the copy and b
// 3. Return the copy
*/
BigInt operator + (const  BigInt &a, const BigInt & b){

  BigInt copA = a;
  copA+=b;
  return copA;
}

/*
//==================
// MEMBER function
//==================
//  Addition assignment operator.
*/
const BigInt & BigInt::operator += (const BigInt &b){
    if(base != b.base){
      cout <<"+EXCEPTION" << endl;
        cout << base << endl;
        cout << b.base << endl;
        throw DiffBaseException();
    }
  //equal signs
   if((isPositive && b.isPositive) || (!isPositive && !b.isPositive)){
    int carry= 0;
    for(unsigned int i = 0; i < max((vec.size()), (b.vec.size()));i++){
        //inside for loop to reset eachc iteration
        int total = 0;
        int valA= 0;
        int valB = 0;
        
        if(i < vec.size()){
          valA = vec[i];
        }
        // value is "0"
        else{
          valA = 0;
        }
        if(i < b.vec.size()){
          valB = b.vec[i];
        }
        else{
          valB = 0;
        }
      total = valA + valB + carry;
      carry = total/base;
      if(i < vec.size()){
        vec[i] = total%base;
      }
      else{
        vec.push_back(total%base);
      }
    }
  if(carry != 0){
    vec.push_back(carry);
  }
}
  //signs are not the same, so a+(-b) == a-b
  else if(isPositive != b.isPositive){
    if(isPositive){
      BigInt temp = b;
      temp.isPositive = !temp.isPositive;//
      *this -= temp;
      // if(vec.size() == 1 && vec[0] == 0){
      //   isPositive = true;
      // }
    }
    else{
      //switch -a to a
      isPositive = !isPositive;
      *this -= b;
      if(vec.size() == 1 && vec[0] == 0){
        isPositive = true;
      }
      else{
        isPositive = !isPositive;
      }
    }
  }
  return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call -= operator on the copy and b
// 3. Return the copy
*/
BigInt operator - (const  BigInt &a, const BigInt & b){

  BigInt copA = a;
  copA-=b;
  return copA;
}
/*
//==================
// MEMBER function
//==================
//  Subtraction assignment operator.
//    i.e., a -= b
*/
const BigInt & BigInt::operator -= (const BigInt &b){
    if(base != b.base){
      cout <<"MINUSEXCEPTION" << endl;
        cout << base << endl;
        cout << b.base << endl;
        throw DiffBaseException();
    }
    if(isPositive && b.isPositive){
      int carry = 0;
      BigInt copyofA  = *this;
      for(unsigned int i = 0; i < max(vec.size(), b.vec.size());i++){
        int top = 0;
        int bottom = 0;
        int total = 0;

        if((*this < b && isPositive) || (*this >= b &&!isPositive)){
          if(i < vec.size()){
            bottom = vec[i];
          }
          if(i < b.vec.size()){
            top = b.vec[i];
          }
        }
        else{
          if(i < vec.size()){
            top = vec[i];
          }
          if(i < b.vec.size()){
            bottom = b.vec[i];
          }
        }
        total = top - bottom + carry + base;
        carry = total/base -1;
        if(i < vec.size()){
          vec[i] = total % base;
        }
        else{
          vec.push_back(total % base);
        }
      }
      isPositive = copyofA >= b;
      int size = vec.size()-1;
      while(vec[size] == 0 && size > 0){
        vec.pop_back();
        size--;
      }
    }
    else{
      if(isPositive){
        BigInt temp = b;
        temp.isPositive = true; // 
        *this += temp;
        if((vec.size() == 1)&& (vec[0] == 0)){
          isPositive = true;
        } 
      }
      else{
        isPositive = true;
        *this += b;
        if(vec.size() == 1 && vec[0] == 0){
          isPositive = true;
        } 
        else{
          isPositive = !isPositive;
        }
      }
    }
  return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call *= operator on the copy and b
*/
BigInt operator * (const  BigInt &a, const BigInt & b){

  BigInt copA = a;
  copA*=b;
  return copA;
  return a;//for now
}



/*
//==================
// MEMBER function
//==================
//  Multiplication assignment operator.
//    i.e., a *= b
//  Implement Long Multiplication
*/
const BigInt & BigInt::operator *= (const BigInt &b){
    if(base != b.base){
      cout <<"MULTIPLY EXCEPTION" << endl;
        cout << base << endl;
        cout << b.base << endl;
        throw DiffBaseException();
    }
  //base cases
  BigInt zeroS(0,base);
  if(*this == zeroS || b == zeroS){
    BigInt zero("0", base);
    *this = zero;
    return *this;
  }
  if(this->to_int() == 1 || b.to_int() == 1){
    if(this->to_int() == 1){
      *this = b;
      return *this;
    }
    else{
      return *this;
    }
  }
  /////
  BigInt total("0",base); ///??
  int carry = 0;
  for(unsigned int i = 0; i < b.vec.size(); i++){
    //create a bigint with no value;
    BigInt temp(base);//??
    for(unsigned int j = 0; j <i;j++){
      temp.vec.push_back(0);// how do i do push vec i times
    }
    for(unsigned int k = 0; k < vec.size();k++){
      int product = b.vec[i] * vec[k] + carry;
      carry = product/base;
      temp.vec.push_back(product%base);
    }
    if(carry != 0){
      temp.vec.push_back(carry);
    }
    total += temp;
    carry  = 0;
  }
  
  if((isPositive && !b.isPositive) || (!isPositive && b.isPositive)){
    total.isPositive = false;
  }
  if(!isPositive && !b.isPositive){
    total.isPositive = true;
  }
  *this = total;
  return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call /= operator on the copy and b
*/
BigInt operator / (const  BigInt &a, const BigInt & b){

  BigInt copA = a;
  copA/=b;
  return copA;
  return a;
}



/*
//==================
// MEMBER function
//==================
//  Division assignment operator.
//    - Call 'divisionMain' to get the quotient;
*/
const BigInt & BigInt::operator /= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    if(b.vec.size() == 1 && b.vec[0] == 0){
        throw DivByZeroException();
    }
  BigInt quotient(base);
  BigInt remainder(base);//
  divisionMain(b, quotient, remainder);
  *this = quotient;
  return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call %= operator on the copy and b
*/
BigInt operator % (const  BigInt &a, const BigInt & b){

  BigInt copA = a;
  copA%=b;
  return copA;
}
  
   



/*
//==================
// MEMBER function
//==================
//  Modulus assignment operator.
//    - Call 'divisionMain' to get the remainder;
//    - Note: remainder takes the sign of the dividend.
*/
const BigInt & BigInt::operator %= (const BigInt &b){
    if(base != b.base){
      cout <<"MODULO EXCEPTION" << endl;
        cout << base << endl;
        cout << b.base << endl;
        throw DiffBaseException();
    }
    if(b.vec.size() == 1 && b.vec[0] == 0){
        throw DivByZeroException();//divide by zero.
    }
    
  BigInt quotient(0,base);
  BigInt remainder(0,base);
  divisionMain(b, quotient, remainder);
  *this = remainder;
  return *this;
}

/*
//  Main function for the Division (/=) and Modulus (%=) operators.
//     - Compute (q)uotient and (r)emainder
//     - Implement Long Division
*/
void BigInt::divisionMain(const BigInt &b, BigInt &quotient, BigInt &remainder){

   //Handle for base cases 
    //one
    BigInt divOne(1,base);
    //one
    BigInt divZero(0,base);
    // negative one for simplicity 
    BigInt neg(-1,base);
    
    BigInt copyofA = *this;
    BigInt copyofB = b;

    copyofA.isPositive = isPositive;

    bool sign = isPositive;
    // check for sign of a and b, if -a/b or a/-b reuslt is neg
    if(isPositive != b.isPositive){
      sign = false;
    }

   if(isPositive == b.isPositive){
      sign = true;
    }
    //vlaue of 0
    if(this-> compare(divZero) == 0){
      quotient = divZero;
      remainder = divZero;
      return;
    }
    
  // if a/1 then return a
    if(b.compare(divOne) == 0){
      quotient.isPositive = sign;
      quotient = *this;
      remainder = divZero;
      return;
    }
    copyofA.isPositive = true;
    copyofB.isPositive = true;
    //base case if equal values
    if(this->compare(b) == 0){
      //positive on
      if(sign == true){
        quotient = divOne;
        remainder = divZero;
      }
      if(sign == false){
        quotient = neg;
        remainder = divZero;
      }
      return;
    }
    // same value but negative
    if(this->compare(b) == 0 && (sign != false)){
      quotient = neg;
      remainder = divZero;
      return;
    }
    
    // a<b
    if(copyofA < copyofB){
      quotient = divZero;
      remainder= *this;
      return;
    }
    int position  = vec.size()-1;
    BigInt positive_divisor = copyofB; // why doesnt = b work?
    BigInt dividend_seq(vec[position],base);
    while(dividend_seq < positive_divisor){
      position--;
      dividend_seq.vec.insert(dividend_seq.vec.begin(),vec[position]);
    }
    //values still in vector
    while(position >= 0){
      int times = 0;
      while(dividend_seq >= positive_divisor){
        dividend_seq -= positive_divisor;
        times++;
      }
      quotient.vec.insert(quotient.vec.begin(), times);
    
      if(dividend_seq == divZero){
        dividend_seq.vec.clear();
      }
      if((position-1) >= 0){
        dividend_seq.vec.insert(dividend_seq.vec.begin(), vec[position-1]);

      }
      position--;
    }
    //after everytinh quotient has proper sign - or +
    quotient.isPositive = sign;
    // dividend must be 0 for no remainders
    if(dividend_seq > divZero){//
      remainder = dividend_seq;
    }
    else{
      remainder = divZero;
      return; 
    }
    //rem for modulus is returned with correct postivity
    remainder.isPositive = isPositive;

}
///////////////////////////////////////
/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call the 'exponentiation' function on the copy and b
*/
BigInt pow(const  BigInt &a, const BigInt & b){

  BigInt copA = a;
  copA.exponentiation(b);
  return copA;
}

/*
//==================
// MEMBER function
//==================
//  Exponentiation assignment function.
//     - i.e., a.exponentiation(b);
// Note: 1. implement Exponentiation by Squaring
//       2. b should be treated as BigInt, not int or other data type.
*/
const BigInt & BigInt::exponentiation(const BigInt &b){
    if(base != b.base){
      cout <<"EXPONENTIATION" << endl;
        cout << base << endl;
        cout << b.base << endl;
        throw DiffBaseException();
    }
    if(!b.isPositive){
        throw ExpByNegativeException();
    }
 //one
  BigInt PowOne(1,base);
  //zero
  BigInt PowZero(0,base);
  //two
  BigInt two(2,base);
 //Make copies because originals causes problems 
 BigInt Power = b;
 BigInt Base = *this;
 BigInt result(1,base);

  //one if statement
  while(Power > PowZero){
    // if even
    if( (Power % two) == PowZero){
      //first square 
      Base*=Base; 
      //then divide by two
      Power /= two; // 
    }
    // odd will thise only execute once?
     else{
       //extract the base and decrement power
      result *= Base;
      Power-= PowOne;
      // Power -= PowOne;
      // PowOne*= Base;
      // Base*=Base;
      // Power /= two;
     } 
  }
  //acount for the extract if there is one, if not it is jsut answer*1
    
    *this = result;
    return *this;
} 

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call the 'modulusExp' function on the copy and b
*/
BigInt modPow(const BigInt &a, const BigInt &b, const BigInt &m){

  BigInt copA = a;
  copA.modulusExp(b,m);
  return copA;
}
/*
//==================
// MEMBER function
//==================
//  Modulus Exponentiation assignment function.
//     - i.e., a.modulusExp(b)
*/
const BigInt & BigInt::modulusExp(const BigInt &b, const BigInt &m){
    if(base != b.base || base != m.base){
      cout <<"MODULUS EXP EXCEPTION" << endl;
        cout << base << endl;
        cout << b.base << endl;
        throw DiffBaseException();
    }
    if(!b.isPositive){
        throw ExpByNegativeException();
    }
 BigInt copyofA = *this;
 BigInt copyofB = b;
 BigInt copyofM = m;
 //one
  BigInt PowOne(1,base);
  //zero
  BigInt PowZero(0,base);
  //two
  BigInt two(2,base);
 //Make copies because originals causes problems 
 BigInt Power = copyofB;
 BigInt Base = copyofA;
 BigInt extract = PowOne;
 BigInt Mod = copyofM;
 //handle base cases
  
  if(Power == PowZero){
    *this = PowOne;
    return *this;
  }
  if(Power == PowOne){
    Base%=Mod;
    *this = Base;
    return *this;
  }
  
  //one while loop 
  //one if statement
  while(Power > PowOne){//
    // if even
    if(Power % two == PowZero){
      //first square 
      Base*=Base; 
      Base%=Mod;
      //then divide by two
      Power /= two;
    }
    // odd will thise only execute once?
     else{
       //extract the base and decrement power
      Power -= PowOne;
      extract*= Base;
      Base*=Base;//
      Base%=Mod;
      //Base *= (Base%Mod);//
      Power /= two;
     } 
  }
  //acount for the extract if there is one, if not it is jsut answer*1
    extract *= Base;
    extract%=Mod;
    *this = extract;
   
    return *this;
}

//******************************************************************
//END OF THE ARITHMETIC OPERATORS SECTION
//******************************************************************

void BigInt::printVecItems(){
  cout<<"[";
  for(size_t i = 0;i<vec.size();i++){
    cout<<vec[i];
    if(i < vec.size()-1){
      cout<<",";
    }
  }
  cout<<"]"<<endl;
}

bool BigInt::getSign(){
	return isPositive;
}

int BigInt::getBase(){
	return base;
}
//******************************************************************
//END OF SANITY CHECKS SECTION
//******************************************************************