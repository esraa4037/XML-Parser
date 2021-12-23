#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_select_clicked();

    void on_validate_clicked();

    void on_correct_clicked();

    void on_formating_clicked();

    void on_json_clicked();

    void on_compress_clicked();

    void on_compress_2_clicked();

    void on_decompress_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
