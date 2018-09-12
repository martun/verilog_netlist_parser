#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QMainWindow>
#include <QTreeView>
#include <QGraphicsView>

#include <tcl.h>

#include "textedit.h"
#include "treeview_model.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
//    void contextMenuEvent(QContextMenuEvent *event);

private:
    void createMenus();
    void createViews();
    void expandTreeView() const;

    void registerTclCommands();

public slots:
    void executeTclCommand();
    void updateModel();

private slots:
    void newProject();
    void openProject();
    void saveProject();
    void closeProject();
    void undo();
    void redo();
    void cut();
    void copy();
    void paste();
    void about();
    void help();

private:
    QMenu* m_fileMenu;
    QMenu* m_editMenu;
    QMenu* m_toolsMenu;
    QMenu* m_helpMenu;

    QTreeView* m_treeView;
    QGraphicsView* m_graphicsView;
    QGraphicsScene* m_scene;
    TextEdit* m_textEdit;

    TreeViewModel* m_treeViewModel;
    Tcl_Interp* m_interp;
};

int openNetlist(ClientData clientData, Tcl_Interp *interp, int objc,
         Tcl_Obj *const objv[]);

int createNewModule(ClientData clientData, Tcl_Interp *interp, int objc,
         Tcl_Obj *const objv[]);

int listModuleDescs(ClientData clientData, Tcl_Interp *interp, int objc,
         Tcl_Obj *const objv[]);

int addModuleInstance(ClientData clientData, Tcl_Interp *interp, int objc,
         Tcl_Obj *const objv[]);

int addModulePort(ClientData clientData, Tcl_Interp *interp, int objc,
         Tcl_Obj *const objv[]);


#endif // MAINWINDOW_H
