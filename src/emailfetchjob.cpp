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

#include "emailfetchjob.h"

#include <QDebug>

EmailFetchJob::EmailFetchJob(QObject* parent)
    : QObject(parent)
{
}

void EmailFetchJob::start()
{
    m_session = new KIMAP::Session(m_hostName, m_port, this);

    KIMAP::LoginJob* loginJob = new KIMAP::LoginJob(m_session);
    loginJob->setUserName(m_userName);
    loginJob->setPassword(m_password);
    loginJob->setEncryptionMode(KIMAP::LoginJob::AnySslVersion);

    connect(loginJob, SIGNAL(finished(KJob*)), this, SLOT(slotLoginJobFinished(KJob*)));
    loginJob->start();
}

void EmailFetchJob::slotLoginJobFinished(KJob* job)
{
    auto loginJob = static_cast<KIMAP::LoginJob*>(job);
    if (loginJob->error()) {
        qDebug() << loginJob->errorString();
        return;
    }

    KIMAP::SelectJob* selectJob = new KIMAP::SelectJob(m_session);
    selectJob->setMailBox("INBOX");
    selectJob->setOpenReadOnly(true);

    connect(selectJob, SIGNAL(finished(KJob*)), this, SLOT(slotSelectJobFinished(KJob*)));
    selectJob->start();
}

void EmailFetchJob::slotSelectJobFinished(KJob* job)
{
    auto selectJob = static_cast<KIMAP::SelectJob*>(job);
    if (selectJob->error()) {
        qDebug() << selectJob->errorString();
        return;
    }

    KIMAP::Term term(KIMAP::Term::Since, QDate::currentDate().addMonths(-2));
    KIMAP::SearchJob* searchJob = new KIMAP::SearchJob(m_session);
    searchJob->setTerm(term);

    connect(searchJob, SIGNAL(finished(KJob*)), this, SLOT(slotSearchJobFinished(KJob*)));
    searchJob->start();
}

void EmailFetchJob::slotSearchJobFinished(KJob* job)
{
    auto searchJob = static_cast<KIMAP::SearchJob*>(job);
    if (searchJob->error()) {
        qDebug() << searchJob->errorString();
        return;
    }

    qDebug() << searchJob->results();
    KIMAP::ImapSet set;
    set.add(searchJob->results());

    KIMAP::FetchJob* fetchJob = new KIMAP::FetchJob(m_session);
    fetchJob->setSequenceSet(set);

    connect(fetchJob, SIGNAL(finished(KJob*)), this, SLOT(slotFetchJobFinished(KJob*)));
    connect(fetchJob, SIGNAL(messagesReceived(QString,QMap<qint64,qint64>,QMap<qint64,KIMAP::MessagePtr>)),
            this, SLOT(slotMessagesReceived(QString,QMap<qint64,qint64>,QMap<qint64,KIMAP::MessagePtr>)));
    fetchJob->start();
}

void EmailFetchJob::slotFetchJobFinished(KJob* job)
{
    Q_UNUSED(job);
    emit finished();
}

void EmailFetchJob::slotMessagesReceived(const QString& mailBox,
                                         const QMap<qint64, qint64>& uids,
                                         const QMap<qint64, KIMAP::MessagePtr>& messages)
{
    Q_UNUSED(mailBox);
    Q_UNUSED(uids);

    QMapIterator<qint64, KIMAP::MessagePtr> it(messages);
    while (it.hasNext()) {
        it.next();

        emit fetchedEmail(it.value());
    }
}
