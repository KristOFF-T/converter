#pragma once

#include <iostream>
#include <vector>
#include <cmath>

#ifndef k
#define k
namespace k {



std::string normalNums = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

std::vector<std::string> mayanNums = {
    "(|) ",          " o  ",               "o o ",                "ooo ",                  "oooo",                  // 0,  1,  2,  3,  4
    "=== ",          " o\n=== ",           "o o\n=== ",           "ooo\n=== ",             "oooo\n=== ",            // 5,  6,  7,  8,  9
    "===\n===",      " o\n===\n=== ",      "o o\n===\n=== ",      "ooo\n===\n=== ",        "oooo\n===\n=== ",       // 10, 11, 12, 13, 14
    "===\n===\n===", " o\n===\n===\n=== ", "o o\n===\n===\n=== ", "ooo\n===\n===\n=== ",   "oooo\n===\n===\n=== ",  // 15, 16, 17, 18, 19
};

std::vector<std::string> splitStr(std::string str, char sc) {
    std::vector<std::string> strVec = {};
    std::string nStr = "";

    for(char c : str) {
        if(c == sc) {
            strVec.push_back(nStr);
            nStr = "";
        } else {
            nStr.push_back(c);
        }
    }
    strVec.push_back(nStr);
    return strVec;
}//splitStr

std::vector<std::string> shadoksNums = {
    "GA", "BU", "ZO", "MEU" 
    //0     1     2     3 
};

// get user input
std::string input(std::string txt) {
    std::cout << txt;
    std::string tinput;
    std::cin >> tinput;
    return tinput;
}
// int converted input
int inputInt(std::string displayStr) {
    return std::stoi(input(displayStr));
}

// to make things easier to read
void print(std::string txt) {
    std::cout << txt << '\n';
}

// reverse a string
std::string revStr(std::string txt) {
    std::string newTxt;
    for(int i=txt.size()-1; i>=0; i--) {
        newTxt += txt[i];
    }
    return newTxt;
}//revStr

// get intex from the "nums" string
int getI(char c) {
    for(int i=0; i<normalNums.length(); i++) {
        if(c == normalNums[i]) {
            return i;
        }
    }
    return -1;
}//getI

int c2dn(std::string num, int ns) {
    int64_t value = 0;
    if(ns == 10) {
        value = std::stoll(num);
    } else {
        std::string rev = revStr(num);
        int length = num.length();
        int val = 1;
        for(int i=0; i<length; i++) {
            char c = rev[i];
            
            int cv = getI(c);
            
            cv *= val;
            //std::cout << cv << '\n';
            value += cv;
            val *= ns;
        }
    }
    return value;
}//c2dn

std::vector<int> getIntVec(int num, int ns) {
    std::vector<int> intVec = {};
    int64_t temp = num;

    for(int64_t count = 1; temp > 0 || count == 1; count++) {
        int cpow = pow(ns, count);
        int ppow = pow(ns, count-1);
        int rem = temp % cpow;
        int d = rem / ppow;

        temp -= rem;
        intVec.push_back(d);
    }

    return intVec;
}//getIntVec

// formats (1,2,3): normal, mayan, shadoks

std::string convertIntVec(std::vector<int> intVec, int ns, int format) {
    std::string result = "";

    if(format == 1) {
        std::string resultRev = "";
        for(int i : intVec) {
            resultRev += normalNums[i];
        }
        result = revStr(resultRev);

    } else if(format == 2 || format == 3) {
        format == 2 ? result = "\n" : result = "";

        for(int n=intVec.size()-1; n>-1; n--) {
            int i = intVec[n];
            if(format == 2) {
                result += mayanNums[i] + '\n';
            } else {
                result += shadoksNums[i] + ' ';
            }
        }
    }

    return result;
}// convertIntVec


} // namespace k


#endif