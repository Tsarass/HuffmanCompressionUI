#pragma once
#ifndef HUFFHELPERCLASSES_H
#define HUFFHELPERCLASSES_H

#include "BinaryTree.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <msclr\marshal_cppstd.h>

#define ENC_BUFFER 16*1024
#define DEC_BUFFER 16*1024

class FreqTable {
public:
	std::vector<fbpair> table;
	FreqTable(unsigned char* buffer, int length);
	FreqTable(int numentries, unsigned char* keys, int* freqs);
	void insert_in_sorted(fbpair dummydat);
};

struct dictentry {
	int byte;
	std::string enc;
	unsigned char depth;
	int code;
	dictentry();
	dictentry(int byte, std::string enc);
	void create_int_code();
};

class HuffDict {
	std::string travstr = "";
	short entries = 0;
	void traverse(Node startnode);
	void update_entry(dictentry entry);

public:
	std::vector<dictentry> dict;
	short num_entries();
	HuffDict(Tree *tree);
};

class HuffEncoder {
	HuffDict* dict;
	int code[256];				//int array holding dict data for faster access
	unsigned char codelen[256];	//char array holding dict data for faster access
	unsigned char *buffer;
	int len;
	char bitstream[ENC_BUFFER]; //the resulting bitstream after encoding
	int pos = 0;				//current position in buffer
	int leftover_bits = 0;			//how many bits were left over from previous chunk
	unsigned int leftover_byte = 0;	//byte holding the leftover bits
	bool done = false;
	int leftover = 0;
	std::string strleftover = "";

public:
	unsigned char lastbits = 0;
	HuffEncoder(unsigned char* buffer, int len, HuffDict* dict);
	int encode_chunk_ex();
	bool isdone() { return this->done; }
	char* get_bitstream_ptr() { return bitstream; };
	float progress();
};

class HuffDecoder {
	Tree* tree;
	Node* curr_node;
	unsigned char *buffer;
	int len = 0;					//length on the buffer in bytes
	char bytestream[DEC_BUFFER];	//the resulting bytestream after decoding
	int bytelength = 0;				//length of decoded message in bytes
	int outputbytes = 0;			//total number of currently output bytes
	unsigned char curr_byte = 0;	//current byte being processed
	int bytepos = 0;				//position of current byte in the buffer
	unsigned char bitpos = 0;		//position in current byte of buffer
	bool done = false;

	bool fetch_next_bit();			//returns the next bit of the buffer

public:
	HuffDecoder(unsigned char* buffer, int len, int bytelength, Tree* tree);
	int decode_chunk();
	bool isdone() { return this->done; }
	char* get_bytestream_ptr() { return bytestream; };
};

#endif