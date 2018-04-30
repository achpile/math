#ifndef __HEADERS
#define __HEADERS


#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sys/stat.h>
#include <stdio.h>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

#include "algo_graph.hpp"

#define deleteList(list)      for (; !(list).empty(); delete (list).back(), (list).pop_back())

#endif
