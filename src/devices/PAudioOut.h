//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/devices/PAudioOut.h
//    Purpose:    Controls sound presentation (but not recording).
//    Author:     Shane T. Mueller, Ph.D.
//    Copyright:  (c) 2003-2005 Shane T. Mueller <smueller@obereed.net>
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
#ifndef __PAUDIOOUT_H__
#define __PAUDIOOUT_H__
#include "PDevice.h"
#include <string>


/// This defines a generic sound presentation interface.
/// It has two basic modes: It can operate 'modally', where a sound file is played, 
/// blocking all other activity until complete; alternatively, it can be 'background', where 
/// the sound gets played by a callback in Loop(), which can be interrupted by the sound's
/// end or something else like a time-out or an interruption.

class PAudioOut: public PDevice
{
 public:
    PAudioOut(){};
    virtual ~PAudioOut(){};
    
    bool LoadSoundFile(const std::string & filename);
    
    virtual bool Play(){return false;};
    virtual bool Stop(){return false;};

    //A PAudioOut has a tunable amplitude parameter.  Set to 100
    //to get the 'real' volume of the file; adjust up or down as needed.
    //Will not avoid clipping.

    int GetAmplitude(){return 0;};
    void SetAmplitude(int ){};
    
    bool Initialize(){return false;};
    
    //These are mainly for programatically-generated sound buffers
    //(see below).
    void SetSampleRate(long int);
    long int GetSampleRate();
    
    
    //Programatically-generated sound buffers.  No file needed.
    bool CreateSineWave(float freq, double length, int amplitude);
    bool CreateSquareWave(float freq, double length, int amplitude);
    bool CreateSawtoothWave(float freq, double length, int amplitude);

    virtual PEBL_DEVICE_TYPE GetDeviceType(){return PDT_AUDIO_OUT;};
    
private:

protected:   
    unsigned int mSampleRate;
    int mChannels;
    int mAmplitude;
    int mFileName;
};


#endif
