#ifndef POLICIES
#define POLICIES

#include <iostream>
#include <stdlib.h>
#include <string.h>

void FIFO(int nframes, char* traceName, char *debugOrQuiet); //previously debugOrQuiet was char *mode
void lru(const char* traceName , int frame_Num, std::string option);
void VMS(char* traceName, int nframes, int p, char *debugOrQuiet);

#endif // POLICIES