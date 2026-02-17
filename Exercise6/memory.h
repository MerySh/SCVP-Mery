#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <tlm.h>
#include <systemc.h>


// TODO: add your code here
template <unsigned int size = 1024>
class memory: sc_module, tlm::tlm_fw_transport_if<>{
    private:
        char mem[size];
    public:
        tlm::tlm_target_socket<> tSocket;
        SC_CTOR(memory) : tSocket("tSocket")
        {
            tSocket.bind(*this);

            /* Initializing the memory with 0 */
            for (int i=0; i<size; i++){
                mem[i]=0;
            }
        }

        void b_transport(tlm::tlm_generic_payload &trans, sc_time &delay){
            if (trans.get_address() >= size){
                cout << "ERROR: address out of range!" << endl;
                SC_REPORT_FATAL(this->name(),"Out of Range");
            }

            if (trans.get_command() == tlm::TLM_READ_COMMAND){
                /* if it is a read, then get_data_ptr() returns the address of the data to be read */
                memcpy(trans.get_data_ptr(), mem+trans.get_address(), trans.get_data_length());
            }
            else if (trans.get_command() == tlm::TLM_WRITE_COMMAND){
                /* if it is a write, then get_data_ptr() returns the the data to be written */
                memcpy(mem+trans.get_address(), trans.get_data_ptr(), trans.get_data_length());
            }
            delay = delay + sc_time(20, SC_NS);
            trans.set_response_status( tlm::TLM_OK_RESPONSE );
        }

        /* Dummy functions that have to be implemented */
         virtual tlm::tlm_sync_enum nb_transport_fw(
            tlm::tlm_generic_payload& trans,
            tlm::tlm_phase& phase,
            sc_time& delay )
        {
            return tlm::TLM_ACCEPTED;
        }

        bool get_direct_mem_ptr(tlm::tlm_generic_payload& trans,
            tlm::tlm_dmi& dmi_data)
        {
            return false;
        }

        unsigned int transport_dbg(
            tlm::tlm_generic_payload& trans)
        {
            return 0;
        }
        

};
#endif // MEMORY_H
