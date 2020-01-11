#ifndef RGB_HPP
#define RGB_HPP
 
class RGB
{
public:
	uint8_t r;
	uint8_t g;
	uint8_t b;
	RGB(): r(0), g(0), b(0) {};
	RGB(float red, float green, float blue): r(red * 255), g(green * 255), b(blue * 255) {};
	RGB(uint8_t red, uint8_t green, uint8_t blue): r(red), g(green), b(blue) {};
};
#endif