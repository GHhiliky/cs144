#include "tcp_sender.hh"

#include "tcp_config.hh"

#include <random>
#include<iostream>
// Dummy implementation of a TCP sender

// For Lab 3, please replace with a real implementation that passes the
// automated checks run by `make check_lab3`.



using namespace std;

//! \param[in] capacity the capacity of the outgoing byte stream
//! \param[in] retx_timeout the initial amount of time to wait before retransmitting the oldest outstanding segment
//! \param[in] fixed_isn the Initial Sequence Number to use, if set (otherwise uses a random ISN)
TCPSender::TCPSender(const size_t capacity, const uint16_t retx_timeout, const std::optional<WrappingInt32> fixed_isn)
    : _isn(fixed_isn.value_or(WrappingInt32{random_device()()}))
    , _initial_retransmission_timeout{retx_timeout}
    , _stream(capacity) 
    ,_window_size(1)
    ,_timer(retx_timeout)
    ,_count_retransmission(0){cout<<"ISN:"<<_isn.raw_value()<<endl;}

uint64_t TCPSender::bytes_in_flight() const { return _next_seqno-_ackno;}

void TCPSender::fill_window() {
    // cout<<"_next_seqno:"<<_next_seqno<<endl;
    if(_have_FIN)return;
    // cout<<"bytes_in_flight"<<bytes_in_flight()<<",win="<<_window_size<<endl;
    uint16_t window_size=_window_size?_window_size:1;
    
    
    while(bytes_in_flight()<window_size){
        //generate a segment
        TCPSegment segment=TCPSegment();
        //set header
        segment.header().win=window_size;
        segment.header().seqno=next_seqno();
        if(_have_SYN==false){
            segment.header().syn=true;
            _have_SYN=true;

        }
        // cout<<"_next_seqno: after"<<_next_seqno<<endl;
        // if(_stream.eof()){
        //     cout<<window_size-bytes_in_flight()<<" "<<segment.length_in_sequence_space()<<endl;
        // }
       

        //if stream is empty ,return
        if(_stream.buffer_empty()&&!(segment.header().syn==true||_stream.eof()))break;

        if(segment.header().syn==false&&!_stream.buffer_empty()){
             std::string str_payload=string();
             if(_stream.buffer_size()>=TCPConfig::MAX_PAYLOAD_SIZE){
                str_payload=_next_seqno+TCPConfig::MAX_PAYLOAD_SIZE-1<=_ackno+window_size-1 ? _stream.read(TCPConfig::MAX_PAYLOAD_SIZE) : _stream.read(_ackno+window_size-1-_next_seqno+1);
             }else{
                str_payload=_next_seqno+TCPConfig::MAX_PAYLOAD_SIZE-1<=_ackno+window_size-1 ? _stream.read(_stream.buffer_size()) : _stream.read(_ackno+window_size-1-_next_seqno+1);
             }
            
             segment.payload()=Buffer(str_payload.c_str());
        }
        

         if(_stream.eof()&&(window_size-bytes_in_flight()-segment.length_in_sequence_space()>0)){
            segment.header().fin=true;
            _have_FIN=true;
        }

        _next_seqno+=segment.length_in_sequence_space();//update _next_seqno,note that FIN or SYN occupies one byte


        // cout<<"payload:"<<segment.payload().copy()<<",fin="<<segment.header().fin<<endl;
        //add to queue of segments will be sent soon
        _segments_out.push(segment);
        _outstanding_segments.push(segment);

        // cout<<"SYN:"<<_segments_out.front().header().syn<<endl;

        //start timer
        if(!_timer.status()){
            _timer.start();
        }

        if(_have_FIN)break;
    }

    // cout<<"cnt:"<<cnt<<endl;
    // cout<<"_next_seqno:"<<_next_seqno<<endl;

}

//! \param ackno The remote receiver's ackno (acknowledgment number)
//! \param window_size The remote receiver's advertised window size
void TCPSender::ack_received(const WrappingInt32 ackno, const uint16_t window_size) { 
    if(unwrap(ackno,_isn,_ackno)<_ackno||unwrap(ackno,_isn,_ackno)>_ackno+(_window_size?_window_size:1)) return;//when new ackno equals to _ackno,it maybe update window_size
    if(unwrap(ackno,_isn,_ackno)==_ackno&&window_size==_window_size)return;//reack

    // cout<<"ack_received():ackno="<<unwrap(ackno,_isn,_ackno)<<",win="<<window_size<<endl;
    
    _ackno=unwrap(ackno,_isn,_ackno);
    _window_size=window_size;

    //update outstanding segments queue
    while(!_outstanding_segments.empty()){
        TCPSegment front_segment=_outstanding_segments.front();
        if(unwrap(front_segment.header().seqno,_isn,_ackno)+front_segment.length_in_sequence_space()<=_ackno){
            _outstanding_segments.pop();
            
        }else{
            break;
        }
        
    }
    
    //if there is no outstanding segment,stop timer
    if(_outstanding_segments.empty()){
        _timer.turn_off();
    }

    _timer.start();
    _count_retransmission=0;

    //FIN_ACKED,stop timer
    if(stream_in().eof()
        &&next_seqno_absolute() == stream_in().bytes_written() + 2
        &&bytes_in_flight() == 0){
            _timer.turn_off();
    }



    
}

//! \param[in] ms_since_last_tick the number of milliseconds since the last call to this method
void TCPSender::tick(const size_t ms_since_last_tick) { 
    // cout<<"_time:"<<_timer.get_time()<<",RTO="<<_initial_retransmission_timeout<<endl;
    
    if(_timer.status()&&_timer.expire(ms_since_last_tick)){
        // cout<<"_time2:"<<_timer.get_time()<<",RTO="<<_initial_retransmission_timeout<<endl;
        _segments_out.push(_outstanding_segments.front());

        if(_window_size>0){

            //count retransmission times
            _count_retransmission++;

            //double RTO
            _timer.double_RTO();
           
        }

        //reset
        _timer.reset();

    }
    cout<<"_count_retransmission"<<_count_retransmission<<endl;


}

unsigned int TCPSender::consecutive_retransmissions() const { return _count_retransmission; }


void TCPSender::send_empty_segment() {
    TCPSegment segment=TCPSegment();
    TCPHeader &header= segment.header();
    header.win=_window_size;
    header.seqno=next_seqno();
    header.ack=true;
    cout<<"send_empty_segment"<<endl;

    _segments_out.push(segment);


}
