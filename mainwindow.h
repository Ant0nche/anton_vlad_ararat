#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QCryptographicHash>
#include <QFile>
#include <QAbstractItemView>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void loginUser();
    //  addPatient();
    // void viewPatients();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;

    void setupDatabase();
    void setupTable();
};

#endif // MAINWINDOW_H
