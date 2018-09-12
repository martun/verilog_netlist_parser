#ifndef TREEVIEW_MODEL_H
#define TREEVIEW_MODEL_H

#include "../database/netlist_builder.hpp"
#include "../database/module_description.hpp"
#include "../database/module_port.hpp"
#include "../database/instance_port.hpp"

#include <QDebug>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QModelIndex>

#include <map>

class TreeViewModel
    : public QStandardItemModel
{
    Q_OBJECT;

public:
    static TreeViewModel* m_model;

public:
    static TreeViewModel* get();
    static void create(); 

    TreeViewModel(QObject* parent = 0);
    ~TreeViewModel();

    std::list<QModelIndex> getExpandedNodes() const;
    
    void updateModel();

    void addNetlist(const QString& netlistPath);
    void addModule(const std::string& moduleName);
    void addModuleInstance(const std::string& sourceModule, const std::string& moduleDesc, const std::string&  instanceName); 
    void addModulePort(const std::string& sourceModule, const std::string& portName, const std::string& portType);

    void addModulePort(QStandardItem* item, std::map<std::string, boost::shared_ptr<Module_port> > ports);
    void addInstancePort(QStandardItem* item, std::vector<Instance_port> ports);

    boost::shared_ptr<Netlist> getActiveNetlist() const;


signals:
    void modelChanged();

private:
    QStandardItem* m_rootNode;
    std::list<QModelIndex> m_expandedNodes;
    boost::shared_ptr<Netlist> m_currentNetlist;
    std::map<std::string, boost::shared_ptr<Netlist> > m_netlists;
    std::map< std::string, boost::shared_ptr<Module_description> > m_modules;
    std::map<std::string, boost::shared_ptr<Module_instance> > m_moduleInstances;
};

#endif // TREEVIEW_MODEL_H
