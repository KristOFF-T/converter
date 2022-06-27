#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <array>

#ifndef k
#define k
namespace k {

// ez fejből
#define PI 3.141592653589793238462

int vecMax(std::vector<int> vec) {
    int max = vec[0];
    for(int i=1; i<vec.size(); i++) {
        if(vec[i] > max)
            max = vec[i];
    }

    return max;
}

int vecMin(std::vector<int> vec) {
    int min = vec[0];
    for(int i=1; i<vec.size(); i++) {
        if(vec[i] < min)
            min = vec[i];
    }

    return min;
}

float modulo(float szam, int n) {
    return ((int)(szam*100) % (n*100)) / 100.0f;
}

float pdv(float n1, float n2) {
    float fraction = n1 / n2;
    return (fraction * 100.0f);
}

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

int64_t c2dn(std::string num, int ns) {
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

// get color ==================================
std::vector<int> getValidRGB() {
    std::vector<int> rgb;
    while(1) {
        rgb.clear();
        std::vector<std::string> rgbStr = splitStr(input("rgb: "), ',');
        for(std::string v : rgbStr) {
            rgb.push_back(std::stoi(v));
        }
        bool valid = (rgb.size() == 3);
        for(int i=0; i < 3 && valid; i++) {
            if(rgb[i] < 0 || rgb[i] > 255)
                valid = false;
        }
        if(valid)
            break;
    }
    return rgb;
}

std::string getValidHEX() {
    std::string hex = "";
    bool valid = false;
    while(!valid) {
        valid = true;
        hex = input("hex: # ");
        if(hex.length() != 6)
            break;

        for(char v : hex) {
            if(getI(v)==-1||getI(v)>15)
                valid = false;
        }
    }
    return hex;
}

std::vector<int> getValidCMYK() {
    std::vector<int> cmyk;
    bool valid = false;
    while(!valid) {
        valid = true; // It's true. Change my mind!
        std::vector<std::string> strVec = splitStr(input("CMYK: "), ',');
        if(strVec.size()!=4)
            valid = false; // Did I changed your mind? Yes.

        for(std::string str : strVec) {
            int val = std::stoi(str);
            if(val < 0 || val > 100)
                valid = false; // Did I changed your mind? Yes.

            cmyk.push_back(val);
            //std::cout << val << '\n';
        }
    }
    return cmyk;
}

std::vector<int> getValidHS(char hs) {
    std::vector<int> hsv;
    bool valid = false;
    while(!valid) {
        valid = true;
        std::string displayText = "HS";
        displayText.push_back(hs);
        displayText = displayText + ": ";
        std::vector<std::string> strVec = splitStr(input(displayText), ',');
        if(strVec.size()!=3) valid = false;

        for(int i=0; i<3 && valid; i++) {
            int val = std::stoi(strVec[i]);
            int max;
            i == 0 ? max=360 : max=100;
            if(val > max+1 || val < 0)
                valid = false;
            hsv.push_back(val);
        }
    }
    return hsv;
}

// convert color ====================================
// to RGB
std::vector<int> HEX2RGB(std::string hex) {
    //print(hex);
    std::vector<int> rgb;
    for(int i=0; i<3; i++) {
        std::string v;
        v.push_back(hex[i*2]);
        v.push_back(hex[i*2+1]);
        rgb.push_back(c2dn(v, 16));
        //std::cout << rgb[i] << '\n';
    }
    return rgb;
}

std::vector<int> CMYK2RGB(std::vector<int> cmyk) {
    std::vector<int> rgb;
    for(int i=0; i<3; i++) {
        int val = 255 * (100-cmyk[i]) * (100-cmyk[3]);
        val = val / 10000;
        rgb.push_back(val);
        //std::cout << rgb[i] << '\n';
    }

    return rgb;
}

std::vector<int> HSV2RGB(std::vector<int> hsv) {
    std::vector<int> rgb;
    int M = hsv[2]*255.0f/100.0f;
    std::cout << "M = " << M << '\n';
    
    int m = M * (100-hsv[1]) / 100;
    std::cout << "m = " << m << '\n';

    std::cout << "M-m = " << M-m << '\n';
    float tm = modulo((float) hsv[0]/60.0f, 2);
    int z = (M-m)*(1 - abs(tm - 1));
    std::cout << tm << '\n';
    std::cout << "z = " << z << '\n';

    //rgb = {M, z+m, m};
    
    if       (0   <= hsv[0] && hsv[0] < 60){
        rgb = {M,   z+m+2, m};

    } else if(60  <= hsv[0] && hsv[0] < 120){
        rgb = {z+m, M,   m};

    } else if(120 <= hsv[0] && hsv[0] < 180) {
        rgb = {m,   M,   z+m+2};

    } else if(180 <= hsv[0] && hsv[0] < 240) {
        rgb = {m,   z+m, M};

    } else if(240 <= hsv[0] && hsv[0] < 300) {
        rgb = {z+m+2, m,   M};

    } else if(300 <= hsv[0] && hsv[0] <= 360) {
        rgb = {M,   m,   z+m};

    }
    //std::cout << rgb[0] << '\n';
    return rgb;
}

std::vector<int> HSL2RGB(std::vector<int> hsl) {
    int H=hsl[0], S=hsl[1], L=hsl[2];
    float d = (S/100.0f)*(1-abs(0.02f*L-1)),
          m = 255*((L/100.0f)-d*0.5f),
          tm = modulo((float) H/60.0f, 2),
          x = d*(1-abs(tm-1));

    std::cout << "tm: " << tm << '\n'
              << "x:  " << x  << '\n'
              << "d:  " << d  << '\n'
              << "m:  " << m  << '\n';

    std::vector<float> frgb;
    if       (0   <= H && H < 60){
        frgb = {255*d+m, 255*x+m, m}; // right

    } else if(60  <= H && H < 120){
        frgb = {255*x+m, 255*d+m, m}; // right

    } else if(120 <= H && H < 180) {
        frgb = {m, 255*d+m, 255*x+m}; // right

    } else if(180 <= H && H < 240) {
        frgb = {m, 255*x+m, 255*d+m}; // right

    } else if(240 <= H && H < 300) {
        frgb = {255*x+m, m, 255*d+m}; // right

    } else if(300 <= H && H <= 360) {
        frgb = {255*d+m, m, 255*x+m}; // right

    }

    std::cout << "R: " << frgb[0] << ','
              << "G: " << frgb[1] << ','
              << "B: " << frgb[2] << '\n';

    return {(int) frgb[0],
            (int) frgb[1],
            (int) frgb[2]};
}


// from RGB ==================

std::string RGB2HEX(std::vector<int> rgb) {
    std::string result;

    for(int v : rgb) {
        std::string newStr = convert(10, 16, std::to_string(v), 1);
        if(newStr.length() < 2) newStr = '0' + newStr;
        result += newStr;
    }

    return result;
}

std::vector<int> RGB2CMYK(std::vector<int> rgb) {
    int R=rgb[0], G=rgb[1], B=rgb[2],
        R2=(R/2.55f),
        G2=(G/2.55f),
        B2=(B/2.55f),

        K=100.0f-vecMax({R2,G2,B2}),

        C=(100.0f-R2-K)/(100.0f-K)*100,
        M=(100.0f-G2-K)/(100.0f-K)*100,
        Y=(100.0f-B2-K)/(100.0f-K)*100;

    if(C<0) C = 0;
    if(M<0) M = 0;
    if(Y<0) Y = 0;

    std::cout << "R2: " << R2 << '\n';
    std::cout << "G2: " << G2 << '\n';
    std::cout << "B2: " << B2 << '\n';

    return {C, M, Y, K};
}

std::vector<int> RGB2HSV(std::vector<int> rgb) {
    int r = rgb[0], g = rgb[1], b = rgb[2],
        h, s, v;

    if(r+g+b == 0) return {0,0,0};

    double M = vecMax(rgb),
           m = vecMax(rgb);
    
    h = acos((r-g/2-b/2)/pow(pow(r,2)+pow(g,2)+pow(b,2)-r*g-r*b-g*b,0.5))*180/PI+1;
    if(b > g)  h = 360 - h;
    if(h < 0) h = 0;

    s = 100 - pdv(vecMin(rgb), vecMax(rgb));
    std::cout << "saturation: " << s << '\n';

    v = M*100/255;

    return {h, s, v};
}

std::vector<int> RGB2HSL(std::vector<int> rgb) {

    int M=vecMax(rgb),
        m=vecMin(rgb);
    
    double d = ((double)M-(double)m)/255;
    double H, S=0, L;

    //std::cout << "d: " << d << '\n';

    L = ((double) M + (double) m)/510;
    double t_abs;
    if(L>0)
        t_abs = abs(2*L-1);
        S = d/(1.0-t_abs);

    //std::cout << t_abs << '\n';
    //std::cout << (int)(S*100) << '\n';

    H = acos((rgb[0]-rgb[1]/2-rgb[2]/2)/pow(
        pow(rgb[0],2)+pow(rgb[1],2)+pow(rgb[2],2)
        -rgb[0]*rgb[1]-rgb[0]*rgb[2]-rgb[1]*rgb[2],0.5))*180/PI+1;

    if(rgb[2]>rgb[1])
        H = 360 - H;
    
    if(H < 0) H = 0;
    /*
    std::cout << "fhsl: " << H << ','
                          << S << ','
                          << L << '\n';

    */

    return {(int) H, (int)(S*100), (int)(L*100)};
}

} // namespace k
#endif