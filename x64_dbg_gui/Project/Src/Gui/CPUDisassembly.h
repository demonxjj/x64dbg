#ifndef CPUDISASSEMBLY_H
#define CPUDISASSEMBLY_H

#include <QtGui>
#include <QtDebug>
#include "NewTypes.h"
#include "Disassembly.h"
#include "Bridge.h"


class CPUDisassembly : public Disassembly
{
    Q_OBJECT
public:
    explicit CPUDisassembly(QWidget *parent = 0);

    // Mouse Management
    void contextMenuEvent(QContextMenuEvent* event);

    // Context Menu Management
    void setupRightClickContextMenu();
    
signals:
    
public slots:
    void toogleInt3BPAction();
    void toogleHwBpActionSlot();
    void setNewOriginHereActionSlot();

private:
    // Rigth Click Context Menu
    QMenu* mRigthClickContextMenu;

    QAction* mToogleInt3BpAction;
    QAction* mToogleHwBpAction;
    QAction* mSetNewOriginHere;
};

#endif // CPUDISASSEMBLY_H