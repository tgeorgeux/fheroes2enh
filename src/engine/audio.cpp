/***************************************************************************
 *   Copyright (C) 2008 by Andrey Afletdinov <fheroes2@gmail.com>          *
 *                                                                         *
 *   Part of the Free Heroes2 Engine:                                      *
 *   http://sourceforge.net/projects/fheroes2                              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "system.h"
#include "audio.h"
#include <sstream>
#include <iostream>

namespace
{
    Audio::Spec hardware;
}

Audio::Spec::Spec() : SDL_AudioSpec()
{
    freq = 0;
    format = 0;
    channels = 0;
    silence = 0;
    samples = 0;
    size = 0;
    callback = nullptr;
    userdata = nullptr;
}

Audio::CVT::CVT() : SDL_AudioCVT()
{
    needed = 0;
    src_format = 0;
    dst_format = 0;
    rate_incr = 0;
    buf = nullptr;
    len = 0;
    len_cvt = 0;
    len_mult = 0;
    len_ratio = 0;
    filters[0] = nullptr;
    filters[1] = nullptr;
    filters[2] = nullptr;
    filters[3] = nullptr;
    filters[4] = nullptr;
    filters[5] = nullptr;
    filters[6] = nullptr;
    filters[7] = nullptr;
    filters[8] = nullptr;
    filters[9] = nullptr;
    filter_index = 0;
}

bool Audio::CVT::Build(const Spec &src, const Spec &dst)
{
    if (1 == SDL_BuildAudioCVT(this, src.format, src.channels, src.freq, dst.format, dst.channels, dst.freq))
        return true;

    ERROR(SDL_GetError());
    return false;
}

bool Audio::CVT::Convert()
{
    if (0 == SDL_ConvertAudio(this)) return true;

    ERROR(SDL_GetError());
    return false;
}

Audio::Spec &Audio::GetHardwareSpec()
{
    return hardware;
}
