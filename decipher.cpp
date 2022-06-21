#include "bigint.h"
#include <iostream>
#include <fstream>
using namespace std;


int main(int argc, char* argv[]) {
	if (argc != 2) {
		cout<<"\033[1;41m----Missing an argument----\033[0m"<<endl;
	  cout << "Usage: ./decipher <file>"<<endl;
	  cout << "Examples:" << endl;
	  cout << "\t./decipher secret/message1.txt \033[1;90m//to decipher message 1\033[0m" << endl;
	  cout << "\t./decipher secret/message2.txt \033[1;90m//to decipher message 2\033[0m"<<endl;
		return -1;
	}

  //owuld they be bigint or int
  int base = 0;
  string privateKey;
  string mod;
  BigInt d;
  BigInt n;
  BigInt result;

  ifstream readIn(argv[1]);
  readIn >> base >> privateKey >> mod;
  try{
     d = BigInt(privateKey,base);
     n = BigInt(mod, base);
  }
  catch(exception& e){
    cout << e.what() << endl;
    return -1;
  }
  string temp;
  readIn >> temp;
  while(!readIn.fail()){
    try{
    BigInt secret_code(temp,base);
    result = modPow(secret_code,d,n);
    }
    catch(exception& e){
      cout << e.what() << endl;
    return -1;
    }
   
    cout << (char)result.to_int();
    readIn >> temp;
  }
  cout << endl;
  readIn.close();
	return 0;
}
