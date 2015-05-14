/*
 * Copyright (C) 2015  Vishesh Handa <vhanda@kde.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include "flightreservation.h"

#include <KDocumentStore/KDocumentStore>
#include <KDocumentStore/KDocumentCollection>
#include <KDocumentStore/KDocumentQuery>

#include <QStandardPaths>
#include <QDebug>

#include <algorithm>

FlightReservation::FlightReservation(QObject* parent)
    : QObject(parent)
{
    QString dir = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + "/kapa";

    KDocumentStore store;
    store.setPath(dir + "/db");
    if (!store.open()) {
        qDebug() << "FAILED to open db";
        return;
    }
    KDocumentCollection coll = store.collection("flightinformation");

    QList<QVariantMap> reservations;
    auto query = coll.find(QVariantMap());
    while (query.next()) {
        reservations << query.result();
    }

    //
    // Find the Reservation which is closest to the current time
    // in the future
    //
    const QDateTime now = QDateTime::currentDateTime();
    for (const QVariantMap& map : reservations) {
        QDateTime dt = map.value("departureTime").toDateTime();
        if (now.secsTo(dt) < 0) {
            continue;
        }

        QDateTime dataDt = m_data.value("departureTime").toDateTime();
        if (dataDt.isNull()) {
            m_data = map;
            continue;
        }

        if (dt < dataDt) {
            m_data = map;
            continue;
        }
    }
}

bool FlightReservation::valid() const
{
    return !m_data.isEmpty();
}

QString FlightReservation::flightName() const
{
    return m_data.value("flightName").toString();
}

QString FlightReservation::flightNumber() const
{
    return m_data.value("flightNumber").toString();
}

QDateTime FlightReservation::departureTime() const
{
    return m_data.value("departureTime").toDateTime();
}

QDateTime FlightReservation::arrivalTime() const
{
    return m_data.value("arrivalTime").toDateTime();
}

QString FlightReservation::arrivalAirportCode() const
{
    return m_data.value("arrivalAirportCode").toString();
}

QString FlightReservation::arrivalAirportName() const
{
    return m_data.value("arrivalAirportName").toString();
}

QString FlightReservation::departureAirportCode() const
{
    return m_data.value("departureAirportCode").toString();
}

QString FlightReservation::departureAirportName() const
{
    return m_data.value("departureAirportName").toString();
}
