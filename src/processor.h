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

#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <QObject>

#include <KMime/Message>
#include <KImap/FetchJob>

#include <KDocumentStore/KDocumentStore>
#include <KDocumentStore/KDocumentCollection>

class Processor : public QObject
{
    Q_OBJECT
public:
    explicit Processor(QObject* parent = 0);

public Q_SLOTS:
    void process(const KIMAP::MessagePtr& email);

private:
    void process(const QVariantMap& map);

    KDocumentStore m_store;
    KDocumentCollection m_coll;
};

#endif // PROCESSOR_H
