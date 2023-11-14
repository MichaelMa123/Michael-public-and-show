#include <iostream>
#include <climits>

#ifndef MARMOSET_TESTING
int main();
#endif
unsigned int add_checksum(unsigned int value_to_protect);
bool verify_checksum(unsigned protected_value);
void add_checksum(unsigned int value_series[],const std::size_t QTY_VALUES);
unsigned int find_value(unsigned int value_checksum[]);
unsigned int find_checksum(unsigned int protecting_value);
unsigned int remove_checksum( unsigned int protected_value );
void remove_checksum( unsigned int value_series[],const std::size_t QTY_VALUES );


void add_checksum(unsigned int value_series[],const std::size_t QTY_VALUES)
{
	for(int array_number{0};array_number<QTY_VALUES;array_number++)
	{
		if(value_series[array_number]<=99999999)
		{
		unsigned int protecting_value{value_series[array_number]*10};
		unsigned int value_checksum[9];
		for(int digits{1}; digits<=9; digits++)
		{
			int divide_by{1};
			for(int divide{2};divide<=digits;divide++)
			{
				divide_by=divide_by*10;

			}
			value_checksum[9-digits]=(protecting_value/ divide_by) % 10;
		}
		value_checksum[8]=find_checksum(protecting_value);
		value_series[array_number]=find_value(value_checksum);
		}
		else
		{
			value_series[array_number]=UINT_MAX;
		}
	}
}

unsigned int find_value(unsigned int value_checksum[])
{
	unsigned int final_value{0};
	for(unsigned int digits{0};digits<=8;digits++)
	{
		unsigned int multiply_by{1};
		for(int multiply{1};multiply<=digits;multiply++)
		{
			multiply_by*=10;
	
		}
		final_value=final_value+(value_checksum[8-digits]*multiply_by);
	}
	return final_value;
}

unsigned int find_checksum(unsigned int protecting_value)
{
	unsigned int value[9];
	unsigned int sum{0};
	for(int digits{2}; digits<=9; digits++)
	{
		int divide_by{1};
		for(int divide{2};divide<=digits;divide++)
		{
			divide_by=divide_by*10;

		}
		value[9-digits]=(protecting_value / divide_by) % 10;
		if((10-digits)%2==0)
		{
			unsigned int test_value[2];
			if(value[(9-digits)]*2>9)
			{
				unsigned doubled{value[9-digits]*2};
				for(int digits_double{1}; digits_double<=2; digits_double++)
        	    {
		            int divide_by2{1};
		            for(int divide2{2};divide2<=digits_double;divide2++)
		            {
			            divide_by2=divide_by2*10;
		            }
					test_value[2-digits_double]=(doubled/divide_by2)%10;
					//std::cout<<test_value[2-digits_double];


			    }
				//std::cout<<std::endl;
				value[(9-digits)]=test_value[0]+test_value[1];
				//applys the mutiplyed value to the slot 
			}
			else
			{
				value[(9-digits)]*=2;
			}
		}
		//std::cout<<value[9-digits]<<" "<<10-digits<<std::endl;
	}
	//extract each digits from the number
	for(int adding{0};adding<=7;adding++ )
	{
		sum=sum+value[adding];

	}
	sum*=9;
	//std::cout<<sum<<std::endl;
	unsigned int checksum=sum%10;

	
	return checksum;

}


unsigned int add_checksum(unsigned int value_to_protect)
{
	if(value_to_protect<=99999999)
	{
	unsigned int protecting_value{value_to_protect*10};
	unsigned int value_checksum[9];
	for(int digits{1}; digits<=9; digits++)
	{
		int divide_by{1};
		for(int divide{2};divide<=digits;divide++)
		{
			divide_by=divide_by*10;

		}
		value_checksum[9-digits]=(protecting_value/ divide_by) % 10;
	}
	value_checksum[8]=find_checksum(protecting_value);
	unsigned int final_value=find_value(value_checksum);
	
	//std::cout<<final_value<<std::endl;
	return final_value;
	}
	else
	{
		return UINT_MAX;
	}

}

bool verify_checksum(unsigned int protected_value)
{
	unsigned int value_checksum[9];
	for(int digits{1}; digits<=9; digits++)
	{
		int divide_by{1};
		for(int divide{2};divide<=digits;divide++)
		{
			divide_by=divide_by*10;

		}
		value_checksum[9-digits]=(protected_value/ divide_by) % 10;
		//std::cout<<value_checksum[9-digits]<<std::endl;
	}
	unsigned int protecting_value{protected_value-value_checksum[8]};
	//std::cout<<find_checksum(protecting_value)<<std::endl;
	//std::cout<<value_checksum[8]<<std::endl;
	if(value_checksum[8]==find_checksum(protecting_value))
	{
		return true;
	}

	else
	{
		return false;
	}


}

unsigned int remove_checksum( unsigned int protected_value )
{
	if (verify_checksum(protected_value))
	{
		unsigned int final_value{0};
		unsigned int protecting_value{protected_value};
		unsigned int value_checksum{protecting_value%10};
	    final_value=(protected_value-value_checksum)/10;
		return final_value;
	}
	else   
	{
		return UINT_MAX;
	} 
}
void remove_checksum( unsigned int value_series[],const std::size_t QTY_VALUES )
{
	for(int array_number{0};array_number<QTY_VALUES;array_number++)
	{
		unsigned int protected_value{value_series[array_number]};
		if (verify_checksum(protected_value))
		{
			unsigned int final_value{0};
			unsigned int protecting_value{protected_value};
			unsigned int value_checksum{protecting_value%10};
	    	final_value=(protected_value-value_checksum)/10;
			value_series[array_number]=final_value;
		}
		else   
		{
			value_series[array_number]=UINT_MAX;
		} 


	}

}
#ifndef MARMOSET_TESTING
int main() {
	unsigned int value_to_protect{964133};
	unsigned int protected_value = add_checksum(value_to_protect);
	std::cout << "The value " << value_to_protect
		<< " with the checksum added is " << protected_value
		<< "." << std::endl;
	
	if (verify_checksum(protected_value))
	{
		std::cout << "The checksum is valid." << std::endl;
		std::cout<<remove_checksum(protected_value)<<std::endl;
	}

	else   {
		std::cout << "The checksum is invalid." << std::endl;
	} 
	const std::size_t QTY_VALUES {3};
	unsigned int value_series[QTY_VALUES] {52819416, 20209913, 20224012};
	
	add_checksum(value_series, QTY_VALUES);
	
	std::cout << "Series with checksums added: ";
	for (std::size_t series_index {0};	series_index < QTY_VALUES; series_index++)
	{
		std::cout << value_series[series_index] << " ";
	}

    std::cout << std::endl;
    return 0;
}
#endif