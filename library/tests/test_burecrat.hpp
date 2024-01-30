#ifndef test_Bureaucrat_HPP
#define test_Bureaucrat_HPP




# include "../include/library.hpp"



void bureaucrat_form(void)
{
	std::cout << "===|Bureaucrat_Form|===" << std::endl;

	Bureaucrat a("Politic", 71) ;
	Bureaucrat b( a );
	Bureaucrat c;
	
	c = b;

	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << c << std::endl;
}

void test_grade_constructor(void)
{
	int i;
	
	std::cout << "===|Test: Grade Constructor|===" << std::endl;
	
	i = -10;
	while(i < 160)
	{
		std::cout << "=>Grade: " << i <<std::endl;
		try
		{
			Bureaucrat a("Politic", i);
		}
		catch(std::exception &e)
		{
			std::cout << e.what();
		}
		i ++;

		std::cout << "---" << std::endl;
	}	
}

void 	test_increment_and_decrement(void)
{
	std::cout << "===|Test: increment and decrement|===" << std::endl;
	
	Bureaucrat incre("Politic", 2);
	Bureaucrat decre("Registry" ,149);
	
	std::cout << "===| Increment |===" << std::endl;
	std::cout << incre.getGrade()  << " after increment ";
	incre.increment();
	std::cout << incre.getGrade() << std::endl;
	try
	{
		std::cout << incre.getGrade()  << " after increment \n";
		incre.increment();
		std::cout << incre.getGrade() << std::endl;
	}
	catch(std::exception &e)
	{
		std::cout << e.what();
	}

	std::cout << "===| Decrement|===" << std::endl;
	std::cout << decre.getGrade()  << " after decrement ";
	decre.decrement();
	std::cout << decre.getGrade() << std::endl;
	try
	{
		std::cout << decre.getGrade()  << " after decrement \n";
		decre.decrement();
		std::cout << decre.getGrade() << std::endl;
	}
	catch(std::exception &e)
	{
		std::cout << e.what();
	}

	
	std::cout << "=> Obsevation: Since grade 1 is the highest one and 150 the lowest" << std::endl;
}


void main_burecrat(void)
{
	//bureaucrat_form( );
	std::cout << "|====End===|" << std::endl;

	test_grade_constructor();
	std::cout << "|====End===|" << std::endl;

	test_increment_and_decrement();
	std::cout << "|====End===|" << std::endl;

}

#endif



