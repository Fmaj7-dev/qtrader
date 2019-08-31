#ifndef TREEMODEL_H
#define TREEMODEL_H

#include "plotting/treeitemtype.h"

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

namespace gui
{
namespace plotting
{

class TreeItem;

class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    TreeModel( const QStringList &headers, const QString &data,
               QObject *parent = nullptr );
    ~TreeModel();

    QVariant data( const QModelIndex &index, int role ) const override;

    TreeItemType getType( const QModelIndex &index ) const;

    int getChildCount( const QModelIndex& index ) const;

    TreeItem* getChild( const QModelIndex& index, int number );

    QVariant headerData( int section, 
                         Qt::Orientation orientation,
                         int role = Qt::DisplayRole ) const override;

    QModelIndex index( int row, 
                       int column,
                       const QModelIndex &parent = QModelIndex() ) const override;

    QModelIndex parent( const QModelIndex &index ) const override;

    int rowCount( const QModelIndex &parent = QModelIndex() ) const override;

    int columnCount( const QModelIndex &parent = QModelIndex() ) const override;

    Qt::ItemFlags flags( const QModelIndex &index ) const override;

    bool setData( const QModelIndex &index, 
                  const QVariant &value,
                  int role = Qt::EditRole ) override;

    bool setHeaderData( int section, 
                        Qt::Orientation orientation,
                        const QVariant &value, 
                        int role = Qt::EditRole ) override;

    bool insertColumns( int position, 
                        int columns,
                        const QModelIndex &parent = QModelIndex() ) override;

    bool removeColumns( int position, 
                        int columns,
                        const QModelIndex &parent = QModelIndex() ) override;

    /* bool insertRows( int position, int rows,
                     const QModelIndex &parent = QModelIndex() ) override; */

    bool removeRows( int position, 
                     int rows,
                     const QModelIndex &parent = QModelIndex() ) override;
    
    /* bool addRow( QVector<QVariant>& data );

    bool addChild( const QModelIndex& index, QVector<QVariant>& data );*/

    bool addLiveSeries( QVector<QVariant>& data );

    bool addSMA( const QModelIndex& index, 
                 QVector<QVariant>& data, 
                 int smaValue );

private:
    //void setupModelData( const QStringList &lines, TreeItem *parent );

    TreeItem *getItem( const QModelIndex &index ) const;

    TreeItem *rootItem;
};
}
}

#endif // TREEMODEL_H
