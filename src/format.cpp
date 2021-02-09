#include <string>
#include<iomanip>
#include<sstream>
#include<iostream>

#include "format.h"
using namespace std;
using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    int ss=seconds%60;
    int tot_min=seconds/60;
    int hh=tot_min/60;
    int mm=tot_min%60;
    stringstream sts;
    sts<<setw(2)<<setfill('0')<<hh<<":"<<setw(2)<<setfill('0')<<mm<<":"<<setw(2)<<setfill('0')<<ss;
    string res;
    sts>>res;
    return res;
}