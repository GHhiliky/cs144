#include "tcp_receiver.hh"
#include<iostream>

// Dummy implementation of a TCP receiver

// For Lab 2, please replace with a real implementation that passes the
// automated checks run by `make check_lab2`.



using namespace std;

void TCPReceiver::segment_received(const TCPSegment &seg) {
    TCPHeader header=seg.header();
    //&&header.ack
    
    if(header.syn){
        _ISN.emplace(header.seqno);
        if(seg.payload().copy().length()>0){
            _start_with_data=true;
        }
    }
    if(_ISN){
        cout<<" isn:"<<_ISN.value().raw_value()<<"seqno:"<<header.seqno.raw_value()<<" payload:"<<seg.payload().copy()<<endl;
        _reassembler.push_substring(seg.payload().copy(),unwrap(header.seqno-1+_start_with_data,_ISN.value(),_reassembler.stream_out().bytes_written()),header.fin);
    }

    if(!_ISN)return;//if it haven't been connected,return
    
    _ackno=wrap(_reassembler.stream_out().bytes_written()+1,_ISN.value());

    if(header.fin&&header.seqno==_ISN.value()){
        _reassembler.stream_out().end_input();
    }

    //when the state is closed,ackno+1
    if(_reassembler.stream_out().input_ended()){
        _ackno=_ackno.value()+1;
    }
    
    
}

optional<WrappingInt32> TCPReceiver::ackno() const { return _ackno; }

size_t TCPReceiver::window_size() const { return _reassembler.stream_out().remaining_capacity(); }
