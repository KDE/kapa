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

#ifndef FLIGHTRESERVATION_H
#define FLIGHTRESERVATION_H

#include <QObject>
#include <QVariantMap>
#include <QDateTime>

/**
 * The most current Flight Reservation.
 *
 * Will not return any value if there is no flight within the week.
 */
class FlightReservation : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString flightName READ flightName)
    Q_PROPERTY(QString flightNumber READ flightNumber)
    Q_PROPERTY(QDateTime departureTime READ departureTime)
    Q_PROPERTY(QDateTime arrivalTime READ arrivalTime)
    Q_PROPERTY(QString departureAirportCode READ departureAirportCode)
    Q_PROPERTY(QString departureAirportName READ departureAirportName)
    Q_PROPERTY(QString arrivalAirportCode READ arrivalAirportCode)
    Q_PROPERTY(QString arrivalAirportName READ arrivalAirportName)

public:
    explicit FlightReservation(QObject* parent = 0);

    QString flightName() const;
    QString flightNumber() const;

    QDateTime departureTime() const;
    QDateTime arrivalTime() const;

    QString departureAirportCode() const;
    QString departureAirportName() const;
    QString arrivalAirportCode() const;
    QString arrivalAirportName() const;

private:
    QVariantMap m_data;
};

#endif // FLIGHTRESERVATION_H
