
#include "calc.h"

//-----------------------------------------------------------------------------

calculator::calculator(void)
{
    FILE* calc_file = fopen("calc_example.txt", "rb");  //C
    if(calc_file == nullptr) {
        std::cout << "Please, create a \"calc_example.txt\"\n";
        exit(); 
    }

    num_symb = number_of_symbols(calc_file);

    counter = new char[num_symb + 1];
    assert(counter);

    fread(counter, sizeof(char), num_symb, calc_file);

    error = 0;

    fclose(calc_file);                                  //C
}

//-----------------------------------------------------------------------------

calculator::~calculator(void)
{
    counter -= num_symb;
    delete[](counter);
}

//-----------------------------------------------------------------------------

double calculator::get_e(void)
{
    assert(counter);

    double value = 0;
    char   sign  = 0;

    isspace_counter();

    if(isdigit(*counter) || *counter == '-' || *counter == '+')
        if(*counter == '-')
        {
            counter++;

            isspace_counter();

            value = -get_t();
        }
        else if(*counter == '+')
        {
            counter++;

            isspace_counter();

            value = get_t();
        }
        else
            value = get_t();
    else
        std::cout << "Something wrong in part 1 \"get_e\"" <<
                     *counter << "\n";

    while(*counter == '+' || *counter == '-')
    {
        isspace_counter();

        if(*counter == '+')
            sign = PLUS;
        else if(*counter == '-')
            sign = MINUS;
        else
            std::cout << "Something wrong in part 2 \"get_e\"" <<
                         *counter << "\n";

        counter++;

        isspace_counter();
        value += sign * get_t();
        isspace_counter();
    }

    return value;
}

//-----------------------------------------------------------------------------

double calculator::get_t(void)
{
    assert(counter);

    double value = 0;
    char   sign  = 0;

    isspace_counter();
    value = get_w();
    isspace_counter();

    while(*counter == '*' || *counter == '/')
    {
        if(*counter == '*')
            sign = MUL;
        else if(*counter == '/')
            sign = DIV;
        else
            std::cout << "Something wrong in \"get_t\"" <<
                         *counter << "\n";

        counter++;

        isspace_counter();
        if(sign == 1)
            value *= get_w();
        else
            value /= get_w();
        isspace_counter();
    }

    return value;
}

//-----------------------------------------------------------------------------

double calculator::get_w(void)
{
    assert(counter);

    double value = 0;

    isspace_counter();
    value = get_p();
    isspace_counter();

    while(*counter == '^')
    {
        counter++;

        isspace_counter();

        double degree    = get_w();
        double tmp_value = value;

        for(double indx = 0; indx < degree - 1; indx++)
            value *= tmp_value;

        isspace_counter();
    }

    return value;

}

//-----------------------------------------------------------------------------

double calculator::get_p(void)
{
    assert(counter);

    double value = 0;

    isspace_counter();

    if(*counter == '(')
    {
        counter++;

        value = get_e();

        if(*counter != ')')
            std::cout << "You forgot \")\"" << "\n";

        counter++;

    }
    else
        value = get_n();

    return value;
}

//-----------------------------------------------------------------------------

double calculator::get_n(void) {

    assert(counter);

    double value = 0;

    if(isdigit(*counter))
        value = atof(counter);
    else
        std::cout << "Something wrong in \"get_n\"" <<
                         *counter << "\n";

    while(isdigit(*counter) || *counter == '.')
        counter++;

    return value;
}

//-----------------------------------------------------------------------------

void calculator::print_console(void)
{
    std::cout << get_e() << "\n";
    system("pause");
}

//-----------------------------------------------------------------------------

inline void calculator::isspace_counter(void)
{
    while(isspace(*counter))
        counter++;
}

//-----------------------------------------------------------------------------

int number_of_symbols(FILE* source)
{
    assert(source);

    long int start_value = ftell(source);
    fseek(source, 0, SEEK_END);

	int num_symbols = ftell(source);
	fseek(source, start_value, SEEK_SET);

	return num_symbols;
}
