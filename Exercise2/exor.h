#ifndef EXOR_H
#define EXOR_H

#include <systemc.h>

#include "nand.h"

// TODO: Insert your code here
SC_MODULE(exor) {
    sc_in<bool> A;
    sc_in<bool> B;
    sc_out<bool> Z;

    sc_signal<bool> h1, h2, h3;

    nand nand_a, nand_b, nand_c, nand_d;

    SC_CTOR(exor) : nand_a("nand_a"), nand_b("nand_b"),
                nand_c("nand_c"), nand_d("nand_d") {
        nand_a.A(A);
        nand_a.B(B);
        nand_a.Z(h1);

        nand_b.A(A);
        nand_b.B(h1);
        nand_b.Z(h2);

        nand_c.A(h1);
        nand_c.B(B);
        nand_c.Z(h3);

        nand_d.A(h2);
        nand_d.B(h3);
        nand_d.Z(Z);
    }
};

#endif // EXOR_H
