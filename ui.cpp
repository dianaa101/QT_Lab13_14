#include "ui.h"

#include <iostream>
#include <limits>

void clearInputBuffer() {
    if (cin.fail()) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void Ui::add_ui() {
    string name, type;
    int number = 0;
    int surface = 0;

    cout << "Add tentant:\n";
    cout << "Number: ";
    cin >> number;

    cout << "Name: ";
    cin >> name;
    clearInputBuffer();

    cout << "Surface: ";
    cin >> surface;

    cout << "Type: ";
    cin >> type;

    controller.add_service(number, name, surface, type);
}


void Ui::update_ui() {
    string name, type;
    int number = 0;
    int surface = 0;

    cout << "Number: ";
    cin >> number;

    cout << "New name: ";
    cin >> name;

    cout << "Surface: ";
    cin >> surface;

    cout << "New type: ";
    cin >> type;

    controller.add_service(number, name, surface, type);
}

void Ui::delete_ui() {
    string name;
    int number = 0;

    cout << "Number: ";
    cin >> number;

    cout << "Name: ";
    cin >> name;

    controller.delete_service(number, name);
}

void Ui::find_ui() {
    string name;
    int number = 0;

    cout << "Insert the number and the name: \n";
    cout << "Number: ";
    cin >> number;

    cout << "Name: ";
    cin >> name;

    Tentant tentant = controller.find_service(number, name);
    cout << "\nYour tentant is:\n " << tentant.to_string_print() << '\n';
}

void Ui::filter_ui() {
    int option = 0;
    cout << "1 - Filter after surface\n\n";
    cout << "2 - Filter after type\n\n";


    cout << "The option is: ";
    cin >> option;
    clearInputBuffer();

    if (option == 1) {
        int surface = 0;
        cout << "Surface: ";
        cin >> surface;
        clearInputBuffer();
        vector<Tentant> filtered = controller.filter_surface(surface);
        cout << "The filtered tenants are: \n";
        print_tentants(filtered);
    }
    else if (option == 2) {
        string type;
        cout << "Apartment type: ";
        cin >> type;
        vector<Tentant> filtered = controller.filter_type(type);
        cout << "The filtered tenants are\n";
        print_tentants(filtered);
    }
    else {
        cout << "Invalid option!\n";
    }
}

void Ui::sort_ui() {
    int option = 0;
    cout << "Pick an option:\n";
    cout << "1 - Sort by surface \n";
    cout << "2 - Sort by name \n";
    cout << "3 - Sort by type + surface \n";

    cout << "The option is: ";
    cin >> option;
    clearInputBuffer();

    if (option == 1) {
        vector<Tentant> sorted = controller.sort_surface();
        cout << "The sorted tenants are:\n";
        print_tentants(sorted);
    }
    else if (option == 2) {
        vector<Tentant> sorted = controller.sort_name();
        cout << "The sorted tenants are:\n";
        print_tentants(sorted);
    }
    else if (option == 3) {
        vector<Tentant> sorted = controller.sort_type_surface();
        cout << "The sorted tenants are:\n";
        print_tentants(sorted);
    }
    else {
        cout << "Invalid option!\n";
    }
}

void Ui::print_tentants(const vector<Tentant>& tentants) {
    if (!tentants.empty()) {
        for (Tentant tentant : tentants) {
            cout << tentant.to_string_print() << '\n';
        }
    }
    else {
        cout << "Tentant doesn't exist";
    }
}

void Ui::print_all() {
    const vector<Tentant>& tentants = controller.get_all();
    cout << '\n' << "The list of tenants:\n";
    if (!tentants.empty()) {
        for (Tentant tentant : tentants) {
            cout << tentant.to_string_print() << '\n';
        }
        cout << '\n';
    }
    else
        cout << "Tentant doesn't exist!\n\n";
}

void Ui::generate_notificare_ui() {
    int nr;
    cout << "Insert the number of notifications to be generated: ";
    cin >> nr;
    cout << '\n';
    controller.generate_notificare_srv(nr);
    cout << "The size of the notifications list is: " << controller.get_notificare_size() << '\n';
}

void Ui::add_notificare_ui() {
    int number;
    cout << "Insert apartment number: ";
    cin >> number;
    clearInputBuffer();

    auto gasit = controller.filter_number(number);
    if (gasit.empty()) {
        cout << "Nonexistent apartment number!\n";
        return;
    }
    if (gasit.size() == 1) {
        cout << "Object added!\n";
        controller.add_notificare_srv(number, gasit[0].get_name(), gasit);
        return;
    }

    if (gasit.size() > 1) {
        cout << "There are multiple apartments with this number. Here's the list: ";
        print_tentants(gasit);

        string name;
        cout << "Insert a name for random generation: ";
        cin >> name;
        controller.add_notificare_srv(number, name, gasit);
    }
    cout << "The size of the list of notifications is: " << controller.get_notificare_size() << '\n';
}

void Ui::export_notificare_ui() {
    string nume;
    cout << "Insert the name of the file: ";
    cin >> nume;

    controller.export_notificare_srv(nume);
    cout << "The size of the list of notifications is: " << controller.get_notificare_size() << '\n';
}

void Ui::empty_notificare_ui() {
    controller.empty_notificare_srv();
    cout << "The size of the list of notifications is: " << controller.get_notificare_size() << '\n';
}


void Ui::raport_ui() {
    map<string, DTO> raport = controller.raport();
    cout << '\n' << "Raportul este:\n";
    for (auto it = raport.begin(); it != raport.end(); ++it) {
        cout << it->first << " " << it->second.get_count() << '\n';
    }
}

void Ui::menu() {
    cout << '\n';
    cout << "Tenant Menu:\n";
    cout << "------------------------------------------------------------------\n";
    cout << "1. Add tenant\n";
    cout << "2. Update tenant\n";
    cout << "3. Delete tenant\n";
    cout << "4. Find tenant\n";
    cout << "5. Filter tenants\n";
    cout << "6. Sort tenants\n";
    cout << "------------------------------------------------------------------\n";
    cout << "7. Generate a notification\n";
    cout << "8. Add to the list of notifications\n";
    cout << "9. Export notification\n";
    cout << "10. Empty notification\n";
    cout << "11. Generate a raport\n";
    cout << "------------------------------------------------------------------\n";
    cout << "12. Undo\n";
    cout << "0. Exit.\n";
}

void Ui::run() {
    int option = -1;

    controller.add_service(1, "maria", 50, "rented");
    controller.add_service(2, "ana", 100, "bought");
    controller.add_service(3, "ana", 150, "rented");

    while (true) {
        print_all();
        menu();

        cout << "Insert option: ";
        cin >> option;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            option = -1;
        }
        cout << '\n';

        switch (option) {
            case 0:
                cout << "Bye bye!\n";
                return;
            case 1:
                try {
                    add_ui();
                    cout << "Tentant added!\n";
                }
                catch (RepoException& e) {
                    cout << e.get_mesaj();
                }
                catch (ValidatorException& ve) {
                    cout << ve.get_mesaj();
                }
                break;
            case 2:
                try {
                    update_ui();
                    cout << "Tentant updated!\n";
                }
                catch (RepoException& e) {
                    cout << e.get_mesaj();
                }
                catch (ValidatorException& ve) {
                    cout << ve.get_mesaj();
                }
                break;
            case 3:
                try {
                    delete_ui();
                    cout << "Tentant deleted!\n";
                }
                catch (RepoException& e) {
                    cout << e.get_mesaj();
                }
                catch (ValidatorException& ve) {
                    cout << ve.get_mesaj();
                }
                break;
            case 4:
                try {
                    find_ui();
                }
                catch (RepoException& e) {
                    cout << e.get_mesaj();
                }
                catch (ValidatorException& ve) {
                    cout << ve.get_mesaj();
                }
                break;
            case 5:
                try {
                    filter_ui();
                }
                catch (RepoException& e) {
                    cout << e.get_mesaj();
                }
                catch (ValidatorException& ve) {
                    cout << ve.get_mesaj();
                }
                break;
            case 6:
                try {
                    sort_ui();
                }
                catch (RepoException& e) {
                    cout << e.get_mesaj();
                }
                catch (ValidatorException& ve) {
                    cout << ve.get_mesaj();
                }
                break;
            case 7:
                try {
                    generate_notificare_ui();
                }
                catch (RepoException& e) {
                    cout << e.get_mesaj();
                }
                catch (ValidatorException& ve) {
                    cout << ve.get_mesaj();
                }
                catch (NotificareException& ve) {
                    cout << ve.get_mesaj();
                }
                break;
            case 8:
                try {
                    add_notificare_ui();
                }
                catch (RepoException& e) {
                    cout << e.get_mesaj();
                }
                catch (ValidatorException& ve) {
                    cout << ve.get_mesaj();
                }
                catch (NotificareException& ve) {
                    cout << ve.get_mesaj();
                }
                break;
            case 9:
                try {
                    export_notificare_ui();
                }
                catch (RepoException& e) {
                    cout << e.get_mesaj();
                }
                catch (ValidatorException& ve) {
                    cout << ve.get_mesaj();
                }
                catch (NotificareException& ve) {
                    cout << ve.get_mesaj();
                }
                break;
            case 10:
                try {
                    empty_notificare_ui();
                }
                catch (RepoException& e) {
                    cout << e.get_mesaj();
                }
                catch (ValidatorException& ve) {
                    cout << ve.get_mesaj();
                }
                catch (NotificareException& ve) {
                    cout << ve.get_mesaj();
                }
                break;

            case 11:
                try {
                    raport_ui();
                }
                catch (RepoException& e) {
                    cout << e.get_mesaj();
                }
                catch (ValidatorException& ve) {
                    cout << ve.get_mesaj();
                }
                catch (NotificareException& ve) {
                    cout << ve.get_mesaj();
                }
                break;
            case 12:
                try {
                    controller.undo();
                    cout << "Undo successfully done!\n";
                }
                catch (RepoException& e) {
                    cout << e.get_mesaj();
                }
                catch (BadLuckException& ve) {
                    cout << ve.get_mesaj();
                }
                break;
            default:
                cout << "Invalid option!!\n\n";
        }

    }
}