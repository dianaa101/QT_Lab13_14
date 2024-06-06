#ifndef MYTABLEMODEL_H_
#define MYTABLEMODEL_H_

#include <QAbstractTableModel>
#include <QAbstractItemView>
#include <iostream>
#include <vector>

#include "domain.h"
using std::vector;

class MyTableModel : public QAbstractTableModel {
    vector<Tentant> tentants;
public:
    MyTableModel(const vector<Tentant>& tentants) : tentants{ tentants } {}

    int rowCount(const QModelIndex& parent = QModelIndex{}) const override {
        return tentants.size();
    }

    int columnCount(const QModelIndex& parent = QModelIndex{}) const override {
        return 4;
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole) {
            const Tentant& d = tentants[index.row()];
            switch (index.column()) {
                case 0:
                    return QString::number(d.get_number());
                case 1:
                    return QString::fromStdString(d.get_name());
                case 2:
                    return QString::number(d.get_surface());
                case 3:
                    return QString::fromStdString(d.get_type());
                default:
                    break;
            }
        }
        return QVariant{};
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
            switch (section) {
                case 0:
                    return "Number";
                case 1:
                    return "Name";
                case 2:
                    return "Surface";
                case 3:
                    return "Type";
                default:
                    break;
            }
        }
        else if (role == Qt::DisplayRole && orientation == Qt::Vertical) {
            return section + 1;
        }
        return QVariant{};
    }
    Tentant get_tentant(const vector<Tentant>& tentants) {
        this->tentants = tentants;
        QModelIndex topLeft = createIndex(0, 0);
        QModelIndex bottomRight = createIndex(rowCount(), columnCount());
        emit dataChanged(topLeft, bottomRight); // notify ca la observer
        emit layoutChanged();
    }
};

#endif // MYTABLEMODEL_H_
