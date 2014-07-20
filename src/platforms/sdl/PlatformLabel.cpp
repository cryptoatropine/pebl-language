//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/platforms/sdl/PlatformLabel.cpp
//    Purpose:    Contains SDL-specific visual representation of a word
//    Author:     Shane T. Mueller, Ph.D.
//    Copyright:  (c) 2004-2013 Shane T. Mueller <smueller@obereed.net>
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
#include "PlatformLabel.h"
#include "../../objects/PLabel.h"
#include "PlatformFont.h"
#include "../../utility/rc_ptrs.h"
#include "../../utility/PError.h"
#include "../../base/PComplexData.h"
#include "../../utility/PEBLUtility.h"
#ifdef PEBL_OSX
#include "SDL.h"
#include "SDL_ttf.h"
#else
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#endif

#include <stdio.h>
#include <algorithm>

using std::cout;
using std::cerr;
using std::endl;
using std::flush;
using std::list;
using std::ostream;



PlatformLabel::PlatformLabel(const std::string & text, counted_ptr<PEBLObjectBase> font):
    PlatformWidget(),
    PLabel(text),
    mFontObject(font)
{
    
    mCDT=CDT_LABEL;

    SetFont(font);
    SetText(text);

    //Make the font property accessible
    counted_ptr<PEBLObjectBase> myFont = counted_ptr<PEBLObjectBase>(mFontObject);
    PComplexData *  pcd = new PComplexData(myFont);
    InitializeProperty("FONT",Variant(pcd));
    delete pcd;
    pcd=NULL;
    InitializeProperty("WIDTH",Variant(0));
    InitializeProperty("HEIGHT",Variant(0));


    Draw();

}


PlatformLabel::PlatformLabel(PlatformLabel & label):
    PlatformWidget(),
    PLabel(label.GetText())

{
    mCDT=CDT_LABEL;

    SetFont(label.GetFont());


    counted_ptr<PEBLObjectBase> myFont = counted_ptr<PEBLObjectBase>(mFontObject);
    PComplexData *  pcd = new PComplexData(myFont);
    delete pcd;
    pcd=NULL;

    InitializeProperty("FONT",Variant(pcd));
    InitializeProperty("WIDTH",Variant(label.GetHeight()));
    InitializeProperty("HEIGHT",Variant(label.GetWidth()));
    
    Draw();
}


///Standard Destructor
PlatformLabel::~PlatformLabel()
{
    //cout << "Label destructor\n";
 
}


// Inheritable function that is called by friend method << operator of PComplexData
ostream & PlatformLabel::SendToStream(ostream& out) const
{
    out << "<SDL PlatformLabel: " << mText << " in " << *mFont << ">" <<flush;
    return out;
}

 


/// This method should be called when the font is initialized or the text is changed.
/// It will make the mSurface pointer hold the appropriate image.
bool  PlatformLabel::RenderText()
{


    //free the memory if it is currently pointing at something.
    if(mSurface)  SDL_FreeSurface(mSurface);


    if(mDirection == 1)
        {

            //Re-render the text using the associated font.
            mSurface = mFont->RenderText(mText.c_str());
        }
    else 
        {
         

            std::string rtext = PEBLUtility::strrev_utf8(mText);

            //Re-render the text using the associated font.
            mSurface = mFont->RenderText(rtext.c_str());

        }
    
    //If mSurface is null, then rendering failed.
    if( mSurface)
        {
            //  SDL_SetAlpha( mSurface, 0, SDL_ALPHA_TRANSPARENT);    
            mWidth  = mSurface->w; 
            mHeight = mSurface->h;

            InitializeProperty("HEIGHT",mHeight);
            InitializeProperty("WIDTH",mWidth);

            return true;
        }


    else
        return false;
}


bool PlatformLabel::SetProperty(std::string name, Variant v)
{

    if(name == "TEXT")
        {
            SetText(v);
        }
    else if(PLabel::SetProperty(name,v))
    {
        // If we set it at higher level, don't worry.
    }
    else if (name == "FONT")
        {
            SetFont(v.GetComplexData()->GetObject());
            
        }
    else return false;
    
    return true;
}

void PlatformLabel::SetFont(counted_ptr<PEBLObjectBase> font)
{

    mFontObject = font;
    mFont = dynamic_cast<PlatformFont*>(mFontObject.get());

    mTextChanged =true;
    Draw();
    //Re-render the text onto mSurface
    //if(!RenderText()) cerr << "Unable to render text.\n";

}


void PlatformLabel::SetText(const std::string & text)
{
    //Chain up to parent method.
    PTextObject::SetText(text);
    mTextChanged =true;
    Draw();

    //Re-render the text onto mSurface
    //if(!RenderText()) cerr << "Unable to render text.\n";

}


bool PlatformLabel::Draw()
{
    if(mTextChanged)
        {

            //cout << "Rendinging platform label\n";
            RenderText();
            //Reposition.  This just recalculates so things are centered
            //correctly; labels are positioned based on their center.
            //cout << "Setting PL position\n";
            SetPosition(mX, mY);

            //cout << "Initializing height/width properties\n";
            InitializeProperty("HEIGHT",mHeight);
            InitializeProperty("WIDTH",mWidth);
            //   mTextChanged = false;
        }
    return  PlatformWidget::Draw();

}
