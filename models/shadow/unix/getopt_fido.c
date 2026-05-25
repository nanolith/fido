/**
 * \file models/shadow/unix/getopt_fido.c
 *
 * \brief A getopt shadow method for exercising fido's command-line options
 * parser.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/model_assert.h>
#include <unistd.h>

int nondet_loop();
int nondet_int();

int loop_count = 2;
char *optarg = NULL;
int optind = 0;
int optopt = 0;
int opterr = 0;
int optreset = 0;
char arg[8];

char nondet_ch();

char* choose_arg()
{
    __CPROVER_havoc_object(arg);
    arg[sizeof(arg)-1] = 0;
    return arg;
}

int choose_result()
{
    optarg = NULL;

    char ch = nondet_ch();
    switch (ch)
    {
        case 'C':
            optarg = choose_arg();
            break;

        case 'n':
            break;

        default:
            MODEL_ASSUME(ch == '?' || ch == ':');
            break;
    }

    return ch;
}

int choose_optind(int argc)
{
    int val = nondet_int();
    MODEL_ASSUME(val >= 0 && val <= argc);

    return val;
}

int
getopt(int argc, char * const argv[], const char *optstring)
{
    int count = nondet_loop();
    MODEL_ASSUME(count > 0);

    optind = choose_optind(argc);

    if (count > loop_count)
    {
        loop_count = 0;
        return -1;
    }
    else
    {
        loop_count -= 1;
    }

    return choose_result();
}
