	template<typename T> void check_nr_iter(T &optimiser, std::vector<std::string> &string_vector, std::vector<int> &default_parameter_number_vector, std::vector<bool> do_cycle_vector, bool do_auto_completion)
	{
		if (default_parameter_number_vector.size() != string_vector.size())
		{
			std::cout << "The default parameter number vector has a different size then the parameter string vector! please check your specification in the parseInitial function" << std::endl;
			exit(-1);
		}
		int total_iter = 0;
		int temp_iter = optimiser->nr_iter;
		int cool_down_cycle = 0;
		int cool_down_iteration = 0;
		for (int i = 1; i <= string_vector.size(); i++)
		{
			// reset the temp_iter to 0
			std::cout << "The current string is " << string_vector[i - 1] << std::endl;
			total_iter = 0;
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
				if ((default_parameter_number_vector[i - 1] - comma_split.size()) > 1 && (do_cycle_vector[i - 1]))
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
				else if ((default_parameter_number_vector[i - 1] - comma_split.size()) == 1 && (do_cycle_vector[i - 1]))
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
					cool_down_cycle = optimiser->nr_iter;
					comma_split.push_back(integerToString(cool_down_iteration, (FLOOR(log10(ABS(cool_down_iteration))) + 1), 0));
					comma_split.push_back(integerToString(cool_down_cycle, (FLOOR(log10(ABS(cool_down_cycle))) + 1), 0));
					colon_split[j - 1] = vector_to_string(comma_split, ",");
				}
				//reassign value to default parameter number vector. This way, all colon separated terms will be completed to the maximum number of comma splitted terms.
				default_parameter_number_vector[j - 1] = comma_split.size();
				temp_iter -= cool_down_cycle * cool_down_iteration;
				total_iter += cool_down_cycle * cool_down_iteration;
			}
			if (total_iter > optimiser->nr_iter)
			{
				optimiser->nr_iter = total_iter;
			}
			string_vector[i - 1] = vector_to_string(colon_split, ":");
		}
		std::cout << "string vector complete!" << std::endl;
	}
template<typename T> void set_parameter(const std::string &parameter_string, std::vector<T> &parameter_iter , const std::string &data_type, const std::vector<std::string> &id_map_vector)
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
	T push_in_value = parameter_iter[0];
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

