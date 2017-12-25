#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <vector>
#include <iterator>
#include <cmath>
#include <string>

void interface( std::vector<std::string> &test );
void handle( std::vector<std::string>::iterator ptr,
             int num1, int num2, int &ans );
int checkcmd( std::string str );

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
    std::vector<std::string>::iterator it;

    // read the file while we have input.
    while (in >> s) {
      first.push_back(s);
    }
    if ( first.size() > 0 ) interface(first);
    for ( it = first.begin(); it != first.end(); it++ )
      std::cout << *it << std::endl;
    in.close();
}
void interface(std::vector<std::string> &test) {
  //General pointers for the vector
  std::vector<std::string>::iterator start, ptr, end;
  //Saves the pointer to no. of repeats for each reccuring repeat
  std::vector<std::vector<std::string>::iterator> repit;
  //Ptr to recurring repeats
  std::vector<std::vector<std::string>::iterator>::iterator curst;
  std::vector<std::string> reparray;
  //std::vector<std::string> array;
  ptr = start = test.begin();
  end = test.end();
  int eos = 1;
  int num1, num2, ans, currep = 0, repeat = 0, noofrep = 0;
  while ( eos ) {
    if ( checkcmd(*ptr) ) {
        if ( *ptr == "repeat" ) {
          repeat = 1;
          currep = 1;
          noofrep = stoi(*(ptr-1));
          repit.push_back(ptr-1); //Save the ptr location to repeat
          for (ptr = ptr + 1; *ptr != "endrepeat"; ptr++ ) {
            reparray.push_back(*ptr);
            if ( *ptr == "repeat" ) { //If there is an imbedded repeat
              reparray.clear();
              noofrep = stoi(*(ptr-1));
              repit.push_back(ptr-1);
              currep++;
            }
          }
          curst = repit.begin(); //Use to point to the current repeat
          //Point to most recent repetition
          curst = curst + currep - 1; //Array starts from 0 hence -1
          std::cout << &(*ptr) << " " << &(**curst) << std::endl;
          ptr = *curst;
          //erase the repeat and no. of repeat statements
          test.erase(ptr, ptr + 2);
          while ( !checkcmd(*ptr) ) ptr++;
        }
        if ( *ptr != "endrepeat" ) {
          if ( (ptr - 1) >= start) num1 = stoi(*(ptr - 1));
          if ( (ptr - 2) >= start) num2 = stoi(*(ptr - 2));
          handle(ptr, num1, num2, ans);
          std::string anss = std::to_string(ans);
          test.erase(ptr - 2, ptr+1);
          test.insert(ptr - 2, anss);
        }
        if ( *ptr == "endrepeat" && repeat == 1) {
          noofrep--;
          if ( noofrep != 0 )
            test.insert(start+1, reparray.begin(), reparray.end());
          if ( noofrep == 0 ) {
            repeat = 0;
            currep--;
            reparray.clear();
            test.erase(ptr, ptr+1);
            repit.pop_back();
          }
        }

        if ( currep > 0 && repeat == 0 ) {
          curst--;
          ptr = *curst;
          if ( ptr - 1 > test.begin() ) start = ptr - 1;
          else start = test.begin();
        }
        else {
          if ( noofrep > 0 ) {
            ptr = *curst - 1;
            start = ptr;
          }
          else {
            ptr = test.begin();
            start = ptr + 1;
          }
        }
    }
    end = test.end();
    ptr++;
    if ( ptr == end ) eos = 0;
  }

}

void handle(std::vector<std::string>::iterator ptr, int num1,
  int num2, int &ans) {

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
