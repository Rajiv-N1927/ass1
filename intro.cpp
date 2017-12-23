#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <vector>
#include <iterator>
#include <cmath>
#include <string>

void interface(std::vector<std::string> test);
void handle(std::vector<std::string>::iterator st,
            std::vector<std::string>::iterator ptr,
            int &ans);
int checkcmd(std::string str);

int main(int argc, char* argv[]) {

    // setup the print out format for the precision required.
    std::cout.setf(std::ios::fixed,std::ios::floatfield);
    std::cout.precision(3);

    // open the file for reading
    std::ifstream in;
    in.open(argv[1]);

    // string to be read into
    std::string s;

    //Vector
    std::vector<std::string> first;

    // read the file while we have input.
    while (in >> s) {
      first.push_back(s);
    }
    interface(first);
    in.close();
}
void interface(std::vector<std::string> test) {
  std::vector<std::string>::iterator start, ptr, end;
  std::vector<std::string> reparray;
  //std::vector<std::string> array;
  ptr = start = test.begin();
  end = test.end();
  int eos = 1;
  int ans, repeat = 0, noofrep;
  while ( eos ) {
    if ( checkcmd(*ptr) ) {
        if ( *ptr == "repeat" ) {
          repeat = 1;
          noofrep = stoi(*(ptr-1));
          if ( !checkcmd(*(ptr-2)) && (ptr-2) >= start )
            reparray.push_back(*(ptr-2));
          for (; *ptr != "endrepeat"; ++ptr )
            reparray.push_back(*ptr);
        }
        handle(start, ptr, ans);
        std::string anss = std::to_string(ans);
        test.erase(start, ptr+1);
        test.insert(start, anss);
        ptr = test.begin();
        end = test.end();
        start = ptr+1;
    }
    std::cout << &(*ptr) << " " << &(*end) << std::endl;
    if ( ptr == end ) eos = 0;
    ptr++;
  }

}

void handle(std::vector<std::string>::iterator st,
            std::vector<std::string>::iterator ptr, int &ans) {

  int num1, num2;
  if ( (ptr - 1) >= st) num1 = stoi(*(ptr - 1));
  if ( (ptr - 2) >= st) num2 = stoi(*(ptr - 2));
  std::string toswitch = *ptr;

  if ( toswitch == "add" ) ans = num1 + num2;
  else if ( toswitch == "sub" ) ans = num1 - num2;
  else if ( toswitch == "div" ) ans = num1 / num2;
  else if ( toswitch == "mult" ) ans = num1 * num2;
  else ans = 0;

}

int checkcmd(std::string str) {
  std::string::iterator it;
  it = str.begin();
  int retval = 0;
  if ( (*it >= 65 && *it <= 90)
      || (*it >= 97 && *it <= 122) )
  { retval = 1; }
  return retval;
}
