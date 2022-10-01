#include "HuffHelperClasses.h"
#include "WindowInfo.h"
#include <assert.h>

using namespace std;

FreqTable::FreqTable(unsigned char* buffer, int length) {
	/*Creates the frequency table data from a buffer of bytes*/
	vector<int> fqs(256, 0);	//vector of every possible byte frequency

	for (int i = 0; i < length; i++)	//fill freq vector
	{
		fqs[(unsigned char)buffer[i]]++;
	}

	int count = 0;
	for (int i = 0; i < 256; i++) //count non zero entries
	{
		if (fqs[i] > 0) count++;
	}

	table.clear();
	table.resize(count);

	int j = 0;
	for (int i = 0; i < 256; i++)
	{
		if (fqs[i] > 0) {
			table[j].freq = fqs[i];
			table[j].byte = i;
			j++;
		}
	}

	//sort table by increasing frequencies
	sort(table.begin(), table.end());
}

FreqTable::FreqTable(int numentries, unsigned char* keys, int* freqs) {
	table.clear();
	table.resize(numentries);
	for (int i = 0; i < numentries; i++) {
		table[i].byte = keys[i];
		table[i].freq = freqs[i];
		assert(freqs[i] >= 0);
	}
}

void FreqTable::insert_in_sorted(fbpair dummydat) {
	/*inserts the fbpair object in sorted table by frequency*/
	//check if to append to the end
	if (table.back().freq > dummydat.freq) {
		table.push_back(dummydat);
		return;
	}
	for (vector<fbpair>::iterator it = table.begin(); it != table.end(); ++it) {
		if ((*it).freq <= dummydat.freq) {
			table.insert(it, dummydat);
			break;
		}
	}
}

dictentry::dictentry() {
	this->byte = 0;
	this->enc = "";
	this->depth = 0;
	this->code = 0;
}

dictentry::dictentry(int byte, string enc) {
	this->byte = byte;
	this->enc = enc;
	this->depth = enc.length();
	create_int_code();
}

void dictentry::create_int_code() {
	this->code = 0;
	//bitwise operations to construct byte from enc string
	for (int i = this->enc.size()-1; i >= 0; i--){
		if (this->enc[i] == '1') {
			this->code += 1 << (this->enc.size()-1 - i);
		}
	}
}

HuffDict::HuffDict(Tree *tree) {
	//initialize dictionary sorted with all 256 bytes
	this->dict.resize(256);
	for (int i = 0; i < 256; i++) {
		this->dict[i].byte = i;
	}

	Node* root = (*tree).getRoot();
	if (tree->numnodes()) {
		traverse(*root);	//traversing creates the huffman dictionary
	}
	else {
		this->entries = 0;
	}
}

void HuffDict::traverse(Node startnode) {
	if (!startnode.dummy) {
		dictentry entry(startnode.key, travstr);
		update_entry(entry);
		entries++;
		if (travstr.length() > 0) {
			travstr.pop_back();
		}
		return;
	}
	if (startnode.l) {
		travstr += '0';
		this->traverse(*startnode.l);
	}
	if (startnode.r) {
		travstr += '1';
		this->traverse(*startnode.r);
	}
	if ((startnode.dummy) && (!travstr.empty())) {
		travstr.pop_back();
	}
}

short HuffDict::num_entries() {
	return this->entries;
}

void HuffDict::update_entry(dictentry entry) {
	dict[entry.byte] = entry;
}

HuffEncoder::HuffEncoder(unsigned char* buffer, int len, HuffDict* dict) {
	this->buffer = buffer;
	this->len = len;
	this->dict = dict;
	for (int i = 0; i < 256; i++) {
		this->code[i] = dict->dict[i].code;
		this->codelen[i] = dict->dict[i].depth;
	}
}

int HuffEncoder::encode_chunk_ex() {
	int bitstreampos = 0;							//position in the bitstream
	unsigned char encoded_byte = 0;					//the byte to be added to the bitstream
	unsigned int curr_byte = this->leftover_byte;	//byte forming by shifting bitcodes into place
	unsigned char bitlen = this->leftover_bits;		//bit length of current byte
	unsigned char bitcodelen = 0;					//length of bitcode for current code

	while ((bitstreampos < ENC_BUFFER) && (!this->done)) {
		
		//first create an int holding more than 8 bits of encoded stream
		while (bitlen < 8) {
			bitcodelen = this->codelen[buffer[this->pos]];
			curr_byte = curr_byte << bitcodelen;
			curr_byte += this->code[buffer[this->pos]];
			this->pos++;
			bitlen += bitcodelen;
			if (this->pos >= this->len) {
				this->done = true;
				break;
			}
		}

		//second break the int into full 8-bit sequences and keep the remainder
		while ((bitlen >= 8) && (bitstreampos < ENC_BUFFER)) {	//have to recheck position in bitstream array
			encoded_byte = curr_byte >> (bitlen - 8);
			bitlen -= 8;
			curr_byte = (curr_byte << (sizeof(curr_byte) * 8 - bitlen)) >> (sizeof(curr_byte) * 8 - bitlen);
			if (!bitlen) {
				curr_byte = 0;
			}
			this->bitstream[bitstreampos] = encoded_byte;
			bitstreampos++;
		}

		//done flag means the last byte of buffer has been processed
		if ((this->done) && (bitlen > 0)) {
			encoded_byte = curr_byte << (8 - bitlen);
			this->bitstream[bitstreampos] = encoded_byte;
			bitstreampos++;
			this->lastbits = bitlen;
		}
	}

	this->leftover_bits = bitlen;
	if (!bitlen) {
		this->leftover_byte = 0;
	} else {
		this->leftover_byte = curr_byte;
	}
	return bitstreampos;	//bitstreampos actually holds the byte size of the chunk
}

float HuffEncoder::progress() {
	return float(this->pos) / this->len;
}

HuffDecoder::HuffDecoder(unsigned char* buffer, int len, int bytelength, Tree* tree) {
	this->len = len;
	this->tree = tree;
	this->bytelength = bytelength;
	this->buffer = buffer;
	this->bytepos = 0;
	this->bitpos = 1;
	this->curr_byte = buffer[0];
	this->curr_node = this->tree->getRoot();
}

int HuffDecoder::decode_chunk() {
	int* addr = &(this->bytelength);
	int bytestreampos = 0;				//position in the bytestream
	bool bit;
	while (bytestreampos < DEC_BUFFER){
		bit = fetch_next_bit();
		if (!bit) {
			this->curr_node = this->curr_node->l;
		} else {
			this->curr_node = this->curr_node->r;
		}
		if (!this->curr_node->hasChildren) {
			this->bytestream[bytestreampos] = this->curr_node->key;
			this->curr_node = this->tree->getRoot();
			bytestreampos++;
			this->outputbytes++;
		}
		if (this->outputbytes >= this->bytelength) {
			this->done = true;
			break;
		}
	}
	return bytestreampos;
}

bool HuffDecoder::fetch_next_bit() {
	unsigned char curr_bit = this->bitpos;
	if (curr_bit > 8) {
		curr_bit = 1;
		this->bytepos++;
		this->curr_byte = buffer[this->bytepos];
	}
	bool bit = this->curr_byte & (1 << (8-curr_bit));
	curr_bit++;
	this->bitpos = curr_bit;
	return bit;
}
