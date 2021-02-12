#pragma once

#include <QString>

class Backend {
public:
	virtual ~Backend() {};
	virtual void yeetToSession(const QString& username) = 0;
};
