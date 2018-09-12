#include "treeview_model.h"
#include "../database/module_port.hpp"
#include "../database/module_instance.hpp"

#include <iostream>
#include <QDebug>

TreeViewModel* TreeViewModel::m_model = 0;

TreeViewModel::TreeViewModel(QObject* parent)
    : QStandardItemModel(parent)
{
    m_rootNode = invisibleRootItem();
}

TreeViewModel::~TreeViewModel()
{
}

TreeViewModel* TreeViewModel::get()
{
    return m_model;
}

void TreeViewModel::create()
{
    m_model = new TreeViewModel();
}

std::list<QModelIndex> TreeViewModel::getExpandedNodes() const
{
    return m_expandedNodes;
}

void TreeViewModel::addModulePort(QStandardItem* parentItem, std::map<std::string, boost::shared_ptr<Module_port> > ports)
{
    QStandardItem* inPortsItem = new QStandardItem("In");
    QStandardItem* outPortsItem = new QStandardItem("Out");
    QStandardItem* inOutPortsItem = new QStandardItem("In/Out");
    
    // get module ports
    std::map<std::string, boost::shared_ptr<Module_port> >::const_iterator portIt;
    for (portIt = ports.begin(); portIt != ports.end(); ++portIt)
    {
        QStandardItem* newPortItem = new QStandardItem(QString::fromStdString(portIt->first));
        switch (portIt->second->get_type())
        {
            case IN:
                inPortsItem->appendRow(newPortItem);
                break;
            case OUT:
                outPortsItem->appendRow(newPortItem);
                break;
            case INOUT:
                inOutPortsItem->appendRow(newPortItem);
                break;
        }
    }
    if (inPortsItem->hasChildren()) 
    {
        parentItem->appendRow(inPortsItem);
        m_expandedNodes.push_back(inPortsItem->index());
    }
    if (outPortsItem->hasChildren())
    {
        parentItem->appendRow(outPortsItem);
        m_expandedNodes.push_back(outPortsItem->index());
    }
    if (inOutPortsItem->hasChildren())
    {
        parentItem->appendRow(inOutPortsItem);
        m_expandedNodes.push_back(inOutPortsItem->index());
    }
}

void TreeViewModel::addInstancePort(QStandardItem* parentItem, std::vector<Instance_port> ports)
{
    QStandardItem* inPortsItem = new QStandardItem("In");
    QStandardItem* outPortsItem = new QStandardItem("Out");
    QStandardItem* inOutPortsItem = new QStandardItem("In/Out");
    
    // get instance ports
    std::vector<Instance_port>::const_iterator portIt;
    for (portIt = ports.begin(); portIt != ports.end(); ++portIt)
    {
        QStandardItem* newPortItem = new QStandardItem(QString::fromStdString(portIt->get_name()));
        switch (portIt->get_type())
        {
            case IN:
                inPortsItem->appendRow(newPortItem);
                break;
            case OUT:
                outPortsItem->appendRow(newPortItem);
                break;
            case INOUT:
                inOutPortsItem->appendRow(newPortItem);
                break;
        }
    }
    if (inPortsItem->hasChildren()) 
    {
        parentItem->appendRow(inPortsItem);
        m_expandedNodes.push_back(inPortsItem->index());
    }
    if (outPortsItem->hasChildren())
    {
        parentItem->appendRow(outPortsItem);
        m_expandedNodes.push_back(outPortsItem->index());
    }
    if (inOutPortsItem->hasChildren())
    {
        parentItem->appendRow(inOutPortsItem);
        m_expandedNodes.push_back(inOutPortsItem->index());
    }
}

void TreeViewModel::addNetlist(const QString& netlistPath)
{
    Netlist_builder* netlistBuilder = new Netlist_builder(netlistPath.toStdString());
    netlistBuilder->construct_netlist();
    m_currentNetlist = netlistBuilder->get_netlist();
    
    // adding netlist
    std::string netlistName = m_currentNetlist->get_name();
    m_netlists[netlistName] = m_currentNetlist;
    
    updateModel();
}

void TreeViewModel::updateModel()
{
    //removeRows(0, rowCount());
    
    // show netlist in treeView
    std::string netlistName = m_currentNetlist->get_name();
    QStandardItem* newNetlistItem = new QStandardItem(QString::fromStdString(netlistName));
    m_rootNode->appendRow(newNetlistItem);
    m_expandedNodes.push_back(newNetlistItem->index());

    // get netlist modules
    m_modules = m_currentNetlist->get_modules();
    std::map< std::string, boost::shared_ptr<Module_description> >::const_iterator moduleIt;
    for (moduleIt = m_modules.begin(); moduleIt != m_modules.end(); ++moduleIt)
    {
        QStandardItem* newModuleItem = new QStandardItem(QString::fromStdString("Type " + moduleIt->first));
        newNetlistItem->appendRow(newModuleItem);

        QStandardItem* moduleInstancesItem = new QStandardItem("Instances");
        QStandardItem* modulePortsItem = new QStandardItem("Ports");
        QStandardItem* moduleNetsItem = new QStandardItem("Nets");

        newModuleItem->appendRow(moduleInstancesItem);
        newModuleItem->appendRow(modulePortsItem);
        newModuleItem->appendRow(moduleNetsItem);

        m_expandedNodes.push_back(newModuleItem->index());

        boost::shared_ptr<Module_description> currentModule = moduleIt->second;
        
        // get module instances used to construct this module
        m_moduleInstances = currentModule->get_module_instances();
        std::map<std::string, boost::shared_ptr<Module_instance> >::const_iterator modDescIt;
        for (modDescIt = m_moduleInstances.begin(); modDescIt != m_moduleInstances.end(); ++modDescIt)
        {
            std::string instanceModuleDescName = modDescIt->second->get_description_name();
            QStandardItem* instanceModuleDescItem = new QStandardItem(QString::fromStdString(instanceModuleDescName));
            moduleInstancesItem->appendRow(instanceModuleDescItem);
            m_expandedNodes.push_back(instanceModuleDescItem->index());

            QStandardItem* newModuleInstanceItem = 
                        new QStandardItem(QString::fromStdString(modDescIt->first));
            instanceModuleDescItem->appendRow(newModuleInstanceItem);

            std::vector<Instance_port> instancePorts = modDescIt->second->get_ports();
            QStandardItem* instancePortsItem = new QStandardItem("Ports");
            newModuleInstanceItem->appendRow(instancePortsItem);
            addInstancePort(instancePortsItem, instancePorts);
        }
        
        // get module ports
        std::map<std::string, boost::shared_ptr<Module_port> > ports = currentModule->get_ports();
        addModulePort(modulePortsItem, ports); 

        // get module nets
        std::map<std::string, boost::shared_ptr<Net> > nets = currentModule->get_nets();
        std::map<std::string, boost::shared_ptr<Net> >::const_iterator netIt;
        for (netIt = nets.begin(); netIt != nets.end(); ++netIt)
        {
            QStandardItem* newNetItem = new QStandardItem(QString::fromStdString(netIt->first));
            moduleNetsItem->appendRow(newNetItem);
        }

    }

    Q_EMIT modelChanged();
}

void TreeViewModel::addModule(const std::string& moduleName)
{
    m_currentNetlist->create_new_module(moduleName);
    updateModel();
}

void TreeViewModel::addModuleInstance(const std::string& sourceModule, const std::string& moduleDesc, const std::string&  instanceName)
{
    boost::shared_ptr<Module_description> sourceModuleDesc = m_currentNetlist->get_module(sourceModule);
    if (!sourceModuleDesc)
    {
        return;
    }
    sourceModuleDesc->add_module_instance(moduleDesc, instanceName, std::vector< std::pair< std::string, std::string> >());
    
    updateModel();
}

void TreeViewModel::addModulePort(const std::string& sourceModule, const std::string& portName, const std::string& portType)
{
    boost::shared_ptr<Module_description> sourceModuleDesc = m_currentNetlist->get_module(sourceModule);
    if (!sourceModuleDesc)
    {
        return;
    }
    PortType type;
    if (portType == "IN") 
    {
        type = IN;
    } 
    else if (portType == "OUT") 
    {
        type = OUT;
    }
    else if (portType == "INOUT")
    {
        type = INOUT;
    }

    boost::shared_ptr<Module_port> port(new Module_port(portName, type, sourceModuleDesc.get()));
    sourceModuleDesc->add_port(port);
    
    updateModel();
}

boost::shared_ptr<Netlist> TreeViewModel::getActiveNetlist() const
{
    return m_currentNetlist;
}
