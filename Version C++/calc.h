#ifndef CALC_H_INCLUDED
#define CALC_H_INCLUDED

//-----------------------------------------------------------------------------

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>

//-----------------------------------------------------------------------------

class calculator
{
    char* counter = nullptr;
    int   num_symb;
    int   error;

    public:

    calculator(void);
    ~calculator(void);

    double get_e(void);
    double get_t(void);
    double get_w(void);
    double get_p(void);
    double get_n(void);

    void print_console(void);

    inline void isspace_counter(void);
};

//-----------------------------------------------------------------------------

enum SIGNS
{
    PLUS  =  1,
    MINUS = -1,
    MUL   =  1,
    DIV   = -1,
};

//-----------------------------------------------------------------------------

int number_of_symbols(FILE* source);

//-----------------------------------------------------------------------------

#endif // CALC_H_INCLUDED
