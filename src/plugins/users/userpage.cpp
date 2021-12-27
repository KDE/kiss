#include <KPluginFactory>
#include <KLocalizedString>

#include <crack.h>

#include "userpage.h"

K_PLUGIN_FACTORY_WITH_JSON(UserPageFactory, "page_user.json", registerPlugin<UserPage>();)

UserPage::UserPage(QObject* parent, const KPluginMetaData& data, const QVariantList& args) : Page(parent, args)
{
    auto eval = [this, ds = this->dataStore()]() {
        const auto realname = ds->value("realname").toString();
        const auto username = ds->value("username").toString();
        const auto password = ds->value("password").toString();

        const auto canNext =
            !realname.isEmpty() &&
            !username.isEmpty() &&
            !password.isEmpty();

        if (canNext == m_canNext)
            return;

        m_canNext = canNext;
        Q_EMIT canGoNextChanged();
    };
    connect(this->dataStore(), &QQmlPropertyMap::valueChanged, this, eval);
    m_accountsInterface = new OrgFreedesktopAccountsInterface(QStringLiteral("org.freedesktop.Accounts"), QStringLiteral("/org/freedesktop/Accounts"), QDBusConnection::systemBus(), this);
}

UserPage::~UserPage()
{

}


QString UserPage::title() const
{
    return i18n("User Setup");
}

QString UserPage::subtitle() const
{
    return i18n("Let's set up your user account");
}

QQuickItem* UserPage::createItem(QQmlEngine* engine)
{
    return createItemFromURL("qrc:/UserPage.qml", engine, this);
}

Croutons::FutureResult<> UserPage::apply()
{
    const auto store = dataStore();
    const auto username = store->value("username").toString();
    const auto realname = store->value("realname").toString();
    const auto password = store->value("password").toString();
    const auto admin = store->value("admin").toBool();
    const auto targetLanguage = store->value("targetLanguage").toString();

	auto reply = m_accountsInterface->CreateUser(username, realname, admin ? 1 : 0);
	auto user = OrgFreedesktopAccountsUserInterface(QStringLiteral("org.freedesktop.Accounts"), reply.value().path(), QDBusConnection::systemBus(), this);
	user.SetLanguage(targetLanguage);
	user.SetPassword(password, QString());

    auto ret = Croutons::FutureResult<>();
    ret.succeed(Croutons::Nil{});
    return ret;
}

bool UserPage::canGoNext() const
{
    return m_canNext;
}

QString UserPage::checkPassword(const QString& username, const QString& realname, const QString& password)
{
	auto usernameData = username.toLocal8Bit();
	auto realnameData = realname.toLocal8Bit();
	auto passwordData = password.toLocal8Bit();

	usernameData.data();

	auto data = FascistCheckUser(passwordData.data(), GetDefaultCracklibDict(), usernameData.data(), realnameData.data());
	if (data == nullptr) {
		return QString();
	}
	return QString::fromLocal8Bit(data);
}

#include "userpage.moc"
