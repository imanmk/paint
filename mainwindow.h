//Iman Rezaei

#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QList>
#include <QMainWindow>

class PaintArea;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

protected:
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

private slots:
    void open();
    void save();
    void penColor();
    void penWidth();
    void about();
    void selectTool();
    void changeBGColor();
    void changeFGColor();

private:
    void createActions();
    void createMenus();
    void createToolBars();
    bool maybeSave();
    bool saveFile(const QByteArray &fileFormat);

    PaintArea *paintArea;

    QMenu *saveAsMenu;
    QMenu *fileMenu;
    QMenu *optionMenu;
    QMenu *helpMenu;
    QMenu *editMenu;
    QMenu *viewMenu;



    QAction *openAct;
    QList<QAction *> saveAsActs;
    QAction *exitAct;
    QAction *penColorAct;
    QAction *penWidthAct;
    QAction *printAct;
    QAction *clearScreenAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
    QAction *selectToolAct;
    QAction *changeBGColorAct;
    QAction *changeFGColorAct;
};




#endif // MAINWINDOW_H

