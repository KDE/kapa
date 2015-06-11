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

#include <QCoreApplication>

#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QFile>
#include <QTextStream>

#include "emailfetchjob.h"

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);

    QCommandLineParser parser;
    parser.addOption(QCommandLineOption("imapServer", "Imap server", "server"));
    parser.addOption(QCommandLineOption("imapPort", "Imap port", "number"));
    parser.addOption(QCommandLineOption("username", "Email", "email"));
    parser.addOption(QCommandLineOption("password", "Email password", "password"));
    parser.addOption(QCommandLineOption("subject", "the email's which contain this subject", "id"));
    parser.addHelpOption();
    parser.process(app);

    if (!parser.isSet("imapServer") || !parser.isSet("imapPort") || !parser.isSet("username") || !parser.isSet("password")) {
        parser.showHelp(1);
    }

    EmailFetchJob* job = new EmailFetchJob();
    job->setHostName(parser.value("imapServer"));
    job->setPort(parser.value("imapPort").toUShort());
    job->setUserName(parser.value("username"));
    job->setPassword(parser.value("password"));
    job->start();

    QObject::connect(job, &EmailFetchJob::fetchedEmail, [&](KIMAP::MessagePtr email) {
        QString subject = email->subject(false)->asUnicodeString();

        if (subject.contains(parser.value("subject"), Qt::CaseInsensitive)) {
            KMime::Content* content = email->mainBodyPart("text/html");
            if (!content) {
                return;
            }
            QString html = content->decodedText();

            QFile file(subject);
            file.open(QIODevice::ReadWrite);

            QTextStream stream(&file);
            stream << html;
            qDebug() << subject;
        }
    });

    QObject::connect(job, &EmailFetchJob::finished, &app, &QCoreApplication::quit);
    return app.exec();
}
