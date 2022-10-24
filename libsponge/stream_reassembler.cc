#include "stream_reassembler.hh"
#include<stdio.h>
#include<iostream>
#include <cstring>

// Dummy implementation of a stream reassembler.

// For Lab 1, please replace with a real implementation that passes the
// automated checks run by `make check_lab1`.

// You will need to add private members to the class declaration in `stream_reassembler.hh`

// template <typename... Targs>
// void DUMMY_CODE(Targs &&... /* unused */) {}
using namespace std;

void  StreamReassembler::copy_to_buf(const string data, const uint64_t index){
    size_t cnt=0;
    for(uint64_t i=index;i<+index+data.length()&&i<_capacity+_output.bytes_read();i++){
        _buf[i%_capacity]= make_pair(data[cnt++],true);
    }
}

StreamReassembler::StreamReassembler(const size_t capacity) : _output(capacity), _capacity(capacity),_buf(vector<pair<char,bool>>(capacity))
                                                            ,_end_input(false),_eof_index(capacity){
    //init
    for(size_t i=0;i<_buf.size();i++){
        _buf[i].second=false;
    }
}


//! \details This function accepts a substring (aka a segment) of bytes,
//! possibly out-of-order, from the logical stream, and assembles any newly
//! contiguous substrings and writes them into the output stream in order.
void StreamReassembler::push_substring(const string &data, const uint64_t index, const bool eof) {
    if(_end_input&&(_output.bytes_written()%_capacity)==_eof_index){return;}
    if(eof){
        _end_input=true;
        _eof_index=(index+data.length())%_capacity;

    }
    if(index>=_capacity+_output.bytes_read()|| index+data.length()<_output.bytes_read()){return;}

    copy_to_buf(data,index);

    //write to _output
    while(_buf[_output.bytes_written()%_capacity].second){
        string _temp_s="";
        _temp_s+=_buf[_output.bytes_written()%_capacity].first;
        _buf[_output.bytes_written()%_capacity].second=false;    //reset

        // cout<<index<<" "<<_temp_s<<endl;
        _output.write(_temp_s);

    }

    //eof
    // cout<<_output.bytes_written()<<" : "<<_eof_index<<endl;
    if(_end_input&&(_output.bytes_written()%_capacity)==_eof_index){
        _output.end_input();
        _buf.clear();
    }

}

size_t StreamReassembler::unassembled_bytes() const {
    size_t cnt=0;
    cout<<endl;
    cout<<"_buf:";
    for(size_t i=0;i<_buf.size();i++){
        if(_buf[i].second) {
            cnt++;
            cout<<_buf[i].first;
        }
    }
    cout<<endl;
    return cnt;
}

bool StreamReassembler::empty() const {
    return unassembled_bytes()==0;

}
void StreamReassembler::clear() {
    for(size_t i=0;i<_buf.size();i++){
        _buf[i].second= false;
    }
}










    






