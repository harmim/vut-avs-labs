#include <map>
#include "RGB.hpp"


#ifndef COLORMAP_HPP
#define COLORMAP_HPP
 
class Colormap
{
public:
	static const std::map<size_t, RGB> colormap;
};
#endif