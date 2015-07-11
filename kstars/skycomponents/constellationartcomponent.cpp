/***************************************************************************
                          ConstellationArtComponent.cpp  -  K Desktop Planetarium
                             -------------------
    begin                : 2015-05-27
    copyright            : (C) 2015 by M.S.Adityan
    email                : msadityan@gmail.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "constellationartcomponent.h"
#include "kstars/auxiliary/ksfilereader.h"
#include "kstars/skymap.h"
#include "kstars/projections/projector.h"

ConstellationArtComponent::ConstellationArtComponent( SkyComposite *parent, CultureList *cultures ):SkyComponent(parent)
{
    cultureName = cultures->current();
    loadData();
}

ConstellationArtComponent::~ConstellationArtComponent()
{    while( !m_ConstList.isEmpty() ) {
        ConstellationsArt *o = m_ConstList.takeFirst();
        delete o;
    }
}

void ConstellationArtComponent::loadData(){

        QSqlDatabase skydb = QSqlDatabase::addDatabase("QSQLITE", "skycultures");
        QString dbfile = QStandardPaths::locate(QStandardPaths::DataLocation, "skycultures.sqlite");

        skydb.setDatabaseName(dbfile);
        if (skydb.open() == false)
        {
            qWarning() << "Unable to open sky cultures database file " << dbfile << endl;
            return;
        }

         QSqlQuery get_query(skydb);
         if (!get_query.exec("SELECT * FROM western"))
         {
            qDebug() << get_query.lastError();
             return;
         }

         while (get_query.next())
         {
             QString abbreviation   = get_query.value("Abbreviation").toString();
             QString filename       = get_query.value("Filename").toString();
             QString midpointRA            = get_query.value("MidpointRA").toString();
             QString midpointDEC           = get_query.value("MidpointDEC").toString();
             double pa                 = get_query.value("Position Angle").toDouble();
             double w         = get_query.value("Width").toDouble();
             double h         = get_query.value("Height").toDouble();

             dms midpointra = dms::fromString(midpointRA,false);
             dms midpointdec = dms::fromString(midpointDEC,true);

             // appends constellation info
             ConstellationsArt *ca = new ConstellationsArt(midpointra, midpointdec, pa, w,h, abbreviation, filename);
             m_ConstList.append(ca);
             qDebug()<<"Successsfully read skyculture.sqlite"<<abbreviation<<filename<<midpointRA<<midpointDEC<<pa<<w<<h;
         }
        skydb.close();
}

void ConstellationArtComponent::showList()
{
    int i = 0;
    for(i = 0; i < m_ConstList.size(); i++)
    {
        qDebug()<<m_ConstList[i]->getAbbrev()<<m_ConstList[i]->getImageFileName();
        qDebug()<<m_ConstList[i]->pa();
    }
}

void ConstellationArtComponent::draw(SkyPainter *skyp){

    if(Options::showConstellationArt()){
         //for(int i =0; i<2; i++)
         skyp->drawConstellationArtImage(m_ConstList[3]);
    }

    //Loops through the QList containing all data required to draw western constellations.
    //There are 85 images, so m_ConstList.size() should return 85.
}
