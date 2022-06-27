#include <iostream>
#include <vector>
#include <cmath>
#include <stdlib.h>

#include "second.hpp"

// main function
int main() {
    int mode;
    while(1) {
        std::cout
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
                
                format = inputInt("a: ");
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
            int cm1 = 0;
            int cm2 = 0;
            while(1) {
                std::cout << '\n';
                std::cout << "1: RGB"        << '\n'
                          << "2: HEX"        << '\n'
                          << "3: CMYK"       << '\n'
                          << "4: HSV"        << '\n'
                          << "5: HSL"        << '\n';

                cm1 = inputInt("input:  ");
                cm2 = inputInt("output: ");
                std::cout << '\n';
                if((cm1 > 0 && cm1 < 5+1) && (cm2 > 0 && cm2 < 5+1)&& cm1 != cm2) 
                    break;
            }

            // main loop
            while(1) {
                std::vector<int> rgb = {0,0,0};
                if(cm1 == 1) {
                    rgb = getValidRGB();

                } else if(cm1 == 2) {
                    std::string hexStr = getValidHEX();
                    rgb = HEX2RGB(hexStr);

                } else if(cm1 == 3) {
                    std::vector<int> cmyk = getValidCMYK();
                    //std::cout << "cmyk: " << cmyk[0] << ',' << cmyk[1] << ',' << cmyk[2] << ',' << cmyk[3] << '\n';
                    rgb = CMYK2RGB(cmyk);

                } else if(cm1 == 4) {
                    std::vector<int> hsv = getValidHS('V');
                    rgb = HSV2RGB(hsv);
                    //std::cout << rgb[0] << '\n';
                } else if(cm1 == 5) {
                    std::vector<int> hsl = getValidHS('L');
                    rgb = HSL2RGB(hsl);
                    
                    
                }



                if(cm2 == 1) {
                    std::cout << "RGB: " << rgb[0] << "," << rgb[1] << "," << rgb[2];

                } else if(cm2 == 2) {
                    std::string hex = RGB2HEX(rgb);
                    std::cout << "HEX: # " << hex;

                } else if(cm2 == 3) {
                    std::vector<int> cmyk = RGB2CMYK(rgb);
                    std::cout << "CMYK: " << cmyk[0] << ',' << cmyk[1] << ','
                                          << cmyk[2] << ',' << cmyk[3];

                } else if(cm2 == 4) {
                    std::vector<int> hsv = RGB2HSV(rgb);
                    std::cout << "HSV: " << hsv[0] << ',' << hsv[1] << ',' << hsv[2];
                
                } else if(cm2 == 5) {
                    std::vector<int> hsl = RGB2HSL(rgb);
                    std::cout << "HSL: " << hsl[0] << ',' << hsl[1] << ',' << hsl[2];

                }

                std::cout << "\n\n";
            }
        }
    }

    return 1;
}
