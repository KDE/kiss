#!/bin/sh

find . -name \*.cc -o -name \*.cpp -o -name \*.h -o -name \*.qml | $XGETTEXT -o "$podir/org.kde.initialsystemsetup.pot" -f -
