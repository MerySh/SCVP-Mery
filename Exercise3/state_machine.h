#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <systemc.h>
#include <string.h>   

// TODO
SC_MODULE(stateMachine) {
    sc_in<bool> clk;
    sc_in<char> input;

    enum base{Start, G, GA, GAA, GAAG};
    base current_state;

    int pos, counter, counter_A;

    void process()
    {
        pos++;

        switch (current_state) {
            case Start:
                if (input.read() == 'G') {
                    current_state = G;
                    counter_A = 0;
                }
                break;

            case G:
                if (input.read() == 'A') {
                    current_state = GA;
                } else if (input.read() == 'G') {
                    current_state = G;
                } else if (input.read() == 'C' || input.read() == 'T') {
                    current_state = Start;
                }
                break;

            case GA:
                if (input.read() == 'A') {
                    current_state = GAA;
                } else if (input.read() == 'G') {
                    current_state = G;
                } else if (input.read() == 'C' || input.read() == 'T') {
                    current_state = Start;
                }
                break;

            case GAA:
                if (input.read() == 'G') {
                    current_state = GAAG;
                } else if (input.read() == 'A') {
                    current_state = GAA;
                    counter_A++;
                } else {
                    current_state = Start;
                }
                break;

            case GAAG:
            {
                counter++;
            std::cout << "GAA" << std::string(counter_A, 'A') << "G" << std::endl;

            counter++;
            std::cout << "Number of occurences: " << counter << std::endl;
            std::cout << "From Character number " << pos-4-counter_A << " to " << pos <<std::endl;
            std::cout << std::endl;
                if (input.read() == 'G') {
                    current_state = G;
                } else {
                    current_state = Start;
                }
            }
                break;

            default:
                current_state = Start;
                std::cout << "Default" << std::endl;
                counter = 0;
                pos = 0;
                break;
        }
    }

    SC_CTOR(stateMachine)
    {
        SC_METHOD(process);
        sensitive << clk.pos();
        current_state = Start;
        pos = 0;
        counter = 0;
        counter_A = 0;
        dont_initialize();
    }
};

#endif // STATE_MACHINE_H
