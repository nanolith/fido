/**
 * \file options/fido_options_parse.c
 *
 * \brief Parse command-line options and create an options instance.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fido/options.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * \brief Parse command-line arguments to produce a fido options record.
 *
 * \param opts          Pointer to the options record pointer to populate with
 *                      the created options record on success.
 * \param argc          The argument count.
 * \param argv          The argument vector.
 *
 * \returns 0 on success and non-zero on failure.
 */
int FN_DECL_MUST_CHECK
fido_options_parse(fido_options** opts, int argc, const char** argv)
{
    int retval;
    bool dry_run = false;
    char* config_file_override = NULL;
    char* binary_name = NULL;
    int ch;

    MODEL_CONTRACT_CHECK_PRECONDITIONS(fido_options_parse, opts, argc, argv);

    /* reset opt variables so we can test this function multiple times. */
    opterr = optind = optreset = 1;

    while ((ch = getopt(argc, (char* const*)argv, "nC:")) != -1)
    {
        switch (ch)
        {
            case 'n':
                dry_run = true;
                break;

            case 'C':
                if (NULL != config_file_override)
                {
                    fprintf(stderr, "error: -C provided multiple times.\n");
                    *opts = NULL;
                    retval = FIDO_ERROR_INVALID_OPTION;
                    goto done;
                }

                config_file_override = strdup(optarg);
                if (NULL == config_file_override)
                {
                    fprintf(stderr, "Out of memory.\n");
                    *opts = NULL;
                    retval = FIDO_ERROR_OUT_OF_MEMORY;
                    goto done;
                }
                break;

            default:
                *opts = NULL;
                retval = FIDO_ERROR_INVALID_OPTION;
                goto done;
        }
    }

    /* verify that we have a command to run. */
    argc -= optind;
    argv += optind;
    if (argc < 1)
    {
        fprintf(stderr, "Missing command.\n");
        *opts = NULL;
        retval = FIDO_ERROR_OPTION_MISSING_COMMAND;
        goto done;
    }

    /* resolve the binary name. */
    binary_name = realpath(argv[0], NULL);
    if (NULL == binary_name)
    {
        fprintf(stderr, "error: Could not resolve binary name %s.\n", argv[0]);
        retval = FIDO_ERROR_OPTION_BINARY_RESOLVE;
        goto done;
    }

    /* Create the options instance. */
    *opts = (fido_options*)malloc(sizeof(fido_options));
    if (NULL == (*opts))
    {
        *opts = NULL;
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto done;
    }

    /* initialize options. */
    memset(*opts, 0, sizeof(fido_options));
    (*opts)->dry_run = dry_run;
    (*opts)->config_file_override = config_file_override;
    (*opts)->binary_name = binary_name;
    (*opts)->arguments_count = argc - 1;
    if ((*opts)->arguments_count > 0)
    {
        (*opts)->arguments = argv + 1;
    }
    else
    {
        (*opts)->arguments = NULL;
    }
    config_file_override = NULL;
    binary_name = NULL;

    /* success. */
    retval = 0;
    goto done;

done:
    if (NULL != binary_name)
    {
        free(binary_name);
    }

    if (NULL != config_file_override)
    {
        free(config_file_override);
    }

    if (0 != retval)
    {
        *opts = NULL;
    }

    MODEL_CONTRACT_CHECK_POSTCONDITIONS(
        fido_options_parse, retval, opts, argc, argv);

    return retval;
}
