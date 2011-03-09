#include <stdio.h>
#include "pcuda_buffer.h"
#include "pcuda_ops.h"

PCudaIntBuffer::PCudaIntBuffer() {
    this->data = new std::vector<long>();
}

PCudaIntBuffer::~PCudaIntBuffer() {
    delete this->data;
}

unsigned int PCudaIntBuffer::size() {
    return this->data->size();
}

void PCudaIntBuffer::write(ErlNifEnv *env, ERL_NIF_TERM data) {
    ERL_NIF_TERM head;
    long value;

    while (enif_get_list_cell(env, data, &head, &data)) {
        if (enif_get_long(env, head, &value)) {
            this->data->push_back(value);
        }
    }
}

bool PCudaIntBuffer::sort() {
    return pcuda_integer_sort(this->data);
}

bool PCudaIntBuffer::contains(ErlNifEnv *env, ERL_NIF_TERM rawTarget) {
    long target;
    if (enif_get_long(env, rawTarget, &target)) {
        return pcuda_integer_binary_search(this->data, target);
    }
    else {
        return false;
    }
}

ERL_NIF_TERM PCudaIntBuffer::toErlTerms(ErlNifEnv *env) {
    std::vector<long>::iterator iter;
    ERL_NIF_TERM retval = enif_make_list(env, 0);
    if (this->data->size() > 0) {
        for (iter = this->data->end(); iter != this->data->begin();) {
            --iter;
            retval = enif_make_list_cell(env, enif_make_long(env, *iter), retval);
        }
    }
    return retval;
}

void PCudaIntBuffer::clear() {
    this->data->clear();
}

bool PCudaIntBuffer::copy(PCudaBuffer *src) {
    if (src->type() == BUF_TYPE_INTEGER) {
        PCudaIntBuffer *source = (PCudaIntBuffer *) src;
        std::vector<long>::iterator iter;
        for (iter = source->data->begin(); iter != source->data->end(); ++iter) {
            this->data->push_back(*iter);
        }
        return true;
    }
    return false;
}
