#include <iostream>
#include <vector>
#include <cmath>
#include <stdlib.h>

#include "second.hpp"

std::string convert(int ins, int ons, std::string num, int format) {
    std::string result;

    int64_t value = c2dn(num, ins);
    std::vector<int> intVec = getIntVec(value, ons);

    result = convertIntVec(intVec, ons, format);

    return result;
}

std::string lister(int ns, int start, int end, int step, int format) {
    std::string numStr, outStr;
    bool done;
    for(int i=start; i<end; i += step) {
        numStr = convert(10, ns, std::to_string(i), format);
        
        std::string indexStr = std::to_string(i)+": ";
        while(indexStr.length() < std::to_string(end).length()+2) indexStr.push_back(' ');
        outStr += indexStr + numStr + "\n";

        
        if(outStr.length() > 20000) {
            std::cout << outStr;
            outStr = "";
        }
    }

    return outStr;
}

// main function
int main() {
    int mode;
    while(1) {
        std::cout
            << "What would you like to do?" << '\n'
            << "1: Convert numbers"    << '\n'
            << "2: List numbers"       << '\n'
            << "3: Convert colors"     << '\n';

        mode = inputInt("a: ");
        
        if(mode == 1 || mode == 2) {
            int ns, start, end, step,
            ins, ons, format, maxNs = normalNums.length();
            // get valid format
            while(1) { 
                std::cout << '\n'
                    << "1: normal"  << '\n' 
                    << "2: mayan"   << '\n'
                    << "3: shadoks" << '\n';
                
                format = inputInt("format: ");
                std::cout << '\n';
                if(format > 3 || format < 1) continue;

                if(format == 1) {
                    if(mode == 1) {
                        while(1) {
                            print("(2 <= NS <= " + std::to_string(maxNs) + ')');
                            ins = std::stoi(input("input  ns: "));
                            ons = std::stoi(input("output ns: "));
                            if(ins > 1 && ins < maxNs+1 && ons > 1 && ons < maxNs+1) {
                                break;
                            }
                        }
                    } else if(mode == 2) 
                        ns = std::stoi(input("ns: "));
                } else if (format == 2) {
                    ns = 20;
                    ins = 10;
                    ons = 20;
                } else if(format == 3) {
                    ns = 4;
                    ins = 10;
                    ons = 4;
                }
                break;
                
            }

            // main loop
            while(1) {
                // convert mode
                if(mode == 1) {
                    std::string num = input("n: ");
                    std::string result = convert(ins, ons, num, format);

                    print("a: " + result + '\n');

                // list mode
                } else if(mode == 2) {
                    start = inputInt("Start: ");
                    end = inputInt("End: ");
                    step = inputInt("Step: ");
                    std::string outStr = lister(ns, start, end, step, format);
                    print(outStr + "\n\n");
                }
            }


        // color converter
        } else if(mode == 3) {

            // get convert mode
            int convertMode = 0;
            while(1) {
                std::cout << '\n';
                std::cout << "Select convert mode!" << '\n'
                          << "1: rgb to hex"        << '\n'
                          << "2: hex to rgb"        << '\n';
                convertMode = inputInt("mode: ");
                std::cout << '\n';
                if(convertMode == 1 || convertMode == 2) 
                    break;
            }



            // main loop
            while(1) {
                if(convertMode == 1) {
                    bool validRGB = false;
                    std::vector<int> rgb = {0, 0, 0};
                    while(!validRGB) {
                        validRGB = true;
                        std::string inputStr = input("rgb: ");
                        std::vector<std::string> rgbStr = splitStr(inputStr, ',');
                        if(rgbStr.size() != 3) validRGB = false;
                        
                        for(int i=0; i<3; i++) {
                            rgb[i] = std::stoi(rgbStr[i]);
                        }

                        for(int v : rgb) {
                            
                            if(v < 0 || v > 255)
                                validRGB = false;

                        }
                    }

                    std::string result = "# ";

                    for(int v : rgb) {
                        std::string newStr = convert(10, 16, std::to_string(v), 1);
                        if(newStr.length() < 2) newStr = '0' + newStr;
                        result += newStr;
                    }

                    std::cout << "hex: " << result << "\n\n";

                } else { // convertMode == 2
                    std::string hexStr;
                    while(1) {
                        hexStr = input("hex: # ");
                        if(hexStr.length() == 6) break;
                    }
                    
                    std::vector<int> rgb = {0, 0, 0};
                    std::vector<std::string> hexRgb = {"", "", ""};

                    for(int i=0; i<3; i++) {
                        std::string v = "";
                        v = v + hexStr[i*2];
                        v = v + hexStr[i*2+1];
                        //std::cout << v << '\n';
                        hexRgb[i] = v;
                    }
                    //std::cout << "hex: " << hexRgb[0] << ' ' << hexRgb[1] << ' ' << hexRgb[2] << '\n';

                    for(int i = 0; i<3; i++) {
                        int v = c2dn(hexRgb[i], 16);
                        //std::cout << v << '\n';
                        rgb[i] = v;
                    }

                    std::cout << "rgb: " << rgb[0] << "," << rgb[1] << "," << rgb[2] << "\n\n";
                }
            }
        }
    }

    return 1;
}
