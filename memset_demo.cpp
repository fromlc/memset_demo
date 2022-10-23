//------------------------------------------------------------------------------
// memset_demo.cpp
// 
// Demonstrates how to initialize an array, 
// or a block of dynamically allocated memory
//------------------------------------------------------------------------------

#include <iostream>
#include <cstring>		// for memset()

//------------------------------------------------------------------------------
// constants
//------------------------------------------------------------------------------
constexpr int ELEMENTS = 10;

//------------------------------------------------------------------------------
// using symbols
//------------------------------------------------------------------------------
using std::cout;

//------------------------------------------------------------------------------
// entry point
//------------------------------------------------------------------------------
int main() {
	// When you declare an array, initialize all elements to zero with {} 

	int ai[ELEMENTS] = {};

	// What happens when you don't initialize the elements?
	// Array memory will contain whatever was there before.
	int aiJunk[ELEMENTS];

	// You can also use memset() but be careful: memset works with bytes.
	// memset() needs to know the number of _bytes_ in your array.

	// How many bytes long is array ai?

	// This won't work as intended..
	memset(ai, 0, ELEMENTS);			// This is a bug!

	// ..in fact, this creates a subtle bug. More on this later.

	// Array ai has more than ELEMENTS bytes: instead,
	// each of the int elements is (usually) 4 bytes long.

	memset(ai, 0, ELEMENTS * 4);		// This works on your platform, but not on all platforms.

	// Skilled programmers don't assume an int is 4 bytes long!
	// We use the sizeof() function that C and C++ provide.

	// This works on any platform
	memset(ai, 0, ELEMENTS * sizeof(int));

	// Use the new operator to allocate arrays like this
	int* pI = new int[ELEMENTS];

	// DON'T do this:
	int* pOneI = new int(ELEMENTS);		// This is a bug!
	//memset(pOneI, 0, ELEMENTS * sizeof(int));

	// pOneI will point to an array of one int initialized to the value of ELEMENTS
	delete pOneI;

	// Write a 0 to each byte of the memory block pointed to by pV
	void* pV = memset(pI, 0, ELEMENTS * sizeof(int));

	// Release allocated arrays like this
	delete[] pI;

	//------------------------------------------------------------------------------
	// Remember that subtle bug on line 39? 
	//------------------------------------------------------------------------------

	// Say you have an array of 10 ints: int ai[10];

	// On most platforms an int occupies 4 bytes, so array ai is 40 bytes long.
	// What happens if you only initialize the first 10 bytes to 0?

	// Q:
	// If you're keeping a running total in each of the 10 elements,
	// how many running totals will be correct?

	// A:
	// If an int occupies 4 bytes, only ai[0] and ai[1] will be correct! 

	// How many 4-byte ints fit in 10 bytes? 2 with 2 bytes left over.

	// Only 16 bits of 32-bit ai[2] will be set to 0.
	// a[2] through a[9] will not be set to 0.
	// a[2] through a[9] will add a running total to random garbage.
    
    cout << "Hello World!\n";

	// The C++ main() function doesn't need to return 0
	return 0;
}
