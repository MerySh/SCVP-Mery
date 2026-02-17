#ifndef BUS_H
#define BUS_H

#include <iostream>
#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/tlm_quantumkeeper.h>

/* Address	Map:
 0‐511		‐>	memory0
 512‐1023	‐>	memory1 */

// TODO: add your code here

/*This is a general case:
     'I' number of Initiators and 'T' number of targets (memories) of size 'MemSize' each */
template <unsigned int I=1, unsigned int T=1, unsigned int MemSize=1024>
class bus: sc_module, tlm::tlm_bw_transport_if<>, tlm::tlm_fw_transport_if<>{
    public:
        tlm::tlm_initiator_socket<> iSocket[I];
        tlm::tlm_target_socket<> tSocket[T];

        SC_CTOR(bus)
        {
            for (int i=0; i<I; i++){
                iSocket[i].bind(*this);
            }          
            for (int t=0; t<T; t++){
                tSocket[t].bind(*this);
            }
        }

        void b_transport(tlm::tlm_generic_payload &trans, sc_time &delay){
            if (trans.get_address() >= MemSize*T){
                cout << "ERROR: address out of range!" << endl;
                SC_REPORT_FATAL(this->name(),"Out of Range");
            }

            int addr = trans.get_address();
            int i = addr/MemSize;
            
            addr %= MemSize;
            trans.set_address(addr);
            iSocket[i]->b_transport(trans, delay); // Remember to call iSockets here not tSockets
        }
        
        /* Dummy functions that have to be implemented */
    
    virtual tlm::tlm_sync_enum nb_transport_fw(
            tlm::tlm_generic_payload& trans,
            tlm::tlm_phase& phase,
            sc_time& delay )
    {
        SC_REPORT_FATAL(this->name(),"nb_transport_fw is not implemented");
        return tlm::TLM_ACCEPTED;
    }

    
    bool get_direct_mem_ptr(tlm::tlm_generic_payload& trans,
                            tlm::tlm_dmi& dmi_data)
    {
        SC_REPORT_FATAL(this->name(),"get_direct_mem_ptr is not implemented");
        return false;
    }

    
    unsigned int transport_dbg(tlm::tlm_generic_payload& trans)
    {
        SC_REPORT_FATAL(this->name(),"transport_dbg is not implemented");
        return 0;
    }

    
    void invalidate_direct_mem_ptr(sc_dt::uint64 start_range,
                                   sc_dt::uint64 end_range)
    {
        SC_REPORT_FATAL(this->name(),"invalidate_direct_mem_ptr not implement");
    }

    
    tlm::tlm_sync_enum nb_transport_bw(
            tlm::tlm_generic_payload& trans,
            tlm::tlm_phase& phase,
            sc_time& delay)
    {
        SC_REPORT_FATAL(this->name(),"nb_transport_bw is not implemented");
        return tlm::TLM_ACCEPTED;
    }
};
#endif // BUS_H
