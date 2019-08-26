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

#ifndef RANDOM_PHASE_H_
#define RANDOM_PHASE_H_


/*#include <pthread.h>
#include "ml_model.h"
#include "parallel.h"
#include "exp_model.h"
#include "fftw.h"
#include "strings.h"
#include "ml_optimiser.h"
#include "ml_optimiser_mpi.h"*/
#include "src/ml_model.h"
#include "src/parallel.h"
#include "src/exp_model.h"
#include "src/fftw.h"
#include "src/strings.h"
#include "src/macros.h"
#include "src/mpi.h"
#define RANDOM_PHASE_DEV_EXIT_CODE -1
#define RANDOM_PHASE_RES 40
#define GOOD_RANDOM_PHASE_RES 10
#define RANDOM_PHASE_RES_UPPER 0.1
#define GOOD_RANDOM_PHASE_RES_UPPER 5
#define COOL_DOWN_CYCLE 3
#define COOL_DOWN_ITERATION 3
#define DEFAULT_AMPLITUDE 1
#define DEFAULT_GOOD_AMPLITUDE 0.1
#define AMPLITUDE_FLOAT_WIDTH 6
#define AMPLITUDE_FLOAT_PREC 5
#define GOOD_AMPLITUDE_FLOAT_WIDTH 6
#define GOOD_AMPLITUDE_FLOAT_PREC 5
//#define TWO_PI  
#define DATA_TYPE_ERROR -10
#define EMPTY_ARG_ERROR -11
//#include "src/ml_optimiser.h"
//#include "src/ml_optimiser_mpi.h"

//class RandomPhase : private MlOptimiserMpi{};
//forward declaration of the two optimiser classes.
class MlOptimiser;
class MlOptimiserMpi;
class RandomPhase
{
	//friend class MlOptimiser;
	//The public members of the class are the parameter setup functions and parameter storing vectors, also the randomize beyond function which carriers out the randomize and broadcasting function.
	public:

		/*template<typename T> void randomize_phase_otherrefs(T &optimiser, bool mpi = false);
		  template<typename T> void randomize_phase_goodrefs(T &optimiser, bool mpi = false);
		  template<typename T> void get_phase_randomized_refs(T &optimiser, bool mpi = false);
		//void auto_parameter_completion(const int &max_nr_iter, const RFLOAT &default_value, std::vector<RFLOAT> parameter_iter_vector);
		//Check the largest total number of iteration according to all given parameters and sets the nr_iter in MlOptimiser(Mpi) to it.
		template<typename T> void check_nr_iter(T &optimiser, std::vector<std::string> &string_vector, const std::vector<int> &default_parameter_number_vector, std::vector<bool> do_cycle_vector, bool do_auto_completion);
		template<typename T> void set_parameter(const std::string &parameter_string, T &parameter_iter , const std::string &data_type, const std::vector<std::string> &id_map_vector);
		template<typename T> void set_parameter_for_randomphase(T &optimiser, const std::string &random_phase_string, const std::string &random_phase_amplitude_string = NULL, const std::string &random_phase_good_string = NULL, const std::string &random_phase_good_amplitude_string = NULL, const std::vector<std::string> id_map_vector = std::vector<std::string>(), const std::vector<std::string> good_id_map_vector = std::vector<std::string>());
		//void setParameterForGoodRandomphase(const std::string &good_random_phase_string, const std::string &good_random_phase_amplitude_string);
		//void setHealpixOrderIter(std::vector<int> &healpix_iter, std::vector<RFLOAT> &sigma_ang_iter ,const std::string &healpix_option);
		//void updateIterLocalSearches(HealpixSampling &sampling,MlModel &mymodel,const int &healpix_order ,const RFLOAT &sigma_ang);

		//Initializes the beginning point of the random phase 3D classification, the references and the noise spectrum should both be considered as opposed to initialization at the beginning of each iteration
		template<typename T> void initialize(T &optimiser, bool mpi = false);

		Sets the parameters for random phase at the beginning of every iteration, this is for future development for run time update of parameter specification.
		template<typename T> void iterate_initialize(T &optimiser, bool mpi = false);

		//These two function checks whether the myrandom is used in a mpi context or not.
		//template<typename T> bool check(T &optimiser_node);
		//bool check();

		//These two functions merely funcion as debug utilities.
		void string_set_up_debug();
		//template<typename T> void iterate_set_up_debug(T &optimiser);*/

		//debug only
		void string_set_up_debug();
		std::string vector_to_string(std::vector<std::string> &parameter_vector, std::string delimiter);
		template<typename T> void check_nr_iter(T &optimiser, std::vector<std::string*> &string_vector, std::vector<int> &default_parameter_number_vector, std::vector<bool> do_cycle_vector, bool do_auto_completion)
		{
			if (default_parameter_number_vector.size() != string_vector.size())
			{
				if (optimiser->verb > 0 && optimiser->node->isMaster())
				{
					std::cout << "The default parameter number vector has a different size then the parameter string vector! please check your specification in the parseInitial function" << std::endl;
				}
				exit(-1);
			}
			int total_iter = 0;
			int temp_iter = optimiser->nr_iter;
			int cool_down_cycle = 0;
			int cool_down_iteration = 0;
			for (int i = 1; i <= string_vector.size(); i++)
			{
				total_iter = 0;
				temp_iter = optimiser->nr_iter;
				std::vector<std::string> colon_split;
				std::vector<std::string> comma_split;
				splitString(*string_vector[i - 1], ":", colon_split, true);
				if (colon_split.empty())
				{
					colon_split.push_back(*string_vector[i - 1]);
				}
				for (int j = 1; j <= colon_split.size(); j++)
				{
					splitString(colon_split[j - 1], ",", comma_split, true);
					if (comma_split.empty())
					{
						comma_split.push_back(colon_split[j - 1]);
					}
					if ((default_parameter_number_vector[i - 1] - comma_split.size()) > 1 && (do_cycle_vector[i - 1]) && (!do_auto_completion))
					{
						if (optimiser->verb > 0 && optimiser->node->isMaster())
						{
							std::cout << "Two parameters short, assigning the default value of COOL_DOWN_ITERATION to cool_down_iteration"<< std::endl;
						}
						if (j != colon_split.size())
						{
							if (optimiser->verb > 0 && optimiser->node->isMaster())
							{
								std::cout << "Setting the cool down cycle to default: COOL_DOWN_CYCLE " << std::endl;
							}
							cool_down_cycle = COOL_DOWN_CYCLE;
						}
						else if (temp_iter < cool_down_iteration )
						{
							if (optimiser->verb > 0 && optimiser->node->isMaster())
							{
								std::cout << "Previous cool down cycles has exceeded the previous maximum number of iterations, setting cool_down_cycle to default: COOL_DOWN_CYCLE" << std::endl;
							}
							cool_down_cycle = COOL_DOWN_CYCLE;
						}
						else
						{
							if (optimiser->verb > 0 && optimiser->node->isMaster())
							{
								std::cout << "Now assigning the remaining iterations to the final run."<< std::endl ;
							}
							cool_down_cycle = temp_iter / cool_down_iteration;
						}
						comma_split.push_back(integerToString(cool_down_iteration, (FLOOR(log10(ABS(cool_down_iteration))) + 1), 0));
						comma_split.push_back(integerToString(cool_down_cycle, (FLOOR(log10(ABS(cool_down_cycle))) + 1), 0));
						colon_split[j - 1] = vector_to_string(comma_split, ",");
					} 
					else if ((default_parameter_number_vector[i - 1] - comma_split.size()) == 1 && (do_cycle_vector[i - 1]) && (!do_auto_completion))
					{
						if (optimiser->verb > 0 && optimiser->node->isMaster())
						{
							std::cout << default_parameter_number_vector[i -1] <<"parameters required for this string!One parameter missing, using the last parameter as cool_down_iteration.";
						}
						cool_down_iteration = textToInteger(*(comma_split.end() - 1));
						if (j != colon_split.size() || (temp_iter < cool_down_iteration))
						{
							if (optimiser->verb > 0 && optimiser->node->isMaster())
							{
								std::cout<< "Previous cycles has exceeded or this is not the final run, assigning the default value of COOL_DOWN_CYCLE to cool_down_cycle." << std::endl;
							}
							cool_down_cycle = COOL_DOWN_CYCLE;
						}
						else
						{
							if (optimiser->verb > 0 && optimiser->node->isMaster())
							{
								std::cout<< "Assigning remaining iterations to the final run." << std::endl;
							}
							cool_down_cycle = temp_iter / cool_down_iteration;
						}
						comma_split.push_back(integerToString(cool_down_cycle, (FLOOR(log10(ABS(cool_down_cycle))) + 1), 0));
						colon_split[j - 1] = vector_to_string(comma_split, ",");
					}
					else if (do_cycle_vector[i - 1] || do_auto_completion)
					{
						cool_down_iteration = textToInteger(*(comma_split.end() - 2));
						cool_down_cycle = textToInteger(*(comma_split.end() - 1));
						if (do_auto_completion)
						{
							if (j == colon_split.size())
							{
								while (temp_iter > (((cool_down_iteration + 1) * cool_down_cycle)))
								{
									cool_down_cycle += 1;
								}
								*(comma_split.end() - 1) = integerToString(cool_down_cycle, (FLOOR(log10(ABS(cool_down_cycle))) + 1), 0);
							}
							colon_split[j - 1] = vector_to_string(comma_split, ",");
						}
						else
						{
							if (optimiser->verb > 0 && optimiser->node->isMaster())
							{
								std::cout << "Using the last parameter as the cool_down_cycle, using the second last parameter as cool_down_iteration." << std::endl;
							}
						}
					}
					else
					{
						cool_down_iteration = 1;
						cool_down_cycle = optimiser->nr_iter;
						if (default_parameter_number_vector[i - 1] == 4)
						{
							comma_split.push_back(floatToString(RANDOM_PHASE_RES_UPPER, 2, 1));
						}
						comma_split.push_back(integerToString(cool_down_iteration, (FLOOR(log10(ABS(cool_down_iteration))) + 1), 0));
						comma_split.push_back(integerToString(cool_down_cycle, (FLOOR(log10(ABS(cool_down_cycle))) + 1), 0));
						colon_split[j - 1] = vector_to_string(comma_split, ",");
					}
					//reassign value to default parameter number vector. This way, all colon separated terms will be completed to the maximum number of comma splitted terms.
					default_parameter_number_vector[i - 1] = comma_split.size();
					temp_iter -= cool_down_cycle * cool_down_iteration;
					total_iter += cool_down_cycle * cool_down_iteration;
				}
				if (total_iter > optimiser->nr_iter)
				{
					optimiser->nr_iter = total_iter;
				}
				*string_vector[i - 1] = vector_to_string(colon_split, ":");
				//std::cout << "The "<< (i - 1) << "th" << " string is now:" << *string_vector[i - 1] << std::endl;
			}
		}


		template<typename U ,typename T> void set_parameter(const U optimiser, const std::string &parameter_string, std::vector<T> &parameter_iter ,  const std::string &data_type, const std::vector<std::string> &id_map_vector)
		{
			//std::string mystrings[3] = {"RFLOAT","int","bool"};
			std::string temp[3] = {"RFLOAT", "int", "bool"};
			std::vector<std::string> support_types(temp, temp + 3);// = {"RFLOAT", "int", "bool"};// (mystrings, mystrings + sizeof(mystrings) / sizeof(std::string));
			std::vector<std::string>::iterator it;
			int value_id;
			int iteration_id;
			int cycle_id;
			//RFLOAT double_value;
			//int int_value;
			//bool bool_value;
			//use the first element in parameter_iter vector to specify the data type of push_in_value
			T push_in_value = parameter_iter[0];
			int data_type_specify_id;
			int cycle;
			int iteration;
                        MPI_Barrier(MPI_COMM_WORLD);
			it = std::find(support_types.begin(), support_types.end(), data_type);
			//debug only
			/*std::string temp_data_type = "bool";
			  it = std::find(support_types.begin(), support_types.end(), temp_data_type);
			  std::cout << "\033[0;31m" << "debug only:" << std::distance(support_types.begin(), it) << "\033[0m\n";
			  std::cout << "\033[0;31m" << "debug only:" << *(it) << "\033[0m\n";
			  exit(1);*/
			if (it == support_types.end())
			{
				if (optimiser->verb > 0 && optimiser->node->isMaster())
				{
					std::cout << "Please provide a valid data type!, the supported types are ";
				}
				for (int i = 0 ; i < (support_types.size() - 1) ; i++)
				{
					if (optimiser->verb > 0 && optimiser->node->isMaster())
					{
						std::cout << *(support_types.begin() + i) << ", ";
					}
				}
				if (optimiser->verb > 0 && optimiser->node->isMaster())
				{
					std::cout << *(support_types.end() - 1) << "." << std::endl;
				}
				exit(DATA_TYPE_ERROR);
			}
			else
			{
				std::vector<std::string> colon_split;
				std::vector<std::string> comma_split;
				splitString(parameter_string, ":", colon_split, true);
				if (colon_split.empty())
				{
					colon_split.push_back(parameter_string);
				}
				for (int i = 0 ; i < id_map_vector.size(); i++)
				{
					if (id_map_vector[i] == "value")  value_id = i;
					if (id_map_vector[i] == "iteration")  iteration_id = i;
					if (id_map_vector[i] == "cycle")  cycle_id = i;
				}
				if (! parameter_iter.empty())
				{
					//If the iter vector passed in is not empty, free it before further pushing in other elements.
					parameter_iter.resize(0);
					parameter_iter.shrink_to_fit();
				}
				for (int i = 0; i < colon_split.size(); i ++)
				{
					splitString(colon_split[i], ",", comma_split, true);
					if (comma_split.empty())
					{
						comma_split.push_back(colon_split[i]);
					}
					for (int j = 0; j < comma_split.size(); j ++)
					{
						if (j == value_id)
						{
							data_type_specify_id = std::distance(support_types.begin(), it);
							if (optimiser->verb > 0 && optimiser->node->isMaster())
							{
								std::cout << "\033[0;31mThe comma split size is " << comma_split.size() << "The current colon split element is "<< colon_split[ i ] << "\033[0m\n" ;
							}
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
									if (comma_split[j] == "false")
										push_in_value = false;
									if (comma_split[j] == "true") 
										push_in_value = true;
									break;
							}
						}
						else if (j == iteration_id)
							iteration = textToInteger(comma_split[j]);
						else if (j == cycle_id)
							cycle = textToInteger(comma_split[j]);
						else
							if (optimiser->verb > 0 && optimiser->node->isMaster())
							{
								std::cout << "The id_map_vector has less elements then parameter string, please check your specification!" << std::endl;
							}
					}
					for (int k = 0; k < (iteration * cycle); k++)
					{
						parameter_iter.push_back(push_in_value);
					}
				}
			}
                        MPI_Barrier(MPI_COMM_WORLD);
		}

		template<typename T> void print_iter_info(T &optimiser)
		{
			for (int i = 1; i <= optimiser->nr_iter; i ++)
			{
				if (optimiser->verb > 0 && optimiser->node->isMaster())
				{
					std::cout << "\033[0;31mThe lower res for iteration" << i << " is " << this->random_phase_res_iter[i - 1] <<"\n";
					std::cout << "The upper res for iteration" << i << " is " << this->random_phase_res_upper_iter[i - 1] <<"\n";
					std::cout << "The bad amplitude for iteration" << i << " is " << this->random_phase_amplitude_iter[i - 1] <<"\033[0m\n";
					std::cout << "The do random phase boolean for iteration" << i << " is " << this->do_random_phase_iter[i - 1] <<"\033[0m\n";
				}
				if (this->do_good_random_phase)
				{
					if (optimiser->verb > 0 && optimiser->node->isMaster())
					{
						std::cout << "\033[0;32mThe lower res of good reference for iteration" << i << " is " << this->random_phase_good_res_iter[i - 1] <<"\n";
						std::cout << "The lower res of good reference for iteration" << i << " is " << this->random_phase_good_res_upper_iter[i - 1] <<"\n";
						std::cout << "The good amplitude for iteration" << i << " is " << this->random_phase_good_amplitude_iter[i - 1] <<"\033[0m\n";
						std::cout << "The do good random phase boolean for iteration" << i << " is " << this->do_good_random_phase_iter[i - 1] <<"\033[0m\n";
					}
				}
				else
				{
					if (optimiser->verb > 0 && optimiser->node->isMaster())
					{
						std::cout << "\033[0;32mNo good reference randomizing, skipping info for good random phase\033[0m\n";
					}
				}
			}
		}


		template<typename T> void set_parameter_for_randomphase(T &optimiser,const std::string &random_phase_string, const std::string &random_phase_amplitude_string = "", const std::string &random_phase_good_string = "", const std::string &random_phase_good_amplitude_string = "", const std::vector<std::string> id_map_vector = std::vector<std::string>(), const std::vector<std::string> good_id_map_vector = std::vector<std::string>())
		{
			std::vector<std::string> colon_split;
			std::vector<std::string> comma_split;
			int temp_int = 100;
			RFLOAT temp_rfloat = 0.1;
			bool temp_bool = false;
			int iteration;
			std::string temp[3] =  {"value", "iteration", "cycle"};
			int cycle;
			std::vector<std::string> lower_id_map_vector(temp, temp + 3);// = {"value", "iteration", "cycle"};
			//the lower res and the upper limit and also the amplitude along with the do_random_phase boolean vector can share a common id_map_vector.
			//std::vector<std::string> upper_id_map_vector;
			std::string lower_string;
			std::string upper_string;
			std::string bool_string;
                        MPI_Barrier(MPI_COMM_WORLD);
			splitString(random_phase_string, ":", colon_split, true);
			if (colon_split.empty())
			{
				colon_split.push_back(random_phase_string);
			}
			for (int i = 1; i <= colon_split.size(); i++)
			{
				//std::cout << "\033[0;31m This is the debug line, the colon split element is now " << colon_split[i - 1] << "\033[0m\n";
				splitString(colon_split[i -1], ",", comma_split, true);
				if (comma_split.empty())
				{
					if (optimiser->verb > 0 && optimiser->node->isMaster())
					{
						std::cout <<"\033[0;31mThe check_nr_iter function should be called to complete the given parameter to the default form, please check your code!\033[0m\n";
					}
				}
				iteration = textToInteger(*(comma_split.end() - 2));
				cycle = textToInteger(*(comma_split.end() - 1));
				for (int mycycle = 1; mycycle <= cycle; mycycle ++) 
				{
					bool_string += "true,1,1:";
					bool_string += "false,1,";
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
			this->random_phase_res_iter.push_back(temp_int);
			this->random_phase_res_upper_iter.push_back(temp_rfloat);
			this->do_random_phase_iter.push_back(temp_bool);
			temp_rfloat = 1.0;
			this->random_phase_amplitude_iter.push_back(temp_rfloat);
			//std::cout << "\033[0;31mCongratulations! You have reached line 444" << upper_string << lower_string << "The boolean string is: " << bool_string << "\033[0m\n";
			this->set_parameter(optimiser, lower_string, this->random_phase_res_iter, "RFLOAT", lower_id_map_vector);
			this->set_parameter(optimiser, upper_string, this->random_phase_res_upper_iter, "RFLOAT", lower_id_map_vector);
			this->set_parameter(optimiser, bool_string, this->do_random_phase_iter, "bool", lower_id_map_vector);
			//std::cout << "\033[0;31mCongratulations! You have solved the initialization problem!\033[0m\n"; 
			if (random_phase_amplitude_string != "")
			{
				set_parameter(optimiser, random_phase_amplitude_string, this->random_phase_amplitude_iter, "RFLOAT", lower_id_map_vector);
			}
			else
			{
				if (optimiser->verb > 0 && optimiser->node->isMaster())
				{
					std::cout << "The phase_amplitude is not provided, using the default amplitude for random phase!" << std::endl;
				}
				//exit(EMPTY_ARG_ERROR);
				std::string temp_string = "";
				temp_string += floatToString(DEFAULT_AMPLITUDE,AMPLITUDE_FLOAT_WIDTH,AMPLITUDE_FLOAT_PREC);
				temp_string += ",";
				temp_string += "1,";
				temp_string += integerToString(optimiser->nr_iter, (FLOOR(log10(ABS(optimiser->nr_iter))) + 1), 0);
				set_parameter(optimiser, temp_string, this->random_phase_amplitude_iter, "RFLOAT", lower_id_map_vector);
			}

			if (random_phase_good_string != "")
			{
				splitString(random_phase_good_string, ":", colon_split, true);
				lower_string = "";
				upper_string = "";
				bool_string = "";
				for (int i = 1; i <= colon_split.size(); i++)
				{
					iteration = textToInteger(comma_split[2]);
					cycle = textToInteger(comma_split[3]);
					for (int mycycle = 1; mycycle <= cycle; mycycle ++) 
					{
						bool_string += "true,1,1:";
						bool_string += "false,1,";
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
				temp_rfloat = 0.1;
				this->random_phase_good_res_iter.push_back(temp_int);
				this->random_phase_good_res_upper_iter.push_back(temp_rfloat);
				temp_rfloat = 1.0;
				this->do_good_random_phase_iter.push_back(temp_bool);
				this->random_phase_good_amplitude_iter.push_back(temp_rfloat);
				this->set_parameter(optimiser, lower_string, this->random_phase_good_res_iter, "RFLOAT", lower_id_map_vector);
				this->set_parameter(optimiser, upper_string, this->random_phase_good_res_upper_iter, "RFLOAT", lower_id_map_vector);
				this->set_parameter(optimiser, bool_string, this->do_good_random_phase_iter, "bool", lower_id_map_vector);
				if (random_phase_good_amplitude_string != "")
				{
					this->set_parameter(optimiser, random_phase_good_amplitude_string, this->random_phase_good_amplitude_iter, "RFLOAT", lower_id_map_vector);
				}
				else
				{
					if (optimiser->verb > 0 && optimiser->node->isMaster())
					{
						std::cout << "The phase_amplitude is not provided, using the default amplitude for good random phase!" << std::endl;
					}
					//exit(EMPTY_ARG_ERROR);
					std::string temp_string = "";
					temp_string += floatToString(DEFAULT_GOOD_AMPLITUDE,GOOD_AMPLITUDE_FLOAT_WIDTH,GOOD_AMPLITUDE_FLOAT_PREC);
					temp_string += ",";
					temp_string += "1,";
					temp_string += integerToString(optimiser->nr_iter, (FLOOR(log10(ABS(optimiser->nr_iter))) + 1), 0);
					this->set_parameter(optimiser, temp_string, this->random_phase_good_amplitude_iter, "RFLOAT", lower_id_map_vector);
				}
			}
                        MPI_Barrier(MPI_COMM_WORLD);
		}

		template<typename T> void randomize_phase_otherrefs(T &optimiser, bool mpi)
		{
			int random_phase_rank;
			int random_phase_index;
			int random_phase_upper_index;
			RFLOAT random_phase_amplitude;
                        MPI_Barrier(MPI_COMM_WORLD);
			if (this->do_random_phase_iter[optimiser->iter])
			{
				//If the mpi is not invoked, then no need to broadcast.
				random_phase_index = ROUND(optimiser->mymodel.ori_size * optimiser->mymodel.pixel_size / this->random_phase_res_iter[optimiser->iter]);     
				random_phase_upper_index = ROUND(optimiser->mymodel.ori_size * optimiser->mymodel.pixel_size / this->random_phase_res_upper_iter[optimiser->iter]);     
				random_phase_amplitude = this->random_phase_amplitude_iter[optimiser->iter];
				for (int i = 1; i < optimiser->mymodel.nr_classes; i ++)
				{
					if (! mpi)
					{
						optimiser->mymodel.tau2_class[i] = optimiser->mymodel.tau2_class[0];
						optimiser->mymodel.data_vs_prior_class[i] = optimiser->mymodel.data_vs_prior_class[0];
						//optimiser->mymodel.pdf_direction[i] = optimiser->mymodel.pdf_direction[0];
						optimiser->mymodel.Iref[i] = optimiser->mymodel.Iref[0];
						randomizePhasesBeyond(optimiser->mymodel.Iref[i], random_phase_index, random_phase_upper_index, random_phase_amplitude); 
					}
					else
					{
						// distribute the phase randomizing tasks to different slaves if mpi is invoked.
						random_phase_rank = (i % (optimiser->node->size - 1) + 1);
						if (optimiser->node->rank == random_phase_rank)
						{
							optimiser->mymodel.tau2_class[i] = optimiser->mymodel.tau2_class[0];
							optimiser->mymodel.data_vs_prior_class[i] = optimiser->mymodel.data_vs_prior_class[0];
							//optimiser->mymodel.pdf_direction[i] = optimiser->mymodel.pdf_direction[0];
							optimiser->mymodel.Iref[i] = optimiser->mymodel.Iref[0];
							randomizePhasesBeyond(optimiser->mymodel.Iref[i], random_phase_index, random_phase_upper_index, random_phase_amplitude);
						}
					}
				}
			}
                        MPI_Barrier(MPI_COMM_WORLD);
		}
		template<typename T> void randomize_phase_goodrefs(T &optimiser, bool mpi)
		{
			int random_phase_rank;
			int random_phase_index;
			int random_phase_upper_index;
			RFLOAT random_phase_amplitude;
                        MPI_Barrier(MPI_COMM_WORLD);
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
				if (optimiser->verb > 0 && optimiser->node->isMaster())
				{
					std::cout<< "randomization of good reference complete!" << std::endl;
				}
			}
                        MPI_Barrier(MPI_COMM_WORLD);
		}

		template<typename T> void get_phase_randomized_refs(T &optimiser, bool mpi)
		{
			int random_phase_rank;
			int start_class = 1;
			//stay silent for mpi slave processes.
                        MPI_Barrier(MPI_COMM_WORLD);
			if (mpi && this-> do_random_phase_iter[optimiser->iter])	
			{
				if (optimiser->verb > 0 && optimiser->node->isMaster())
				{
					std::cout << "Broadcasting the phase randomized refereces with phase randomized at " << this->random_phase_res_iter[optimiser->iter] << " with upper limit at " << this->random_phase_res_upper_iter[optimiser->iter] << std::endl;
					std::cout << "Amplitude for phase randomization has been set to " << this->random_phase_amplitude_iter[optimiser->iter] << std::endl;
				}
				if (this->do_good_random_phase && this->do_good_random_phase_iter[optimiser->iter])
				{
					start_class = 0;
					if (optimiser->verb > 0 && optimiser->node->isMaster())
					{
						std::cout << "Broadcasting phase randomized good reference at " << this->random_phase_good_res_iter[optimiser->iter] << " with upper limit at " << this->random_phase_good_res_upper_iter[optimiser->iter] << std::endl;
						std::cout << "Amplitude for phase randomization for the good reference has been set to " << this->random_phase_good_amplitude_iter[optimiser->iter] << std::endl;
					}
				}
				for (int i = start_class; i < optimiser->mymodel.nr_classes; i++)
				{
					if (optimiser->verb > 0 && optimiser->node->isMaster())
					{
						std::cout << "\033[0;32mNow broadcasting phase randomized reference for class " << i <<"\033[0m\n";
					}
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
					std::cout << "\033[0;32mBroadcasting for class " << i << "complete! " << "\033[0m\n";
					//std::cout << "\033[0;32mBroadcasting complete! " << "\033[0m\n";
				}
			}
                        //MPI_Barrier(MPI_COMM_WORLD);
		}

		//set the parameters for random phase classification.
		template<typename T> void initialize(T &optimiser,bool mpi)
		{
                        MPI_Barrier(MPI_COMM_WORLD);
			//this->do_random_phase = optimiser->parser.checkOption("--random_phase_otherrefs","This switch turns on the random phase 3D classification procedure");
			//this->do_good_random_phase = optimiser->parser.checkOption("--random_phase_good_refs", "This option is similar to the --random_phase_other_refs option except that its used to specify the phase randomization of the good reference.");
			//DEBUG ONLY
			/*for (int i = 1; i <= this->parameter_string_vector.size(); i ++)
			  {
			  std::cout << "\033[0;31m" << *parameter_string_vector[i - 1] <<"\033[0m\n";
			  }*/
			if (this->do_good_random_phase)
			{
				this->check_nr_iter(optimiser, this->parameter_string_vector, this->default_parameter_number_vector, this->do_cycle_vector, false);
				this->check_nr_iter(optimiser, this->parameter_string_vector, this->default_parameter_number_vector, this->do_cycle_vector, true);
				this->set_parameter_for_randomphase(optimiser, this->random_phase_string, this->random_phase_amplitude_string, this->random_phase_good_string, this->random_phase_good_amplitude_string);
			}
			else
			{
				this->check_nr_iter(optimiser, this->parameter_string_vector, this->default_parameter_number_vector, this->do_cycle_vector, false);
				this->check_nr_iter(optimiser, this->parameter_string_vector, this->default_parameter_number_vector, this->do_cycle_vector, true);
				this->set_parameter_for_randomphase(optimiser, this->random_phase_string, this->random_phase_amplitude_string);
			}
			if (optimiser->verb > 0 && optimiser->node->isMaster())
			{
				std::cout << "\033[0;31m Entering initialization function!\033[0m"  << std::endl;
			}
			this->randomize_phase_otherrefs(optimiser, mpi);
			if (this->do_good_random_phase)
			{
				this->randomize_phase_goodrefs(optimiser, mpi);
			}
			if (mpi)
			{
				//std::cout << "\033[0;33mOop! Seems to be a problem in broadcasting.....\033[0m\n";
				this->get_phase_randomized_refs(optimiser, mpi);
			}
                        MPI_Barrier(MPI_COMM_WORLD);
		}

		template<typename T> void iterate_initialize(T &optimiser, bool mpi)
		{
                        MPI_Barrier(MPI_COMM_WORLD);
			if (this->do_random_phase_iter[optimiser->iter])
			{
				this->randomize_phase_otherrefs(optimiser, mpi);
				if (optimiser->verb > 0 && optimiser->node->isMaster())
				{
					std::cout << "\033[0;31mNow doing initialization for iterations, the randomization of the bad references complete!\033[0m\n";
				}
			}
			if (this->do_good_random_phase && this->do_good_random_phase_iter[optimiser->iter])
			{
				this->randomize_phase_goodrefs(optimiser, mpi);
				if (optimiser->verb > 0 && optimiser->node->isMaster())
				{
					std::cout << "\033[0;32mNow doing initialization for iterations, the randomization of the good references complete!\033[0m\n";
				}
			}
			if (mpi)
			{
				this->get_phase_randomized_refs(optimiser, mpi);
				if (optimiser->verb > 0 && optimiser->node->isMaster())
				{
					std::cout << "\033[0;33mBroadcasting complete!\033[0m\n";
				}
			}
                        MPI_Barrier(MPI_COMM_WORLD);
		}

		template<typename T> void iterate_set_up_debug(T &optimiser)
		{
			for (int i = 1; i <= optimiser->iter; i++)
			{
				if (optimiser->verb > 0 && optimiser->node->isMaster())
				{
					std::cout << this->random_phase_res_iter[i - 1] << std::endl;
					std::cout << this->random_phase_good_res_iter[i - 1] << std::endl;
					std::cout << this->random_phase_res_upper_iter[i - 1] << std::endl;
					std::cout << this->random_phase_good_res_upper_iter[i - 1] << std::endl;
					std::cout << this->random_phase_amplitude_iter[i - 1] << std::endl;
					std::cout << this->random_phase_good_amplitude_iter[i - 1] << std::endl;
				}
			}
		}
		template<typename T> void parse_initial(T &optimiser)
		{
			MPI_Barrier(MPI_COMM_WORLD);
			this->do_random_phase = true;
			if (! this->parameter_string_vector.empty())
			{
				this->parameter_string_vector.resize(0);
				//*(this->parameter_string_vector).shrink_to_fit();
			}
			if (! this->default_parameter_number_vector.empty())
			{
				this->default_parameter_number_vector.resize(0);
				//*(this->default_parameter_number_vector).shrink_to_fit();
			}
			if (this->do_random_phase)
			{
				this->random_phase_string = optimiser->parser.getOption("--random_phase_res", "This sets the random phase resolution and random phase resolution upper limit for the random phase 3D classification, if specified, the random phase classification will be turned on and the 4 parameters to specify in a single cycle are the random phase resolution, the random phase upper limit , the cool down iteration number and the cool down cycle, these 4 parameters should be separated by ',', different cycles of random phase cool down should be separated by ':', for example 40,10,5,3:30,10,3,5  \nAlternatively, one single parameter is also supported, by providing only one parameter the random phase resolution is set, for example 40 means to perform randomize uppon 40 angstrom and the --iter specified iteration number is used, no cool down is performed. \nDefault:40", "40");
				if (this->random_phase_string.find(":") == std::string::npos && this->random_phase_string.find(",") == std::string::npos)
				{
					//std::cout << "\033[0;31mThis is the parse initial function, the do cyclic random phase has been set to false\033[0m\n";
					this->do_cyclic_random_phase = false;
				}
				else
				{
					this->do_cyclic_random_phase = true;
				}
				this->parameter_string_vector.push_back(&this->random_phase_string);
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
				this->parameter_string_vector.push_back(&this->random_phase_amplitude_string);
				this->default_parameter_number_vector.push_back(3);
				if (optimiser->verb > 0 && optimiser->node->isMaster())
				{
					std::cout <<"\033[0;31mThe do cyclic random phase is now " << do_cyclic_random_phase << "The do cyclic amplitude is now " <<  do_cyclic_amplitude << "\033[0m\n";
				}
				this->do_cycle_vector.push_back(do_cyclic_random_phase);
				this->do_cycle_vector.push_back(do_cyclic_amplitude);
			}
			this->do_good_random_phase = optimiser->parser.checkOption("--random_phase_good_refs","This is for turning on the phase randomization procedure of the good classes.");
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
				this->parameter_string_vector.push_back(&this->random_phase_good_string);
				this->default_parameter_number_vector.push_back(4);
				this->random_phase_good_amplitude_string = optimiser->parser.getOption("--random_amplitude_goodrefs", "This is for specifying the amplitude for phase randomization in units of 2pi for the good references, please refer to the documentation of the --random_amplitude_other_refs option. Default:1", "1");
				if (this->random_phase_good_amplitude_string.find(":") == std::string::npos && this->random_phase_good_amplitude_string.find(",") == std::string::npos)
				{
					this->do_cyclic_good_amplitude = false;
				}
				else
				{
					this->do_cyclic_good_amplitude = true;
				}
				this->parameter_string_vector.push_back(&this->random_phase_good_amplitude_string);
				this->default_parameter_number_vector.push_back(3);
				this->do_cycle_vector.push_back(do_cyclic_good_random_phase);
				this->do_cycle_vector.push_back(do_cyclic_good_amplitude);

			}
			if (optimiser->verb > 0 && optimiser->node->isMaster())
			{
				std::cout <<"\033[0;31mparse initial for random phase set up complete! \033[0m\n";
				std::cout << "\033[0;31mThe size of the string vector is " << parameter_string_vector.size() << " " << *parameter_string_vector[1] << " " <<default_parameter_number_vector[1] << "\033[0m\n";
			}
			MPI_Barrier(MPI_COMM_WORLD);
		}


		//The private members of the class are the parameter storing vectors that can only be accessed by the setup functions that is a public member of the class
	private:
		//Used private derivation to avoid name conflicts, need to make a few public public members of MlOptimiserMpi private in this class. 
		/*using MlOptimiserMpi::mymodel; 
		  using MlOptimiserMpi::iter; 
		  using MlOptimiserMpi::node;*/
		//self defined variables and functions.
		bool do_random_phase ;
		bool do_good_random_phase ;
		bool random_phase_amplitude_switch ; 
		bool random_phase_good_amplitude_switch ;
		bool do_cyclic_random_phase ;
		bool do_cyclic_amplitude ;
		bool do_cyclic_good_random_phase ;
		bool do_cyclic_good_amplitude ;
		bool do_cool_down ;
		bool do_good_cool_down ;
		bool do_particle_score_random_phase ; 
		bool do_bfactor_refinement_random_phase ;
		bool do_particle_movie_refinement_random_phase ;
		int random_phase_index ;
		int random_phase_upper_index ;
		RFLOAT random_phase_amplitude ;
		std::vector<bool> do_random_phase_iter ;
		std::vector<bool> do_good_random_phase_iter ;
		std::vector<std::string*> parameter_string_vector;
		std::vector<int> default_parameter_number_vector;
		std::vector<bool> do_cycle_vector;
		std::string random_phase_string ;
		std::string random_phase_amplitude_string = "" ;
		std::string random_phase_good_string ;
		std::string random_phase_good_amplitude_string ;
		std::vector<RFLOAT> random_phase_res_iter;
		std::vector<RFLOAT> random_phase_res_upper_iter;
		std::vector<RFLOAT> random_phase_good_res_iter;
		std::vector<RFLOAT> random_phase_good_res_upper_iter;
		std::vector<RFLOAT> random_phase_amplitude_iter;
		std::vector<RFLOAT> random_phase_good_amplitude_iter;


};
#endif
