//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       utility/PEBLUtility.h
//    Purpose:    Miscellaneous Utility Functions used in PEBL
//    Author:     Shane T. Mueller, Ph.D.
//    Copyright:  (c) 2003-2011 Shane T. Mueller <smueller@obereed.net>
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
#ifndef __PEBLUTILITY_H__
#define __PEBLUTILITY_H__

/// This file defines a bunch of class-less functions, inside the PEBLUtility namespace,
/// that accomplish little things that might be useful for a variety of classes.
/// To use, include the file and refer to a function by PEBLUtility::FunctionName(),
/// or do a 'using namespace PEBLUtility', or 'using PEBLUtility::FunctionName;'.
#include "../devices/PKeyboard.h"
#include "../apps/Globals.h"
#include "Defs.h"
#include <string>

class Variant;

namespace PEBLUtility
{

    std::string ToUpper(const std::string & text);
    std::string ToLower(const std::string & text);


    /// This does its best, with the available libraries, to convert
    /// a string to a long double.
    pDouble StringToPDouble(const char * mystring);

    pDouble Log2(pDouble val);
    pInt Round(pDouble val);
    pDouble Round(pDouble val, pInt prec);
    pInt Truncate(pDouble val);

    Variant Tokenize(const char* line, char separator);

    PEBLKey TranslateString(const std::string & letters);
    std::string TranslateKeyCode(const PEBLKey key, int modkeys);


    /// These functions are used frequently enough that it is good to have
    /// our own definition.

    pDouble RandomUniform();
    pDouble RandomNormal();

    std::string ShiftSwitch(int modkeys, std::string lower, std::string upper);

    PEBLVideoMode GetVideoMode(std::string modeline);
    PEBLVideoDepth GetVideoDepth(std::string depthline);


    Variant GetDirectoryListing(std::string path);
    Variant IsDirectory(std::string path);
    Variant FileExists(std::string path);
    Variant MakeDirectory(std::string path);
    Variant DeleteMyFile(std::string path);
    Variant GetHomeDirectory();
    Variant GetWorkingDirectory();
    Variant SetWorkingDirectory(std::string path);

    const std::string  StripFile(const std::string &  file);

    Variant LaunchFile(std::string file);
    Variant SystemCall(std::string path, std::string args);

    void strrev(char*p);
    void strrev_utf8(char*p);
    std::string strrev(std::string p);
    std::string strrev_utf8(std::string p);


    std::string MD5File(const std::string & filename);
    std::string MD5String(const std::string & text);

    void CopyToClipboard(const std::string & text);

}


#endif
