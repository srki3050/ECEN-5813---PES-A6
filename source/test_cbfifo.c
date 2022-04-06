/* Name  		: Sricharan Kidambi S
 * File  		: test_cbfifo.c
 * Date	 		: 04/06/2022
 * Brief 		: Writing a basic test suite to circular buffers program.
 * References	: Discussed with Abijith Ananda Krishnan and compared his test suite against my production code
 * 				  to see if mine is a compatible version to most of the scenarios.
 */

#include "test_cbfifo.h"
void test_cbfifo()
{
	char *str ="To be, or not to be: that is the question:\n"
	        "Whether 'tis nobler in the mind to suffer\n"
			"The slings and arrows of outrageous fortune,\n"
	        "Or to take arms against a sea of troubles,\n"
	        "And by opposing end them? To die, to sleep--\n"
	        "No more--and by a sleep to say we end\n"
	        "The heart-ache and the thousand natural shocks\n"
	        "That flesh is heir to, 'tis a consummation\n"
	        "Devoutly to be wish'd. To die, to sleep;\n"
	        "To sleep: perchance to dream: ay, there's the rub;\n"
	        "For in that sleep of death what dreams may come\n"
	        "When we have shuffled off this mortal coil,\n"
	        "Must give us pause.";
	char buf[1024];
	cbfifo_t cb_TX;
	initialize(&cb_TX);
	const int cap = MAX_SIZE;
	assert(strlen(str) >= cap*2);
	assert(sizeof(buf)>cap);
	assert(cap==MAX_SIZE);
	assert(cb_TX.length==0);
	assert(dequeue(&cb_TX,buf,cap)==0);
	assert(dequeue(&cb_TX,buf,1)==0);
	assert(enqueue(&cb_TX,str,10)==10);
	assert(cb_TX.length==10);
	assert(dequeue(&cb_TX,buf,10)==10);
	assert(strncmp(buf,str,10)==0);
	assert(cb_TX.length==0);
	assert(enqueue(&cb_TX,str,20)==20);
	assert(cb_TX.length==20);
	assert(dequeue(&cb_TX,buf,5)==5);
	assert(cb_TX.length==15);
	assert(dequeue(&cb_TX,buf+5,20)==15);
	assert(cb_TX.length==0);
	assert(strncmp(buf,str,20)==0);
	assert(enqueue(&cb_TX,str,cap)==cap);
	assert(cb_TX.length==cap);
	assert(enqueue(&cb_TX,str,1)==0);
	assert(dequeue(&cb_TX,buf,cap)==cap);
	assert(cb_TX.length==0);
	assert(strncmp(buf,str,cap)==0);
	assert(enqueue(&cb_TX,str,20)==20);
	assert(cb_TX.length==20);
	assert(dequeue(&cb_TX,buf,18)==18);
	assert(cb_TX.length==2);
	assert(strncmp(buf,str,18)==0);
	int chunk_size = (cap-2)/4;
	for(int i=0;i<4;i++)
	{
		assert(enqueue(&cb_TX,str+i*chunk_size,chunk_size)==chunk_size);
		assert(cb_TX.length==(i+1)*chunk_size+2);
	}
	assert(cb_TX.length == 4*chunk_size+2);
	assert(dequeue(&cb_TX,buf,2)==2);
	assert(strncmp(buf,str+18,2)==0);
	for(int i=0;i<chunk_size*4;i++)
	{
		assert(dequeue(&cb_TX,buf+i,1)==1);
		assert(cb_TX.length==chunk_size*4 - i - 1);
	}
	assert(strncmp(buf,str,chunk_size*4)==0);
	assert(enqueue(&cb_TX,str, 65) == 65);
	assert(enqueue(&cb_TX,str+65, cap) == cap-65);
	assert(cb_TX.length == cap);
	assert(dequeue(&cb_TX,buf,cap) == cap);
	assert(cb_TX.length == 0);
	assert(strncmp(buf, str, cap) == 0);
	assert(enqueue(&cb_TX,str,0) == 0);
	assert(cb_TX.length == 0);
	assert(enqueue(&cb_TX,str,32) == 32);
	assert(cb_TX.length == 32);
	assert(dequeue(&cb_TX,buf,16) == 16);
	assert(cb_TX.length == 16);
	assert(strncmp(buf, str, 16) == 0);
	assert(enqueue(&cb_TX,str+32, 32) == 32);
	assert(cb_TX.length == 48);
	assert(enqueue(&cb_TX,str+64, cap-64) == cap-64);
	assert(cb_TX.length == cap-16);
	assert(dequeue(&cb_TX,buf+16, cap-16) == cap-16);
	assert(strncmp(buf, str, cap) == 0);
	assert(enqueue(&cb_TX,str, 32) == 32);
	assert(cb_TX.length == 32);
	assert(dequeue(&cb_TX,buf, 16) == 16);
	assert(cb_TX.length == 16);
	assert(strncmp(buf, str, 16) == 0);
	assert(enqueue(&cb_TX,str+32, cap-20) == cap-20);
	assert(cb_TX.length == cap-4);
	assert(dequeue(&cb_TX,buf, cap-8) == cap-8);
	assert(strncmp(buf, str+16, cap-8) == 0);
	assert(cb_TX.length == 4);
	assert(dequeue(&cb_TX,buf, 8) == 4);
	assert(strncmp(buf, str+16+cap-8, 4) == 0);
	assert(cb_TX.length == 0);
	assert(enqueue(&cb_TX,str, 49) == 49);
	assert(cb_TX.length == 49);
	assert(dequeue(&cb_TX,buf, 16) == 16);
	assert(cb_TX.length == 33);
	assert(strncmp(buf, str, 16) == 0);
	assert(enqueue(&cb_TX,str+49, cap-33) == cap-33);
	assert(cb_TX.length == cap);
	assert(dequeue(&cb_TX,buf, cap) == cap);
	assert(cb_TX.length == 0);
	assert(strncmp(buf, str+16, cap) == 0);
	assert(enqueue(&cb_TX,str, 32) == 32);
	assert(cb_TX.length == 32);
	assert(dequeue(&cb_TX,buf, 16) == 16);
	assert(cb_TX.length == 16);
	assert(strncmp(buf, str, 16) == 0);
	assert(enqueue(&cb_TX,str+32, cap) == cap-16);
	assert(dequeue(&cb_TX,buf, 1) == 1);
	assert(cb_TX.length == cap-1);
	assert(dequeue(&cb_TX,buf+1, cap-1) == cap-1);
	assert(cb_TX.length == 0);
	assert(strncmp(buf, str+16, cap) == 0);
	int wpos=0, rpos=0;
	assert(enqueue(&cb_TX,str, cap-4) == cap-4);
	wpos += cap-4;
	assert(cb_TX.length == cap-4);
	assert(dequeue(&cb_TX,buf, 32) == 32);
	rpos += 32;
	assert(cb_TX.length == cap-36);
	assert(strncmp(buf, str, 32) == 0);
	assert(enqueue(&cb_TX,str+wpos, 12) == 12);
	wpos += 12;
	assert(cb_TX.length == cap-24);
	assert(enqueue(&cb_TX,str+wpos, 16) == 16);
	assert(cb_TX.length == cap-8);
	assert(dequeue(&cb_TX,buf, cap) == cap-8);
	assert(cb_TX.length == 0);
	assert(strncmp(buf, str+rpos, cap-8) == 0);
	wpos=0;
	rpos=0;
	assert(enqueue(&cb_TX,str, cap-4) == cap-4);
	wpos += cap-4;
	assert(cb_TX.length == cap-4);
	assert(dequeue(&cb_TX,buf, 32) == 32);
	rpos += 32;
	assert(cb_TX.length == cap-36);
	assert(strncmp(buf, str, 32) == 0);
	assert(enqueue(&cb_TX,str+wpos, 12) == 12);
	wpos += 12;
	assert(cb_TX.length == cap-24);
	assert(enqueue(&cb_TX,str+wpos, 24) == 24);
	assert(cb_TX.length == cap);
	assert(dequeue(&cb_TX,buf, cap) == cap);
	assert(cb_TX.length == 0);
	assert(strncmp(buf, str+rpos, cap) == 0);
	wpos=0;
	rpos=0;
	assert(enqueue(&cb_TX,str, cap-4) == cap-4);
	wpos += cap-4;
	assert(cb_TX.length == cap-4);
	assert(dequeue(&cb_TX,buf, 32) == 32);
	rpos += 32;
	assert(cb_TX.length == cap-36);
	assert(strncmp(buf, str, 32) == 0);
	assert(enqueue(&cb_TX,str+wpos, 12) == 12);
	wpos += 12;
	assert(cb_TX.length == cap-24);
	assert(enqueue(&cb_TX,str+wpos, 64) == 24);
	assert(cb_TX.length == cap);
	assert(dequeue(&cb_TX,buf, cap) == cap);
	assert(cb_TX.length == 0);
	assert(strncmp(buf, str+rpos, cap) == 0);
	printf("%s: Circular buffer Test cases passed",__FUNCTION__);
}
