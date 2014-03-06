/*
 *  This file is part of Experiental.
 *
 *  Experiental is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  Experiental is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Experiental.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _MISC_H_
#define _MISC_H_

inline float clamp(float val, float minVal, float maxVal)
{
    return std::min(std::max(val, minVal), maxVal);
}

float inline pow(float base, int power)
{
    if(power == 1) return base;
    if(power == 0) return 1;
    return base * pow(base, power - 1);
}

#endif      //_MISC_H_
