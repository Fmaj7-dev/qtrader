#ifndef CONFIGTREE_H
#define CONFIGTREE_H

#include <QWidget>
#include <QTreeView>
#include <QLabel>
#include <QVBoxLayout>

class ConfigTree : public QWidget
{
    Q_OBJECT
public:
    ConfigTree();
    virtual ~ConfigTree();

private:
    QTreeView* view;
    QLabel* label;
    QVBoxLayout* layout;
    
};

#endif