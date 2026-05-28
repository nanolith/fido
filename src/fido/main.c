/**
 * \file fido/main.c
 *
 * \brief Entry point for fido.
 *
 * \copyright 2026 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <fcntl.h>
#include <fido/config.h>
#include <fido/options.h>
#include <fido/policy.h>
#include <fido/user.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/capsicum.h>
#include <sys/stat.h>
#include <unistd.h>

/* forward decls. */
static int setup_process(void);
static int policy_check(const fido_user* user, const fido_options* opts);

/**
 * \brief Entry point for fido.
 *
 * \param argc          Argument count.
 * \param argv          Arguments.
 *
 * \returns 0 on success an non-zero on error.
 */
int main(int argc, char* argv[])
{
    int retval;
    fido_user* user = NULL;
    fido_options* opts = NULL;

    /* basic program setup. */
    retval = setup_process();
    if (0 != retval)
    {
        fprintf(stderr, "error: setup_process failed.\n");
        goto done;
    }

    /* get the user details. */
    retval = fido_user_create(&user);
    if (0 != retval)
    {
        fprintf(stderr, "error: could not get user details.\n");
        goto done;
    }

    /* parse the command line options. */
    retval = fido_options_parse(&opts, argc, (const char**)argv);
    if (0 != retval)
    {
        goto done;
    }

    /* should we perform a policy check? */
    if (opts->dry_run)
    {
        retval = policy_check(user, opts);
        goto done;
    }

    printf("Not yet implemented.\n");
    retval = 1;
    goto done;

done:
    if (NULL != opts)
    {
        fido_options_release(opts);
    }

    if (NULL != user)
    {
        fido_user_release(user);
    }

    if (0 != retval)
        return 1;
    else
        return 0;
}

/**
 * \brief Set up the process by closing other file handles and setting the
 * process name.
 *
 * \returns 0 on success and non-zero on error.
 */
static int setup_process(void)
{
    setprogname("fido");
    closefrom(STDERR_FILENO + 1);

    return 0;
}

/**
 * \brief Perform a policy check.
 *
 * \param user          The user for this policy check.
 * \param opts          The options for this policy check.
 *
 * \returns 0 on success and non-zero on error.
 */
static int policy_check(const fido_user* user, const fido_options* opts)
{
    int retval = 0, fd;
    bool checkperms = true;
    struct stat st;
    char* buffer = NULL;
    const char* as_user;
    const char* as_group;
    const fido_config_add_variable* env_head;
    fido_config* config;

    /* TODO - add support for config file override. */

    /* open the file for reading. */
    fd = open("/etc/fido.conf", O_RDONLY);
    if (fd < 0)
    {
        fprintf(stderr, "error: could not open config file.\n");
        retval = FIDO_ERROR_CONFIG_FILE_OPEN;
        goto done;
    }

    /* ensure that this file is writeable only by root. */
    retval = fstat(fd, &st);
    if (0 != retval)
    {
        fprintf(stderr, "error: could not stat config file.\n");
        retval = FIDO_ERROR_CONFIG_FILE_STAT;
        goto cleanup_fd;
    }

    if (checkperms)
    {
        if (0 != st.st_uid)
        {
            fprintf(stderr, "error: config file is not owned by root.\n");
            retval = FIDO_ERROR_CONFIG_FILE_PERMISSIONS;
            goto cleanup_fd;
        }

        if (0 != (st.st_mode & (S_IWGRP | S_IWOTH)))
        {
            fprintf(stderr, "error: config file is writeable by non-root.\n");
            retval = FIDO_ERROR_CONFIG_FILE_PERMISSIONS;
            goto cleanup_fd;
        }
    }

    /* calculate file size. */
    ssize_t filesize = st.st_size;
    if (filesize < 0)
    {
        fprintf(stderr, "error: invalid config file size.\n");
        retval = FIDO_ERROR_CONFIG_FILE_READ;
        goto cleanup_fd;
    }

    /* allocate a buffer large enough to hold the config. */
    buffer = (char*)malloc(filesize + 1);
    if (NULL == buffer)
    {
        retval = FIDO_ERROR_OUT_OF_MEMORY;
        goto cleanup_fd;
    }
    memset(buffer, 0, filesize+1);

    /* enter capsicum sandbox. */
    retval = cap_enter();
    if (0 != retval)
    {
        fprintf(stderr, "error: could not enter sandbox.\n");
        retval = FIDO_ERROR_SANDBOX;
        goto cleanup_buffer;
    }

    /* read config data. */
    ssize_t size = read(fd, buffer, filesize);
    if (size != filesize)
    {
        fprintf(stderr, "error: config file read failed.\n");
        retval = FIDO_ERROR_CONFIG_FILE_READ;
        goto cleanup_buffer;
    }
    buffer[filesize] = 0;

    /* parse config data. */
    retval = fido_config_parse(&config, buffer);
    if (0 != retval)
    {
        fprintf(stderr, "error: config file parse failed.\n");
        goto cleanup_buffer;
    }

    /* perform policy check. */
    retval =
        fido_policy_check(
            &as_user, &as_group, &env_head, config, opts, user);
    if (0 != retval)
    {
        printf("UNAUTH\n");
        goto cleanup_config;
    }

    /* We are authorized; share details. */
    printf("AUTH:%s:%s:", as_user, as_group);

    /* print any variables. */
    size_t var_count = 0;
    while (NULL != env_head)
    {
        printf("%s%s", (var_count ? "," : ""), env_head->name);
        env_head = env_head->next;
    }

    /* complete auth line. */
    printf("\n");

    /* success. */
    retval = 0;
    goto cleanup_config;

cleanup_config:
    fido_config_release(config);

cleanup_buffer:
    free(buffer);

cleanup_fd:
    close(fd);

done:
    return retval;
}
