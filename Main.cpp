/* 16-bit XOR Shift White Noise Generator 
 * Language:  C
 * Author:  Cole Jepson
 * Date:  6/5/2017
 * References:  https://en.wikipedia.org/wiki/Xorshift
 */

#include "mbed.h"
 
AnalogIn ADC16(p16);
AnalogOut DAC18(p18);

uint16_t  noise;
uint32_t  randn, mask = 0;

int main() 
{
    mask = (1 << 16) - 1;      // 16-bit mask to reduce 32-bit to 16-bit
    randn = ADC16.read_u16();  // read floating pin voltage (seed) on DIP16

    while(1)
    {
        randn ^= randn << 13;   // bit-shift to create random numbers from seed
        randn ^= randn >> 17;
        randn ^= randn << 5;  
        noise = randn & mask;   // convert 32-bit uint to 16-bit       
        DAC18.write_u16(noise);
    }
}
