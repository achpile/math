/***********************************************************************
     * File       : misc_vect.cpp
     * Created    : Feb 23, 2016
     * Copyright  : (C) 2016 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "headers.hpp"



/***********************************************************************
     * getDirection

***********************************************************************/
sf::Vector2i getDirection(al::Direction direction) {
	switch (direction) {
		case al::dUp    : return sf::Vector2i( 0, -1);
		case al::dDown  : return sf::Vector2i( 0,  1);
		case al::dLeft  : return sf::Vector2i(-1,  0);
		case al::dRight : return sf::Vector2i( 1,  0);
		default         : return sf::Vector2i( 0,  0);
	}
}
