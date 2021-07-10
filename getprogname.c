/* Place this in getprogname.c as needed. It occurs in many programs. */

extern char** __Argv;

char const* last_component (const char*);

char const* getprogname (void)
{
    return last_component (__Argv [0]);
}
