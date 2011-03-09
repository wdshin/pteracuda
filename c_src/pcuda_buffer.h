#ifndef PCUDA_BUFFER
#define PCUDA_BUFFER

#include <vector>

#include "erl_nif.h"

enum PCudaBufferTypes {
    BUF_TYPE_INTEGER
};

class PCudaBuffer {
public:
    virtual ~PCudaBuffer() { };
    virtual unsigned int size() = 0;
    virtual PCudaBufferTypes type() = 0;
    virtual bool sort() = 0;
    virtual bool contains(ErlNifEnv *env, ERL_NIF_TERM rawTarget) = 0;
    virtual void write(ErlNifEnv *env, ERL_NIF_TERM data) = 0;
    virtual void clear() = 0;
    virtual bool copy(PCudaBuffer *src) = 0;
    virtual ERL_NIF_TERM toErlTerms(ErlNifEnv *env) = 0;
};

class PCudaIntBuffer : public PCudaBuffer {
public:
    PCudaIntBuffer();
    virtual ~PCudaIntBuffer();
    virtual unsigned int size();
    virtual PCudaBufferTypes type() { return BUF_TYPE_INTEGER; };
    virtual bool sort();
    virtual bool contains(ErlNifEnv *env, ERL_NIF_TERM rawTarget);
    virtual ERL_NIF_TERM toErlTerms(ErlNifEnv *env);
    virtual void write(ErlNifEnv *env, ERL_NIF_TERM data);
    virtual void clear();
    virtual bool copy(PCudaBuffer *src);

protected:
    std::vector<long> *data;
};
#endif
