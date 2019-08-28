#!/bin/bash
#for i in Class3D_bin2/run2_it001_data.star
for i in $1
# We generally run about 30-50 iterations for a 3D classification cycle.
do
	b=${i/_it001_data.star/}
	echo $b
		plotStatofRandomPhaseRef.py -i ${i} -d ${b}.dat --save_class_dis_particles=${b}_lowertimes_cls.png --plot_lower_times 1 --start_iter 5 
	for j in 40 60 80
	# j is the threshold time for bad particles.
	# Use smaller value of j to remove more "bad" particles, but some "good" particles may also be removed.
	#
	do
		plotStatofRandomPhaseRef.py  -i ${i} -d ${b}.dat --save_class_dis_particles=${b}_ptcls_s5.png --save_class_dis_iteration=${b}_iter_s5.png -o ${b}_startiter5_sel_${j}.star -t ${j} --start_iter 5
	done
done



