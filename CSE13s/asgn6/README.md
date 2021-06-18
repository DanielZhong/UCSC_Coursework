# Assignment 6

The program will implement Huffman encoder and decoder. Encoder will read in a text, use tree data structure to reassign bits for each character based on the text and compress the file size.  Decoder will receive information about the tree data structure and encode output, and then decode it back to the original text characters.

## Build
	$make

## Running
	$./encode
	$./decode

## Command-line
	Both Encode and Decode:
		-h: print help message that describe purpose of the program, command line options,
		-i: Specifies input file
		-o: Specifies output file
		-v: Print compression statics(include uncompressed file size, compressed file size, and space saving)

