#include "domain.h"
#include "repo.h"
#include "service.h"
#include "ui.h"
#include "QTLab13_14.h"
// #include "tests.h"

#define _CRTDBG_MAP_ALLOC


#include <iostream>
#include <crtdbg.h>
#include <QApplication>
using namespace std;

int main(int argc, char* argv[]) {
    // Tests tests;
    // tests.test_all();

    QApplication app(argc, argv);

    vector<Tentant> vector;
    // Repo repo{ vector };
    FileRepo repo("tenants.txt");
    // RepoProb repo(0.57);
    Validator validator;
    Notificare notificare;
    Service controller(repo, validator, notificare);
    // Ui ui{ controller };
    AppGUI gui{ controller };
    gui.show();

    return app.exec();

    // ui.run();
}

// _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
// create();
// _CrtDumpMemoryLeaks();