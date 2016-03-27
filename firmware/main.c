/* -----------------------------------------------
 *  Program: 7x5 Dotmatrix Scroller and Animator
 *  Version: 0.1.v
 *  Compiler: avr-gcc
 * -----------------------------------------------
*/

// Library includes
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

// **** Edit this file for configure pins ****
#include "config.h"

// **** Edit this file and paste from JS Generator for animation setup ****
#include "animation.h"

// Some fixed values
#define LOW 0
#define HIGH 1

// Prototipes
void setPixel(uint8_t pin,  uint8_t value);
void paint(uint8_t matrix[], uint8_t times);
void digitalWrite(uint8_t pin, uint8_t val);



// Here is the main 
int main (void)
{
	// setup all pins to outputs
	DDRB  = 0xff;
	DDRD  = 0xff;
	
	
	// this is for SCROLL mode
	if (MODE==1) {
		while (1)  	// infinite loop
		{
			uint8_t i,offset,frame;	// some variables
		    uint8_t screen[5]; 		// buffer for paint
			
			// for each frame...
			for (frame=0;frame<=FRAMES;frame++){
				// scroll every frame to left
				for (offset=0;offset<8;offset++){
					// Fill screen buffer
					for (i=0;i<5;i++){
						if (frame==0)     screen[i] = (pgm_read_byte(&animation[frame][i])>>(8-offset));
						if (frame>0)      screen[i] = (pgm_read_byte(&animation[frame-1][i])<<(offset));
						if (frame<FRAMES&&frame>0) screen[i] = screen[i]|(pgm_read_byte(&animation[frame][i])>>(8-offset));
					}
					// Now paint the screen the SPEED times
					paint(screen, SPEED);
				} // end of frame scrolling
			} // end of frame cycle
		} // end of infinite loop
	}// end of SCROLL mode

	// this is for ANIMATION mode
    if (MODE==2) {
		while (1)  // infinite loop
		{
			uint8_t i,frame;   // some variables
		    uint8_t screen[5]; // buffer for paint

			// for each frame
			for (frame=0;frame<FRAMES;frame++){
				
					// Fill screen buffer with frame
					for (i=0;i<5;i++){
						screen[i] = pgm_read_byte(&animation[frame][i]);
					}
					// Now we paint the screen SPEED times
					paint(screen, SPEED);
			}// end of frame cycle
		}// end infinite loop
	}// end of ANIMATION mode

	return 0;
}
// Set a pixel by the pin number (value can be HIGH or LOW)
void setPixel(uint8_t pin, uint8_t value){
  		digitalWrite(pin,value);
		_delay_us(600);
		digitalWrite(pin,LOW);
}

// Refresh paint all the dotmatrix by scanning all rows and cols
// Use times for choose the speeds
void paint(uint8_t matrix[], uint8_t times){
	uint8_t col,row, i;

		for (i=0;i<times;i++){
			for (row=0;row<7;row++){
				digitalWrite(rows[row],LOW);
				for(col=0;col<5;col++){
					setPixel(cols[col],matrix[col]&1<<row);
				}
				digitalWrite(rows[row],HIGH);
			}
		}
}

// digitalWrite from Arduino modified for use absolute pins
void digitalWrite(uint8_t pin, uint8_t val)
{
	uint8_t bit = digitalPinToBitMask[pin];
	uint8_t port = digitalPinToPort[pin];
	volatile uint8_t *out;

    if (port == PB) {
		 out = &PORTB; 
	} else 
	if (port == PD) { 
	     out = &PORTD; 
	}

	if (val == LOW) *out &= ~bit;
	else *out |= bit;
    
}
