#include "plotting/treemodel.h"
#include "plotting/treeitem.h"
#include "utils/logger.h"

#include <QtWidgets>

using namespace gui;
using namespace gui::plotting;

TreeModel::TreeModel( const QStringList &headers, const QString &data, QObject *parent )
    : QAbstractItemModel( parent )
{
    QVector< QVariant > rootData;
    for ( const QString &header : headers )
        rootData << header;

    rootItem = new TreeItem( rootData );
    //setupModelData( data.split('\n'), rootItem );
}

TreeModel::~TreeModel()
{
    delete rootItem;
}

int TreeModel::columnCount( const QModelIndex &parent ) const
{
    Q_UNUSED( parent );
    return rootItem->columnCount();
}

QVariant TreeModel::data( const QModelIndex &index, int role ) const
{
    if ( !index.isValid() )
        return QVariant();

    if ( role != Qt::DisplayRole && role != Qt::EditRole )
        return QVariant();

    TreeItem *item = getItem( index );

    return item->data( index.column() );
}

TreeItemType TreeModel::getType( const QModelIndex &index ) const
{
    if ( !index.isValid() )
        return TreeItemType::DEFAULT;

    TreeItem *item = getItem( index );

    return item->getItemType();
}

int TreeModel::getChildCount( const QModelIndex& index ) const
{
    if ( !index.isValid() )
        return 0;

    TreeItem *item = getItem( index );

    return item->childCount();
}

TreeItem* TreeModel::getChild( const QModelIndex& index, int number )
{
    if ( !index.isValid() )
        return nullptr;

    TreeItem* item = getItem( index );
    return item->child( number );
}

Qt::ItemFlags TreeModel::flags( const QModelIndex &index ) const
{
    if ( !index.isValid() )
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | QAbstractItemModel::flags( index );
}

TreeItem *TreeModel::getItem( const QModelIndex &index ) const
{
    if ( index.isValid() ) 
    {
        TreeItem *item = static_cast<TreeItem*>( index.internalPointer() );
        if ( item )
            return item;
    }
    return rootItem;
}

QVariant TreeModel::headerData( int section, Qt::Orientation orientation,
                                int role ) const
{
    if ( orientation == Qt::Horizontal && role == Qt::DisplayRole )
        return rootItem->data( section );

    return QVariant();
}

QModelIndex TreeModel::index( int row, int column, const QModelIndex &parent ) const
{
    if ( parent.isValid() && parent.column() != 0 )
        return QModelIndex();

    TreeItem *parentItem = getItem( parent );
    if (!parentItem)
        return QModelIndex();

    TreeItem *childItem = parentItem->child( row );
    if (childItem)
        return createIndex( row, column, childItem );
    return QModelIndex();
}

bool TreeModel::insertColumns( int position, int columns, const QModelIndex &parent )
{
    beginInsertColumns( parent, position, position + columns - 1 );
    const bool success = rootItem->insertColumns( position, columns );
    endInsertColumns();

    return success;
}

/* bool TreeModel::insertRows( int position, int rows, const QModelIndex &parent )
{
    TreeItem *parentItem = getItem( parent );
    if ( !parentItem )
        return false;

    beginInsertRows( parent, position, position + rows - 1 );
    const bool success = parentItem->insertChildren( position,
                                                     rows,
                                                     rootItem->columnCount() );
    endInsertRows();

    return success;
} */

QModelIndex TreeModel::parent( const QModelIndex &index ) const
{
    if ( !index.isValid() )
        return QModelIndex();

    TreeItem *childItem = getItem( index );
    TreeItem *parentItem = childItem ? childItem->parent() : nullptr;

    if ( parentItem == rootItem || !parentItem )
        return QModelIndex();

    return createIndex( parentItem->childNumber(), 0, parentItem );
}

bool TreeModel::removeColumns( int position, int columns, const QModelIndex &parent )
{
    beginRemoveColumns( parent, position, position + columns - 1 );
    const bool success = rootItem->removeColumns( position, columns );
    endRemoveColumns();

    if (rootItem->columnCount() == 0)
        removeRows( 0, rowCount() );

    return success;
}

bool TreeModel::removeRows( int position, int rows, const QModelIndex &parent )
{
    TreeItem *parentItem = getItem( parent );
    if ( !parentItem )
        return false;

    beginRemoveRows( parent, position, position + rows - 1 );
    const bool success = parentItem->removeChildren( position, rows );
    endRemoveRows();

    return success;
}

int TreeModel::rowCount( const QModelIndex &parent ) const
{
    const TreeItem *parentItem = getItem( parent );

    return parentItem ? parentItem->childCount() : 0;
}

bool TreeModel::setData( const QModelIndex &index, const QVariant &value, int role )
{
    if ( role != Qt::EditRole )
        return false;

    TreeItem *item = getItem( index );
    bool result = item->setData( index.column(), value );

    if ( result )
        emit dataChanged(index, index, { Qt::DisplayRole, Qt::EditRole });

    return result;
}

bool TreeModel::setHeaderData( int section, Qt::Orientation orientation,
                               const QVariant &value, int role )
{
    if ( role != Qt::EditRole || orientation != Qt::Horizontal )
        return false;

    const bool result = rootItem->setData( section, value );

    if (result)
        emit headerDataChanged( orientation, section, section );

    return result;
}

/* void TreeModel::setupModelData( const QStringList &lines, TreeItem *parent )
{
    QVector<TreeItem*> parents;
    QVector<int> indentations;
    parents << parent;
    indentations << 0;

    int number = 0;

    while (number < lines.count()) 
    {
        int position = 0;
        while (position < lines[number].length()) 
        {
            if ( lines[number].at(position) != ' ' )
                break;
            ++position;
        }

        const QString lineData = lines[number].mid( position ).trimmed();

        if ( !lineData.isEmpty() )
        {
            // Read the column data from the rest of the line.
            const QStringList columnStrings = lineData.split('\t', QString::SkipEmptyParts);
            QVector<QVariant> columnData;
            columnData.reserve(columnStrings.size());
            for ( const QString &columnString : columnStrings )
                columnData << columnString;

            if ( position > indentations.last() )
            {
                // The last child of the current parent is now the new parent
                // unless the current parent has no children.

                if (parents.last()->childCount() > 0) 
                {
                    parents << parents.last()->child(parents.last()->childCount()-1);
                    indentations << position;
                }
            } else 
            {
                while (position < indentations.last() && parents.count() > 0) 
                {
                    parents.pop_back();
                    indentations.pop_back();
                }
            }

            // Append a new item to the current parent's list of children.
            TreeItem *parent = parents.last();
            parent->insertChildren(parent->childCount(), 1, rootItem->columnCount());

            for (int column = 0; column < columnData.size(); ++column)
                parent->child(parent->childCount() - 1)->setData(column, columnData[column]);
        }
        ++number;
    }
} */

bool TreeModel::addLiveSeries( QVector<QVariant>& data )
{
    TreeItem *parent = rootItem;

    parent->insertChildren( parent->childCount(), 1, rootItem->columnCount(), TreeItemType::LIVE_SERIES );
    for ( int column = 0; column < data.size(); ++column )
        parent->child( parent->childCount() - 1)->setData(column, data[column] );    

    return true;
}

bool TreeModel::addSMA( const QModelIndex& index, 
                        QVector<QVariant>& data, 
                        int smaValue )
{
    using namespace core;
    using namespace utils;
    
    TreeItem* parent = getItem( index );

    beginInsertRows( index, parent->childCount(), parent->childCount() );

    parent->insertChildren( parent->childCount(), 
                            1, 
                            rootItem->columnCount(), 
                            TreeItemType::SMA );

    SMATreeItem* item = static_cast<SMATreeItem*>(parent->child( parent->childCount() - 1) );

    for ( int column = 0; column < data.size(); ++column )
        //parent->child( parent->childCount() - 1)->setData(column, data[ column ] );    
        item->setData(column, data[ column ] );

    item->setSmaValue( smaValue );

    endInsertRows();

    // test
    /*{
        log("begin test---");
        TreeItem* treeitem = getChild( index, 0 );
        SMATreeItem* smaTreeItem = dynamic_cast<SMATreeItem*> ( treeitem );

        if( smaTreeItem )
        {
            TreeItemType type = smaTreeItem->getItemType();
            if( type == TreeItemType::LIVE_SERIES )
                log("live_series type ");
            else if ( type == TreeItemType::SMA )
                log(" sma type ");

            log("sma value: ", smaTreeItem->getSmaValue() );
        }
        log("end test---");
    }*/

    return true;
}