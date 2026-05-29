#pragma once

#define MAX_SHADOW_DESCRIPTORS 2

#define SHADOW_FILE_DESCRIPTOR_OPEN     1

typedef struct shadow_file_descriptor shadow_file_descriptor
{
    int mode;
};

extern shadow_file_descriptor* shadow_descriptors[MAX_SHADOW_DESCRIPTORS];

void unix_init();
