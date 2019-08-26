
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

#ifndef ML_OPTIMISER_H_
#define ML_OPTIMISER_H_

#include <pthread.h>
#include "src/ml_model.h"
#include "src/parallel.h"
#include "src/exp_model.h"
#include "src/ctf.h"
#include "src/time.h"
#include "src/mask.h"
#include "src/healpix_sampling.h"
#include "src/helix.h"
#include "src/local_symmetry.h"


// for profiling
//#define TIMING

class Test;

class Test
{
public:

        // modified bty ZhouQ and gaoxing for randomphase classification
	bool do_random_phase
	std::vector<RFLOAT> random_phase_res_iter
	std::vector<RFLOAT> random_phase_res_upper_iter
	bool do_cyclic_random_phase
	bool do_cool_down
	std::vector<int> cool_down_iter_vector
	std::vector<int> cool_down_cycle_vector
	bool do_good_map_random_phase
	std::vector<RFLOAT> random_phase_good_res_iter
	std::vector<RFLOAT> random_phase_good_res_upper_iter
	bool do_weighted_random_phase
	std::vector<RFLOAT> random_phase_amplitude_iter
	std::vector<RFLOAT> random_phase_good_amplitude_iter
	bool do_B_factor_dose_weighting_refinement
	bool do_particle_polishing

        //For deep neural network generation of adversarial 2d images for optimization of the filter to use in the 3D classification and refinement.

    /** ========================== Random Phase set up functions ================================= */
        // Modified by ZhouQ and Gaoxing for random phase
        // This function parses the option into two vectors. One vector contains the sequence of bool values indicating whether to randomize reference for each iteration .
        // The other vector contains the sequence of the resolution for phase randomizing if necessary.
        void setParameterForRandomphase(const std::string &random_phase_string, const std::string &random_phase_amplitude_string);
        void setHealpixOrderIter(std::vector<int> &healpix_iter, std::vector<DOUBLE> &sigma_ang_iter ,const std::string &healpix_option);
        void updateIterLocalSearches(HealpixSampling &sampling,MlModel &mymodel,const int &healpix_order ,const DOUBLE &sigma_ang);
}
