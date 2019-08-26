/*************************************************************************

Author:  "Gaoxingyu Huang"
 * School of Life Sciences, Tsinghua University, Shilab
 *This program is free software; you can redistribute it and/or modify
 *it under the terms of the GNU General Public License as published by
 *the Free Software Foundation; either version 2 of the License, or
 *(at your option) any later version.
 *
 *This program is distributed in the hope that it will be useful,
 *but WITHOUT ANY WARRANTY; without even the implied warranty of
 *MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *GNU General Public License for more details.
 *
 * This complete copyright notice must be included in any revised version of the
 * source code. Additional authorship citations may be added, but existing
 * author citations must be preserved.
 ***************************************************************************/
#ifndef covariance.h
#define covariance.h

class
public:

//need functions to read in the data or pass the data.
//need functions to do preprocessing
//need functions to calculate the projection of raw image onto Fourier-Bessel basis
/*
 * This function projects the Fourier coefficients into steerable FourierBessel basis and allows in-plane 
 * invariant functions to be calculated
 */
void fourier_to_fourierBessel(const MultidimArray<Complex> &FourierArray, MultidimArray<Complex> $FourierBesselArray);

//need functions to estimate the mean values
//need functions to estimate the covariance matrices
//need functions to to the final filtering procedure.






