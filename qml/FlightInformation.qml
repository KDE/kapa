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
import QtQuick.Controls 1.1 as QtControls

import org.kde.kquickcontrolsaddons 2.0 as KQuickControls

ColumnLayout {
    spacing: 20

    Heading {
        text: "Vueling Flight 8992"
        wrapMode: Text.WordWrap
        Layout.alignment: Qt.AlignTop
        Layout.fillWidth: true
    }

    // FIXME: Add the Image?

    // Seperator
    Rectangle {
        color: "black"
        opacity: 0.15
        Layout.fillWidth: true
        Layout.alignment: Qt.AlignTop
        height: 1
    }

    // We can add "Status: On Time"
    Heading {
        text: "Mon 29 Oct 2014"
        level: 5
        Layout.alignment: Qt.AlignTop
    }

    ColumnLayout {
        Layout.alignment: Qt.AlignTop
        spacing: 2

        QtControls.Label {
            text: "Depart Barcelona"
            color: "grey"
        }
        RowLayout {
            spacing: 20
            Heading {
                text: "BCN"
                level: 1
                Layout.alignment: Qt.AlignTop
            }

            ColumnLayout {
                spacing: 0
                Heading {
                    text: "12:30 PM"
                    level: 5
                }

                Heading {
                    text: "Terminal 1"
                    level: 5
                    opacity: 0.5
                }
            }
        }
    }

    ColumnLayout {
        Layout.alignment: Qt.AlignTop
        spacing: 5

        QtControls.Label {
            text: "Arrive Brussels"
            color: "grey"
        }
        RowLayout {
            spacing: 20
            Heading {
                text: "BRU"
                level: 1
                Layout.alignment: Qt.AlignTop
            }

            ColumnLayout {
                spacing: 0
                Heading {
                    text: "2:20 PM"
                    level: 5
                }

                Heading {
                    text: "Terminal 1"
                    level: 5
                    opacity: 0.5
                }
            }
        }
    }

    // Seperator
    Rectangle {
        color: "black"
        opacity: 0.15
        Layout.fillWidth: true
        Layout.alignment: Qt.AlignTop
        height: 1
    }

    RowLayout {
        Layout.alignment: Qt.AlignTop
        spacing: 20

        KQuickControls.QIconItem {
            width: 32
            height: 32
            icon: "mail-message-new"
        }

        QtControls.Label {
            text: "View Email"
            color: "blue"
            opacity: 0.5
        }
    }
}
