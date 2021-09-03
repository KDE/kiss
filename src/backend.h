// SPDX-FileCopyrightText: 2021 Carson Black <uhhadd@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QString>

class Backend {
public:
	virtual ~Backend() {};
	virtual void yeetToSession(const QString& username) = 0;
};
