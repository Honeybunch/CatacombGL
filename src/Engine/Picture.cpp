// Copyright (C) 2018 Arno Ansems
// 
// This program is free software: you can redistribute it and/or modify 
// it under the terms of the GNU General Public License as published by 
// the Free Software Foundation, either version 3 of the License, or 
// (at your option) any later version. 
// 
// This program is distributed in the hope that it will be useful, 
// but WITHOUT ANY WARRANTY; without even the implied warranty of 
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
// GNU General Public License for more details. 
// 
// You should have received a copy of the GNU General Public License 
// along with this program.  If not, see http://www.gnu.org/licenses/ 

#include "Picture.h"

Picture::Picture(const uint32_t textureId, const uint16_t width, const uint16_t height)
{
    m_width = width;
    m_height = height;
    m_textureId = textureId;
}

Picture::~Picture()
{

}

uint32_t Picture::GetTextureId() const
{
    return m_textureId;
}

uint16_t Picture::GetWidth() const
{
    return m_width;
}

uint16_t Picture::GetHeight() const
{
    return m_height;
}