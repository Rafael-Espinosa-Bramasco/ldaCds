#ifndef LDACDS_H
#define LDACDS_H

#include <stdbool.h>
#include <stddef.h>

#define LDACDS_CBF(fn,type,name) void (*_callback##fn)(ldaCds_##type *_##name)

typedef enum
{
    ldaCds_StatusNoErrorDetected = 0,
    ldaCds_StatusNodeParameterIsNUll,
    ldaCds_StatusStructureIsAlreadyEmpty,
    ldaCds_StatusStructureCantBeCleared,
    ldaCds_StatusIndexOutOfRange,
}ldaCds_StatusCode;

#endif /* LDACDS_H */
