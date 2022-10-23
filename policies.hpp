#include <iostream>
#include <stdlib.h>
#include <string.h>

void FIFO(int nframes, char* traceName, char *debugOrQuiet);
void lru(const char* traceName , int frame_Num, std::string option);
void VMS(const char* traceName, int nframes, int p, char *debugOrQuiet);