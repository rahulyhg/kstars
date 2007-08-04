/***************************************************************************
               constellationlines.h  -  K Desktop Planetarium
                             -------------------
    begin                : 25 Oct. 2005
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

#ifndef CONSTELLATIONLINES_H
#define CONSTELLATIONLINES_H

#include <QHash>

#include "linelistindex.h"
#include "kstarsdatetime.h"

class SkyMesh;
class LineListComponent;

   /*
	*@class ConstellationLines
	*Collection of lines making the 88 constellations

	*@author Jason Harris
	*@version 0.1
	*/

class ConstellationLines : public LineListIndex 
{

	public:
	   /* @short Constructor
	    * @p parent Pointer to the parent SkyComponent object
        * @p mesh Pointer to the one true SkyMesh used for indexing.
		*/
		ConstellationLines( SkyComponent *parent );

	   /* @short Initialize the Constellation lines 
		*
		*Reads the constellation lines data from clines.dat.
		*Each line in the file contains a command character ("M" means move to 
		*this position without drawing a line, "D" means draw a line from 
		*the previous position to this one), followed by the genetive name of 
		*a star, which marks the position of the constellation node.
		*@p data Pointer to the KStarsData object
		*/
		void init( KStarsData *data );

        /* @short we need to override the update routine because stars are
         * updated differently from mere SkyPoints.
         */
        void JITupdate( KStarsData *data, LineList* lineList );

        /* @short we use the update hook to re-index the constellation lines
         * every 150 years to account for proper motion of the stars.
         */
        void update( KStarsData *data, KSNumbers *num );

       /* @short Set the QColor and QPen for drawing.
        */
        void preDraw( KStars *ks, QPainter &psky );

        bool selected();

    private:

        KStarsDateTime m_indexDate;

};


#endif
