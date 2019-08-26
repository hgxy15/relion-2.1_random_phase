
/*************************************************************************

Author: "Qiang Zhou" 
 * School of Medicine, Tsinghua University
 *      "Gaoxingyu Huang"
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

#include "src/random_phase.h"

#define RANDOM_PHASE_RES 40
#define GOOD_RANDOM_PHASE_RES 10
#define RANDOM_PHASE_RES_UPPER 0.1
#define GOOD_RANDOM_PHASE_RES_UPPER 5
#define COOL_DOWN_CYCLE 3
#define COOL_DOWN_ITERATION 3
#define TWO_PI
#define DATA_TYPE_ERROR -10
#define EMPTY_ARG_ERROR -11
//#define RFLOATWIDTH 22
//TODO



/*
   void RandomPhase::auto_parameter_completion(const int &max_nr_iter, const RFLOAT &default_value, std::vector<RFLOAT> parameter_iter_vector)
   {
   if (parameter_iter_vector.size() < max_nr_iter)
   {
   for (int i = parameter_iter_vector.size(); i < max_nr_iter; i++ )
   {
   parameter_iter_vector.push_back(default_value);
   }
   }
   else
   {
   std::cout << "The size of the input vector is identical to or greater then the given maximum number of iteration, skipping auto completion....." << std::endl;
   }
   }
   */
/*
//We always use the last two parameters in a comma split vector. 
template<typename T> void RandomPhase::check_nr_iter(T &optimiser, std::vector<std::string> &string_vector, const std::vector<int> &default_parameter_number_vector, std::vector<bool> do_cycle_vector, bool do_auto_completion)
{
	if (default_parameter_number_vector.size() != string_vector.size())
	{
		std::cout << "The default parameter number vector has a different size then the parameter string vector! please check your specification in the parseInitial function" << std::endl;
		exit(-1);
	}
	int total_iter = 0;
	int temp_iter = optimiser.nr_iter;
	int cool_down_cycle = 0;
	int cool_down_iteration = 0;
	for (int i = 1; i <= string_vector.size(); i++)
	{
		// reset the temp_iter to 0
		total_iter = 0;
		std::vector<std::string> colon_split;
		std::vector<std::string> comma_split;
		splitString(string_vector[i-1], ":", colon_split, true);
		for (int j = 1; j <= colon_split.size(); j++)
		{
			splitString(colon_split[j-1], ",", comma_split, true);
			if ((default_parameter_number_vector[i - 1] - comma_split.size()) > 1 && (! do_cycle_vector[i - 1]))
			{
				std::cout << "Two parameters short, assigning the default value of COOL_DOWN_ITERATION to cool_down_iteration"<< std::endl;
				if (j != colon_split.size())
				{
					std::cout << "Setting the cool down cycle to default: COOL_DOWN_CYCLE " << std::endl;
					cool_down_cycle = COOL_DOWN_CYCLE;
				}
				else if (temp_iter < cool_down_iteration )
				{
					std::cout << "Previous cool down cycles has exceeded the previous maximum number of iterations, setting cool_down_cycle to default: COOL_DOWN_CYCLE" << std::endl;
					cool_down_cycle = COOL_DOWN_CYCLE;
				}
				else
				{
					std::cout << "Now assigning the remaining iterations to the final run."<< std::endl ;
					cool_down_cycle = temp_iter / cool_down_iteration;
				}
				colon_split[j-1] += ",";
				colon_split[j-1] += integerToString(cool_down_iteration, (FLOOR(log10(ABS(cool_down_iteration))) + 1), 0);
				colon_split[j-1] += ",";
				colon_split[j-1] += integerToString(cool_down_cycle, (FLOOR(log10(ABS(cool_down_cycle))) + 1), 0);
			} 
			else if ((default_parameter_number_vector[i-1] - comma_split.size()) == 1 && (! do_cycle_vector[i - 1]))
			{
				std::cout << "One parameter missing, using the last parameter as cool_down_iteration.";
				cool_down_iteration = textToInteger(*(comma_split.end() - 1));
				if (j != colon_split.size() || (temp_iter < cool_down_iteration))
				{
					std::cout<< "Previous cycles has exceeded or this is not the final run, assigning the default value of COOL_DOWN_CYCLE to cool_down_cycle." << std::endl;
					cool_down_cycle = COOL_DOWN_CYCLE;
				}
				else
				{
					std::cout<< "Assigning remaining iterations to the final run." << std::endl;
					cool_down_cycle = temp_iter / cool_down_iteration;
				}
				colon_split[j - 1] += ",";
				colon_split[j - 1] += integerToString(cool_down_cycle, (FLOOR(log10(ABS(cool_down_cycle))) + 1), 0);
			}
			else if (do_cycle_vector[i - 1])
			{
				cool_down_iteration = textToInteger(*(comma_split.end() - 2));
				cool_down_cycle = textToInteger(*(comma_split.end() - 1));
				if (do_auto_completion)
				{
					if (j == colon_split.size() - 1)
					{
						while (temp_iter > (cool_down_iteration * cool_down_cycle))
						{
							cool_down_cycle += 1;
						}
						*(comma_split.end() - 1) = integerToString(cool_down_cycle, (FLOOR(log10(ABS(cool_down_cycle))) + 1), 0);
					}
				}
				else
				{
					std::cout << "Using the last parameter as the cool_down_cycle, using the second last parameter as cool_down_iteration." << std::endl;
				}
			}
			else
			{
				cool_down_iteration = 1;
				cool_down_cycle = optimiser->nr_iter;
				colon_split[j - 1] += ",";
				colon_split[j - 1] += integerToString(cool_down_iteration, (FLOOR(log10(ABS(cool_down_iteration)))), 0);
				colon_split[j - 1] += ",";
				colon_split[j - 1] += integerToString(cool_down_cycle, (FLOOR(log10(ABS(cool_down_cycle)))), 0);
			}
			temp_iter -= cool_down_cycle * cool_down_iteration;
			total_iter += cool_down_cycle * cool_down_iteration;
			// for each string in the string_vector, initialize before passing value to it, this function should kick in whether do_auto_completion is set on or not.
			string_vector[i-1] = "";
			for (int k = 1; k <= comma_split.size(); k++)
			{
				string_vector[i] += comma_split[k-1];
				if (k != comma_split.size())
				{
					string_vector[i-1] += ",";
				}
			}
			if (j != colon_split.size())
			{
				string_vector[j-1] += ":";
			}
		}
		if (total_iter > optimiser.nr_iter)
		{
			optimiser->nr_iter = total_iter;
		}
	}
}

template<typename T> void RandomPhase::set_parameter(const std::string &parameter_string, T &parameter_iter , const std::string &data_type, const std::vector<std::string> &id_map_vector)
{
	std::string mystrings[3] = {"RFLOAT","int","bool"};
	std::vector<std::string> support_types (mystrings, mystrings + sizeof(mystrings) / sizeof(std::string));
	std::vector<std::string>::iterator it;
	int value_id;
	int iteration_id;
	int cycle_id;
	//RFLOAT double_value;
	//int int_value;
	//bool bool_value;
	//use the first element in parameter_iter vector to specify the data type of push_in_value
	auto push_in_value = parameter_iter[0];
	int data_type_specify_id;
	int cycle;
	int iteration;
	it = find(support_types.begin(), support_types.end(), data_type);
	if (it == support_types.end())
	{
		std::cout << "Please provide a valid data type!, the supported types are ";
		for (int i = 0 ; i < (support_types.size() - 1) ; i++)
		{
			std::cout << *(support_types.begin() + i) << ", ";
		}
		std::cout << *(support_types.end() - 1) << "." << std::endl;
		exit(DATA_TYPE_ERROR);
	}
	else
	{
		std::vector<std::string> colon_split;
		std::vector<std::string> comma_split;
		splitString(parameter_string, ":", colon_split, true);
		for (int i = 0 ; i < id_map_vector.size(); i++)
		{
			if (id_map_vector[i] == "value")  value_id = i;
			if (id_map_vector[i] == "iteration")  iteration_id = i;
			if (id_map_vector[i] == "cycle")  cycle_id = i;
		}
		if (! parameter_iter.empty())
		{
			//If the iter vector passed in is not empty, free it before further pushing in other elements.
			delete &parameter_iter;
		}
		for (int i = 0; i < colon_split.size(); i ++)
		{
			splitString(colon_split[i], ",", comma_split, true);
			for (int j = 0; j < comma_split.size(); j ++)
			{
				switch (j) 
				{
					if (j == value_id)
					{
						data_type_specify_id = (find(support_types.begin(), support_types.end(), data_type) - support_types.begin()) / sizeof(std::string);
						switch (data_type_specify_id)
						{
							//This switch case is dependent on the relative order of the element in the support_types vector, 0 for RFLOAT, 1 for int, 2 for bool.
							case 0 :
								push_in_value = textToDouble(comma_split[j]);
								break;
							case 1 :
								push_in_value = textToInteger(comma_split[j]);
								break;
							case 2 :
								if (comma_split[j] == "0") push_in_value = false;
								else push_in_value = true;
								break;
						}
					}
					else if (j == iteration_id)
						iteration = textToInteger(comma_split[j]);
					else if (j == cycle_id)
						cycle = textToInteger(comma_split[j]);
					else
						std::cout << "The id_map_vector has less elements then parameter string, please check your specification!" << std::endl;
				}
			}
			for (int k = 0; k < (iteration * cycle); k++)
			{
				parameter_iter.push_back(push_in_value);
			}
		}
	}
}
template<typename T> void RandomPhase::set_parameter_for_randomphase(T &optimiser,const std::string &random_phase_string, const std::string &random_phase_amplitude_string, const std::string &random_phase_good_string, const std::string &random_phase_good_amplitude_string, const std::vector<std::string> id_map_vector, const std::vector<std::string> good_id_map_vector)
{
	std::vector<std::string> colon_split;
	std::vector<std::string> comma_split;
	std::vector<std::string> lower_id_map_vector;
	std::string temp[3];
	if (id_map_vector.empty())
	{
		temp[0] ="value";
		temp[1] ="iteration";
		temp[2] ="cycle";
		for (int i = 1; i <= sizeof(temp) / sizeof(std::string); i++)
		{
			lower_id_map_vector.push_back(*(temp + i - 1));
		}
		delete temp;
	}
	//the lower res and the upper limit and also the amplitude along with the do_random_phase boolean vector can share a common id_map_vector.
	//std::vector<std::string> upper_id_map_vector;
	std::string lower_string;
	std::string upper_string;
	std::string bool_string;
	splitString(random_phase_string, ":", colon_split, true);
	int iteration;
	int cycle;
	for (int i = 1; i <= colon_split.size(); i++)
	{
		splitString(colon_split[i -1], ",", comma_split, true);
		iteration = textToInteger(comma_split[2]);
		cycle = textToInteger(comma_split[3]);
		for (int mycycle = 1; mycycle <= cycle; mycycle ++) 
		{
			bool_string += "true, 1, 1";
			bool_string += "false, 1,";
			bool_string += integerToString((iteration - 1), (FLOOR(log10(ABS(iteration))) + 1), 0);
			if (mycycle != cycle || i != colon_split.size())
			{
				bool_string += ":";
			}
		}
		lower_string += comma_split[0];
		lower_string += ",";
		lower_string += comma_split[2];
		lower_string += ",";
		lower_string += comma_split[3];
		upper_string += comma_split[1];
		upper_string += ",";
		upper_string += comma_split[2];
		upper_string += ",";
		upper_string += comma_split[3];
		if (i != colon_split.size()) 
		{
			lower_string += ":" ;
			upper_string += ":" ;
		}
	}
	this->set_parameter(lower_string, this->random_phase_res_iter, "RFLOAT", lower_id_map_vector);
	this->set_parameter(upper_string, this->random_phase_res_upper_iter, "RFLOAT", lower_id_map_vector);
	this->set_parameter(bool_string, this->do_random_phase_iter, "bool", lower_id_map_vector);
	if (random_phase_amplitude_string != "-1")
	{
		set_parameter(random_phase_amplitude_string, this->random_phase_amplitude_iter, "RFLOAT", lower_id_map_vector);
	}
	else
	{
		std::cout << "The phase_amplitude is not provided, please specify the correct amplitude for random phase!" << std::endl;
		exit(EMPTY_ARG_ERROR);
	}

	if (random_phase_good_string != "-1")
	{
		splitString(random_phase_good_string, ":", colon_split, true);
		delete &lower_string;
		delete &upper_string;
		delete &bool_string;
		for (int i = 1; i <= colon_split.size(); i++)
		{
			iteration = textToInteger(comma_split[2]);
			cycle = textToInteger(comma_split[3]);
			for (int mycycle = 1; mycycle <= cycle; mycycle ++) 
			{
				bool_string += "true, 1, 1";
				bool_string += "false, 1,";
				bool_string += integerToString((iteration - 1), (FLOOR(log10(ABS(iteration))) + 1), 0);
				if (mycycle != cycle || i != colon_split.size())
				{
					bool_string += ":";
				}
			}
			splitString(colon_split[i - 1], ",", comma_split, true);
			lower_string += comma_split[0];
			lower_string += ",";
			lower_string += comma_split[2];
			lower_string += ",";
			lower_string += comma_split[3];
			upper_string += comma_split[1];
			upper_string += ",";
			upper_string += comma_split[2];
			upper_string += ",";
			upper_string += comma_split[3];
			if (i != colon_split.size()) 
			{
				lower_string += ":" ;
				upper_string += ":" ;
			}
		}
		this->set_parameter(lower_string, this->random_phase_good_res_iter, "RFLOAT", lower_id_map_vector);
		this->set_parameter(upper_string, this->random_phase_good_res_upper_iter, "RFLOAT", lower_id_map_vector);
		this->set_parameter(bool_string, this->do_good_random_phase_iter, "bool", lower_id_map_vector);
		if (random_phase_good_amplitude_string != "-1")
		{
			set_parameter(random_phase_good_amplitude_string, this->random_phase_amplitude_iter, "RFLOAT", lower_id_map_vector);
		}
		else
		{
			std::cout<< "The phase_amplitude for good reference is not provided, please specify the correct amplitude for good reference random phase! "<< std::endl;
			exit (EMPTY_ARG_ERROR);
		}
	}
}
template<typename T> void RandomPhase::randomize_phase_otherrefs(T &optimiser, bool mpi)
{
	int random_phase_rank;
	int random_phase_index;
	int random_phase_upper_index;
	RFLOAT random_phase_amplitude;
	if (this->do_random_phase_iter[optimiser->iter])
	{
		//If the mpi is not invoked, then no need to broadcast.
		random_phase_index = ROUND(optimiser->optimiser->mymodel.ori_size * optimiser->optimiser->mymodel.pixel_size / this->random_phase_res_iter[optimiser->iter]);     
		random_phase_upper_index = ROUND(optimiser->optimiser->mymodel.ori_size * optimiser->optimiser->mymodel.pixel_size / this->random_phase_res_upper_iter[optimiser->iter]);     
		random_phase_amplitude = this->random_phase_amplitude_iter[optimiser->iter];
		for (int i = 1; i < optimiser->optimiser->mymodel.nr_classes; i ++)
		{
			if (! mpi)
			{
				optimiser->optimiser->mymodel.tau2_class[i] = optimiser->optimiser->mymodel.tau2_class[0];
				optimiser->optimiser->mymodel.data_vs_prior_class[i] = optimiser->optimiser->mymodel.data_vs_prior_class[0];
				//optimiser->mymodel.pdf_direction[i] = optimiser->mymodel.pdf_direction[0];
				optimiser->optimiser->mymodel.Iref[i] = optimiser->optimiser->mymodel.Iref[0];
				randomizePhasesBeyond(optimiser->optimiser->mymodel.Iref[i], random_phase_index, random_phase_upper_index, random_phase_amplitude); 
			}
			else
			{
				// distribute the phase randomizing tasks to different slaves if mpi is invoked.
				random_phase_rank = (i % (optimiser->optimiser->node->size - 1) + 1);
				if (optimiser->optimiser->node->rank == random_phase_rank)
				{
					optimiser->optimiser->mymodel.tau2_class[i] = optimiser->optimiser->mymodel.tau2_class[0];
					optimiser->optimiser->mymodel.data_vs_prior_class[i] = optimiser->optimiser->mymodel.data_vs_prior_class[0];
					//optimiser->mymodel.pdf_direction[i] = optimiser->mymodel.pdf_direction[0];
					optimiser->optimiser->mymodel.Iref[i] = optimiser->optimiser->mymodel.Iref[0];
					randomizePhasesBeyond(optimiser->optimiser->mymodel.Iref[i], random_phase_index, random_phase_upper_index, random_phase_amplitude);
				}
			}
		}
	}
}
template<typename T> void RandomPhase::randomize_phase_goodrefs(T &optimiser, bool mpi)
{
	int random_phase_rank;
	int random_phase_index;
	int random_phase_upper_index;
	RFLOAT random_phase_amplitude;
	if (this->do_good_random_phase_iter[optimiser->iter])
	{
		//If the mpi is not invoked, then no need to broadcast.
		random_phase_index = ROUND(optimiser->mymodel.ori_size * optimiser->mymodel.pixel_size / this->random_phase_good_res_iter[optimiser->iter]);     
		random_phase_upper_index = ROUND(optimiser->mymodel.ori_size * optimiser->mymodel.pixel_size / this->random_phase_good_res_upper_iter[optimiser->iter]);     
		random_phase_amplitude = this->random_phase_good_amplitude_iter[optimiser->iter];
		if (! mpi)
		{
			//optimiser->mymodel.tau2_class[i] = optimiser->mymodel.tau2_class[0];
			//optimiser->mymodel.data_vs_prior_class[i] = optimiser->mymodel.data_vs_prior_class[0];
			//optimiser->mymodel.pdf_direction[i] = optimiser->mymodel.pdf_direction[0];
			//optimiser->mymodel.Iref[i] = optimiser->mymodel.Iref[0];
			randomizePhasesBeyond(optimiser->mymodel.Iref[0], random_phase_index, random_phase_upper_index, random_phase_amplitude); 
		}
		else
		{
			// distribute the phase_randomization to the slave mpi_process with least phase_randomizing process running.
			random_phase_rank = (optimiser->mymodel.nr_classes % (optimiser->node->size - 1) + 1);
			if (optimiser->node->rank == random_phase_rank)
			{
				//optimiser->mymodel.tau2_class[i] = optimiser->mymodel.tau2_class[0];
				//optimiser->mymodel.data_vs_prior_class[i] = optimiser->mymodel.data_vs_prior_class[0];
				//optimiser->mymodel.pdf_direction[i] = optimiser->mymodel.pdf_direction[0];
				//optimiser->mymodel.Iref[i] = optimiser->mymodel.Iref[0];
				randomizePhasesBeyond(optimiser->mymodel.Iref[0], random_phase_index, random_phase_upper_index, random_phase_amplitude);
			}
		}
		std::cout<< "randomization of good reference complete!" << std::endl;
	}
}

template<typename T> void RandomPhase::get_phase_randomized_refs(T &optimiser, bool mpi)
{
	int random_phase_rank;
	int start_class = 1;
	//stay silent for mpi slave processes.
	if (mpi && this-> do_random_phase_iter[optimiser->iter])	
	{
		std::cout << "Broadcasting the phase randomized refereces with phase randomized at " << this->random_phase_res_iter[optimiser->iter] << " with upper limit at " << this->random_phase_res_upper_iter[optimiser->iter] << std::endl;
		std::cout << "Amplitude for phase randomization has been set to " << this->random_phase_amplitude_iter[optimiser->iter] << std::endl;
		if (this->do_good_random_phase_iter[optimiser->iter])
		{
			std::cout << "Broadcasting phase randomized good reference at " << this->random_phase_good_res_iter[optimiser->iter] << " with upper limit at " << this->random_phase_good_res_upper_iter[optimiser->iter] << std::endl;
			std::cout << "Amplitude for phase randomization for the good reference has been set to " << this->random_phase_good_amplitude_iter[optimiser->iter] << std::endl;
			start_class = 0;
		}
	}
	for (int i = start_class; i < optimiser->mymodel.nr_classes; i++)
	{
		//int random_phase_index = (((((i - 1) % optimiser->mymodel.nr_classes) + 1) % (optimiser->node->size - 1)) + 1);
		if (i == 0)
		{
			random_phase_rank = ((optimiser->mymodel.nr_classes % (optimiser->node->size - 1)) + 1);
		}
		else
		{
			random_phase_rank = ((i % (optimiser->node->size - 1)) + 1);
		}
		optimiser->node->relion_MPI_Bcast(MULTIDIM_ARRAY(optimiser->mymodel.tau2_class[i]), MULTIDIM_SIZE(optimiser->mymodel.tau2_class[i]), MY_MPI_DOUBLE, random_phase_rank, MPI_COMM_WORLD);
		optimiser->node->relion_MPI_Bcast(MULTIDIM_ARRAY(optimiser->mymodel.data_vs_prior_class[i]), MULTIDIM_SIZE(optimiser->mymodel.data_vs_prior_class[i]), MY_MPI_DOUBLE, random_phase_rank, MPI_COMM_WORLD);
		optimiser->node->relion_MPI_Bcast(MULTIDIM_ARRAY(optimiser->mymodel.Iref[i]), MULTIDIM_SIZE(optimiser->mymodel.Iref[i]), MPI_DOUBLE, random_phase_rank, MPI_COMM_WORLD);
	}
}

//set the parameters for random phase classification.
template<typename T> void RandomPhase::initialize(T &optimiser,bool mpi)
{
	std::vector<std::string> parameter_string_vector;
	std::vector<int> default_parameter_number_vector;
	std::vector<bool> do_cycle_vector;
	this->do_random_phase = optimiser->parser.checkOption("--random_phase_otherrefs","This switch turns on the random phase 3D classification procedure");
	this->do_good_random_phase = optimiser->parser.checkOption("--random_phase_good_refs", "This option is similar to the --random_phase_other_refs option except that its used to specify the phase randomization of the good reference.");
	if (this->do_random_phase)
	{
		this->random_phase_string = optimiser->parser.getOption("--random_phase_res", "This sets the random phase resolution and random phase resolution upper limit for the random phase 3D classification, if specified, the random phase classification will be turned on and the 4 parameters to specify in a single cycle are the random phase resolution, the random phase upper limit , the cool down iteration number and the cool down cycle, these 4 parameters should be separated by ',', different cycles of random phase cool down should be separated by ':', for example 40,10,5,3:30,10,3,5  \nAlternatively, one single parameter is also supported, by providing only one parameter the random phase resolution is set, for example 40 means to perform randomize uppon 40 angstrom and the --iter specified iteration number is used, no cool down is performed. \nDefault:40", "40");
		if (random_phase_string.find(":") == std::string::npos && random_phase_string.find(",") == std::string::npos)
		{
			this->do_cyclic_random_phase = false;
		}
		else
		{
			this->do_cyclic_random_phase = true;
		}
		parameter_string_vector.push_back(random_phase_string);
		default_parameter_number_vector.push_back(4);
		this->random_phase_amplitude_string = optimiser->parser.getOption("--random_amplitude_other_refs", "This is for specifying the amplitude for phase randomization in units of 2pi, the iteration number to use this amplitude should follow the unit separated by comma, different cycles should be separated by colon, for example 0.8,10:0.6,20, when only a single number is provided, the iteration number is set to the total_iteration number that is specified by other options, Default:1", "1");
		if (random_phase_amplitude_string.find(":") == std::string::npos && random_phase_amplitude_string.find(",") == std::string::npos)
		{
			this->do_cyclic_amplitude = false;
		}
		else
		{
			this->do_cyclic_amplitude = true;
		}
		parameter_string_vector.push_back(random_phase_amplitude_string);
		default_parameter_number_vector.push_back(3);
		do_cycle_vector.push_back(do_cyclic_random_phase);
		do_cycle_vector.push_back(do_cyclic_amplitude);
	}
	if (this->do_good_random_phase)
	{
		this->random_phase_good_string = optimiser->parser.getOption("--random_phase_good_res", "Similar to the --random_phase_res option, this sets the random phase resolution and random phase resolution upper limit for the good reference, if specified, the phase randomization of the good reference will be turned on and the 4 parameters to specify in a single cycle are the random phase resolution, the random phase upper limit , the cool down iteration number and the cool down cycle, these 4 parameters should be separated by ',', different cycles of random phase cool down should be separated by ':', for example 40,10,5,3:30,10,3,5  \nAlternatively, one single parameter is also supported, by providing only one parameter the random phase resolution is set, for example 40 means to perform randomize uppon 40 angstrom and the --iter specified iteration number is used, no cool down is performed. \nTo maintain a divergence between the good and bad reference default is set to 10", "10");
		if (random_phase_good_string.find(":") == std::string::npos && random_phase_good_string.find(",") == std::string::npos)
		{
			this->do_cyclic_good_random_phase = false;
		}
		else
		{
			this->do_cyclic_good_random_phase = true;
		}
		parameter_string_vector.push_back(random_phase_good_string);
		default_parameter_number_vector.push_back(4);
		this->random_phase_good_amplitude_string = optimiser->parser.getOption("--random_amplitude_good_refs", "This is for specifying the amplitude for phase randomization in units of 2pi for the good references, please refer to the documentation of the --random_amplitude_other_refs option. Default:1", "1");
		if (random_phase_good_amplitude_string.find(":") == std::string::npos && random_phase_good_amplitude_string.find(",") == std::string::npos)
		{
			this->do_cyclic_good_amplitude = false;
		}
		else
		{
			this->do_cyclic_good_amplitude = true;
		}
		parameter_string_vector.push_back(random_phase_good_amplitude_string);
		default_parameter_number_vector.push_back(4);
		do_cycle_vector.push_back(do_cyclic_good_random_phase);
		do_cycle_vector.push_back(do_cyclic_good_amplitude);
		this->check_nr_iter(optimiser, parameter_string_vector, default_parameter_number_vector, do_cycle_vector, false);
		this->check_nr_iter(optimiser, parameter_string_vector, default_parameter_number_vector, do_cycle_vector, true);
		this->set_parameter_for_randomphase(this->random_phase_string, this->random_phase_amplitude_string, this->random_phase_good_string, this->random_phase_good_amplitude_string);
	}
	else
	{
		this->check_nr_iter(optimiser, parameter_string_vector, default_parameter_number_vector, do_cycle_vector, false);
		this->check_nr_iter(optimiser, parameter_string_vector, default_parameter_number_vector, do_cycle_vector, true);
		this->set_parameter_for_randomphase(this->random_phase_string, this->random_phase_amplitude_string);
	}
	this->randomize_phase_otherrefs(optimiser, mpi);
	if (this->do_good_random_phase)
	{
		this->randomize_phase_goodrefs(optimiser, mpi);
	}
	if (mpi)
	{
		this->get_phase_randomized_refs(optimiser, mpi);
	}
}

template<typename T> void RandomPhase::iterate_initialize(T &optimiser, bool mpi)
{
	if (this->do_random_phase_iter[optimiser->iter])
	{
		this->randomize_phase_otherrefs(mpi);
	}
	if (this->do_good_random_phase_iter[optimiser->iter])
	{
		this->randomize_phase_goodrefs(optimiser, mpi);
	}
	if (mpi)
	{
		this->get_phase_randomized_refs(optimiser, mpi);
	}
}
*/
/*RandomPhase::template<typename T> bool check(T &optimiser->node)
{
	return true;
}

bool check()
{
	return false;
}*/

void RandomPhase::string_set_up_debug() {
    std::cout << this->random_phase_string << std::endl;
    std::cout << this->random_phase_amplitude_string << std::endl;
    std::cout << this->random_phase_good_string << std::endl;
    std::cout << this->random_phase_good_amplitude_string << std::endl;
}

std::string RandomPhase::vector_to_string(std::vector<std::string> &parameter_vector, std::string delimiter) {
    std::string return_string = "";
    if (parameter_vector.size() == 0) {
        std::cout << "vector empty!" << std::endl;
        exit(EMPTY_ARG_ERROR);
    }
    for (int i = 1; i <= parameter_vector.size(); i++) {
        return_string += parameter_vector[i - 1];
        if (i != parameter_vector.size()) {
            return_string += delimiter;
        }
    }
    std::cout << return_string << std::endl;
    return return_string;
}
/*template<typename T> void RandomPhase::parse_initial(T &optimiser)
{
	this->do_random_phase = true;
	if (this->do_random_phase)
	{
		this->random_phase_string = optimiser->parser.getOption("--random_phase_res", "This sets the random phase resolution and random phase resolution upper limit for the random phase 3D classification, if specified, the random phase classification will be turned on and the 4 parameters to specify in a single cycle are the random phase resolution, the random phase upper limit , the cool down iteration number and the cool down cycle, these 4 parameters should be separated by ',', different cycles of random phase cool down should be separated by ':', for example 40,10,5,3:30,10,3,5  \nAlternatively, one single parameter is also supported, by providing only one parameter the random phase resolution is set, for example 40 means to perform randomize uppon 40 angstrom and the --iter specified iteration number is used, no cool down is performed. \nDefault:40", "40");
		if (this->random_phase_string.find(":") == std::string::npos && this->random_phase_string.find(",") == std::string::npos)
		{
			this->do_cyclic_random_phase = false;
		}
		else
		{
			this->do_cyclic_random_phase = true;
		}
		this->parameter_string_vector.push_back(random_phase_string);
		this->default_parameter_number_vector.push_back(4);
		this->random_phase_amplitude_string = optimiser->parser.getOption("--random_amplitude_other_refs", "This is for specifying the amplitude for phase randomization in units of 2pi, the iteration number to use this amplitude should follow the unit separated by comma, different cycles should be separated by colon, for example 0.8,10:0.6,20, when only a single number is provided, the iteration number is set to the total_iteration number that is specified by other options, Default:1", "1");
		if (this->random_phase_amplitude_string.find(":") == std::string::npos && this->random_phase_amplitude_string.find(",") == std::string::npos)
		{
			this->do_cyclic_amplitude = false;
		}
		else
		{
			this->do_cyclic_amplitude = true;
		}
		this->parameter_string_vector.push_back(random_phase_amplitude_string);
		this->default_parameter_number_vector.push_back(3);
		this->do_cycle_vector.push_back(do_cyclic_random_phase);
		this->do_cycle_vector.push_back(do_cyclic_amplitude);
	}
	this->do_good_random_phase = parser.checkOption("random_phase_good_refs","This is for turning on the phase randomization procedure of the good classes.");
	if (this->do_good_random_phase)
	{
		this->random_phase_good_string = optimiser->parser.getOption("--random_phase_good_res", "Similar to the --random_phase_res option, this sets the random phase resolution and random phase resolution upper limit for the good reference, if specified, the phase randomization of the good reference will be turned on and the 4 parameters to specify in a single cycle are the random phase resolution, the random phase upper limit , the cool down iteration number and the cool down cycle, these 4 parameters should be separated by ',', different cycles of random phase cool down should be separated by ':', for example 40,10,5,3:30,10,3,5  \nAlternatively, one single parameter is also supported, by providing only one parameter the random phase resolution is set, for example 40 means to perform randomize uppon 40 angstrom and the --iter specified iteration number is used, no cool down is performed. \nTo maintain a divergence between the good and bad reference default is set to 10", "10");
		if (this->random_phase_good_string.find(":") == std::string::npos && this->random_phase_good_string.find(",") == std::string::npos)
		{
			this->do_cyclic_good_random_phase = false;

		}
		else
		{
			this->do_cyclic_good_random_phase = true;
		}
		this->parameter_string_vector.push_back(random_phase_good_string);
		this->default_parameter_number_vector.push_back(4);
		this->random_phase_good_amplitude_string = optimiser->parser.getOption("--random_amplitude_good_refs", "This is for specifying the amplitude for phase randomization in units of 2pi for the good references, please refer to the documentation of the --random_amplitude_other_refs option. Default:1", "1");
		if (this->random_phase_good_amplitude_string.find(":") == std::string::npos && this->random_phase_good_amplitude_string.find(",") == std::string::npos)
		{
			this->do_cyclic_good_amplitude = false;
		}
		else
		{
			this->do_cyclic_good_amplitude = true;
		}
		this->parameter_string_vector.push_back(random_phase_good_amplitude_string);
		this->default_parameter_number_vector.push_back(4);
		this->do_cycle_vector.push_back(do_cyclic_good_random_phase);
		this->do_cycle_vector.push_back(do_cyclic_good_amplitude);

	}
}
*/

/*template<typename T> void RandomPhase::iterate_set_up_debug(T &optimiser)
{
	for (int i = 1; i <= optimiser->iter; i++)
	{
		std::cout << this->random_phase_res_iter[i - 1] << std::endl;
		std::cout << this->random_phase_good_res_iter[i - 1] << std::endl;
		std::cout << this->random_phase_res_upper_iter[i - 1] << std::endl;
		std::cout << this->random_phase_good_res_upper_iter[i - 1] << std::endl;
		std::cout << this->random_phase_amplitude_iter[i - 1] << std::endl;
		std::cout << this->random_phase_good_amplitude_iter[i - 1] << std::endl;
	}
}
*/
