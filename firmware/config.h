
#define PB 2
#define PD 4

uint8_t cols[] = {
6,
10,
4,
3,
11
};

uint8_t rows[] = {
2,
7,
1,
5,
8,
12,
9
};

const uint8_t digitalPinToPort[] = {
	PB, 
	PB,
	PB,
	PB,
	PB,
	PB,
    PB,
	PB,
	PD, 
	PD,
	PD,
	PD,
	PD,
	PD,
	PD
};

const uint8_t  digitalPinToBitMask[] = {
	1, 
	2,
	4,
	8,
	16,
	32,
    64,
	128,
	1, 
	2,
	4,
	8,
	16,
	32,
	64
};
