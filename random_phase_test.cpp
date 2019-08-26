#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include "src/strings.h"
#include "src/macros.h"
#include "src/error.h"
#include <strstream>
#define RANDOM_PHASE_DEV_EXIT_CODE -1
#define RANDOM_PHASE_RES 40
#define GOOD_RANDOM_PHASE_RES 10
#define RANDOM_PHASE_RES_UPPER 0.1
#define GOOD_RANDOM_PHASE_RES_UPPER 5
#define COOL_DOWN_CYCLE 3
#define COOL_DOWN_ITERATION 3
//#define TWO_PI  
#define DATA_TYPE_ERROR -10
#define EMPTY_ARG_ERROR -11
RelionError::RelionError(const std::string &what, const std::string &fileArg, const long lineArg)
{
	msg = "ERROR: \n" + what;
	file= fileArg;
	line=lineArg;
}

std::string integerToString(int I, int _width, char fill_with)
{
	char aux[15];

	// Check width
	int width = _width;
	int Iaux = ABS(I);

	if (SGN(I) < 0)
		width--;

	if (width == 0)
		do
		{
			Iaux /= 10;
			width++;
		}
		while (Iaux != 0);

	// Fill the number with the fill character
	for (int i = 0; i < width; i++)
		aux[i] = fill_with;

	// Start filling the array
	aux[width--] = '\0';
	Iaux = ABS(I);
	do
	{
		int digit = Iaux % 10;
		Iaux /= 10;
		aux[width--] = '0' + digit;
	}
	while (Iaux != 0);

	if (SGN(I) < 0)
		return static_cast< std::string >("-")  + aux;
	else
		return static_cast< std::string >(aux);
}

int splitString(const std::string& input,
		const std::string& delimiter,
		std::vector< std::string >& results,
		bool includeEmpties)
{
	results.clear();
	int iPos = 0;
	int newPos = -1;
	int sizeS2 = static_cast< int >(delimiter.size());
	int isize = static_cast< int >(input.size());

	if (isize == 0 || sizeS2 == 0)
		return 0;

	std::vector< int > positions;
	newPos = input.find(delimiter, 0);

	if (newPos < 0)
		return 0;

	int numFound = 0;
	while (newPos >= iPos)
	{
		numFound++;
		positions.push_back(newPos);
		iPos = newPos;
		newPos = input.find(delimiter, iPos + sizeS2);
	}

	if (numFound == 0)
		return 0;

	for (int i = 0; i <= static_cast< int >(positions.size()); i++)
	{
		std::string s("");
		if (i == 0)
			s = input.substr(i, positions[i]);
		int offset = positions[i-1] + sizeS2;
		if (offset < isize)
		{
			if (i == positions.size())
				s = input.substr(offset);
			else if (i > 0)
				s = input.substr(positions[i-1] + sizeS2,
						positions[i] - positions[i-1] - sizeS2);
		}
		if (includeEmpties || s.size() > 0)
			results.push_back(s);
	}
	return numFound;
}

int textToInteger(const char* str, int _errno, std::string errmsg)
{
	int retval;
	int ok;

	if (str == NULL)
		REPORT_ERROR( errmsg);

	ok = sscanf(str, "%d", &retval);

	if (ok)
		return retval;

	REPORT_ERROR( errmsg);

	return 0;
}

double textToDouble(const char* str, int _errno, std::string errmsg)
{
	RFLOAT retval;
	int ok;

	if (str == NULL)
		REPORT_ERROR( errmsg);

#ifdef RELION_SINGLE_PRECISION
	ok = sscanf(str, "%f", &retval);
#else
	ok = sscanf(str, "%lf", &retval);
#endif

	if (ok)
		return retval;

	REPORT_ERROR( errmsg);

	return 0;
}

std::string floatToString(float F, int _width, int _prec)
{
#if GCC_VERSION < 30300
    char aux[15];
    std::ostrstream outs(aux, sizeof(aux));
#else
    std::ostringstream outs;
#endif

    outs.fill(' ');

    if (_width != 0)
        outs.width(_width);

    if (_prec == 0)
        _prec = bestPrecision(F, _width);

    if (_prec == -1 && _width > 7)
    {
        outs.precision(_width - 7);
        outs.setf(std::ios::scientific);
    }
    else
        outs.precision(_prec);

#if GCC_VERSION < 30301
    outs << F << std::ends;
#else
    outs << F;
#endif

#if GCC_VERSION < 30300
    return std::string(aux);
#else
    std::string retval = outs.str();
    int i = retval.find('\0');

    if (i != -1)
        retval = retval.substr(0, i);

    return retval;
#endif
}

int bestPrecision(float F, int _width)
{
    // If it is 0
    if (F == 0)
        return 1;

    // Otherwise
    int exp = FLOOR(log10(ABS(F)));
    int advised_prec;

    if (exp >= 0)
        if (exp > _width - 3)
            advised_prec = -1;
        else
            advised_prec = _width - 2;
    else
    {
        advised_prec = _width + (exp - 1) - 3;
        if (advised_prec <= 0)
            advised_prec = -1;
    }

    if (advised_prec < 0)
        advised_prec = -1; // Choose exponential format

    return advised_prec;
}

template<typename T> void set_parameter(const std::string &parameter_string, std::vector<T> &parameter_iter ,  const std::string &data_type, const std::vector<std::string> &id_map_vector)
{
	//std::string mystrings[3] = {"RFLOAT","int","bool"};
	std::vector<std::string> support_types = {"RFLOAT", "int", "bool"};// (mystrings, mystrings + sizeof(mystrings) / sizeof(std::string));
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
	it = std::find(support_types.begin(), support_types.end(), data_type);
	//debug only
	/*std::string temp_data_type = "bool";
	it = std::find(support_types.begin(), support_types.end(), temp_data_type);
	std::cout << "\033[0;31m" << "debug only:" << std::distance(support_types.begin(), it) << "\033[0m\n";
	std::cout << "\033[0;31m" << "debug only:" << *(it) << "\033[0m\n";
	exit(1);*/
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
					std::cout << "\033[0;31mThe data_specify_id is " << data_type_specify_id << "\033[0m\n" ;
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
					std::cout << "The id_map_vector has less elements then parameter string, please check your specification!" << std::endl;
			}
			for (int k = 0; k < (iteration * cycle); k++)
			{
				parameter_iter.push_back(push_in_value);
			}
		}
	}
}

class test_random_phase{
	private:
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
		std::vector<std::string> parameter_string_vector;
		std::vector<int> default_parameter_number_vector;
		std::vector<bool> do_cycle_vector;
		std::string random_phase_string ;
		std::string random_phase_amplitude_string ;
		std::string random_phase_good_string ;
		std::string random_phase_good_amplitude_string ;
		std::vector<RFLOAT> random_phase_res_iter;
		std::vector<RFLOAT> random_phase_res_upper_iter;
		std::vector<RFLOAT> random_phase_good_res_iter;
		std::vector<RFLOAT> random_phase_good_res_upper_iter;
		std::vector<RFLOAT> random_phase_amplitude_iter;
		std::vector<RFLOAT> random_phase_good_amplitude_iter; 
	public:
		void set_bool(bool bo1, bool bo2)
		{
			this->do_random_phase = bo1;
			this->do_good_random_phase = bo2;
		}
		template<typename T> void print_iter_info(T &optimiser)
		{
			for (int i = 1; i <= optimiser->nr_iter; i ++)
			{
				std::cout << "\033[0;31mThe lower res for iteration" << i << " is " << this->random_phase_res_iter[i - 1] <<"\n";
				std::cout << "The upper res for iteration" << i << " is " << this->random_phase_res_upper_iter[i - 1] <<"\n";
				std::cout << "The bad amplitude for iteration" << i << " is " << this->random_phase_amplitude_iter[i - 1] <<"\033[0m\n";
				std::cout << "The do random phase boolean for iteration" << i << " is " << this->do_random_phase_iter[i - 1] <<"\033[0m\n";
				if (this->do_good_random_phase)
				{
					std::cout << "\033[0;32mThe lower res of good reference for iteration" << i << " is " << this->random_phase_good_res_iter[i - 1] <<"\n";
					std::cout << "The lower res of good reference for iteration" << i << " is " << this->random_phase_good_res_upper_iter[i - 1] <<"\n";
					std::cout << "The good amplitude for iteration" << i << " is " << this->random_phase_good_amplitude_iter[i - 1] <<"\033[0m\n";
					std::cout << "The do good random phase boolean for iteration" << i << " is " << this->do_good_random_phase_iter[i - 1] <<"\033[0m\n";
				}
				else
				{
					std::cout << "\033[0;32mNo good reference randomizing, skipping info for good random phase\033[0m\n";
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
			int cycle;
			std::vector<std::string> lower_id_map_vector = {"value", "iteration", "cycle"};
			//the lower res and the upper limit and also the amplitude along with the do_random_phase boolean vector can share a common id_map_vector.
			//std::vector<std::string> upper_id_map_vector;
			std::string lower_string;
			std::string upper_string;
			std::string bool_string;
			splitString(random_phase_string, ":", colon_split, true);
			if (colon_split.empty())
			{
				colon_split.push_back(random_phase_string);
			}
			for (int i = 1; i <= colon_split.size(); i++)
			{
				splitString(colon_split[i -1], ",", comma_split, true);
				if (comma_split.empty())
				{
					std::cout <<"\033[0;31mThe check_nr_iter function should be called to complete the given parameter to the default form, please check your code!\033[0m\n";
				}
				else
				{
					std::cout << "\033[0;31mCongratulations! You have reached line 406" << "\033[0m\n";
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
			std::cout << "\033[0;31mCongratulations! You have reached line 444" << upper_string << lower_string << "The boolean string is: " << bool_string << "\033[0m\n";
			set_parameter(lower_string, this->random_phase_res_iter, "RFLOAT", lower_id_map_vector);
			set_parameter(upper_string, this->random_phase_res_upper_iter, "RFLOAT", lower_id_map_vector);
			set_parameter(bool_string, this->do_random_phase_iter, "bool", lower_id_map_vector);
			std::cout << "\033[0;31mCongratulations! You have solved the initialization problem!\033[0m\n"; 
			if (random_phase_amplitude_string != "")
			{
				set_parameter(random_phase_amplitude_string, this->random_phase_amplitude_iter, "RFLOAT", lower_id_map_vector);
			}
			else
			{
				std::cout << "The phase_amplitude is not provided, using the default amplitude for random phase!" << std::endl;
				//exit(EMPTY_ARG_ERROR);
				std::string temp_string = "";
				temp_string += "1,";
				temp_string += "1,";
				temp_string += integerToString(optimiser->nr_iter, (FLOOR(log10(ABS(optimiser->nr_iter))) + 1), 0);
				set_parameter(temp_string, this->random_phase_amplitude_iter, "RFLOAT", lower_id_map_vector);
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
						bool_string += "true,1,1";
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
				set_parameter(lower_string, this->random_phase_good_res_iter, "RFLOAT", lower_id_map_vector);
				set_parameter(upper_string, this->random_phase_good_res_upper_iter, "RFLOAT", lower_id_map_vector);
				set_parameter(bool_string, this->do_good_random_phase_iter, "bool", lower_id_map_vector);
				if (random_phase_good_amplitude_string != "")
				{
					set_parameter(random_phase_amplitude_string, this->random_phase_good_amplitude_iter, "RFLOAT", lower_id_map_vector);
				}
				else
				{
					std::cout << "The phase_amplitude is not provided, using the default amplitude for random phase!" << std::endl;
					//exit(EMPTY_ARG_ERROR);
					std::string temp_string = "";
					temp_string += "1,";
					temp_string += "1,";
					temp_string += integerToString(optimiser->nr_iter, (FLOOR(log10(ABS(optimiser->nr_iter))) + 1), 0);
					set_parameter(temp_string, this->random_phase_good_amplitude_iter, "RFLOAT", lower_id_map_vector);
				}
			}
		}
};
std::string vector_to_string(std::vector<std::string> &parameter_vector, std::string delimiter)
{
	std::string return_string = "";
	if (parameter_vector.size() == 0)
	{
		std::cout << "vector empty!"  << std::endl;
		exit(EMPTY_ARG_ERROR);
	}
	for (int i = 1; i <= parameter_vector.size(); i++)
	{
		return_string += parameter_vector[i - 1];
		if (i != parameter_vector.size())
		{
			return_string += delimiter;
		}
	}
	std::cout << return_string << std::endl;
	return return_string;
}

template<typename T> void check_nr_iter(T &optimiser, std::vector<std::string> &string_vector, std::vector<int> &default_parameter_number_vector, std::vector<bool> do_cycle_vector, bool do_auto_completion)
{
	if (default_parameter_number_vector.size() != string_vector.size())
	{
		std::cout << "The default parameter number vector has a different size then the parameter string vector! please check your specification in the parseInitial function" << std::endl;
		exit(-1);
	}
	int total_iter = 0;
	int temp_iter = optimiser->get_iter();
	int cool_down_cycle = 0;
	int cool_down_iteration = 0;
	for (int i = 1; i <= string_vector.size(); i++)
	{
		total_iter = 0;
		temp_iter = optimiser->get_iter();
		std::vector<std::string> colon_split;
		std::vector<std::string> comma_split;
		splitString(string_vector[i - 1], ":", colon_split, true);
		std::cout << colon_split.size() << std::endl;
		if (colon_split.empty())
		{
			colon_split.push_back(string_vector[i - 1]);
		}
		for (int j = 1; j <= colon_split.size(); j++)
		{
			std::cout << "The current string colon split element is " << colon_split[j - 1] << std::endl;
			splitString(colon_split[j - 1], ",", comma_split, true);
			if (comma_split.empty())
			{
				comma_split.push_back(colon_split[j - 1]);
			}
			if ((default_parameter_number_vector[i - 1] - comma_split.size()) > 1 && (do_cycle_vector[i - 1]) && (!do_auto_completion))
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
				comma_split.push_back(integerToString(cool_down_iteration, (FLOOR(log10(ABS(cool_down_iteration))) + 1), 0));
				comma_split.push_back(integerToString(cool_down_cycle, (FLOOR(log10(ABS(cool_down_cycle))) + 1), 0));
				colon_split[j - 1] = vector_to_string(comma_split, ",");
			} 
			else if ((default_parameter_number_vector[i - 1] - comma_split.size()) == 1 && (do_cycle_vector[i - 1]) && (!do_auto_completion))
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
						std::cout <<"now doing autocompletion with "<<cool_down_iteration<<" "<<cool_down_cycle<<"\n";
						while (temp_iter > (cool_down_iteration * cool_down_cycle))
						{
							cool_down_cycle += 1;
						}
						*(comma_split.end() - 1) = integerToString(cool_down_cycle, (FLOOR(log10(ABS(cool_down_cycle))) + 1), 0);
					}
					colon_split[j - 1] = vector_to_string(comma_split, ",");
				}
				else
				{
					std::cout << "Using the last parameter as the cool_down_cycle, using the second last parameter as cool_down_iteration." << std::endl;
				}
			}
			else
			{
				cool_down_iteration = 1;
				cool_down_cycle = optimiser->get_iter();
				comma_split.push_back(floatToString(RANDOM_PHASE_RES_UPPER, 2, 1));
				comma_split.push_back(integerToString(cool_down_iteration, (FLOOR(log10(ABS(cool_down_iteration))) + 1), 0));
				comma_split.push_back(integerToString(cool_down_cycle, (FLOOR(log10(ABS(cool_down_cycle))) + 1), 0));
				colon_split[j - 1] = vector_to_string(comma_split, ",");
			}
			//reassign value to default parameter number vector. This way, all colon separated terms will be completed to the maximum number of comma splitted terms.
			default_parameter_number_vector[j - 1] = comma_split.size();
			temp_iter -= cool_down_cycle * cool_down_iteration;
			total_iter += cool_down_cycle * cool_down_iteration;
		}
		if (total_iter > optimiser->get_iter())
		{
			optimiser->set_iter(total_iter);
		}
		std::cout << "The total number of iteration in this function call is "<< total_iter  << std::endl;
		std::cout << "The number of iteration in this function call is "<< optimiser->get_iter() << std::endl;
		string_vector[i - 1] = vector_to_string(colon_split, ":");
		std::cout << "The "<< (i - 1) << "th" << " string is now:" << string_vector[i - 1] << std::endl;
	}
}

class opt_test
{
	/*private :
		int nr_iter;*/
	public :
		int nr_iter;
		int get_iter()
		{
			return this->nr_iter;
		}
		void set_iter(int iter)
		{
			this->nr_iter = iter;
		}
};

int main()
{
	std::vector<RFLOAT> test_int_vector = {5,4,3,2,1};
	std::vector<std::string> id_map_vector = {"value", "value", "iteration", "cycle"};
	std::string test_string[3] = {"40", "40,1,3,3", "30,4,3,3"};
	std::vector<std::string> test_string_vector(test_string, test_string + sizeof(test_string) / sizeof(std::string)); 
	int test_int[3] = {4,4,4};
	std::vector<int> test_default_number_vector(test_int, test_int + sizeof(test_int) / sizeof(int));
	bool test_bool[3] = {false,true,true};
	std::vector<bool> test_bool_vector(test_bool, test_bool + sizeof(test_bool) / sizeof(bool));
	opt_test temp_optimiser;
	opt_test* test_optimiser = &temp_optimiser;
	test_optimiser->set_iter(5);
	check_nr_iter(test_optimiser, test_string_vector, test_default_number_vector, test_bool_vector, false);
	std::cout << "After the first function call, the number of iteration has been set to "<< test_optimiser->get_iter() << " for the test optimiser object." << std::endl;
	check_nr_iter(test_optimiser, test_string_vector, test_default_number_vector, test_bool_vector, true);
	std::cout << test_optimiser->get_iter()  << std::endl;
	for (int i = 1; i <= test_string_vector.size(); i ++)
	{
		std::cout << test_string_vector[i - 1] << std::endl;
	}
	std::cout << test_optimiser->get_iter() << std::endl;
	set_parameter(test_string_vector[0], test_int_vector, "RFLOAT", id_map_vector);
	std::cout << "after the set parameter function call, the size of the vector is now" << test_int_vector.size() << ". The values stored in it are as shown below:\n";
	for (int i = 1; i <= test_int_vector.size(); i ++)
	{
		std::cout<< test_int_vector[i - 1] << "\n";
	}
	test_random_phase  random_test;
        random_test.set_bool(true, false);
	random_test.set_parameter_for_randomphase(test_optimiser, test_string_vector[2]);
	random_test.print_iter_info(test_optimiser);
}
