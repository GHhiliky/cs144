#include "wrapping_integers.hh"
#include<math.h>
#include<iostream>
// Dummy implementation of a 32-bit wrapping integer

// For Lab 2, please replace with a real implementation that passes the
// automated checks run by `make check_lab2`.



using namespace std;

namespace mymath{


    uint64_t abs(uint64_t n){
        return n>0?n:-n;
    }
   

    uint64_t substracion(uint64_t a,uint64_t b){
        return a>b?a-b:b-a;
    }
    uint32_t substracion(uint32_t a,uint32_t b){
        return a>b?a-b:b-a;
    }

}

//! Transform an "absolute" 64-bit sequence number (zero-indexed) into a WrappingInt32
//! \param n The input absolute 64-bit sequence number
//! \param isn The initial sequence number
WrappingInt32 wrap(uint64_t n, WrappingInt32 isn) {
    return isn+n;
}

//! Transform a WrappingInt32 into an "absolute" 64-bit sequence number (zero-indexed)
//! \param n The relative sequence number
//! \param isn The initial sequence number
//! \param checkpoint A recent absolute 64-bit sequence number
//! \returns the 64-bit sequence number that wraps to `n` and is closest to `checkpoint`
//!
//! \note Each of the two streams of the TCP connection has its own ISN. One stream
//! runs from the local TCPSender to the remote TCPReceiver and has one ISN,
//! and the other stream runs from the remote TCPSender to the local TCPReceiver and
//! has a different ISN.
uint64_t unwrap(WrappingInt32 n, WrappingInt32 isn, uint64_t checkpoint) {
    
    uint32_t relative_n=n.raw_value()>isn.raw_value() ? (n.raw_value()-isn.raw_value()):(pow(2,32)-mymath::substracion(n.raw_value(),isn.raw_value()));
   
    uint64_t ans=relative_n;
    for(int i=0;i<32;i++){
        uint64_t _new_val=mymath::abs(ans+pow(2,32+i));
        // cout<<i<<" :1 "<<_new_val<<" : "<<ans<<endl;
        if(mymath::substracion(checkpoint,_new_val)<mymath::substracion(checkpoint,ans)){
            ans=_new_val;
        }
       
    }
    return ans;
}

// int main(){
//     //WrappingInt32 w32=WrappingInt32(pow(2,32)-2);
//     //cout<<unwrap(WrappingInt32(1),WrappingInt32(0),0)<<endl;

//     uint64_t value=413978866713359ll;
//     uint32_t isn=0ll;
//     uint64_t checkpoint=413978866713359ll;
//     //cout<<unwrap(wrap(value,WrappingInt32(isn)),WrappingInt32(isn),checkpoint)<<endl;
//     cout<<unwrap(WrappingInt32(1),WrappingInt32(0),UINT32_MAX)<<endl;
//     cout<<UINT32_MAX<<endl;
    
//     return 0;
// }
