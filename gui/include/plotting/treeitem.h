#ifndef TREEITEM_H
#define TREEITEM_H

#include "plotting/treeitemtype.h"

#include <QVariant>
#include <QVector>

namespace gui
{
namespace plotting
{

class TreeItem
{
public:
    explicit TreeItem( const QVector<QVariant> &data, 
                       TreeItem *parent = nullptr,
                       TreeItemType type = TreeItemType::DEFAULT );

    virtual ~TreeItem();

    TreeItem *child( int number );

    int childCount() const;

    int columnCount() const;

    QVariant data( int column ) const;

    bool insertChildren( int position, 
                         int count, 
                         int columns, 
                         const gui::plotting::TreeItemType& type );

    bool insertColumns( int position, int columns );

    TreeItem *parent();

    bool removeChildren( int position, int count );

    bool removeColumns( int position, int columns );

    int childNumber() const;

    bool setData( int column, const QVariant &value );

    TreeItemType getItemType() const;

private:
    QVector< TreeItem* > childItems;

    QVector< QVariant > itemData;
    
    TreeItem* parentItem;

    gui::plotting::TreeItemType type_;
};

class LiveSeriesTreeItem : public TreeItem
{
public:
    LiveSeriesTreeItem( const QVector<QVariant> &data, 
                        TreeItem *parent = nullptr )
    :TreeItem( data, parent, TreeItemType::LIVE_SERIES )
    {}
};

class SMATreeItem : public TreeItem
{
    int smaValue;

public:
    SMATreeItem( const QVector<QVariant> &data, 
                 TreeItem *parent = nullptr )
    :TreeItem( data, parent, TreeItemType::SMA )
    {}

    void setSmaValue( int value )
    {
        smaValue = value;
    }

    int getSmaValue( ) const
    {
        return smaValue;
    }
};

}
}

#endif // TREEITEM_H
