#ifndef SYMBOLVIEW_H
#define SYMBOLVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QList>
#include <QMenu>
#include "StdTable.h"
#include "Bridge.h"

namespace Ui {
class SymbolView;
}

class SymbolView : public QWidget
{
    Q_OBJECT

public:
    explicit SymbolView(QWidget *parent = 0);
    ~SymbolView();
    void setupContextMenu();

public slots:
    void addMsgToSymbolLogSlot(QString msg);
    void clearSymbolLogSlot();
    void moduleSelectionChanged(int index);
    void updateSymbolList(int module_count, SYMBOLMODULEINFO* modules);
    void symbolFollow();
    void symbolContextMenu(const QPoint & pos);
    void symbolAddressCopy();
    void symbolDecoratedCopy();
    void symbolUndecoratedCopy();
    void symbolKeyPressed(QKeyEvent* event);
    void searchTextChanged(const QString &arg1);

signals:
    void showCpu();

private:
    Ui::SymbolView *ui;
    QVBoxLayout* mMainLayout;
    QVBoxLayout* mSymbolLayout;
    QWidget* mSymbolPlaceHolder;

    StdTable* mModuleList;
    StdTable* mSymbolList;
    StdTable* mSymbolSearchList;

    QList<uint_t> mModuleBaseList;

    QAction* mFollowSymbolAction;
    QAction* mCopySymbolAddress;
    QAction* mCopyDecoratedSymbolAction;
    QAction* mCopyUndecoratedSymbolAction;

    static void cbSymbolEnum(SYMBOLINFO* symbol, void* user);
};

#endif // SYMBOLVIEW_H