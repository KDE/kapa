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

#include <QTest>
#include <QSignalSpy>
#include <QDebug>

#include <QCoreApplication>
#include <QTime>
#include <QFile>
#include <QTextStream>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "microdataparser.h"
#include "config.h"

class MicroDataParserTest : public QObject
{
    Q_OBJECT

private slots:
    void test();
    void test_data();
};

void MicroDataParserTest::test()
{
    QFETCH(QString, microdata);
    QFETCH(QString, jsonld);

    QFile file(TEST_FILES_PATH + QString("testdata/") + microdata);
    file.open(QIODevice::ReadOnly);

    QTextStream stream(&file);
    const QString data = stream.readAll();

    MicroDataParser parser;
    QVariant result = parser.parse(data);

    QFile file2(TEST_FILES_PATH + QString("testdata/") + jsonld);
    file2.open(QIODevice::ReadOnly);

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(file2.readAll(), &error);
    if (error.error) {
        qDebug() << error.errorString();
        Q_ASSERT(error.error == 0);
    }

    QVariant actual = doc.toVariant();

    QCOMPARE(result, actual);
}

void MicroDataParserTest::test_data()
{
    QTest::addColumn<QString>("microdata");
    QTest::addColumn<QString>("jsonld");

    QTest::newRow("person") << "data1.html" << "data1.json-ld";
    QTest::newRow("flight-with-sub-item") << "data2.html" << "data2.json-ld";
    QTest::newRow("full-email") << "microDataTest.html" << "microDataTest.jsonld";
}

QTEST_MAIN(MicroDataParserTest)

#include "microdataparsertest.moc"
