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

#include "microdataparser.h"

#include <QDomDocument>
#include <QDomElement>
#include <QDebug>

MicroDataParser::MicroDataParser()
{

}

static QVariantMap processItemScope(QDomElement e)
{
    QVariantMap map;

    while (!e.isNull()) {
        if (e.hasAttribute("itemscope") && e.hasAttribute("itemtype")) {
            QString prop = e.attribute("itemprop");
            QString type = e.attribute("itemtype");
            if (type.startsWith("http://schema.org/")) {
                type = type.mid(QString("http://schema.org/").length());
            }

            QVariantMap subMap = processItemScope(e.firstChildElement());
            subMap["@type"] = type;

            if (!map.contains(prop)) {
                map[prop] = subMap;
            } else {
                QVariant v = map.value(prop);
                if (v.type() == QVariant::List) {
                    QVariantList list = v.toList();
                    list << subMap;
                    v = list;
                }
                else {
                    qDebug() << subMap;
                    QVariantList list;
                    list << v << subMap;
                    v = list;
                }
                map[prop] = v;
            }
        }
        else if (e.hasAttribute("itemprop")) {
            QString prop = e.attribute("itemprop");
            QString value = e.attribute("content");
            if (value.isEmpty()) {
                value = e.text();
            }

            // FIXME: Add special handling for different data types
            map.insert(prop, value);
        }
        else if (e.hasChildNodes()) {
            map.unite(processItemScope(e.firstChildElement()));
        }

        e = e.nextSiblingElement();
    }

    return map;
}

static QVariant convertToVariant(QDomElement e)
{
    QVariantList list;

    while (!e.isNull()) {
        if (e.hasAttribute("itemscope") && e.hasAttribute("itemtype")) {
            Q_ASSERT(!e.hasAttribute("itemprop"));

            QString type = e.attribute("itemtype");
            if (type.startsWith("http://schema.org/")) {
                type = type.mid(QString("http://schema.org/").length());
            }

            QVariantMap subMap = processItemScope(e.firstChildElement());
            subMap["@type"] = type;

            list << subMap;
        }
        else if (e.hasChildNodes()) {
            QVariant var = convertToVariant(e.firstChildElement());
            if (!var.isNull()) {
                list << var;
            }
        }

        e = e.nextSiblingElement();
    }

    if (list.isEmpty()) {
        return QVariant();
    }
    else if (list.size() == 1) {
        return list.first();
    }
    return list;
}

QVariant MicroDataParser::parse(const QString& html)
{
    QDomDocument dom;
    dom.setContent(html);
    QDomElement docElem = dom.documentElement();

    QVariant var = convertToVariant(docElem);
    if (var.type() == QVariant::Map) {
        auto map = var.toMap();
        map.insert("@context", "http://schema.org/");
        var = map;
    } else if (var.type() == QVariant::List) {
        auto list = var.toList();
        for (QVariant& v : list) {
            auto map = var.toMap();
            map.insert("@context", "http://schema.org/");
            v = map;
        }
        var = list;
    }

    return var;
}
