#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPrinter>


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {

    Q_OBJECT

private:
    QString _fileName;
    qreal _brightness;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);
    void resizeEvent(QResizeEvent *e);
    void closeEvent(QCloseEvent *e);

private:
    bool loadFile(const QString &f);
    bool saveIfModified();
    void setCurrentFileName(const QString &fileName);

public slots:
    void toggleFullscreen();
    void exitFullscreen();
    void toggleBlur();
    void printPreview(QPrinter *);
    void newFile();
    bool saveFile();
    bool saveFileAs();
    void openFile();
    void printFile();
    void exportFile();
    void increaseBrightness();
    void decreaseBrightness();
    void showIntro();
    void showHelp();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
