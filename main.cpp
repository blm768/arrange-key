#include <fstream>

#include <QApplication>
#include <QTableView>
#include <QHBoxLayout>
#include <QHeaderView>

#include "compose_parser.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.show();

    // TODO: implement properly.
    std::ifstream compose_file("/usr/share/X11/locale/en_US.UTF-8/Compose");
    auto entries = parse_compose_bindings(compose_file);

    ComposeEntryModel entry_model(std::move(entries));
    QTableView table;
    table.setModel(&entry_model);
    table.horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QHBoxLayout layout;
    layout.addWidget(&table);
    w.centralWidget()->setLayout(&layout);

    return app.exec();
}
