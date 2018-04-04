#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAbstractTableModel>
#include <QMainWindow>

#include "compose_parser.h"

class ComposeEntryModel : public QAbstractTableModel {
public:
    ComposeEntryModel(std::vector<ComposeEntry>&& entries);

    int rowCount(const QModelIndex& index) const override;
    int columnCount(const QModelIndex& index) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    // TODO: provide headers.
private:
    std::vector<ComposeEntry> _entries;
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
