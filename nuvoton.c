#ifdef __NUVOTON__

#include <Arduino.h>

void nvtShow(
 uint8_t pin, uint8_t *pixels, uint32_t numBytes, boolean is800KHz) 
{
  uint8_t *p, *end, pix, mask;
  uint32_t setMask, clrMask;
  volatile uint32_t *port;

  setMask   =  digitalPinToBitMask(pin);
  clrMask   =  ~setMask;
  port 		=  portOutputRegister(digitalPinToPort(pin));
  p         =  pixels;
  end       =  p + numBytes;
  pix       = *p++;
  mask      = 0x80;

#ifdef NEO_KHZ400 // 800 KHz check needed only if 400 KHz support enabled
  if(is800KHz) {
#endif
    for(;;) {		
      *port |= setMask;
      asm("nop; nop; nop; nop; nop; nop; nop; nop; nop; nop;"
		  "nop; nop;"); // 0.4us
      if(pix & mask) {
        asm("nop; nop; nop; nop; nop; nop; nop; nop; nop; nop;"
			"nop; nop;"); // 0.4us
        *port &= clrMask;
      } 
	  else {
        *port &= clrMask;
        asm("nop; nop; nop; nop; nop; nop; nop; nop; nop; nop;"
			"nop; nop;"); //0.4us
      }
	  asm("nop; nop; nop; nop; nop; nop; nop; nop; nop; nop;" //0.45us
		  "nop; nop; nop;");
		  
	  if(!(mask >>= 1)) {
        if(p >= end) break;
		pix  = *p++;
		mask = 0x80;
      }
    }
	delayMicroseconds(50); //50us 

#ifdef NEO_KHZ400
 } 
  else { // 400 KHz bitstream
     for(;;) {		
      *port |= setMask;
      asm("nop; nop; nop; nop; nop; nop; nop; nop; nop; nop;"
		  "nop; nop; nop; nop; nop; nop;"); // 0.5us
      if(pix & mask) {
        asm("nop; nop; nop; nop; nop; nop; nop; nop; nop; nop;"
			"nop; nop; nop; nop; nop; nop; nop; nop; nop; nop;"
			"nop; nop; nop;"); // 0.7us
        *port &= clrMask;
      } 
	  else {
        *port &= clrMask;
        asm("nop; nop; nop; nop; nop; nop; nop; nop; nop; nop;"
			"nop; nop; nop; nop; nop; nop; nop; nop; nop; nop;"
			"nop; nop; nop;"); //0.7us
      }
	  asm("nop; nop; nop; nop; nop; nop; nop; nop; nop; nop;"
			"nop; nop; nop; nop; nop; nop; nop; nop; nop; nop;"
			"nop; nop; nop; nop; nop; nop; nop; nop; nop; nop;"
			"nop; nop; nop; nop; nop; nop; nop; nop; nop; nop;"
			"nop; nop;"); // 1.3us
		  
	  if(!(mask >>= 1)) {
        if(p >= end) break;
		pix  = *p++;
		mask = 0x80;
      }
    }
	delayMicroseconds(50); //50us
  }
#endif
}

#endif // nuvoton
