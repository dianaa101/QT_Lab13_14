#ifndef MYLISTMODEL_H_
#define MYLISTMODEL_H_

#include <QAbstractListModel>
#include <vector>
#include "service.h"
#include <sstream>

using namespace std;

class MyListModel : public QAbstractListModel {
    vector<Tentant> tentants;
public:
    MyListModel(const vector<Tentant>& tentants) : tentants{ tentants } {}

    int rowCount(const QModelIndex& parent = QModelIndex{}) const override {
        return tentants.size();
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole) {
            const Tentant& d = tentants[index.row()];
            stringstream ss;
            ss << d.get_number() << " - name. " << d.get_name();
            return QString::fromStdString(ss.str());
        }
        if (role == Qt::UserRole) {
            const Tentant& d = tentants[index.row()];
            return QString::fromStdString(d.to_string_print());
        }
        return QVariant{};
    }
};

#endif // MYLISTMODEL_H_
