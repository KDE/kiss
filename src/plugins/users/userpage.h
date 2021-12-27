#pragma once

#include <KPluginMetaData>
#include "ipage.h"

#include "AccountsService.h"
#define org org_collision_prevention
#include "User.h"
#undef org

class UserPage : public Page
{

    Q_OBJECT

    bool m_canNext = false;
    OrgFreedesktopAccountsInterface* m_accountsInterface = nullptr;

public:

    explicit UserPage(QObject* parent, const KPluginMetaData& data, const QVariantList& args);
    ~UserPage();

    QString title() const override;
    QString subtitle() const override;

    QQuickItem* createItem(QQmlEngine* engine) override;
    Croutons::FutureResult<> apply() override;

    bool canGoNext() const override;
    Q_INVOKABLE QString checkPassword(const QString& username, const QString& realname, const QString& password);

};
