#include "bigint.h"
#include <iostream>
#include <fstream>
using namespace std;


int main() {

    // custom testing
    //BigInt one("-10000000000000000000000000000000000000000000000000000000000000000", 2);
    //BigInt two("-1",2);
    //  BigInt tes("1765150783540087597715532421333357225424178687",10);
    BigInt one("10",2);
    BigInt two("1001000", 2);
    BigInt sum = pow(one,two);


     //cout << sum.to_int() <<endl;
    //BigInt one("37",10);
    //BigInt two("1260257",10);
    //BigInt sum = two/one;
    cout << sum.to_string() <<endl;

    // BigInt a("123456789ABCDEF0",16);
    // a.printVecItems();//should print [0,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1]
    // cout<<boolalpha<<a.getSign()<<endl;//should print true (positive)
    // cout<<a.getBase()<<endl;//16
    // BigInt b("-123456789ABCDEF0",32);
    // b.printVecItems();//should print [0,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1]
    // cout<<boolalpha<<b.getSign()<<endl;//should print false (negative)
    // cout<<b.getBase()<<endl;
    // BigInt c("DADBEEF",16);
    // BigInt d("-2022",10);
    // d.printVecItems();//should print [2,2,0,2]
    // cout<<boolalpha<<d.getSign()<<endl;//false
    // cout<<d.getBase()<<endl;//10
    // d = c;
    // d.printVecItems();//should print [5,14,14,11,13,10,13]
    // cout<<boolalpha<<d.getSign()<<endl;//true (positive)
    // cout<<d.getBase()<<endl;//16
    // BigInt f(-123456789,10);
    // f.printVecItems();//should print [9,8,7,6,5,4,3,2,1]
    // cout<<boolalpha<<f.getSign()<<endl;//false
    // cout<<f.getBase()<<endl;//10
    // BigInt g(123456789,16);
    // g.printVecItems();//should print [5,1,13,12,11,5,7]
    // cout<<boolalpha<<g.getSign()<<endl;//true
    // cout<<g.getBase()<<endl;//16
	return 0;
}
