/***************************************************************************
                           magellanicclouds.h  -  K Desktop Planetarium
                             -------------------
    begin                : 2005/07/08
    copyright            : (C) 2005 by Jason Harris
    email                : kstars@30doradus.org
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef MAGELLANICCLOUDS
#define MAGELLANICCLOUDS

#include "skiplistindex.h"

/**
	*@class MlkyWay
    *This  stores a SkipList for each chunk.  
	*
	*@author James B. Bowlin
	*@version 0.1
	*/
class MagellanicClouds : public SkipListIndex
{
public:
    /**
    	*@short Constructor
    	*@p parent pointer to the parent SkyComponent
    	*/
    MagellanicClouds( SkyComponent *parent );

    void init( KStarsData *data );

    /**
    	*@short Draw the Magellanic Clouds on the sky map
    	*@p psky Reference to the QPainter on which to paint
    	*/
    void draw( QPainter& psky );

    bool selected();
};
#endif
