# Assignment 5

This encode and decode program(Hamming) will check and correct errors for text caused by random bit-flip(noise). Specifically, we will multiply binary from a string in text with the G matrix provided in pdf to encode and multiply H matrix for decode. If decode result (0, 0, 0, 0) meaning no error, else if the result is 4 bits appear in the matrix, meaning it’s possible to fix. Otherwise if the result 4 bits not 0,0,0,0 and not appear in the matrix, then it’s an error and not possible to fix.

## Build
	$make

## Running
	$./encode
	$./decode
	$./entropy
	$./error

## Command-line
	Encode:
    		-h: print help message
    		-i: input for input file
    		-o: output for output file
	Decode:
    		-h: print help message
    		-i: input for input file
    		-o: output for output file
    		-v: print the statics of error stat(Total bytes processed, uncorrected errors, corrected errors, and error rate)

	Error:
		-h program usage and help
		-s input random seed
		-e input error rate
