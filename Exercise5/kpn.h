#ifndef KPN_H
#define KPN_H

#include <systemc.h>

template <unsigned int depth = 10>
SC_MODULE(kpn)
{
private:
    // ADD THINGS HERE
    sc_fifo<unsigned int> a, b, c, d;
    unsigned int counter = 0;

public:
    sc_out<unsigned int> e;
    SC_CTOR(kpn): a(depth), b(depth), c(depth), d(depth) // : ADD THINGS HERE
    {
        // ADD THINGS HERE
        b.write(1);
        c.write(0);

        SC_THREAD(Add);
        SC_THREAD(Split);
        SC_THREAD(Delay);
    }

    void Add();
    void Split();
    void Delay();
};

#endif // KPN_H