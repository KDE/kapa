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

import QtGraphicalEffects 1.0

Item {
    id: root
    width: 600
    height: 600

    Item {
        id: container
        // DropShadow duplicates the source and if we do not set visible to false
        // the container appears twice and we get strange rendering issues
        visible: false
        anchors.centerIn: parent
        width: mainItem.width  + (2 * shadow.radius)
        height: mainItem.height + (2 * shadow.radius)

        Rectangle {
            id: mainItem
            anchors.centerIn: parent

            width: root.width - 50
            height: root.height - 50
            color: "white"

            FlightInformation {
                anchors.fill: parent
                anchors.leftMargin: 15
                anchors.rightMargin: 15
                anchors.topMargin: 20
                anchors.bottomMargin: 20
            }
        }
    }

    DropShadow {
        id: shadow;
        anchors.fill: parent

        cached: true;
        radius: 16
        samples: 16
        smooth: true
        color: "#80000000"
        source: container
    }
}
