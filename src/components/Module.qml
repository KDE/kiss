// SPDX-FileCopyrightText: 2025 Carl Schwan <carl@carlschwan.eu>
// SPDX-License-Identifier: LGPL-2.0-or-later

import QtQuick
import QtQuick.Controls as QQC2
import org.kde.kirigami as Kirigami

QQC2.ScrollView {
    id: root

    readonly property real cardWidth: Math.min(Kirigami.Units.gridUnit * 30, root.width - Kirigami.Units.gridUnit * 2)

    QQC2.ScrollBar.horizontal.policy: QQC2.ScrollBar.AlwaysOff
    contentWidth: -1

    required property bool nextEnabled
}
