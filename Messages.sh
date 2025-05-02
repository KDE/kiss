#! /usr/bin/env bash
# SPDX-FileCopyrightText: None
# SPDX-License-Identifier: CC0-1.0

#!/bin/sh find . -name \*.cc -o -name \*.cpp -o -name \*.h -o -name \*.qml | $XGETTEXT -o "$podir/org.kde.initialsystemsetup.pot" -f -
