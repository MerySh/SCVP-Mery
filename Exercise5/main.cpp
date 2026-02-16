#include <iostream>
#include <systemc.h>

#include "kpn.cpp"

/*  What is this KPN doing? 
    It is performing a Fibonacci Sequence
    */
int sc_main(int, char**)
{
    kpn kahn("kpn");
    sc_signal<unsigned int> output_signal;
    kahn.e.bind(output_signal);
    sc_start();
    return 0;
}