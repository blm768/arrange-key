#include "mainwindow.h"
#include "ui_mainwindow.h"

ComposeEntryModel::ComposeEntryModel(std::vector<ComposeEntry>&& entries) : _entries(entries) { }

int ComposeEntryModel::rowCount(const QModelIndex& index) const {
    return index.isValid() ? 0 : _entries.size();
}

int ComposeEntryModel::columnCount(const QModelIndex& index) const {
    return index.isValid()? 0 : 2;
}

QVariant ComposeEntryModel::data(const QModelIndex& index, int role) const {
    if(!index.isValid() || index.parent().isValid()) {
        return QVariant();
    }

    // TODO: implement.
    return QVariant();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}
