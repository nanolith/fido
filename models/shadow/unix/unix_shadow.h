#pragma once

#define MAX_SHADOW_DESCRIPTORS 2

typedef struct shadow_file_descriptor shadow_file_descriptor
{
    int mode;
};

extern shadow_file_descriptor* shadow_descriptors[MAX_SHADOW_DESCRIPTORS];
