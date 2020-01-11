/** 
 * @File      sections-critical.cpp
 *
 * @author    Marta Cudova \n
 *            Faculty of Information Technology \n
 *            Brno University of Technology \n
 *            icudova@fit.vutbr.cz
 *
 * @brief     Implementation of a two stage pipeline with section and 
 *            synchronization using omp critical.
 *
 * @date      18 March 2018, 16:00
 */


#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <queue>
#include <omp.h>

using namespace std;

/**
 * @class  ParallelQueue
 * @brief  ParallelQueue class
 */
class ParallelQueue
{
  public:
     /// Constructor
     ParallelQueue();
     /// Destructor
     ~ParallelQueue();
     /// Returns true if the queue is empty, otherwise false
     bool  empty();
     /// Pushed the element to the back of the queue.
     void  push(const int value);
     /// Returns and pops the element from the front.
     int   pop();
     /// Waits until the queue is empty, then calls pop().
     int   popOrWait();

  private:
    /// internal queue
    queue<int> mQueue;
}; // end of ParallelQueue
//------------------------------------------------------------------------------

/**
 * Constructor
 */
ParallelQueue::ParallelQueue() : mQueue()
{

}// end of ParallelQueue
//------------------------------------------------------------------------------

/**
 * Destructor
 */
ParallelQueue::~ParallelQueue()
{

}
//------------------------------------------------------------------------------

/**
 * Tests on the queue emptiness.
 * @return true if emtpy.
 */
bool ParallelQueue::empty() 
{
  // ******************************************** //
  // *********** WRITE YOUR CODE HERE *********** //  
  // ******************************************** //
} // end of empty()
//-----------------------------------------------------------------------------

/**
 * Pushes the element to the back of the queue.
 * @param [in] value - Element value
 */
void ParallelQueue::push(const int value)
{
  // ******************************************** //
  // *********** WRITE YOUR CODE HERE *********** //  
  // ******************************************** //
} // end of push()
//-----------------------------------------------------------------------------

/**
 * Returns and pops the element from the front.
 * @return Element from the queue front.
 */
int ParallelQueue::pop()
{
  // ******************************************** //
  // *********** WRITE YOUR CODE HERE *********** //  
  // ******************************************** //
} // end of pop()
//-----------------------------------------------------------------------------

/**
 *  Waits until the queue is empty, then calls pop().
 * @return Element from the queue front.
 */
int ParallelQueue::popOrWait()
{
  // ******************************************** //
  // *********** WRITE YOUR CODE HERE *********** //  
  // ******************************************** //
}	 // end of popOrWait()
//------------------------------------------------------------------------------

/**
 * Generates a random number from <0; range).
 * @param [in] range - Range of the generation.
 * @return random value
 */
int generate(const int range)
{
  int randNum = rand() % range;
  return randNum;
}//------------------------------------------------------------------------------

/**
 * Updates the histogram. Value on the position is incremented.
 * @param [in,out] histogram - Histogram.
 * @param [in]     position  - Position in the histogram.
 */
void histogramAdd(int histogram[], const int position)
{
  histogram[position]++;
}
//------------------------------------------------------------------------------


/**
 * The main function.
 */
int main()
{
  /// Number of processed values
  constexpr int iterations = 1000000;
  /// Stopper is set when all random values (iterations) are generated
  constexpr int stopper    = -1;
  /// Range of random generated values
  constexpr int range      = 256;
  /// Histogram
  int histogram[range];
  /// Seed for the random generator
  srand(0);// seed

  // ParallelQueue instance
  ParallelQueue workQueue;  

  // Histogram initialization
  for (int i = 0; i < range; i++)
  {
  	histogram[i] = 0;
  }	

  double startTime = omp_get_wtime();
  // Parallel region with sections
  #pragma omp parallel sections
  {
    // ******************************************** //
    // *********** WRITE YOUR CODE HERE *********** //  
    // ******************************************** //

  
  } // end of parallel sections
  double stopTime = omp_get_wtime(); 
  // print histogram
  for (int i = 0; i < range; i++)
  {
  	cout << i << ": " << histogram[i] << endl;
  }	
  cout << "Calculation time: " << stopTime - startTime << " s" << endl;

  return 0;
} // end of main
//------------------------------------------------------------------------------

