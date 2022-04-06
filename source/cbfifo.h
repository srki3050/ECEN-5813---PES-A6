/* Name  		: Sricharan Kidambi S
 * File  		: cbfifo.h
 * Date	 		: 04/06/2022
 * Brief 		: Protype to Perform Circular Buffer Operation.
 * References	: Took Excerpts from MY assignment 2 and modified a little bit to fit this scenario.
 * 				  Credits to Howdy Pierce, and TA's for helping to configure a cbfifo.
 */

#ifndef CBFIFO_H_
#define CBFIFO_H_
#include "stdint.h"
#include "stdbool.h"

#define MAX_SIZE 256

typedef struct{
    uint8_t buf[MAX_SIZE];
    uint8_t head;
    uint8_t tail;
    size_t length;
}cbfifo_t;

void initialize(cbfifo_t *cb);
/* Function : Enqeues the amount of bytes specified in nbytes to the buffer of that object.
 * Parameters: The cbfifo object, input string, no of bytes to be enqueued from input string.
 * Returns : The number of nbytes enqueued. (if the space in buffer is 3 and nbytes = 10, then nbytes = 3
 */
size_t enqueue(cbfifo_t *cb,void *buf,size_t nbytes);
/* Function : deqeues the amount of bytes specified in nbytes from the buffer of that object.
 * Parameters: The cbfifo object, resultant string, no of bytes to be enqueued from input string.
 * Returns : The number of nbytes dequeued. (if no of elements in buffer is 3 and nbytes = 10, then nbytes = 3
 */
size_t dequeue(cbfifo_t *cb,void *buf,size_t nbytes);
/* Function : check for buffer full condition
 * Parameters: The cbfifo object.
 * Returns : 1 if buffer is full, 0 otherwise.
 */
bool bufferfull(cbfifo_t *cb);
/* Function : check for buffer full condition
 * Parameters: The cbfifo object.
 * Returns :1 if buffer is empty, 0 otherwise.
 */
bool bufferempty(cbfifo_t *cb);

#endif /* CBFIFO_H_ */
