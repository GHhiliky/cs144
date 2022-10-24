#include "byte_stream.hh"
#include <string>
#include<vector>
#include<iostream>
// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

// template <typename... Targs>
// void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity) { 
    _capacity=capacity;
    _buf=vector<char>(capacity);
    
 }
 ByteStream::ByteStream(size_t capacity,vector<char> buf,unsigned nread,unsigned nwrite,bool end_input){
    _capacity=capacity;
    _buf=buf;
    _nread=nread;
    _nwrite=nwrite;
    _end_input=end_input;


 }

size_t ByteStream::write(const string &data) {
    //if(input_ended())return 0;

    size_t remaining_capacity=ByteStream::remaining_capacity();
    size_t count=0;
    for(size_t i=_nwrite;i<_nwrite+data.length()&&i<_nwrite+remaining_capacity;i++){
        _buf[i%_capacity]=data[count++];
        
    }
    _nwrite+=count;
    
    return count;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    size_t buffer_size=ByteStream::buffer_size();
    string data=string();
    for(size_t i=_nread;i<_nread+len&&i<_nread+buffer_size;i++){
        data.push_back(_buf[i%_capacity]);
    }

    return data;
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) { 
    size_t buffer_size=ByteStream::buffer_size();
    size_t count=0;
    for(size_t i=_nread;i<_nread+len&&i<_nread+buffer_size;i++){
        count++;

    }
    _nread+=count;

}

std::string ByteStream::read(const size_t len) {
    string data=peek_output(len);
    pop_output(len);
    return data;
}

void ByteStream::end_input() {_end_input=true;}

bool ByteStream::input_ended() const { return _end_input; }

size_t ByteStream::buffer_size() const { return _nwrite-_nread; }

bool ByteStream::buffer_empty() const { return buffer_size()==0; }

bool ByteStream::eof() const { 

    return input_ended()&&buffer_empty(); 
}

size_t ByteStream::bytes_written() const { return _nwrite; }

size_t ByteStream::bytes_read() const { return _nread; }

size_t ByteStream::remaining_capacity() const { return _capacity-(_nwrite-_nread); }


