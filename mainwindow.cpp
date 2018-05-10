#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <cassert>
#include <sstream>

ComposeEntryModel::ComposeEntryModel(std::vector<ComposeEntry>&& entries) : _entries(entries) { }

int ComposeEntryModel::rowCount(const QModelIndex& parent) const {
    return parent.isValid() ? 0 : _entries.size();
}

int ComposeEntryModel::columnCount(const QModelIndex& parent) const {
    return parent.isValid() ? 0 : 2;
}

QVariant ComposeEntryModel::data(const QModelIndex& index, int role) const {
    if(!index.isValid() || index.parent().isValid()) {
        return QVariant();
    }

    const ComposeEntry& entry = _entries.at(index.row());

    switch(role) {
    case Qt::DisplayRole:
        switch(index.column()) {
        case 0: {
            // Join codes into one string.
            // See https://stackoverflow.com/questions/1430757/c-vector-to-string
            std::ostringstream stream;
            std::copy(entry.key_codes.begin(), entry.key_codes.end(), std::ostream_iterator<std::string>(stream, " "));
            return QString::fromStdString(stream.str());
        }
        case 1:
            return QString::fromStdString(entry.result);
        default:
            assert(false);
        }
        break;
    default:
        return QVariant();
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}
