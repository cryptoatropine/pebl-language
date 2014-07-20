//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/objects/PFont.cpp
//    Purpose:    Contains generic specification for a font
//    Author:     Shane T. Mueller, Ph.D.
//    Copyright:  (c) 2003-2009 Shane T. Mueller <smueller@obereed.net>
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
#include "PFont.h"
#include "PColor.h"
#include "../base/Variant.h"
#include "../base/PComplexData.h"
#include "../utility/rc_ptrs.h"


#include <iostream>
using std::cout;
using std::endl;
///Standard constructor of PFont

PFont::PFont():
    mFontFileName("Vera.ttf"),
    mFontStyle(PFS_Normal),
    mFontSize(16),
    mAntiAliased(false)

{
    mCDT = CDT_FONT;
    mFontColor       = PColor(0,0,0,255);
    mBackgroundColor = PColor(0,0,0,255);

    InitializeProperty("FILENAME", mFontFileName);
    InitializeProperty("BOLD", Variant(IsBoldFont()));
    InitializeProperty("UNDERLINE",Variant(IsUnderlineFont()));
    InitializeProperty("ITALIC",  Variant(IsItalicFont()));
    InitializeProperty("SIZE", mFontSize);
    InitializeProperty("NAME", Variant("<FONT>"));

    
    counted_ptr<PEBLObjectBase> pob = counted_ptr<PEBLObjectBase>(&mFontColor);
    PComplexData * pcd = new PComplexData(pob);
    Variant col = Variant(pcd);
    delete pcd;  //col now controls pcd
    pcd=NULL;

    InitializeProperty("FGCOLOR", col);
    

    pob = counted_ptr<PEBLObjectBase>(&mBackgroundColor);
    pcd = new PComplexData(pob);
    col = Variant(pcd);
    delete pcd;  //col now controls pcd
    pcd=NULL;

    InitializeProperty("BGCOLOR", col);
    InitializeProperty("ANTIALIASED", Variant(mAntiAliased));

}


///Convenience constructor of PFont:
PFont::PFont(const std::string & filename, int style, int size, PColor fgcolor, PColor bgcolor, bool aa):
    mFontFileName(filename),
    mFontStyle(style),
    mFontSize(size),
    mAntiAliased(aa)
{

    mCDT = CDT_FONT;

    mFontColor       = fgcolor;
    mBackgroundColor = bgcolor;
    
    InitializeProperty("NAME", Variant("<FONT>"));
    InitializeProperty("FILENAME", mFontFileName);
    InitializeProperty("BOLD", Variant(IsBoldFont()));
    InitializeProperty("UNDERLINE",Variant(IsUnderlineFont()));
    InitializeProperty("ITALIC",  Variant(IsItalicFont()));
    InitializeProperty("SIZE", mFontSize);


     counted_ptr<PEBLObjectBase> pob = counted_ptr<PEBLObjectBase>(&mFontColor);
     PComplexData * pcd = new PComplexData(pob);
     Variant col = Variant(pcd);
     //col now contrlols pcd data, so get rid of it
     delete pcd; 
     pcd=NULL;
     InitializeProperty("FGCOLOR", col);
    

     pob = counted_ptr<PEBLObjectBase>(&mBackgroundColor);
     pcd = new PComplexData(pob);
     col = Variant(pcd);
     delete pcd;
     pcd=NULL;

     InitializeProperty("BGCOLOR", col);
     InitializeProperty("ANTIALIASED", Variant(mAntiAliased));
}


///Copy constructor of PFont:
PFont::PFont(const PFont & font)

{
    mCDT = CDT_FONT;

    mFontFileName    = font.GetFontFileName();
    mFontStyle       = font.GetFontStyle();
    mFontSize        = font.GetFontSize();
    mFontColor       = font.GetFontColor();
    mBackgroundColor = font.GetBackgroundColor();
    mAntiAliased     = font.GetAntiAliased();
    
    InitializeProperty("FILENAME", mFontFileName);
    InitializeProperty("BOLD", Variant(IsBoldFont()));
    InitializeProperty("UNDERLINE",Variant(IsUnderlineFont()));
    InitializeProperty("ITALIC",  Variant(IsItalicFont()));
    InitializeProperty("SIZE", mFontSize);
    InitializeProperty("NAME", Variant("<FONT>"));

    
    counted_ptr<PEBLObjectBase> pob = counted_ptr<PEBLObjectBase>(&mFontColor);
    PComplexData * pcd = new PComplexData(pob);
    Variant col = Variant(pcd);
    delete pcd;
    pcd=NULL;
    InitializeProperty("FGCOLOR", col);
    
    
    pob = counted_ptr<PEBLObjectBase>(&mBackgroundColor);
    pcd = new PComplexData(pob);
    col = Variant(pcd);
    delete pcd;
    pcd=NULL;
    InitializeProperty("BGCOLOR", col);
    InitializeProperty("ANTIALIASED", Variant(mAntiAliased));
}


///Standard destructor of PFont
PFont::~PFont()
{
    
    cout << "Deleting pfont\n";
}


//overloaded generic PEBLObjectBase methods
bool PFont::SetProperty(std::string name, Variant v)
{
    if(name == "FILENAME") SetFontFileName(v);
    else if (name == "BOLD" )
        {
            int b,u,i;
            if(v.GetInteger()) b = PFS_Bold;
            else b = PFS_Normal;

            if(IsItalicFont()) i = PFS_Italic;
            else i = PFS_Normal;
            
            if(IsUnderlineFont()) u = PFS_Underline;
            else u = PFS_Normal;
            
            SetFontStyle( b | i | u);

        }
    else if (name == "ITALIC" )
        {
            int b,u,i;
            if(IsBoldFont()) b = PFS_Bold;
            else b = PFS_Normal;

            if(v.GetInteger()) i = PFS_Italic;
            else i = PFS_Normal;
            
            if(IsUnderlineFont()) u = PFS_Underline;
            else u = PFS_Normal;
            
            SetFontStyle( b | i | u);

        }
    else if (name == "UNDERLINE" )
        {
            int b,u,i;
            if(IsBoldFont()) b = PFS_Bold;
            else b = PFS_Normal;

            if(IsItalicFont()) i = PFS_Italic;
            else i = PFS_Normal;
            
            if(v.GetInteger()) u = PFS_Underline;
            else u = PFS_Normal;
            
            SetFontStyle( b | i | u);
        }
    else if (name == "SIZE") SetFontSize(v) ;

    
    else if (name == "FGCOLOR")
        {
            //For colors, directly set the property to avoid 
            //dual conversion.
            PEBLObjectBase::SetProperty(name,v);
            mFontColor = *(dynamic_cast<PColor*>(v.GetComplexData()->GetObject().get()));
        }
    else if (name == "BGCOLOR") 
        {
            PEBLObjectBase::SetProperty(name,v);
            mBackgroundColor = *(dynamic_cast<PColor*>(v.GetComplexData()->GetObject().get()));
        }
    else if (name == "ANTIALIASED")SetAntiAliased(v.GetInteger());
    else return false;
    
    return true;
}

Variant PFont::GetProperty(std::string name)const
{
    return PEBLObjectBase::GetProperty(name);
}


ObjectValidationError PFont::ValidateProperty(std::string name, Variant v)const
{
    return ValidateProperty(name);
}
ObjectValidationError PFont::ValidateProperty(std::string name)const
{
    return OVE_SUCCESS;
}

std::string PFont::ObjectName()const
{
    return "PFont";
}



///Set methods for all of the data in font
void PFont::SetFontFileName(const std::string & name)  
{
    mFontFileName = name;
    PEBLObjectBase::SetProperty("FILENAME", mFontFileName);
}

void PFont::SetFontStyle(const int style)         
{
    mFontStyle=style;
    PEBLObjectBase::SetProperty("BOLD", Variant(IsBoldFont()));
    PEBLObjectBase::SetProperty("UNDERLINE",Variant(IsUnderlineFont()));
    PEBLObjectBase::SetProperty("ITALIC",  Variant(IsItalicFont()));
}

void PFont::SetFontSize(const int size) 
{
    mFontSize = size;
    PEBLObjectBase::SetProperty("SIZE", mFontSize);
}

void PFont::SetFontColor(const PColor color) 
{

    mFontColor = color;  
    counted_ptr<PEBLObjectBase> pob = counted_ptr<PEBLObjectBase>(&mFontColor);
    PComplexData * pcd = new PComplexData(pob);
    Variant col = Variant(pcd);
    delete pcd;  //col now controls pcd
    pcd=NULL;

    InitializeProperty("FGCOLOR", col);

}  

void PFont::SetBackgroundColor(const PColor color)
{
    mBackgroundColor = color;  
    counted_ptr<PEBLObjectBase> pob = counted_ptr<PEBLObjectBase>(&mBackgroundColor);
    PComplexData * pcd = new PComplexData(pob);
    Variant col = Variant(pcd);
    delete pcd;  //col now controls pcd
    pcd=NULL;

    InitializeProperty("BGCOLOR", col);
}

void PFont::SetAntiAliased(const bool aa)  
{
    mAntiAliased = aa;
    PEBLObjectBase::SetProperty("ANTIALIASED", Variant(mAntiAliased));
}



/// This sends the font descriptions to the specified stream.
std::ostream & PFont::SendToStream(std::ostream& out) const
{
    out << "<PFont: Name:        [" << mFontFileName << "]\n";
    out << "        Style:       ["<< mFontStyle<< "]\n";
    out << "        Size:        ["<< mFontSize << "]\n";
    out << "        Color:       ["<< mFontColor << "]\n";
    out << "        BGColor:     ["<< mBackgroundColor<< "]\n";
    out << "        Antialiased: ["<< mAntiAliased << "]>\n";

    return out;
}

 
//These get different styles
bool PFont::IsNormalFont() const
{
    return mFontStyle == 0;
}

bool PFont::IsBoldFont() const
{
    //The PFS_Bold acts as a bit filter, if it isn't bold the & should be 0.
    return (mFontStyle & PFS_Bold);
}

bool PFont::IsItalicFont() const
{
    //The PFS_Italic acts as a bit filter, if it isn't bold the & should be 0.
    return (mFontStyle & PFS_Italic);
}

bool PFont::IsUnderlineFont() const
{
    //The PFS_Underline acts as a bit filter, if it isn't bold the & should be 0.
    return (mFontStyle & PFS_Underline);
}

