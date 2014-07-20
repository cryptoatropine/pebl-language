//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/objects/PColor.cpp
//    Purpose:    Contains lightweight specification for a color
//    Author:     Shane T. Mueller, Ph.D.
//    Copyright:  (c) 2003-2010 Shane T. Mueller <smueller@obereed.net>
//    License:    GPL 2
//
//
//
//     This file is part of the PEBL project.
//
//    PEBL is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    PEBL is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with PEBL; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
////////////////////////////////////////////////////////////////////////////////

#include "PColor.h"
#include "../base/Variant.h"
#include "../base/PEBLObject.h"
#include "RGBColorNames.h"
#include "../utility/PEBLUtility.h"
#include "../utility/PError.h"


#include <string>
#include <cstring>

using std::string;
using std::cout;
using std::endl;
///Standard constructor of PColor

PColor::PColor():
    PEBLObjectBase(CDT_COLOR),
    mRed(0),
    mGreen(0),
    mBlue(0),
    mAlpha(255)

{

    InitializeProperty("NAME", Variant("<COLOR>"));
     InitializeProperty("RED",Variant(GetRed()));
     InitializeProperty("GREEN",Variant(GetGreen()));
     InitializeProperty("BLUE",Variant(GetBlue()));
     InitializeProperty("ALPHA",Variant(GetAlpha()));
    
} 


///Convenience constructor of PColor:
PColor::PColor(int red, int green, int blue, int alpha):
    PEBLObjectBase(CDT_COLOR),
    mRed(To8BitColor(red)),
    mGreen(To8BitColor(green)),
    mBlue(To8BitColor(blue)),
    mAlpha(To8BitColor(alpha))

{
    InitializeProperty("NAME", Variant("<COLOR>"));
     InitializeProperty("RED",Variant(GetRed()));
     InitializeProperty("GREEN",Variant(GetGreen()));
     InitializeProperty("BLUE",Variant(GetBlue()));
     InitializeProperty("ALPHA",Variant(GetAlpha()));

}

///Name-based constructor of PColor:
PColor::PColor(const string & colorname):
    PEBLObjectBase(CDT_COLOR)
{
    InitializeProperty("NAME", Variant("<COLOR>"));
     InitializeProperty("RED",Variant(0));
     InitializeProperty("GREEN",Variant(0));
     InitializeProperty("BLUE",Variant(0));
     InitializeProperty("ALPHA",Variant(0));

    SetColorByName(colorname);
    SetAlpha(255);    
}


///Copy constructor of PColor:
PColor::PColor(const PColor & pcolor):
    PEBLObjectBase(CDT_COLOR)
{
    mRed   = pcolor.GetRed();
    mGreen = pcolor.GetGreen();
    mBlue  = pcolor.GetBlue();
    mAlpha = pcolor.GetAlpha();

     InitializeProperty("NAME", Variant("<COLOR>"));
     InitializeProperty("RED",Variant(GetRed()));
     InitializeProperty("GREEN",Variant(GetGreen()));
     InitializeProperty("BLUE",Variant(GetBlue()));
     InitializeProperty("ALPHA",Variant(GetAlpha()));
    
}

PColor::~PColor()
{
}

void PColor::__SetProps__()
{
     PEBLObjectBase::SetProperty("RED",Variant(GetRed()));
     PEBLObjectBase::SetProperty("GREEN",Variant(GetGreen()));
     PEBLObjectBase::SetProperty("BLUE",Variant(GetBlue()));
     PEBLObjectBase::SetProperty("ALPHA",Variant(GetAlpha()));
}




bool PColor::SetProperty(std::string name, Variant v)
{

    if(name == "RED") SetRed(v);
    else if(name == "GREEN") SetGreen(v);
    else if(name == "BLUE") SetBlue(v);
    else if(name == "ALPHA") SetAlpha(v);
    else return false;

    return true;
}



ObjectValidationError PColor::ValidateProperty(std::string name, Variant v)const
{
    if(ValidateProperty(name) == OVE_INVALID_PROPERTY_NAME) return OVE_INVALID_PROPERTY_NAME;
    
    if(!v.IsNumber()) return OVE_INVALID_PROPERTY_TYPE;
    if( v < Variant(0) || v > Variant(255)) return OVE_INVALID_PROPERTY_VALUE;
    return OVE_SUCCESS;
}


ObjectValidationError PColor::ValidateProperty(std::string name)const
 {
     return PEBLObjectBase::ValidateProperty(name);
 }




/// This makes sure that color is between 0 and 255.  If less, it
/// makes it 0; if greater, it makes it 255.
int PColor::To8BitColor(int color)
{
    if(color<0) color = 0;
    if(color>255) color = 255;

    return color;
}


 //These will set a single color
void PColor::SetRed  (int color)
{
    mRed   = To8BitColor(color);
    PEBLObjectBase::SetProperty("RED",GetRed());
}

void PColor::SetGreen(int color)
{
    mGreen = To8BitColor(color);
    PEBLObjectBase::SetProperty("GREEN",GetGreen());
}

void PColor::SetBlue (int color)
{
    mBlue  = To8BitColor(color);
    PEBLObjectBase::SetProperty("BLUE",GetBlue());
}

void PColor::SetAlpha(int color)
{
    mAlpha = To8BitColor(color);
    PEBLObjectBase::SetProperty("ALPHA",GetAlpha());
}

   //These will return a single color
int PColor::GetRed  () const { return mRed;}
int PColor::GetGreen() const { return mGreen;}
int PColor::GetBlue () const { return mBlue;}
int PColor::GetAlpha() const { return mAlpha;}
 

///This uses modular arithmetic to extract colors from unsigned int.
///There could be more efficient ways to do it, but this is clear, and 
///More likely to work cross-platform.
void PColor::SetColorByRGBA(unsigned int color)
{
    mAlpha  = color % 255;
    mBlue   = color / 255 % 255;
    mGreen  = color / (255 * 255) % 255;
    mRed    = color / ( 255 * 255 * 255) % 255;
    __SetProps__();
}



///Convenience constructor of PColor:
void PColor::SetColorByRGBA(int red, int green, int blue, int alpha)
{
    mRed   = To8BitColor(red);
    mGreen = To8BitColor(green);
    mBlue  = To8BitColor(blue);
    mAlpha = To8BitColor(alpha);
    __SetProps__();
}


void PColor::SetColorByName(const string & colorname)
{

    std::string ucasename = PEBLUtility::ToUpper(colorname);
    
    
    ///the RGBNames::Colornames is uppercase and sorted, so use a simple search 
    ///to find the right one really fast.
    int bottom = 0;
    int top    = RGBNames::NumRGBColorNames-1; 
    int mid = (top + bottom)/2;
    int foundindex = -1;
    int test;
    bool sep1=false;          //This flags if the separation between top and bottom is 1. 
                           
    
    //Check the top-most name first.  If this is a hit, we could get stuck
    if(ucasename ==  RGBNames::ColorNames[top].name)
        {
            foundindex = top;    //It is a hit.
        }
    
    //Check the bottom-most name.  If this is a hit, we could get stuck
    if(ucasename == RGBNames::ColorNames[bottom].name)
        {
            foundindex = bottom;    //It is a hit.
        }
    

    //repeat until you find it or there is nothing to find.
    while(((top - bottom) > 1) && (foundindex == -1) && !sep1)
        {

            
            mid = (top + bottom)/2;

            //set the '1-item separation' flag to true.
            if((top - bottom) == 1) sep1 = true;
            
             
            //Compare the library color and the current color. 0 means they are the same.
            test =strcmp(ucasename.c_str(), RGBNames::ColorNames[mid].name.c_str());

          
            if(test < 0)           //If test < 0, the chosen word comes before the point in the dictionary. Move top down.
                {
                    top = mid;
                }
            else if(test > 0)       //If test > 0, the chosen word comes after the point in the dictionary. Move bottom up.
                {
                    bottom = mid;
                }
            else 
                {
                    foundindex = mid;
                }
           
            
        }

    //Check top & bottom to see if there is a match.
    //if(strcmp(ucasename, RGBNames::ColorNames[top].name) == 0) foundindex = top;
    //if(strcmp(ucasename, RGBNames::ColorNames[bottom].name) == 0) foundindex = bottom;
   

    //If foundindex is still -1, we did not find the color name in the library.
    if(foundindex == -1)
        {
            PError::SignalWarning("Color name [" + string(ucasename) + "] not found.  Using Black.");
            foundindex = 25;   //25 is the index of black.

            //Better error detection should be done here: searching with levenshtien distance,
            //ignoring _ or - or #s, etc.
        }

    

    mRed   = RGBNames::ColorNames[foundindex].r;
    mGreen = RGBNames::ColorNames[foundindex].g;
    mBlue  = RGBNames::ColorNames[foundindex].b;
    mAlpha = 255;
    __SetProps__();
}


//This will return an unsigned int that encapsulates the RGBA values into a 32-bit number.
//It does this using *, which might be slower than bit-shifting/masking, but 
///this is a bit clearer and easier to deal with cross-platform.
unsigned int PColor::GetColor() const
{
    unsigned int color=0;
    color = mAlpha + (255 * mBlue)  + (255 * 255 * mGreen) + (255 * 255 * 255 * mRed);
    return color;
}




/// This sends the color descriptions to the specified stream.
std::ostream & PColor::SendToStream(std::ostream& out) const
{
    out << ObjectName() << std::flush;
    return out;
}

std::string PColor::ObjectName() const
{
    Variant tmp = "<PColor: Red: [";

    tmp = tmp + Variant((int)mRed) ;
    tmp = tmp + Variant("] Green: [");
    tmp = tmp +  Variant((int)mGreen);
    tmp = tmp + Variant("] Blue: [");
    tmp = tmp + Variant((int)mBlue );
    tmp = tmp + Variant("] Alpha: [");
    tmp = tmp + Variant((int)mAlpha );
    tmp = tmp + Variant("] Color Code: [");
    tmp = tmp + Variant((long unsigned int)GetColor());
    tmp = tmp + Variant("]>");

    return tmp.GetString();
}
