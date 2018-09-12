#include "mainwindow.h"
#include "treeview_model.h"

#include <tcl.h>

#include <QDebug>
#include <QVBoxLayout>
#include <QSplitter>
#include <QMenu>
#include <QMenuBar>
#include <QGraphicsEllipseItem>
#include <QFileDialog>

#include <list>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_treeViewModel(0)
{
    resize(800, 600);
    createMenus();
    createViews();

    TreeViewModel::create();
    m_treeViewModel = TreeViewModel::get();

    registerTclCommands();
        
    connect(m_textEdit, SIGNAL(commandEntered()), this, SLOT(executeTclCommand()));
    connect(m_treeViewModel, SIGNAL(modelChanged()), this, SLOT(updateModel()));
}

MainWindow::~MainWindow()
{
    
}

void MainWindow::registerTclCommands()
{
    m_interp = Tcl_CreateInterp();
    
    Tcl_CreateObjCommand(m_interp, "open_netlist", openNetlist, 0, 0);
    Tcl_CreateObjCommand(m_interp, "create_new_module", createNewModule, 0, 0);
    Tcl_CreateObjCommand(m_interp, "add_module_instance", addModuleInstance, 0, 0);
    Tcl_CreateObjCommand(m_interp, "add_module_port", addModulePort, 0, 0);
}

void MainWindow::updateModel()
{
    m_treeViewModel = TreeViewModel::get();
    m_treeView->setModel(m_treeViewModel);
    expandTreeView();
}

void MainWindow::executeTclCommand()
{
    std::string command = m_textEdit->getLastCommand();
    Tcl_Eval(m_interp, m_textEdit->getLastCommand().c_str());
}

void MainWindow::createMenus()
{
    m_fileMenu = new QMenu(tr("&File"), 0);
    m_editMenu = new QMenu(tr("&Edit"), 0);
    m_toolsMenu = new QMenu(tr("&Tools"), 0);
    m_helpMenu = new QMenu(tr("&Help"), 0);

    // file menu actions
    QAction* newProjectAction = new QAction(tr("&New"), this);
    connect(newProjectAction, SIGNAL(triggered()), this, SLOT(newProject()));
    m_fileMenu->addAction(newProjectAction);

    QAction* openProjectAction = new QAction(tr("&Open"), this);
    connect(openProjectAction, SIGNAL(triggered()), this, SLOT(openProject()));
    m_fileMenu->addAction(openProjectAction);

    QAction* saveProjectAction = new QAction(tr("&Save"), this);
    connect(saveProjectAction, SIGNAL(triggered()), this, SLOT(saveProject()));
    m_fileMenu->addAction(saveProjectAction);

    QAction* closeProjectAction = new QAction(tr("&Close"), this);
    connect(closeProjectAction, SIGNAL(triggered()), this, SLOT(closeProject()));
    m_fileMenu->addAction(closeProjectAction);

    m_fileMenu->addSeparator();

    QAction* exitAction = new QAction(tr("&Exit"), this);
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
    m_fileMenu->addAction(exitAction);

    // edit menu actions
    QAction* undoAction = new QAction(tr("&Undo"), this);
    connect(undoAction, SIGNAL(triggered()), this, SLOT(undo()));
    m_editMenu->addAction(undoAction);

    QAction* redoAction = new QAction(tr("&Redo"), this);
    connect(redoAction, SIGNAL(triggered()), this, SLOT(redo()));
    m_editMenu->addAction(redoAction);

    m_editMenu->addSeparator();

    QAction* cutAction = new QAction(tr("Cu&t"), this);
    connect(cutAction, SIGNAL(triggered()), this, SLOT(cut()));
    m_editMenu->addAction(cutAction);

    QAction* copyAction = new QAction(tr("&Copy"), this);
    connect(copyAction, SIGNAL(triggered()), this, SLOT(copy()));
    m_editMenu->addAction(copyAction);

    QAction* pasteProjectAction = new QAction(tr("&Paste"), this);
    connect(pasteProjectAction, SIGNAL(triggered()), this, SLOT(paste()));
    m_editMenu->addAction(pasteProjectAction);

    // tools menu actions

    // help menu actions
    QAction* aboutProjectAction = new QAction(tr("&About"), this);
    connect(aboutProjectAction, SIGNAL(triggered()), this, SLOT(about()));
    m_helpMenu->addAction(aboutProjectAction);

    QAction* helpAction = new QAction(tr("&Help"), this);
    connect(helpAction, SIGNAL(triggered()), this, SLOT(help()));
    m_helpMenu->addAction(helpAction);

    this->menuBar()->addMenu(m_fileMenu);
    this->menuBar()->addMenu(m_editMenu);
    this->menuBar()->addMenu(m_toolsMenu);
    this->menuBar()->addMenu(m_helpMenu);

}

void MainWindow::createViews()
{
    QWidget *widget = new QWidget(widget);

    QVBoxLayout* verticalLayout = new QVBoxLayout(widget);
    QSplitter* horizontalSplitter = new QSplitter(Qt::Horizontal);

    m_treeView = new QTreeView();
    m_treeView->setModel(m_treeViewModel);
    QSizePolicy spLeft(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spLeft.setHorizontalStretch(1);
    m_treeView->setSizePolicy(spLeft);

    m_scene = new QGraphicsScene();
    m_scene->setSceneRect( -100.0, -100.0, 200.0, 200.0 );

    QGraphicsEllipseItem *item = new QGraphicsEllipseItem( 0, m_scene ); // to be removed
    item->setRect( -50.0, -50.0, 100.0, 100.0 );

    m_graphicsView = new QGraphicsView();
    m_graphicsView->setScene(m_scene);
    QSizePolicy spRight(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spRight.setHorizontalStretch(3);
    m_graphicsView->setSizePolicy(spRight);

    m_textEdit = new TextEdit();//("shell commands...");

    horizontalSplitter->addWidget(m_treeView);
    horizontalSplitter->addWidget(m_graphicsView);

    verticalLayout->addWidget(horizontalSplitter);
    verticalLayout->addWidget(m_textEdit);
    verticalLayout->setStretch(0, 4);
    verticalLayout->setStretch(1, 1);

    widget->setLayout(verticalLayout);
    setCentralWidget(widget);
}

void MainWindow::newProject()
{
    qDebug()<<"newProject";
}

void MainWindow::openProject()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File..."));
    if (0 == m_treeViewModel) {
        m_treeViewModel = TreeViewModel::get();
    }
    m_treeViewModel->addNetlist(fileName);
    //m_treeView->setModel(m_treeViewModel);
    //expandTreeView();
    //m_treeView->expandAll();
}

void MainWindow::expandTreeView() const
{
    std::list<QModelIndex> indices = m_treeViewModel->getExpandedNodes();
    std::list<QModelIndex>::const_iterator it;
    for (it = indices.begin(); it != indices.end(); ++it)
    {
        m_treeView->setExpanded(*it, true);
    }
}

void MainWindow::saveProject()
{
    qDebug()<<"saveProject";
}

void MainWindow::closeProject()
{
    qDebug()<<"closeProject";
}

void MainWindow::undo()
{
    qDebug()<<"undo";
}

void MainWindow::redo()
{
    qDebug()<<"redo";
}

void MainWindow::cut()
{
    qDebug()<<"cut";
}

void MainWindow::copy()
{
    qDebug()<<"copy";
}

void MainWindow::paste()
{
    qDebug()<<"paste";
}

void MainWindow::about()
{
    qDebug()<<"about";
}

void MainWindow::help()
{
    qDebug()<<"help";
}

int openNetlist(ClientData clientData, Tcl_Interp *interp, int objc,
         Tcl_Obj *const objv[])
{
    if (objc != 2) 
    {
        return TCL_ERROR;
    }
    std::string fileName = objv[1]->bytes;
    TreeViewModel* model = TreeViewModel::get();
    model->addNetlist(QString::fromStdString(fileName));
    
    return TCL_OK;
}

int createNewModule(ClientData clientData, Tcl_Interp *interp, int objc,
         Tcl_Obj *const objv[])
{
    if (objc != 2) 
    {
        return TCL_ERROR;
    }
    std::string moduleName = objv[1]->bytes;
    TreeViewModel* model = TreeViewModel::get();
    model->addModule(moduleName);
    
    return TCL_OK;
}


int listModuleDescs(ClientData clientData, Tcl_Interp *interp, int objc,
         Tcl_Obj *const objv[])
{
    if (objc != 2)
    {
        return TCL_ERROR;
    }
    TreeViewModel* model = TreeViewModel::get();
    boost::shared_ptr<Netlist> netlist = model->getActiveNetlist();
}

int addModuleInstance(ClientData clientData, Tcl_Interp *interp, int objc,
         Tcl_Obj *const objv[])
{
    if (objc != 4) 
    {
        return TCL_ERROR;
    }
    std::string sourceModuleName = objv[1]->bytes;
    std::string moduleDescName = objv[2]->bytes;
    std::string instanceName = objv[3]->bytes;
    
    TreeViewModel* model = TreeViewModel::get();
    model->addModuleInstance(sourceModuleName, moduleDescName, instanceName);

}

int addModulePort(ClientData clientData, Tcl_Interp *interp, int objc,
         Tcl_Obj *const objv[])
{ 
    if (objc != 4) 
    {
        return TCL_ERROR;
    }
    std::string sourceModuleName = objv[1]->bytes;
    std::string portName = objv[2]->bytes;
    std::string portType = objv[3]->bytes;
    
    TreeViewModel* model = TreeViewModel::get();
    model->addModulePort(sourceModuleName, portName, portType);

}


