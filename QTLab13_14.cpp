#include "QTLab13_14.h"


std::string trim(const std::string &str) {
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}


void AppGUI::initGUI() {

    vector_btn.clear();
    this->setWindowTitle("Aplicatie ~ Administrator bloc");
    QPalette palette = QPalette();
    palette.setColor(QPalette::Window, "#BB8FCE");

    QLinearGradient gradient(this->width() / 2, 0, this->width(), 0);
    gradient.setColorAt(0, QColor("#BB8FCE"));
    gradient.setColorAt(1, QColor("#AF7AC5"));

    palette.setBrush(QPalette::Window, QBrush(gradient));

    // fonts
    QFont font = QFont("Helvetica", 12, 10, false);
    QFont boldFont = font;
    boldFont.setBold(true);

    this->setAutoFillBackground(true); //
    this->setPalette(palette);
    this->setFont(font);

    //Layout principal
    QHBoxLayout* mainLayout = new QHBoxLayout;
    setLayout(mainLayout);

    //layout lista
    //layout stanga

    mainLayout->addLayout(lista_layout, 1);
    lista_layout->addSpacing(20);
    QLabel* listaLabel = new QLabel("Tenants table");
    listaLabel->setAlignment(Qt::AlignCenter);
    listaLabel->setFont(boldFont);

    lista_layout->addWidget(listaLabel, 1);

    auto s = srv.raport();

    table->resizeColumnsToContents();
    table->setMinimumSize(500, 200);
    lista_layout->addWidget(table, 2);

    lista_layout->addSpacing(20);
    QLabel* infoLabel = new QLabel("Tenants list");
    infoLabel->setAlignment(Qt::AlignCenter);
    infoLabel->setFont(boldFont);

    lista_layout->addWidget(infoLabel, 1);

    //size the list like the table
    list->setMinimumSize(500, 200);
    lista_layout->addWidget(list, 2);

    // layout operatii
    QVBoxLayout* operatiiLayout = new QVBoxLayout; //layout dreapta

    mainLayout->addLayout(operatiiLayout, 1);

    QFormLayout* formLayout = new QFormLayout;
    operatiiLayout->addLayout(formLayout);

    formLayout->addRow(new QLabel{ "Number: " }, txtNumber);
    formLayout->addRow(new QLabel{ "Name: " }, txtName);
    formLayout->addRow(new QLabel{ "Surface: " }, txtSurface);
    formLayout->addRow(new QLabel{ "Type: " }, txtType);

    QHBoxLayout* actiuniLayout = new QHBoxLayout;
    operatiiLayout->addLayout(actiuniLayout);

    actiuniLayout->addWidget(btn_add);
    actiuniLayout->addWidget(btn_delete);
    actiuniLayout->addWidget(btn_update);
    actiuniLayout->addWidget(btn_find);

    QVBoxLayout* sortLayout = new QVBoxLayout;
    operatiiLayout->addLayout(sortLayout);
    sortLayout->addSpacing(20);

    QLabel* sortLabel = new QLabel("Sorting type");
    sortLabel->setAlignment(Qt::AlignCenter);
    sortLabel->setFont(boldFont);

    sortLayout->addWidget(sortLabel, 1);

    sortLayout->addWidget(sort_name);
    sortLayout->addWidget(sort_surface);

    sortLayout->addWidget(sort_type_surface);
    sortLayout->addSpacing(20);

    QLabel* filtrareLabel = new QLabel("Filters");
    filtrareLabel->setAlignment(Qt::AlignCenter);
    filtrareLabel->setFont(boldFont);

    sortLayout->addWidget(filtrareLabel, 1);

    QFormLayout* filtrareFormLayout = new QFormLayout;
    sortLayout->addLayout(filtrareFormLayout);
    txtfilter->setStyleSheet("QLineEdit{font-size: 16px;font-weight: 500;border: 1px solid transparent;border-radius: 4px;padding: 4px 6px;}");
    filtrareFormLayout->addRow(new QLabel{ "Input: " }, txtfilter);

    QHBoxLayout* filtrareLayout = new QHBoxLayout;
    operatiiLayout->addLayout(filtrareLayout);

    filtrareLayout->addWidget(filter_number);
    filtrareLayout->addWidget(filter_type);

    lista_layout->addWidget(load);

    lista_layout->addSpacing(20);
    QLabel* tipLabel = new QLabel("Tenants type");
    tipLabel->setAlignment(Qt::AlignCenter);
    tipLabel->setFont(boldFont);
    lista_layout->addWidget(tipLabel);
    for (const auto& rap : s) {
        QPushButton* btn = new QPushButton{ QString::fromStdString(rap.first) };
        vector_btn.push_back(btn);
    }

    for (const auto& btn : vector_btn) {
        QGraphicsDropShadowEffect* btnShadowEffect = new QGraphicsDropShadowEffect(this);
        btnShadowEffect->setOffset(2, 2);
        btn->setGraphicsEffect(btnShadowEffect);
        lista_layout->addWidget(btn);
    }

    QGraphicsDropShadowEffect* exitShadowEffect = new QGraphicsDropShadowEffect(this);
    exitShadowEffect->setOffset(2, 2);
    exit->setGraphicsEffect(exitShadowEffect);
    operatiiLayout->addSpacing(20);
    operatiiLayout->addWidget(exit);

}

void AppGUI::notificareGUI() {
    notificare->setWindowTitle("Setare notificare");

    QPalette palette_notificare = QPalette();
    QLinearGradient gradient(this->width() / 2, 0, this->width(), 0);
    gradient.setColorAt(0, QColor("#BB8FCE"));
    gradient.setColorAt(1, QColor("#AF7AC5"));

    palette_notificare.setBrush(QPalette::Window, QBrush(gradient));
    notificare->setAutoFillBackground(true);

    notificare->setPalette(palette_notificare);
    notificare->setFont(QFont("Helvetica", 12, 10, false));

    QHBoxLayout* Layout = new QHBoxLayout;
    notificare->setLayout(Layout);

    QVBoxLayout* notificareLayout = new QVBoxLayout;
    Layout->addLayout(notificareLayout);

    QLabel* notificareLabel= new QLabel("Notificare");
    notificareLabel->setAlignment(Qt::AlignCenter);

    QFont font = QFont("Helvetica", 12, 10, false);
    QFont boldFont = font;
    boldFont.setBold(true);
    notificareLabel->setFont(boldFont);

    notificareLayout->addWidget(notificareLabel);
    notificareLayout->addWidget(btn_delete_notificare);
    notificareLayout->addSpacing(20);

    QFormLayout* genereazaLayout = new QFormLayout;
    notificareLayout->addLayout(genereazaLayout);

    txtNotificareNumber->setStyleSheet("QLineEdit{font-size: 16px;font-weight: 500;border: 1px solid transparent;border-radius: 4px;padding: 4px 6px;}");
    txtNotificareName->setStyleSheet("QLineEdit{font-size: 16px;font-weight: 500;border: 1px solid transparent;border-radius: 4px;padding: 4px 6px;}");
    genereazaLayout->addRow(new QLabel{ "Denumire: " }, txtNotificareNumber);
    genereazaLayout->addRow(new QLabel{ "Profesor: " }, txtNotificareName);

    notificareLayout->addWidget(btn_add_notificare);
    notificareLayout->addSpacing(20);

    QLabel* genereazaNotificareLabel = new QLabel("Genereaza notificare");
    genereazaNotificareLabel->setAlignment(Qt::AlignCenter);
    genereazaNotificareLabel->setFont(boldFont);
    notificareLayout->addWidget(genereazaNotificareLabel);
    QFormLayout* genereazaNotificareLayout = new QFormLayout;
    notificareLayout->addLayout(genereazaNotificareLayout);

    txtNotificareNumar->setStyleSheet("QLineEdit{font-size: 16px;font-weight: 500;border: 1px solid transparent;border-radius: 4px;padding: 4px 6px;}");
    genereazaNotificareLayout->addRow(new QLabel{ "Numar notificari: " }, txtNotificareNumar);
    notificareLayout->addWidget(btn_generate_notificari);
    notificareLayout->addSpacing(20);

    QLabel* exportaNotificareLabel = new QLabel("Exporta notificare");
    exportaNotificareLabel->setAlignment(Qt::AlignCenter);
    exportaNotificareLabel->setFont(boldFont);
    notificareLayout->addWidget(exportaNotificareLabel);
    QFormLayout* exportLayout = new QFormLayout;
    notificareLayout->addLayout(exportLayout);

    txtNotificareFile->setStyleSheet("QLineEdit{font-size: 16px;font-weight: 500;border: 1px solid transparent;border-radius: 4px;padding: 4px 6px;}");
    exportLayout->addRow(new QLabel{ "Nume fisier: " }, txtNotificareFile);

    notificareLayout->addWidget(btn_export_notificari);

    QVBoxLayout* notificareOperatiiLayout = new QVBoxLayout;
    Layout->addLayout(notificareOperatiiLayout);

    notificareOperatiiLayout->addWidget(lista_notificari);

    notificareOperatiiLayout->addWidget(btn_exit_notificari);
}

void AppGUI::load_table(const vector<Tentant>& tentant) {
    this->table->clearContents();
    this->table->setColumnCount(5);
    this->table->setRowCount(tentant.size() + 1);

    int nr_linie = 0;
    table->verticalHeader()->setVisible(false);
    table->horizontalHeader()->setVisible(false);
    table->setItem(nr_linie, 0, new QTableWidgetItem("Nr."));
    table->setItem(nr_linie, 1, new QTableWidgetItem("Number"));
    table->setItem(nr_linie, 2, new QTableWidgetItem("Name"));
    table->setItem(nr_linie, 3, new QTableWidgetItem("Surface"));
    table->setItem(nr_linie, 4, new QTableWidgetItem("Type"));

    nr_linie++;

    for (const auto& Tentant : tentant) {
        table->setItem(nr_linie, 0, new QTableWidgetItem(QString::number(nr_linie)));
        table->setItem(nr_linie, 1, new QTableWidgetItem(QString::number(Tentant.get_number())));
        table->setItem(nr_linie, 2, new QTableWidgetItem(QString::fromStdString(Tentant.get_name())));
        table->setItem(nr_linie, 3, new QTableWidgetItem(QString::number(Tentant.get_surface())));
        table->setItem(nr_linie, 4, new QTableWidgetItem(QString::fromStdString(Tentant.get_type())));
        nr_linie++;
    }
}

void AppGUI::load_list_from_table(const vector<Tentant>& tentants) {
    list->clear();
    int index = 0;
    for (const auto& tentant : tentants) {
        index++;
        list->addItem(QString::fromStdString(std::to_string(index) + " - number " + std::to_string(tentant.get_number()) + "  - name " + tentant.get_name() + "  - surface " + std::to_string(tentant.get_surface()) + "  - type " + tentant.get_type()));
    }
}

void AppGUI::load_list(const vector<Tentant>& tentants) {
    lista_notificari->clear();
    for (const auto& tentant : tentants) {
        lista_notificari->addItem(QString::fromStdString(tentant.get_number() + " - name " + tentant.get_name()));
    }
}

void AppGUI::clearNotificareTextBox() {
    txtNotificareNumber->clear();
    txtNotificareName->clear();
}

void AppGUI::uiNotificareAdd() {
    int number = txtNotificareNumber->text().toInt();
    string name = txtNotificareName->text().toStdString();
    QMessageBox msg;

    auto found = srv.filter_number(number);
    if (found.empty()) {
        msg.warning(notificare, "Warning", "Tenant doesn't exist!");
        clearNotificareTextBox();
        return;
    }

    if (found.size() == 1) {
        try {
            srv.add_notificare_srv(number, found[0].get_name(), found);
        }
        catch (NotificareException& mesaj) {
            msg.warning(notificare, "Warning", QString::fromStdString(mesaj.get_mesaj()));
        }
        catch (RepoException& mesaj) {
            msg.warning(notificare, "Warning", QString::fromStdString(mesaj.get_mesaj()));
        }
        catch (ValidatorException& mesaj) {
            msg.warning(notificare, "Warning", QString::fromStdString(mesaj.get_mesaj()));
        }
    }
    else {
        if (name != "") {
            try {
                srv.add_notificare_srv(number, name, found);
            }
            catch (NotificareException& mesaj) {
                msg.warning(notificare, "Warning", QString::fromStdString(mesaj.get_mesaj()));
            }
            catch (RepoException& mesaj) {
                msg.warning(notificare, "Warning", QString::fromStdString(mesaj.get_mesaj()));
            }
            catch (ValidatorException& mesaj) {
                msg.warning(notificare, "Warning", QString::fromStdString(mesaj.get_mesaj()));
            }
        }
        else {
            msg.warning(notificare, "Warning", "Introduceti numele!");
        }
    }
    clearNotificareTextBox();
    load_list(srv.get_all_notifications());
}

void AppGUI::clearTextBox() {
    txtNumber->clear();
    txtName->clear();
    txtSurface->clear();
    txtType->clear();
}

void AppGUI::uiAdd() {
    string number = txtNumber->text().toStdString();
    string name = txtName->text().toStdString();
    string surface = txtSurface->text().toStdString();
    string type = txtType->text().toStdString();
    QMessageBox msgBox;

    trim(number);
    trim(surface);

    qDebug() << number << name;

    int correct_number;
    try {
        correct_number = stoi(number);
    }
    catch (std::invalid_argument& mesaj) {
        msgBox.warning(this, "Warning", "Numarul trebuie sa fie corect");
        return;
    }

    int correct_surface;
    try {
        correct_surface = stoi(surface);
    }
    catch (std::invalid_argument& mesaj) {
        msgBox.warning(this, "Warning", "Surafata trebuie sa fie un numar corect");
        return;
    }

    try {
        srv.add_service(correct_number, name, correct_surface, type);
    }
    catch (RepoException& mesaj) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(mesaj.get_mesaj()));
    }
    catch (ValidatorException& mesaj) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(mesaj.get_mesaj()));
    }

    clearTextBox();
    load_table(srv.get_all());
    load_list_from_table(srv.get_all());
}

void AppGUI::uiDelete() {
    string number = txtNumber->text().toStdString();
    string name = txtName->text().toStdString();
    QMessageBox msgBox;

    trim(number);

    qDebug() << number << name;

    int correct_number;
    try {
        correct_number = stoi(number);
    }
    catch (std::invalid_argument& mesaj) {
        msgBox.warning(this, "Warning", "Numarul trebuie sa fie corect");
        return;
    }

    try {
        srv.delete_service(correct_number, name);
    }
    catch (RepoException& mesaj) {
        msgBox.warning(this, "Warning", QString::fromStdString(mesaj.get_mesaj()));
    }
    catch (ValidatorException& mesaj) {
        msgBox.warning(this, "Warning", QString::fromStdString(mesaj.get_mesaj()));
    }

    clearTextBox();
    load_table(srv.get_all());
    load_list_from_table(srv.get_all());
}

void AppGUI::uiUpdate() {
    string number = txtNumber->text().toStdString();
    string name = txtName->text().toStdString();
    string surface = txtSurface->text().toStdString();
    string type = txtType->text().toStdString();
    QMessageBox msgBox;

    trim(number);
    trim(surface);

    qDebug() << number << name;

    int correct_number;
    try {
        correct_number = stoi(number);
    }
    catch (std::invalid_argument& mesaj) {
        msgBox.warning(this, "Warning", "Numarul trebuie sa fie corect");
        return;
    }

    int correct_surface;
    try {
        correct_surface = stoi(surface);
    }
    catch (std::invalid_argument& mesaj) {
        msgBox.warning(this, "Warning", "Surafata trebuie sa fie un numar corect");
        return;
    }

    try {
        srv.update_service(correct_number, name, correct_surface, type);
    }
    catch (RepoException& mesaj) {
        msgBox.warning(this, "Warning", QString::fromStdString(mesaj.get_mesaj()));
    }
    catch (ValidatorException& mesaj) {
        msgBox.warning(this, "Warning", QString::fromStdString(mesaj.get_mesaj()));
    }

    clearTextBox();
    load_table(srv.get_all());
    load_list_from_table(srv.get_all());
}

void AppGUI::uiFind() {
    string number = txtNumber->text().toStdString();
    string name = txtName->text().toStdString();
    QMessageBox msgBox;

    trim(number);

    qDebug() << number << name;

    int correct_number;
    try {
        correct_number = stoi(number);
    }
    catch (std::invalid_argument& mesaj) {
        msgBox.warning(this, "Warning", "Numarul trebuie sa fie corect");
        return;
    }
    try {
        Tentant tentant = srv.find_service(correct_number, name);
        qDebug() << tentant.to_string_print();

        vector<Tentant> tentants;
        tentants.push_back(tentant);

        clearTextBox();
        load_table(tentants);
        load_list_from_table(tentants);
    }
    catch (RepoException& mesaj) {
        msgBox.warning(this, "Warning", QString::fromStdString(mesaj.get_mesaj()));
    }
    catch (ValidatorException& mesaj) {
        msgBox.warning(this, "Warning", QString::fromStdString(mesaj.get_mesaj()));
    }
    txtNumber->clear();
    txtName->clear();
}

void AppGUI::sortName() {
    vector<Tentant> tentants = srv.sort_name();
    load_table(tentants);
    load_list_from_table(tentants);
}

void AppGUI::sortSurface() {
    vector<Tentant> tentants = srv.sort_surface();
    load_table(tentants);
    load_list_from_table(tentants);
}

void AppGUI::sortTypeSurface() {
    vector<Tentant> tentants = srv.sort_type_surface();
    load_table(tentants);
    load_list_from_table(tentants);
}

void AppGUI::uiFilterNumber() {
    string number = txtfilter->text().toStdString();
    int correct_number;
    QMessageBox msgBox;

    trim (number);

    try {
        correct_number = stoi(number);
    }
    catch (std::invalid_argument& mesaj) {
        msgBox.warning(this, "Warning", "Input invalid!!");
        txtfilter->clear();
        return;
    }

    vector<Tentant> tentants = srv.filter_number(correct_number);
    for (const auto& tentant : tentants) {
        qDebug() << tentant.to_string_print();
    }

    txtfilter->clear();
    load_table(tentants);
    load_list_from_table(tentants);
}

void AppGUI::uiFilterType() {
    string type = txtfilter->text().toStdString();
    qDebug() << type;

    vector<Tentant> tentants = srv.filter_type(type);
    for (const auto& tentant : tentants) {
        qDebug() << tentant.to_string_print();
    }

    txtfilter->clear();
    load_table(tentants);
    load_list_from_table(tentants);
}

void AppGUI::connectSignals() {
    QMessageBox msgBox;

    QObject::connect(exit, &QPushButton::clicked, [&]() {
        QMessageBox exitMessageBox;

        exitMessageBox.setWindowTitle("Iesire");
        exitMessageBox.setText("Goodbye!");

        exitMessageBox.exec();
        this->close();
    });

    QObject::connect(load, &QPushButton::clicked, [&]() {
        this->load_table(srv.get_all());
        this->load_list_from_table(srv.get_all());
    });

    for (const auto& btn : vector_btn) {
        QObject::connect(btn, &QPushButton::clicked, [&]() {
            for (const auto& rap : srv.raport()) {
                if (btn->text().toStdString() == rap.first) {
                    //write in the information box the number of disciplines of the selected type
                    QMessageBox msg;
                    msg.information(this, "Raport", QString::fromStdString(rap.first) + " - " + QString::number(rap.second.get_count()));
                }
            }
        });
    }

    QObject::connect(btn_add, &QPushButton::clicked, this, &AppGUI::uiAdd);
    QObject::connect(btn_delete, &QPushButton::clicked, this, &AppGUI::uiDelete);
    QObject::connect(btn_update, &QPushButton::clicked, this, &AppGUI::uiUpdate);
    QObject::connect(btn_find, &QPushButton::clicked, this, &AppGUI::uiFind);

    QObject::connect(sort_name, &QRadioButton::clicked, this, &AppGUI::sortName);
    QObject::connect(sort_surface, &QRadioButton::clicked, this, &AppGUI::sortSurface);
    QObject::connect(sort_type_surface, &QRadioButton::clicked, this, &AppGUI::sortTypeSurface);

    QObject::connect(filter_number, &QPushButton::clicked, this, &AppGUI::uiFilterNumber);
    QObject::connect(filter_type, &QPushButton::clicked, this, &AppGUI::uiFilterType);

    QObject::connect(btn_undo, &QPushButton::clicked, [&]() {
        try {
            srv.undo();
        }
        catch (RepoException& mesaj) {
            msgBox.warning(this, "Warning", QString::fromStdString(mesaj.get_mesaj()));
        }

        load_table(srv.get_all());
        load_list_from_table(srv.get_all());
    });

    QObject::connect(btn_notificare, &QPushButton::clicked, [&]() {
        notificare->show();
    });

    QObject::connect(btn_exit_notificari, &QPushButton::clicked, [&]() {
        notificare->close();
    });

    QObject::connect(btn_delete_notificare, &QPushButton::clicked, [&]() {
        srv.empty_notificare_srv();
        load_list(srv.get_all_notifications());
    });
    QMessageBox mesajNotificare;

    QObject::connect(btn_generate_notificari, &QPushButton::clicked, [&]() {
        string nr_tentants = txtNotificareNumar->text().toStdString();
        int nr_tentats_correct;

        try {
            nr_tentats_correct = stoi(nr_tentants);
        }
        catch (std::invalid_argument& mesaj) {
            txtNotificareNumar->clear();
            mesajNotificare.warning(notificare, "Warning", "Numarul de locatari trebuie sa fie natural!");
            return;
        }
        try {
            srv.generate_notificare_srv(nr_tentats_correct);
        }
        catch (NotificareException& mesaj) {
            mesajNotificare.warning(notificare, "Warning", QString::fromStdString(mesaj.get_mesaj()));
        }
        txtNotificareNumar->clear();
        load_list(srv.get_all_notifications());
    });

    QObject::connect(btn_add_notificare, &QPushButton::clicked, this, &AppGUI::uiNotificareAdd);
    QObject::connect(btn_export_notificari, &QPushButton::clicked, [&]() {
        string nume_fisier = txtNotificareFile->text().toStdString();
        srv.export_notificare_srv(nume_fisier);
        txtNotificareFile->clear();
    });
}