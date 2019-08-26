/***************************************************************************
 *
 * Author: "Sjors H.W. Scheres"
 * MRC Laboratory of Molecular Biology
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * This complete copyright notice must be included in any revised version of the
 * source code. Additional authorship citations may be added, but existing
 * author citations must be preserved.
 ***************************************************************************/

//#define DEBUG
//#define DEBUG_CHECKSIZES
//#define DEBUG_BODIES
//#define DEBUG_HELICAL_ORIENTATIONAL_SEARCH
//#define PRINT_GPU_MEM_INFO

#ifdef TIMING
		#define RCTIC(timer,label) (timer.tic(label))
		#define RCTOC(timer,label) (timer.toc(label))
#else
		#define RCTIC(timer,label)
    	#define RCTOC(timer,label)
#endif

#include <sys/time.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <ctime>
#include <iostream>
#include <string>
#include <fstream>
#include "src/macros.h"
#include "src/error.h"
#include "src/ml_optimiser.h"
#ifdef CUDA
#include "src/gpu_utils/cuda_ml_optimiser.h"
#endif

#define NR_CLASS_MUTEXES 5

//Modified by Gaoxing for random phase set up.
//The different cycles of random phase set up should be separated by colon, if only a single number is provided, then the upper limit and the cycle number and cool down iteration will be used to default 
void Test::setParameterForRandomphase(const std::string &random_phase_string, const std::string &random_phase_amplitude_string)
{
    std::vector<std::string> colon_split;
    std::vector<std::string> comma_split;
    std::vector<std::string> amp_colon_split;
    std::vector<std::string> amp_comma_split;
    // The default cycle iteration is 3
    int cycle_iteration = 3; 
    // The default cycle number is 3
    int cycle_number = 3;
    // The default random phase resolution will be 100 if not specified. The default random_phase_upper would be 0.1.
    DOUBLE random_phase_res = 40;
    DOUBLE random_phase_upper = 0.1;
    int total_cycle_iteration = cycle_iteration * cycle_number;
    int total_iteration = 0;
    splitString(random_phase_string,":",colon_split,true);
    splitString(random_phase_amplitude_string,":",amp_colon_split,true);
    // sets the amplitude iteration vector according to the given amplitude vector.
    for (int i = 1; i <= amp_colon_split.size; i++)
    {
        splitString(amp_colon_split,",",amp_comma_split,true);
	if (amp_comma_split.size == 1)
	{
	    // If the second iteration number parameter is not specified, then set it to a default value of the total number of iterations.
	    amp_comma_split.push_back(nr_iter);
	    std::cout << "Because not provided, the number of amplitude specification has been set to the total number of iterations: " << nr_iter << std::endl
	}
	std::cout << "the amplitude from iteration" << << "to iteration" << << "has been set to: "<< amp_comma_split[0] << std::endl
	for (int j = 1; j <= amp_comma_split[1]; j++)
	{
	   random_phase_amplitude_iter.push_back(amp_comma_split[0]); 
           
	}

    }
    // sets the random phase iteration vector according to the given random_phase_string.
    if (colon_split.size < 2)
    {
        // If only one colon separated parameter is given, then the parameters are set by default values.
        do_cyclic_random_phase = false;
        splitString(colon_split[0],",",comma_split,true);
	// If only the random phase resolution is given, then rest of the parameters will be set to default values
	if (comma_split.size == 1)
	{
	    random_phase_res = textToFloat(comma_split[0])
	    random_phase_res = 0.01
	    do_cool_down = false
	}
	if (comma_split.size == 2)
	{
	    random_phase_res = textToFloat(comma_split[0])
	    random_phase_upper = textToFloat(comma_split[1])
	    do_cool_down = false
	}
	if (comma_split.size == 3 || comma_split.size == 4)
	{
	    
	}
	for (int j=1;j <= nr_iter; j++)
	{
	    random_phase_res_iter.push_back(random_phase_res)
	    random_phase_res_upper_iter.push_back(random_phase_res_upper)
	}
	
    }
    else
    {
        do_cyclic_random_phase = true;
        for (int i=1;i<=colon_split.size();i++)
        {
            // re-initialize the three variables to the default value
            cycle_iteration=3;
	    cycle_number=3;
	    random_phase_res=100;
	    random_phase_upper=0.1;
            splitString(colon_split[i-1],",",comma_split,true);
            if (comma_split.size()>0)
	    {
	        //set the resolution according to the first member of the comma_split vector
	        random_phase_res=textToFloat(comma_split[0]);
	        //random_phase_res_iter[iteration]=comma_split[0];
	        if (comma_split.size()>1)
	        {
	            random_phase_upper=textToFloat(comma_split[1]);
	            if (comma_split.size()>2)
	            {
	                cycle_iteration=textToInteger(comma_split[2]);
    		        if (comma_split.size()>3)
		        {
		            cycle_number=textToInteger(comma_split[3]);
		        }
	            }
	        }
	    }
	    // update the total_cycle_iteation variable
	    // Broadcast the scheduled annealing.
	    std::cout<<cycle_number<<" cycles of annealing with "<<cycle_iteration<<" of iterations per cycle has been scheduled with randomized phase at "<<random_phase_res<<std::endl;
            total_cycle_iteration=cycle_iteration*cycle_number;
	    total_iteration+=total_cycle_iteration;
	    for (int j=1;j<total_cycle_iteration;j++)
	    {
	        random_phase_res_iter.push_back(random_phase_res);
	        random_phase_res_upper_iter.push_back(random_phase_upper);
	        if (j%cycle_iteration==1)
	        {
	            do_random_phase_iter.push_back(true);
	        }
	        else
	        {
	            do_random_phase_iter.push_back(false);
	        }
	    }
        }
        if (total_iteration>nr_iter)
        {
            nr_iter=total_iteration;
        }
    }

    // To do
    
//nr_iter
//do_random_phase_iter
//random_phase_res_iter
}

