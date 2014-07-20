//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/platforms/sdl/PlatformAudioOut.h
//    Purpose:    Contains platform-specific sound playing routines
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
#ifndef __PLATFORMAUDIOOUT_H__
#define __PLATFORMAUDIOOUT_H__

#include "../../devices/PAudioOut.h"
#include "../../base/PEBLObject.h"
#include "SDL/SDL.h"
#include "SDL/SDL_audio.h"
  
#include <string>

struct AudioInfo{

    SDL_AudioSpec spec;
    Uint8   *audio;			/* Pointer to wave data */
    Uint32   audiolen;		/* Length of wave data */
    Uint32      audiopos;		/* Current play position */


    unsigned int bytesPerSample;  //size of a sample
	Uint32 recordpos;      //current index in the buffer (in bytes)
    Uint32 counter;        //A counter to use that keeps track of samples
                           //since the beginning of recording.


    int      volume;           /* Relative volume. 0-100*/
    const char*    name;
};

class PlatformAudioOut: virtual public PAudioOut, public PEBLObjectBase
{
 public:
    PlatformAudioOut();
    PlatformAudioOut(const std::string & filename);
    ~PlatformAudioOut();
  
    bool LoadSoundFile(const std::string & filename);
    bool LoadSoundFromData( Uint8 *buffer, long unsigned int size, SDL_AudioSpec *spec);

    void SaveBufferToWave(Variant filename);
    bool CreateSineWave(float freq, long unsigned int length,long double volume);

    bool CreateSquareWave(float freq, double length, int amplitude);
    bool CreateSawtoothWave(float freq, double length, int amplitude);
    bool CreateChirp();

    bool Play();
    bool PlayForeground();
    bool Stop();
    
    bool ConvertAudio(AudioInfo & info);    
    AudioInfo * GetAudioInfo();
    bool Initialize();

    //    void AddTrack(const std::string &  handle, AudioInfo track);
    //    void RemoveTrack(const std::string &  handle);

    Uint8 * MixTracks();
    
    void PrintAudioInfo();

private:
  

    //    void PlayCallBack(void * dummy, Uint8 * stream, int len);
    
    bool mLoaded;               //This will be true when a file 
                                //has been loaded or a buffer has been
                                //generated.

    std::string mFilename;
    AudioInfo mWave;
};


#endif
