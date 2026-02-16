#ifndef TRANSITION_H
#define TRANSITION_H

#include <systemc.h>

#include "place.h"

// Transition:
// TODO
// template<unsigned int N = 1, unsigned int M = 1>
// SC_MODULE(transition)
// {
//     sc_port<placeInterface, N, SC_ALL_BOUND> in;
//     sc_port<placeInterface, M, SC_ALL_BOUND> out;

//     SC_CTOR(transition) {}

//     void fire()
//     {
//         bool cond = true;
//         /* If there is one input port without token then do not do anything*/
//         for (int i = 0; i < N; ++i) {
//             if (in[i]->testTokens() == 0) {
//                 cond = false;
//                 break;
//             }
//         }

//         /* If all input ports have at least one token then remove one from
//             each of them and add one to each output port */
//         if (cond) {
//             std::cout << this->name() << ": Fired" << std::endl;
//             for (int i = 0; i < N; ++i) {
//                 in[i]->removeTokens();
//             }

//             for (int i = 0; i < M; ++i) {
//                 out[i]->addTokens();
//             }
//         } else {
//             std::cout << this->name() << ": NOT Fired" << std::endl;
//         }
//     }
// };

template<unsigned int N = 1, unsigned int M = 1, unsigned int L = 0>
SC_MODULE(transition)
{
    sc_port<placeInterface, N, SC_ALL_BOUND> in;
    sc_port<placeInterface, M, SC_ALL_BOUND> out;
    sc_port<placeInterface, L, SC_ZERO_OR_MORE_BOUND> inhibitors;

    SC_CTOR(transition) {}

    void fire ()
    {
        bool cond = true;

        for (int i = 0; i < N; ++i) {
            if (in[i]->testTokens() == 0) {
                cond = false;
                break;
            }
        }
        
        // Checking if there are no inhebitors
        if (cond) {
            for (int i = 0; i < L; ++i) {
                if (inhibitors[i]->testTokens() > 0 ) {
                    cond = false;
                    break;
                }
            }
        }

        if (cond) {
            std::cout << this->name() << ": Fired" << std::endl;
            for (int i = 0; i < N; ++i) {
                in[i]->removeTokens();
            }
            for (int i = 0; i < M; ++i) {
                out[i]->addTokens();
            }
        }
        else {
            std::cout << this->name() << ": Not fired" << std::endl;
        }
    }
};

#endif // TRANSITION_H
