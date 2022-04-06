/* Name  		: Sricharan Kidambi S
 * File  		: cbfifo.c
 * Date	 		: 04/06/2022
 * Brief 		: Perform Circular Buffer Operation.
 * References	: Took Excerpts from MY assignment 2 and modified a little bit to fit this scenario.
 * 				  Credits to Howdy Pierce, and TA's for helping to configure a cbfifo.
 * 				  For Desription please look cbfifo.h
 */
#include "cbfifo.h"
#include "assert.h"
#include "stddef.h"

void initialize(cbfifo_t *cb){
    cb->head = 0;
    cb->tail = 0;
    cb->length = 0;
    __builtin_memset(cb->buf,'_',MAX_SIZE);
}
size_t enqueue(cbfifo_t *cb,void *buf,size_t nbytes){
    if(buf == NULL)
    	return -1;
    if(cb->length == MAX_SIZE)
        return 0;
    if(cb->length + nbytes > MAX_SIZE)
        nbytes = MAX_SIZE - cb->length;
    for(int i = 0;i < nbytes;i++){
        cb->buf[cb->tail] = * (uint8_t *)buf++;//[cb->buffer_position];
        cb->tail = ((cb->tail + 1) & (MAX_SIZE - 1));
        cb->length += 1;
    }
    return nbytes;
}
size_t dequeue(cbfifo_t *cb,void *buf,size_t nbytes){
    if(buf == NULL)
    	return -1;
    if(cb->length == 0)
        return 0;
    if(cb->length < nbytes)
        nbytes = cb->length;
    for(int i = 0;i < nbytes;i++){
        *(uint8_t *)buf++ = cb->buf[cb->head];
        cb->buf[cb->head] = '_';
        cb->head = ((cb->head + 1) & (MAX_SIZE - 1));
        cb->length -= 1;
    }
    return nbytes;
}
bool bufferfull(cbfifo_t *cb){
	if(cb->length == MAX_SIZE)
		return 1;
	else{
		return 0;
	}
}

bool bufferempty(cbfifo_t *cb){
	if(cb->length == 0)
		return 1;
	else{
		return 0;
	}
}
