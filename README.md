RANDOMPHASE Classification is based on the widly used Cryo-EM processing software RELION which is developed in the
research group of Sjors Scheres at the MRC Laboratory of Molecular Biology.

## Installation
The installation is identical to that of RELION

##Additional parameters

The basic working concept of random phase 3D classification is that we randomize the good reference at the start of an iteration to create a bad reference that differs with the good one only beyond a certain frequency range. By classifying against these two references, the particles that have no significant contribution to the higher frequency shells tend to be classified into the bad class. 

This is switched on by providing the --random_phase_otherrefs option.

However, in practice we observe that as the classification and alignment proceeds, particles in the good class tend to overrefine, an attempt to solve this problem is introduction of an additional factor that allows information beyond a higher resolution shell to be preserved in the bad reference, for example, we randomize the pixels between 10 and 3.5 angstrom when the current resolution is 3.8 angstrom, this way, we tend to classify out the particles that differ with the good class only between 10 and 4 angstrom,  particles that only contribute to frequencies beyond 4 (where the SNR in the good reference is significantly lower) or  particles that only contributes to low frequencies will be removed.

by providing --random_phase_res option, you can gradually change the randomization frequency,  for example, 10,4,2,10 means that perform randomization every 2 iterations,  the randomization is between 10 and 4 angstrom, this cycle will be repeated by 10 times, if you would like to provide additional cycles, simply attach another 4 numbers separated by "," with the ";" in between different cycles.

The same can be performed on the good reference, this is useful when some ragged ridge is present in your map indicating that overrefinement has already happened, randomizing the good reference beyond certain frequency can sometimes help to remove these artifacts.

The phase randomization works by adding random phase to the existing phase.

--random_amplitude_goodrefs and random_amplitude_other_refs control the range of this randomization, providing 0.4,1,10 means that for the first 10 iterations, if randomization happens (specified by random_phase_good_res option), the added random phase would be in the range of [-pi*0.4,pi*0.4], same as above, different cycles are separated by ";", the second number in each cycle should always be 1.

The smaller the amplitude, the less different the bad and good references become, and the more stringent the criteria becomes. If you want to try to clean up your data set as much as possible, decrease this value gradually. However, more stringent criteria does not neccesarily lead to higher resolution but sometimes lead to better map quality.

A good starting point for improving the resolution could be --random_phase_otherrefs --random_phase_res 30,4,2,10:20,3,2,10,15,3,2,10, by not providing the other options, the program will skip randomization of the good reference and the randomization amplitude will always be 1.

random_phase_template.sh provides a template.
##Result analysis

Please place the attached plotStatofRandomPhaseRef.py in your ~/bin directory and authenticate for execution. 
Please place the attached plot_randomPhase3D_template.sh in your working folder and authenticate for execution. 
change the first line in plot_randomPhase3D_template.sh to the it001_data.star of your randomphase output, a png file will be generated in your data directory along with a few additional data star file in your randomphase output directory (e.g if you provide Class3D_bin2/run1_it001_data.star, the png files and sel star files will be in Class3D_bin2/). The png file will show you how the particles are distributed with the x axes being times the particle is classified into the bad class and the y coordinate being the particle number, this will help you to decide on  a reasonable cutoff for removing bad particles. The generated data star file are some generated star file that has already removed particles that appear in the bad class beyond certain number of times, for example sel10 means particles that appear in the bad class for over 10 times are removed.





