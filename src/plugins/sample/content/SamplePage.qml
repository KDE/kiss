// SPDX-FileCopyrightText: 2021 Carson Black <uhhadd@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick 2.5
import QtQuick.Controls 2.10
import QtQuick.Layouts 1.10
import org.kde.kirigami 2.10 as Kirigami

// The item is in a fixed size viewport, so
// it can't change width, height, x, or y.
Item {
	id: _root

    // The C++ object is set as the "page"
    // property of the root item.
	required property var page

    // Put whatever you want in here.
    Kirigami.Heading {
        text: i18n("Hello World!")
        anchors.centerIn: parent
    }
}
