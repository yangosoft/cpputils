#ifndef __CCPUTILS_COLORS_h__
#define __CCPUTILS_COLORS_h__

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>

/* Converted from https://github.com/antimatter15/rgb-lab/blob/master/color.js */

namespace CppUtils
{
    namespace Misc
    {
        
        using Pixel = std::array<uint8_t,4>;
        
        static Pixel Lab2Rgb(const Pixel& p)
        {            
            double y = (p[0] + 16) / 116.0;
            double x = p[1] / 500 + y;
            double z = y - p[2] / 200;
            
            
            x = 0.95047 * ((x * x * x > 0.008856) ? x * x * x : (x - 16/116) / 7.787);
            y = 1.00000 * ((y * y * y > 0.008856) ? y * y * y : (y - 16/116) / 7.787);
            z = 1.08883 * ((z * z * z > 0.008856) ? z * z * z : (z - 16/116) / 7.787);
            
            double r = x *  3.2406 + y * -1.5372 + z * -0.4986;
            double g = x * -0.9689 + y *  1.8758 + z *  0.0415;
            double b = x *  0.0557 + y * -0.2040 + z *  1.0570;

            r = (r > 0.0031308) ? (1.055 * std::pow(r, 1/2.4) - 0.055) : 12.92 * r;
            g = (g > 0.0031308) ? (1.055 * std::pow(g, 1/2.4) - 0.055) : 12.92 * g;
            b = (b > 0.0031308) ? (1.055 * std::pow(b, 1/2.4) - 0.055) : 12.92 * b;
            
            Pixel q;
            q[0] = (0.0, std::min(1.0, r)) * 255; 
            q[1] = std::max(0.0, std::min(1.0, g)) * 255;
            q[2] = std::max(0.0, std::min(1.0, b)) * 255;
            q[3] = p[3];
            
            
            
            return q;
        }
        
        static Pixel Rgb2Lab(const Pixel& p)
        {            
            double r = p[0] / 255;
            double g = p[1] / 255;
            double b = p[2] / 255;
            
            
            r = (r > 0.04045) ? std::pow((r + 0.055) / 1.055, 2.4) : r / 12.92;
            g = (g > 0.04045) ? std::pow((g + 0.055) / 1.055, 2.4) : g / 12.92;
            b = (b > 0.04045) ? std::pow((b + 0.055) / 1.055, 2.4) : b / 12.92;

            double x = (r * 0.4124 + g * 0.3576 + b * 0.1805) / 0.95047;
            double y = (r * 0.2126 + g * 0.7152 + b * 0.0722) / 1.00000;
            double z = (r * 0.0193 + g * 0.1192 + b * 0.9505) / 1.08883;

            x = (x > 0.008856) ? std::pow(x, 1/3) : (7.787 * x) + 16/116;
            y = (y > 0.008856) ? std::pow(y, 1/3) : (7.787 * y) + 16/116;
            z = (z > 0.008856) ? std::pow(z, 1/3) : (7.787 * z) + 16/116;

            Pixel q{ (116 * y) - 16, 500 * (x - y), 200 * (y - z), p[3] };
            
            
            
            return q;
            
        }
    
        static double DeltaE(const Pixel& p, const Pixel& q)
        {
            auto deltaL = p[0] - q[0];
            auto deltaA = p[1] - q[1];
            auto deltaB = p[2] - q[2];
            auto c1 = std::sqrt(p[1] * p[1] + p[2] * p[2]);
            auto c2 = std::sqrt(q[1] * q[1] + q[2] * q[2]);
            auto deltaC = c1 - c2;
            auto deltaH = deltaA * deltaA + deltaB * deltaB - deltaC * deltaC;
            deltaH = deltaH < 0 ? 0 : std::sqrt(deltaH);
            auto sc = 1.0 + 0.045 * c1;
            auto sh = 1.0 + 0.015 * c1;
            auto deltaLKlsl = deltaL / (1.0);
            auto deltaCkcsc = deltaC / (sc);
            auto deltaHkhsh = deltaH / (sh);
            auto i = deltaLKlsl * deltaLKlsl + deltaCkcsc * deltaCkcsc + deltaHkhsh * deltaHkhsh;
            return i < 0 ? 0 : std::sqrt(i);
        }
    

    }
}

#endif //__CCPUTILS_COLORS_h__
