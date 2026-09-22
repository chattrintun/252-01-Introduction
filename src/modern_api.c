#include "api_bridge_lab.h"

#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int modern_parse_year(const char *record, int *out_year) {
    /* TODO(student): strict parsing with strtol
       Requirements:
       - find ':'
       - fail if ':' missing
       - fail if no digits after ':'
       - fail if extra characters remain after number
       - fail on overflow/underflow via errno
       - on success, set *out_year and return 0
       - on failure, return -1
    */
    const char *colon = strchr(record, ':'); // find colon
    if (colon == NULL) {
        return -1;
    }

    char *endptr;
    errno = 0;
    long value = strtol(colon + 1, &endptr, 10); // start at colon +1 till it hits character then endptr( endpointer is pointing at char). and value will be 18 EX 1815 it will point at \0 but if 18x5 it will point at x

    if (colon + 1 == endptr) // no digits after :
    {
        return -1;
    }
    else if (*endptr != '\0')// ends on something else thats not end of massage indicator
    {
        return -1;
    }
    if (errno == ERANGE) // when its out of range, strtol autimatically sets errno to ERANGE, to indicate that its out of range that why we set it at 0 in the beginning
    {
        return -1;
    }
    else
    {
        *out_year = (int)value;
        return 0;
    }
    
}

int modern_make_slug(const char *name, char *out, size_t out_size) {
    size_t i;

    /* TODO(student): safe slug conversion
       - same transformation as legacy_make_slug
       - must not write past out_size
       - always NUL-terminate on success
       - return 0 on success, -1 if output buffer too small
    */
    if (out_size == 0) {
        return -1;
    }

    for (i = 0; name[i] != '\0' && i + 1 < out_size; i++) {
        if (name[i] == ' ')
        {
            out[i] = '_';
        }
        else if (isalpha(name[i]))
        {
            out[i] = tolower(name[i]);
        }
        else out[i] = name[i];
    }

    if (name[i] != '\0') {
        return -1;
    }

    out[i] = '\0';
    return 0;
}
