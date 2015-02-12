/*
 * Copyright (C) 2015 Vishesh Handa <vhanda@kde.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) version 3, or any
 * later version accepted by the membership of KDE e.V. (or its
 * successor approved by the membership of KDE e.V.), which shall
 * act as a proxy defined in Section 6 of version 3 of the license.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

import QtQuick 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.3

import org.kde.now 0.1 as KdeNow
import org.kde.plasma.extras 2.0 as PlasmaExtras

Item {
    Layout.minimumWidth: 300
    Layout.maximumWidth: 300
    Layout.minimumHeight: 600
    Layout.maximumHeight: 600

    KdeNow.FlightReservation {
        id: reservation
    }

    KdeNow.FlightInformation {
        anchors.fill: parent
        visible: reservation.valid

        flightName: reservation.flightName + " Flight"
        flightNumber: reservation.flightNumber
        departureTime: reservation.departureTime
        arrivalTime: reservation.arrivalTime

        departureAirportCode: reservation.departureAirportCode
        departureAirportName: reservation.departureAirportName
        arrivalAirportCode: reservation.arrivalAirportCode
        arrivalAirportName: reservation.arrivalAirportName
    }

    PlasmaExtras.Heading {
        anchors.fill: parent
        text: "No Upcoming Flights"
        visible: !reservation.valid
    }
}
