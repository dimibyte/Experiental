#ifndef _SYSTEM_SERIALIZER_H_
#define _SYSTEM_SERIALIZER_H_

#include <string>

namespace Experiental
{

class ISerializer
{
public:
    virtual void IO(unsigned char &value) = 0;
    virtual void IO(unsigned long &value) = 0;
    virtual void IO(std::string &str) = 0;
};

class CSerialSizer : public ISerializer
{
protected:
    unsigned long length;
public:
    CSerialSizer();

    void IO(unsigned char &value);
    void IO(unsigned long &value);
    void IO(std::string &str);

    unsigned long getLength();
};

class CSerialSaver : public ISerializer
{
protected:
    unsigned char *buffer;
    bool bHasOverflowed;
    unsigned long length;
    unsigned long bytesUsed;
public:
    CSerialSaver(unsigned char *buf, unsigned long size);

    void IO(unsigned char &value);
    void IO(unsigned long &value);
    void IO(std::string &str);

    bool hasOverflowed();

    //should be equal to 0 when we're done
    long getFlow();
};

class CSerialLoader : public ISerializer
{
protected:
    unsigned char *buffer;
    bool bHasOverflowed;
    unsigned long length;
    unsigned long bytesUsed;
public:
    CSerialLoader(unsigned char *buf, unsigned long size);

    void IO(unsigned char &value);
    void IO(unsigned long &value);
    void IO(std::string &str);

    bool hasOverflowed();

    //should be equal to 0 when we're done
    long getFlow();
};

}

#endif // _SYSTEM_SERIALIZER_H_

