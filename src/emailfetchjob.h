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

#ifndef EMAILFETCHJOB_H
#define EMAILFETCHJOB_H

#include <QObject>

#include <KIMAP/Session>
#include <KIMAP/LoginJob>
#include <KIMAP/SelectJob>
#include <KIMAP/SearchJob>
#include <KIMAP/FetchJob>

#include <KMime/Message>

class EmailFetchJob : public QObject
{
    Q_OBJECT
public:
    explicit EmailFetchJob(QObject* parent = 0);

    void setHostName(const QString& hostName) { m_hostName = hostName; }
    void setPort(quint16 port) { m_port = port; }
    void setUserName(const QString& userName) { m_userName = userName; }
    void setPassword(const QString& pass) { m_password =  pass; }

    void start();

Q_SIGNALS:
    void fetchedEmail(KIMAP::MessagePtr email);
    void finished();

private Q_SLOTS:
    void slotLoginJobFinished(KJob* job);
    void slotSelectJobFinished(KJob* job);
    void slotSearchJobFinished(KJob* job);
    void slotFetchJobFinished(KJob* job);
    void slotMessagesReceived(const QString &mailBox, const QMap<qint64, qint64> &uids,
                              const QMap<qint64, KIMAP::MessagePtr> &messages);

private:
    QString m_hostName;
    quint16 m_port;
    QString m_userName;
    QString m_password;

    KIMAP::Session* m_session;
};

#endif // EMAILFETCHJOB_H
