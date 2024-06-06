#ifndef QTLAB_H_
#define QT_LAB_H

#include <QMainWindow.h>
#include <QTableWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QLabel>
#include <QDebug>
#include <QRadioButton>
#include <QHeaderView>
#include <QSplitter>
#include <QIcon>
#include <QGraphicsDropShadowEffect>

#include <QPaintEvent>
#include <QPainter>
#include <QRadioButton>

#include "service.h"
#include "observer.h"
#include "MyListModel.h"
#include "MyTableModel.h"

class NotificareGUI : public QWidget, public Observable, public Observer {
    friend class AppGUI;
    friend class Service;
    friend class NotificareReadOnlyGUI;

private:
    Service& srv;

    //butoane
    QPushButton* empty_notificare = new QPushButton{ "&Goleste notificare" };
    QPushButton* generate_notificare = new QPushButton{ "&Genereaza notificare" };
    QPushButton* exit = new QPushButton{ "&Exit" };

    //textboxuri
    QLineEdit* txtNotificareNumar = new QLineEdit;

    //lista
    QListView* lista_notificare = new QListView;
    MyListModel* model = nullptr;


public:
    explicit NotificareGUI(Service& srv) : srv{ srv } {
        srv.addObserver(this);
    };

    void initNotificareGUI();
    void connectNotificareSignals();
    void reloadList(const vector<Tentant>& tentants);
    void update() override {
        reloadList(srv.get_all_notifications());
    }
};


class NotificareReadOnlyGUI : public QWidget, public Observer {
    friend class NotificareGUI;
    Service& srv;
    QListWidget* lista_obiecte = new QListWidget;
public:
    explicit NotificareReadOnlyGUI(Service& service) : srv{ service } {
        initContractReadOnlyGUI();
        srv.addObserver(this);
    }

    void initContractReadOnlyGUI() {
        this->setWindowTitle("Desene notificare");
        /*lista_obiecte = new QListWidget();
        QHBoxLayout* layout = new QHBoxLayout;
        layout->addWidget(lista_obiecte);
        setLayout(layout);*/
    }

    void update() override {
        repaint();
    }

    void reload() {
        lista_obiecte->clear();
        for (const auto& d : srv.get_all_notifications()) {
            lista_obiecte->addItem(QString::fromStdString(d.to_string_print()));
        }
    }

    void paintEvent(QPaintEvent* e) override {
        QPainter p(this);
        srand(time(0));

        int x = -20;
        for (const auto& elem : srv.get_all_notifications()) {
            x += 40;
            int forma = rand() % 4;
            int inaltime = rand() % 130;
            int start_y = rand() % 60;
            QColor color;

            int color_num = rand() % 5;
            switch (color_num) {
                case 0:
                    color = Qt::red;
                    break;
                case 1:
                    color = Qt::blue;
                    break;
                case 2:
                    color = Qt::green;
                    break;
                case 3:
                    color = Qt::yellow;
                    break;
                case 4:
                    color = Qt::cyan;
                    break;
                default:
                    break;
            }

            switch (forma) {
                case 0:
                    p.drawRect(x, start_y, 20, inaltime);
                    break;
                case 1:
                    p.drawEllipse(x, start_y, 20, inaltime);
                    break;
                case 2:
                    p.fillRect(x, start_y, 20, inaltime, color);
                    break;
                default:
                    p.fillRect(x, start_y, 20, inaltime, color);
                    break;
            }
        }
    }

    ~NotificareReadOnlyGUI() {
        srv.removeObserver(this);
    }
};


class AppGUI : public QWidget {

public:
    AppGUI(Service& service) : srv{ service } {
        initGUI();
        notificare = new NotificareGUI(srv);
        notificare->initNotificareGUI();
        notificare->connectNotificareSignals();
        connectSignals();
    }
private:
    MyTableModel* model = nullptr;
    QTableView* table_view = new QTableView;

    Service& srv;
    NotificareGUI* notificare;
    QTableWidget* table_main = new QTableWidget;
    QVBoxLayout* lista_layout = new QVBoxLayout;

    /*
    QWidget* notificare = new QWidget;
    QTableWidget* table = new QTableWidget;
    QListWidget* list = new QListWidget;
    QListWidget* lista_notificari = new QListWidget;
    QVBoxLayout* lista_layout = new QVBoxLayout;
*/

    // butoane
    vector<QPushButton*> vector_btn;
    QPushButton* btn_add = new QPushButton{ "Add" };
    QPushButton* btn_delete = new QPushButton{ "Delete" };
    QPushButton* btn_update = new QPushButton{ "Update" };
    QPushButton* btn_find = new QPushButton{ "Find" };
    QPushButton* btn_undo = new QPushButton{ "Undo" };
    QPushButton* btn_notificare = new QPushButton{ "Notificare" };
    QPushButton* sort_name = new QPushButton{ "Sort by name" };
    QPushButton* sort_surface = new QPushButton{ "Sort by surface" };
    QPushButton* sort_type_surface = new QPushButton{ "Sort by type and surface" };
    QPushButton* filter_number = new QPushButton{ "Filter by number" };
    QPushButton* filter_type = new QPushButton{ "Filter by type" };
    QLineEdit* txtfilter = new QLineEdit;
    QPushButton* exit = new QPushButton{ "Exit" };
    QPushButton* load = new QPushButton{ "Load" };


    /*
    // butoane lista notificari
    QPushButton* btn_add_notificare = new QPushButton{ "Add to the notifications list" };
    QPushButton* btn_delete_notificare = new QPushButton{ "Delete notifications list" };
    QPushButton* btn_generate_notificari = new QPushButton{ "Generate notifications" };
    QPushButton* btn_export_notificari = new QPushButton{ "Export notifications" };
    QPushButton* btn_exit_notificari = new QPushButton{ "Exit" };
*/
    //Butoane pt contract
    QPushButton* open_notificare = new QPushButton{ "Deschide notificare" };
    QPushButton* open_notificare_readonly = new QPushButton{ "Deschide notificare readonly" };
    QPushButton* add_notificare = new QPushButton{ "&Adauga la notificari" };
    QPushButton* export_notificare = new QPushButton{ "&Exporta notificare" };
    QLineEdit* txtNotificareNumber = new QLineEdit;
    QLineEdit* txtNotificareName = new QLineEdit;
    QLineEdit* txtNotificareFile = new QLineEdit;

    // layout
    QLineEdit* txtNumber = new QLineEdit;
    QLineEdit* txtName = new QLineEdit;
    QLineEdit* txtSurface = new QLineEdit;
    QLineEdit* txtType = new QLineEdit;

    /*
    // notificari
    QLineEdit* txtNotificareNumar = new QLineEdit;
    QLineEdit* txtNotificareFile = new QLineEdit;
    QLineEdit* txtNotificareNumber = new QLineEdit;
    QLineEdit* txtNotificareName = new QLineEdit;
*/

   //  void load_list(const vector<Tentant>& tentants);
    void load_table(const vector<Tentant>& tentants);
   //  void load_list_from_table(const vector<Tentant>& tentants);
   //  void notificareGUI();
    void connectSignals();

    void initGUI();

    void clearTextBox();
    void clearNotificareTextBox();
    void uiAdd();
    void uiDelete();
    void uiUpdate();
    void uiFind();
    void uiNotificareAdd();
    void uiFilterNumber();
    void uiFilterType();
    void sortName();
    void sortSurface();
    void sortTypeSurface();


};

#endif // !QTLAB_H_