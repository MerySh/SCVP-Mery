#ifndef PLACE_H
#define PLACE_H

#include <systemc.h>

// Place Interface:
// TODO
class placeInterface : public sc_interface
{
public:
    // virtual void addTokens(unsigned int n) = 0;
    // virtual void removeTokens(unsigned int n) = 0;
    // virtual unsigned int testTokens() = 0;
    virtual void addTokens() = 0;
    virtual void removeTokens() = 0;
    virtual bool testTokens() = 0;
};

// Place Channel:
// TODO
template<unsigned int Win = 1, unsigned int Wout = 1>
class place : public placeInterface
{
public:
    unsigned int tokens;
    
    place(unsigned int t) : tokens(t) {}

    // void addTokens(unsigned int n);
    // void removeTokens(unsigned int n);
    // unsigned int testTokens();
    void addTokens();
    void removeTokens();
    bool testTokens();
};

#endif // PLACE_H
