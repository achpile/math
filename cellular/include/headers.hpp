/***********************************************************************
     * File       : headers.hpp
     * Created    : Feb 16, 2015
     * Copyright  : (C) 2015 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __HEADERS
#define __HEADERS

#include <SFML/System.hpp>
#include <sys/stat.h>
#include <stdio.h>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
#include <math.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <ncurses.h>
#include <vector>


#include "enums.hpp"
#include "algo_map.hpp"
#include "misc_vect.hpp"

void gen(al::AlgoMap *map, sf::Vector2i size);

#endif
