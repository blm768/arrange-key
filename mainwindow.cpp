#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "unicode.h"

#include <algorithm>
#include <cassert>
#include <experimental/iterator>
#include <sstream>

ComposeEntryModel::ComposeEntryModel(std::vector<ComposeEntry>&& entries) : _entries(entries) { }

int ComposeEntryModel::rowCount(const QModelIndex& parent) const {
    return parent.isValid() ? 0 : _entries.size();
}

int ComposeEntryModel::columnCount(const QModelIndex& parent) const {
    return parent.isValid() ? 0 : 3;
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
            // Join key code names into one string.
            std::ostringstream stream;
            std::transform(
                entry.key_codes.begin(), entry.key_codes.end(),
                std::experimental::ostream_joiner<std::string>(stream, " "),
                [] (auto s) { return "<" + s + ">"; }
            );
            return QString::fromStdString(stream.str());
        }
        case 1:
            return QString::fromStdString(entry.result);
        case 2: {
            auto names = code_point_names(entry.result);
            std::ostringstream stream;
            std::copy(
                names.begin(), names.end(),
                std::experimental::ostream_joiner<std::string>(stream, " + ")
            );
            return QString::fromStdString(stream.str());
        }
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
