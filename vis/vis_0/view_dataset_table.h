#ifndef VIEW_DATASET_TABLE_H
#define VIEW_DATASET_TABLE_H

//
#include "common.h"

//
class dataset_db;

//
class view_dataset_table : public QWidget
{
    Q_OBJECT
public:
    explicit view_dataset_table(QWidget *parent = 0);

    //
    void restart_table( dataset_db *db );
    
    //
    void select_row( int row );

    //
    void clear();
signals:
    
public slots:

private:

    //
    void label_model();
    void label_column_categories( int col );
    bool get_label( int val, QString col_name, QString& new_val );

    //
    QHBoxLayout *_hbox;

    //
    QSqlTableModel *_table_model;
    QTableView *_table_view;

    //
    dataset_db* _ref_db;

};

#endif // VIEW_DATASET_TABLE_H
