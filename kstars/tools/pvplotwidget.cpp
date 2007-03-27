/***************************************************************************
                          pvplotwidget.cpp
                             -------------------
    begin                : Sat 17 Dec 2005
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

#include <math.h> //for sqrt()

#include <qapplication.h>

#include "pvplotwidget.h"
#include "planetviewer.h"
#include "kplotobject.h"

PVPlotWidget::PVPlotWidget( QWidget *parent ) :
			KPlotWidget( parent ), 
			mouseButtonDown(false), oldx(0), oldy(0)
{
	setFocusPolicy( Qt::StrongFocus );
	setMouseTracking (true);
	pv = (PlanetViewer*)topLevelWidget();
}

PVPlotWidget::~ PVPlotWidget() {}
 
void PVPlotWidget::keyPressEvent( QKeyEvent *e ) {
	double xc = (dataRect().right() + dataRect().x())*0.5;
	double yc = (dataRect().bottom() + dataRect().y())*0.5;
	double xstep = 0.01*(dataRect().right() - dataRect().x());
	double ystep = 0.01*(dataRect().bottom() - dataRect().y());
	double dx = 0.5*dataRect().width();
	double dy = 0.5*dataRect().height();
	
	switch ( e->key() ) {
		case Qt::Key_Left:
			if ( xc - xstep > -AUMAX ) {
				setLimits( dataRect().x() - xstep, dataRect().right() - xstep, dataRect().y(), dataRect().bottom() );
				pv->setCenterPlanet(QString());
				update();
			}
			break;
		
		case Qt::Key_Right:
			if ( xc + xstep < AUMAX ) { 
				setLimits( dataRect().x() + xstep, dataRect().right() + xstep, dataRect().y(), dataRect().bottom() );
				pv->setCenterPlanet(QString());
				update();
			}
			break;
		
		case Qt::Key_Down:
			if ( yc - ystep > -AUMAX ) {
				setLimits( dataRect().x(), dataRect().right(), dataRect().y() - ystep, dataRect().bottom() - ystep );
				pv->setCenterPlanet(QString());
				update();
			}
			break;
		
		case Qt::Key_Up:
			if ( yc + ystep < AUMAX ) {
				setLimits( dataRect().x(), dataRect().right(), dataRect().y() + ystep, dataRect().bottom() + ystep );
				pv->setCenterPlanet(QString());
				update();
			}
			break;
		
		case Qt::Key_Plus:
		case Qt::Key_Equal:
			slotZoomIn();
			break;
		
		case Qt::Key_Minus:
		case Qt::Key_Underscore:
			slotZoomOut();
			break;
		
		case Qt::Key_0: //Sun
			setLimits( -dx, dx, -dy, dy );
			pv->setCenterPlanet( "Sun" );
			update();
			break;
		
		case Qt::Key_1: //Mercury
		{
			KPlotPoint *p = plotObjects().at(10)->points().at(0);
			setLimits( p->x() - dx, p->x() + dx, p->y() - dy, p->y() + dy );
			pv->setCenterPlanet( "Mercury" );
			update();
			break;
		}
		
		case Qt::Key_2: //Venus
		{
			KPlotPoint *p = plotObjects().at(12)->points().at(0);
			setLimits( p->x() - dx, p->x() + dx, p->y() - dy, p->y() + dy );
			pv->setCenterPlanet( "Venus" );
			update();
			break;
		}
		
		case Qt::Key_3: //Earth
		{
			KPlotPoint *p = plotObjects().at(14)->points().at(0);
			setLimits( p->x() - dx, p->x() + dx, p->y() - dy, p->y() + dy );
			pv->setCenterPlanet( "Earth" );
			update();
			break;
		}
		
		case Qt::Key_4: //Mars
		{
			KPlotPoint *p = plotObjects().at(16)->points().at(0);
			setLimits( p->x() - dx, p->x() + dx, p->y() - dy, p->y() + dy );
			pv->setCenterPlanet( "Mars" );
			update();
			break;
		}
		
		case Qt::Key_5: //Jupiter
		{
			KPlotPoint *p = plotObjects().at(18)->points().at(0);
			setLimits( p->x() - dx, p->x() + dx, p->y() - dy, p->y() + dy );
			pv->setCenterPlanet( "Jupiter" );
			update();
			break;
		}
		
		case Qt::Key_6: //Saturn
		{
			KPlotPoint *p = plotObjects().at(20)->points().at(0);
			setLimits( p->x() - dx, p->x() + dx, p->y() - dy, p->y() + dy );
			pv->setCenterPlanet( "Saturn" );
			update();
			break;
		}
		
		case Qt::Key_7: //Uranus
		{
			KPlotPoint *p = plotObjects().at(22)->points().at(0);
			setLimits( p->x() - dx, p->x() + dx, p->y() - dy, p->y() + dy );
			pv->setCenterPlanet( "Uranus" );
			update();
			break;
		}
		
		case Qt::Key_8: //Neptune
		{
			KPlotPoint *p = plotObjects().at(24)->points().at(0);
			setLimits( p->x() - dx, p->x() + dx, p->y() - dy, p->y() + dy );
			pv->setCenterPlanet( "Neptune" );
			update();
			break;
		}
		
		case Qt::Key_9: //Pluto
		{
			KPlotPoint *p = plotObjects().at(26)->points().at(0);
			setLimits( p->x() - dx, p->x() + dx, p->y() - dy, p->y() + dy );
			pv->setCenterPlanet( "Pluto" );
			update();
			break;
		}
		
		default:
			e->ignore();
			break;
	}
}

void PVPlotWidget::mousePressEvent( QMouseEvent *e ) {
	mouseButtonDown = true;
	oldx = e->x();
	oldy = e->y();
}

void PVPlotWidget::mouseReleaseEvent( QMouseEvent * ) {
	mouseButtonDown = false;
	update();
}

void PVPlotWidget::mouseMoveEvent( QMouseEvent *e ) {
	if ( mouseButtonDown ) {
		//Determine how far we've moved
		double xc = (dataRect().right() + dataRect().x())*0.5;
		double yc = (dataRect().bottom() + dataRect().y())*0.5;
		double xscale = dataRect().width()/( width() - leftPadding() - rightPadding() );
		double yscale = dataRect().height()/( height() - topPadding() - bottomPadding() );
		
		xc += ( oldx  - e->x() )*xscale;
		yc -= ( oldy - e->y() )*yscale; //Y data axis is reversed...
		
		if ( xc > -AUMAX && xc < AUMAX && yc > -AUMAX && yc < AUMAX ) {
			setLimits( xc - 0.5*dataRect().width(), xc + 0.5*dataRect().width(), 
					yc - 0.5*dataRect().height(), yc + 0.5*dataRect().height() );
			update();
			qApp->processEvents();
		}
		
		oldx = e->x();
		oldy = e->y();
	}
}

void PVPlotWidget::mouseDoubleClickEvent( QMouseEvent *e ) {
	double xscale = dataRect().width()/( width() - leftPadding() - rightPadding() );
	double yscale = dataRect().height()/( height() - topPadding() - bottomPadding() );
	
	double xc = dataRect().x() + xscale*( e->x() - leftPadding() );
	double yc = dataRect().bottom() - yscale*( e->y() - topPadding() );

	if ( xc > -AUMAX && xc < AUMAX && yc > -AUMAX && yc < AUMAX ) {
		setLimits( xc - 0.5*dataRect().width(), xc + 0.5*dataRect().width(), 
				yc - 0.5*dataRect().height(), yc + 0.5*dataRect().height() );
		update();
	}

	pv->setCenterPlanet( QString() );
	for ( unsigned int i=0; i<9; ++i ) {
		KPlotPoint *point = pv->planetObject(i)->points().at(0);
		double dx = ( point->x() - xc )/xscale;
		if ( dx < 4.0 ) {
			double dy = ( point->y() - yc )/yscale;
			if ( sqrt( dx*dx + dy*dy ) < 4.0 ) {
				pv->setCenterPlanet( pv->planetName(i) );
			}
		}
	}
}

void PVPlotWidget::wheelEvent( QWheelEvent *e ) {
	if ( e->delta() > 0 ) slotZoomIn();
	else slotZoomOut();
}

void PVPlotWidget::slotZoomIn() {
	double size = dataRect().width();
	if ( size > 0.8 ) {
		setLimits( dataRect().x() + 0.02*size, dataRect().right() - 0.02*size, dataRect().y() + 0.02*size, dataRect().bottom() - 0.02*size );
		update();
	}
}

void PVPlotWidget::slotZoomOut() {
	double size = dataRect().width();
	if ( (size) < 100.0 ) {
		setLimits( dataRect().x() - 0.02*size, dataRect().right() + 0.02*size, dataRect().y() - 0.02*size, dataRect().bottom() + 0.02*size );
		update();
	}
}

#include "pvplotwidget.moc"
