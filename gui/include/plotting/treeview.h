#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QTreeView>
#include <QItemSelection>

class TreeView : public QTreeView
{
  Q_OBJECT

public:
  void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
  {
    QTreeView::selectionChanged( selected, deselected );
    emit valueChanged(selected, deselected);
  }

signals:
    void valueChanged(const QItemSelection& current, const QItemSelection& previous);

};

#endif
