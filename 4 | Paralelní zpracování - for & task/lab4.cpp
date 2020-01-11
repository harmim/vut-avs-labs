#include <vector>
#include <random>
#include <cmath>
#include <iostream>
#include <fstream>
#include <bitset>
#include "RGB.hpp"
#include "Colormap.hpp"
#include "ComplexFloat.hpp"
#include "TinyPngOut.hpp"
#include "PapiCounters.hpp"

constexpr size_t width = 2048;
constexpr size_t height = 1080;

constexpr float real_lim = 2;
constexpr float imag_lim = 1;

constexpr float real_center = 0;
constexpr float imag_center = 0.5;

constexpr size_t iter_limit = 2048;

constexpr size_t fibb_check = 832040;

constexpr double delta_error = 1e-5;

constexpr size_t vect_size = 20480000;
constexpr long vect_length_check = 0b0100000010100100011010010110111011010111111100100110111100110111;

size_t fibb(size_t n)
{
	if(n < 2)
	{
		return n;
	}
	else
	{
		size_t f1, f2;
#pragma omp task shared(f1)
		f1 = fibb(n-1);
#pragma omp task shared(f2)
		f2 = fibb(n-2);
#pragma omp taskwait
		return f2+f1;
	}
}

int main (int argc, char** argv)
{
    // Define papi counters
	PapiCounterList papi_exampined_routines;
   	papi_exampined_routines.AddRoutine("mandelbrot");
   	papi_exampined_routines.AddRoutine("fibbonaci");
   	papi_exampined_routines.AddRoutine("vectnorm");

/*
 * ####################################################################################################################
 */

    // Define input and and coresponding image
	std::vector<float> divergence_map(width*height);
	std::vector<RGB>   image(width*height);

    // Variable for calculated number C
    ComplexFloat c;
    // Number in computed series S
	ComplexFloat s;

    // Cast width and height
	float widthf  = width;
	float heightf = height;

    // PART 1
	papi_exampined_routines["mandelbrot"].Start();

    //Walk through complex plane
	#pragma omp parallel for private(s,c) schedule(guided)
	for(size_t b = 0; b < height; ++b)
	{
		for(size_t a = 0; a < width; ++a)
		{
            // Initialise map (black color)
			divergence_map[b*width + a] = 64.0f/63.0f;

            // Compute complex value from width and height
			c.re = ((a/widthf)  * real_lim) - (real_lim/2.0f) + real_center;
			c.im = ((b/heightf) * imag_lim) - (imag_lim/2.0f) + imag_center;

            // Initialise seris
			s = c;

            // Until diverged or limit is reached
			size_t i = 0;
			bool diverged = false;
			while(i < iter_limit && !diverged)
			{
                // counter
				++i;

                // S(n+1) = s(n)*s(n) +c
				s *= s;
				s += c;

                // Above treshhold?
				if(s.length() > 2.0f)
				{
                    // Stop while
					diverged = true;
                    // Store value for the image
					divergence_map[b*width + a] = (log(i)/static_cast<float>(log(iter_limit)));
				}
			}
		}
	}
	papi_exampined_routines["mandelbrot"].Stop();

    // Convert divergence map to image
	for(size_t b = 0; b < height; ++b)
	{
		for(size_t a = 0; a < width; ++a)
		{

			size_t  colormap_index = divergence_map[b*width + a] * 63.0f;
			image[b*width + a] = Colormap::colormap.at(colormap_index);
		}
	}

	// Store the image
	try {
		std::ofstream out("mandelbrot.png", std::ios::binary);
		TinyPngOut pngout(static_cast<uint32_t>(width), static_cast<uint32_t>(height), out);
		pngout.write(reinterpret_cast<uint8_t *> (image.data()), static_cast<size_t>(width * height));

	} catch (const char *msg) {
		std::cerr << msg << std::endl;
		return EXIT_FAILURE;
	}

/*
 * ####################################################################################################################
 */

	// PART 2
	papi_exampined_routines["fibbonaci"].Start();

	size_t f30;

#pragma omp parallel shared(f30)
{
	#pragma omp single
	f30 = fibb(30);
}
	papi_exampined_routines["fibbonaci"].Stop();

	std::cout<<"Fibbonaci check"<<std::endl;
	std::cout<<"--------------------------------"<<std::endl;
	std::cout<<"Ground truth "<<fibb_check<<std::endl;
	std::cout<<"Computed "<<f30<<std::endl;
	std::cout<<"-------skwait-------------------------"<<std::endl;
	if(f30 == fibb_check)
	{
		std::cout<<"PASSED!"<<std::endl;
	}
	else
	{
		std::cout<<"FAILED!"<<std::endl;
	}
	std::cout<<"--------------------------------"<<std::endl<<std::endl;


/*
 * ####################################################################################################################
 */

	std::mt19937 gen(0);
    std::uniform_real_distribution<> dis(0.0, 1.0);

	std::vector<double> vect(vect_size);
	for(size_t i = 0; i < vect_size; ++i)
	{
		vect[i] = dis(gen);
	}

	double vect_length = 0.0;


	papi_exampined_routines["vectnorm"].Start();

#pragma omp parallel reduction(+:vect_length)
#pragma omp simd reduction(+:vect_length)
	for(size_t i = 0; i < vect_size; ++i)
	{
		vect_length += vect[i] * vect[i];
	}
	papi_exampined_routines["vectnorm"].Stop();

	vect_length = sqrt(vect_length);

	for(size_t i = 0; i < vect_size; ++i)
	{
		vect[i] /= vect_length;	}


	std::cout<<"Vector normalization check"<<std::endl;
	std::cout<<"-----skwait---------------------------"<<std::endl;
	std::cout<<"Ground truth "<<*(reinterpret_cast<const double *>(&vect_length_check))<<std::endl;
	std::cout<<"Computed "<<vect_length<<std::endl;
	std::cout<<"--------------------------------"<<std::endl;
	if(fabs(vect_length - *(reinterpret_cast<const double *>(&vect_length_check))) < delta_error)
	{
		std::cout<<"PASSED!"<<std::endl;
	}
	else
	{
		std::cout<<"FAILED!"<<std::endl;
	}
	std::cout<<"--------------------------------"<<std::endl<<std::endl;

	papi_exampined_routines.PrintScreen();
}
