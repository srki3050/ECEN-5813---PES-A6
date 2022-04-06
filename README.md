# ECEN-5813---PES-A6

Name : Sricharan Kidambi.
Course : ECEN 5813 Principles of Embedded Software.

//cbfifo.c./.h
Initializes 2 circular buffer objects
Enqueues the requested number of bytes
Dequeues the requested number of bytes
Performs the circular buffer operations to enqueue and dequeue. Here we create 2 buffer objects TXBUF and RXBUF

//command_processor.c/.h

Performs the basic command processing with input commands
1.	Accumulate into buffer
2.	Call the process command function (lexicalise into argv array).
3.	Perform the table mapping to the respective functions
	1.	Functions available (Author name).
	2.	Hexdump handling
	3.	Help String
4.	Additional commands to test Scalability	
UART .c/.h
1.	Inititalize the UART module
2.	Interrupts of the UART module
3.	Write the sys_write function to enqueue to TXBUF (System called)
4.	Write the sys_read function to dequeue from RXBUF (System called)

//hexdump.c/.h

1.	Perform basic hexdump functionality with the given start address and length.
//app.c/.h

Initialize the functions and write the essesntial characteristics of main while loop.
