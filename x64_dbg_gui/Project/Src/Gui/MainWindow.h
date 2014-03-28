#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QFileDialog>
#include <QMdiArea>
#include <QMdiSubWindow>
#include "CPUWidget.h"
#include "CommandLineEdit.h"
#include "MemoryMapView.h"
#include "LogView.h"
#include "StatusLabel.h"
#include "BreakpointsView.h"
#include "ScriptView.h"
#include "SymbolView.h"
#include "ReferenceView.h"
#include "ThreadView.h"
#include "SettingsDialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setTab(QWidget* widget);

public slots:
    void executeCommand();
    void execStepOver();
    void execStepInto();
    void setFocusToCommandBar();
    void displayMemMapWidget();
    void displayLogWidget();
    void displayScriptWidget();
    void displayAboutWidget();
    void execClose();
    void execRun();
    void execRtr();
    void openFile();
    void execPause();
    void startScylla();
    void restartDebugging();
    void displayBreakpointWidget();
    void updateWindowTitleSlot(QString filename);
    void execeStepOver();
    void execeStepInto();
    void execeRun();
    void execeRtr();
    void displayCpuWidget();
    void displaySymbolWidget();
    void displayReferencesWidget();
    void displayThreadsWidget();
    void openSettings();
    void addRecentFile(QString file);
    void setLastException(unsigned int exceptionCode);

private:
    Ui::MainWindow *ui;

    CommandLineEdit* mCmdLineEdit;
    QTabWidget* mTabWidget;
    CPUWidget* mCpuWidget;
    MemoryMapView* mMemMapView;
    LogView* mLogView;
    SymbolView* mSymbolView;
    BreakpointsView* mBreakpointsView;
    ScriptView* mScriptView;
    ReferenceView* mReferenceView;
    ThreadView* mThreadView;

    StatusLabel* mStatusLabel;
    StatusLabel* mLastLogLabel;

    const char* mWindowMainTitle;

    std::vector<QString> mMRUList;
    unsigned int mMaxMRU;
    unsigned int lastException;

    void loadMRUList(int maxItems);
    void saveMRUList();
    void addMRUEntry(QString entry);
    void removeMRUEntry(QString entry);
    void updateMRUMenu();
    QString getMRUEntry(size_t index);

protected:
    void dragEnterEvent(QDragEnterEvent* pEvent);
    void dropEvent(QDropEvent* pEvent);
};

#endif // MAINWINDOW_H
