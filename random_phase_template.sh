#!/bin/bash

source /home/zhouq/.relion2.1_randomphase_bashrc 

mpirun -n 9 `which relion_refine_mpi` --o random_phase_test/run1  --i t.star --ref reference/3.07_class001.mrc --K 2 --random_phase_otherrefs  --random_phase_res 20,0.1,2,10:10,0.1,3,10 --random_amplitude_other_refs 0.7,1,20:0.5,1,30  --ini_high 5 --dont_combine_weights_via_disc --pool 1000 --ctf --ctf_corrected_ref --iter 50 --tau2_fudge 8 --particle_diameter 220 --K 2 --flatten_solvent --zero_mask --solvent_mask mask_creation/good_VDSIII_36solvent_mask.mrc  --oversampling 1 --healpix_order 5 --sigma_ang 1.66667 --offset_range 3 --offset_step 2 --sym C1 --norm --scale  --j 12 --random_phase_good_refs --random_phase_good_res 3.3,0.1,2,10:2.8,0.1,3,10 --random_amplitude_goodrefs 0.4,1,10:0.3,1,10:0.2,1,10:0.1,1,10:0.05,1,10
##--random_phase_res 20
