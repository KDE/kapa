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

#include "processor.h"
#include "microdataparser.h"

#include <kmime/kmime_message.h>

#include <QStandardPaths>
#include <QDir>

Processor::Processor(QObject* parent)
    : QObject(parent)
{
    QString dir = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + "/kapa";
    QDir().mkpath(dir);

    m_store.setPath(dir + "/db");
    m_store.open();
    m_coll = m_store.collection("flightinformation");
}

void Processor::process(const KIMAP::MessagePtr& email)
{
    qDebug() << email->subject(false)->asUnicodeString();
    KMime::Content* content = email->mainBodyPart("text/html");
    if (!content) {
        return;
    }

    if (!content->contentType(false)->isHTMLText()) {
        return;
    }
    QString html = content->decodedText();

    MicroDataParser parser;
    QVariant result = parser.parse(html);
    if (result.isNull() || result.type() != QVariant::Map) {
        return;
    }
    qDebug() << result;

    process(result.toMap());
}

void Processor::process(const QVariantMap& map)
{
    const QString type = map.value("@type").toString();
    if (type != QStringLiteral("ReservationPackage")) {
        qDebug() << "ABORT";
        return;
    }

    QVariantList flights = map.value("reservation").toList();
    for (const QVariant& variant : flights) {
        QVariantMap fr = variant.toMap();

        const QString frtype = fr.value("@type").toString();
        if (frtype != QStringLiteral("FlightReservation")) {
            qDebug() << "ABORT";
            return;
        }

        QVariantMap flight = fr.value("reservationFor").toMap();

        QDateTime departureTime = QDateTime::fromString(flight.value("departureTime").toString(), Qt::ISODate);
        QDateTime arrivalTime = QDateTime::fromString(flight.value("arrivalTime").toString(), Qt::ISODate);

        QVariantMap departureAirport = flight.value("departureAirport").toMap();
        QVariantMap arrivalAirport = flight.value("arrivalAirport").toMap();

        QString depCode = departureAirport.value("iataCode").toString();
        QString depName = departureAirport.value("name").toString();
        QString ariCode = arrivalAirport.value("iataCode").toString();
        QString ariName = arrivalAirport.value("name").toString();

        QString flightNum = flight.value("flightNumber").toString();
        QString airline = flight.value("airline").toMap().value("name").toString();

        QVariantMap data;
        data["flightNumber"] = flightNum;
        data["flightName"] = airline;
        data["departureTime"] = departureTime;
        data["arrivalTime"] = arrivalTime;
        data["departureAirportCode"] = depCode;
        data["departureAirportName"] = depName;
        data["arrivalAirportCode"] = ariCode;
        data["arrivalAirportName"] = ariName;

        m_coll.insert(data);
    }
}
