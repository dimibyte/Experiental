#include "system/serializer.h"
#include "system/SDL.h"

namespace Experiental
{

CSerialSizer::CSerialSizer()
{
    length = 0;
}

void CSerialSizer::IO(unsigned char &value)
{
    ++length;
}

void CSerialSizer::IO(unsigned long &value)
{
    length += 4;
}

void CSerialSizer::IO(std::string &str)
{
    IO(length);
    length += str.length();
}

unsigned long CSerialSizer::getLength()
{
    return length;
}

CSerialSaver::CSerialSaver(unsigned char *buf, unsigned long size)
{
    buffer = buf;
    length = size;
    bytesUsed = 0;
    bHasOverflowed = false;
}

void CSerialSaver::IO(unsigned char &value)
{
    if(bHasOverflowed)
        return;     //stop writing when overflowed
    if(bytesUsed + 1 > length)
    {
        bHasOverflowed = true;
        return;
    }
    *buffer = value;
    ++buffer; ++bytesUsed;
}

void CSerialSaver::IO(unsigned long &value)
{
    if(bHasOverflowed)
        return;     //stop writing when overflowed
    if(bytesUsed + 4 > length)
    {
        bHasOverflowed = true;
        return;
    }
    SDLNet_Write32(value, buffer);
    buffer += 4; bytesUsed += 4;
}

void CSerialSaver::IO(std::string &str)
{
    unsigned long l = str.length();
    IO(l);
    if(bHasOverflowed)
        return;
    if(bytesUsed + l > length)
    {
        bHasOverflowed = true;
        return;
    }
    memcpy(buffer, str.c_str(), l);
    buffer += l; bytesUsed += l;
}

bool CSerialSaver::hasOverflowed()
{
    return bHasOverflowed;
}

long CSerialSaver::getFlow()
{
    return length - bytesUsed;
}

CSerialLoader::CSerialLoader(unsigned char *buf, unsigned long size)
{
    buffer = buf;
    length = size;
    bytesUsed = 0;
    bHasOverflowed = false;
}

void CSerialLoader::IO(unsigned char &value)
{
    if(bHasOverflowed)
        return;     //stop writing when overflowed
    if(bytesUsed + 1 > length)
    {
        bHasOverflowed = true;
        return;
    }
    value = *buffer;
    ++buffer; ++bytesUsed;
}

void CSerialLoader::IO(unsigned long &value)
{
    if(bHasOverflowed)
        return;     //stop writing when overflowed
    if(bytesUsed + 4 > length)
    {
        bHasOverflowed = true;
        return;
    }
    value = SDLNet_Read32(buffer);
    buffer += 4; bytesUsed += 4;
}

void CSerialLoader::IO(std::string &str)
{
    unsigned long l = str.length();
    IO(l);
    if(bHasOverflowed)
        return;
    if(bytesUsed + l > length)
    {
        bHasOverflowed = true;
        return;
    }
    char *szBuf = new char[l + 1];
    szBuf[l] = 0;
    memcpy(szBuf, buffer, l);
    str = szBuf;
    delete[] szBuf;
    buffer += l; bytesUsed += l;
}

bool CSerialLoader::hasOverflowed()
{
    return bHasOverflowed;
}

long CSerialLoader::getFlow()
{
    return length - bytesUsed;
}

}
