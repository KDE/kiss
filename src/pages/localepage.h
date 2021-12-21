#include "plugins/ipage.h"

class LocalePage : public Page
{

    Q_OBJECT

public:

    explicit LocalePage(QObject* parent = nullptr);
    ~LocalePage();

    QString title() const override;
    QString subtitle() const override;

    QQuickItem* createItem(QQmlEngine* engine) override;
    Croutons::FutureResult<> apply() override;

    bool canGoNext() const override;

};