//Iman Rezaei



#include <QtWidgets>

#include "mainwindow.h"
#include "paintarea.h"

MainWindow::MainWindow()
{
    paintArea = new PaintArea;
    setCentralWidget(paintArea);

    createActions();
    createToolBars();
    createMenus();

    setWindowTitle(tr("Paint"));
    resize(500, 500);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::open()
{
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this,
                                   tr("Open File"), QDir::currentPath());
        if (!fileName.isEmpty())
            paintArea->openImage(fileName);
    }
}

void MainWindow::save()
{
    QAction *action = qobject_cast<QAction *>(sender());
    QByteArray fileFormat = action->data().toByteArray();
    saveFile(fileFormat);
}

void MainWindow::penColor()
{
    QColor newColor = QColorDialog::getColor(paintArea->penColor());
    if (newColor.isValid())
        paintArea->setPenColor(newColor);
}

void MainWindow::changeBGColor()
{
    QColor bgColor = QColorDialog::getColor(paintArea->changeBGColor());
    if (bgColor.isValid())
        paintArea->setBGColor(bgColor);
}

void MainWindow::changeFGColor()
{

}

void MainWindow::selectTool()
{

}

void MainWindow::penWidth()
{
    bool ok;
    int newWidth = QInputDialog::getInt(this, tr("Paint"),
                                        tr("Select pen width:"),
                                        paintArea->penWidth(),
                                        1, 50, 1, &ok);
    if (ok)
        paintArea->setPenWidth(newWidth);
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Paint"),
            tr("<p>The <b>Paint</b></p>"));
}

void MainWindow::createActions()
{
    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    foreach (QByteArray format, QImageWriter::supportedImageFormats()) {
        QString text = tr("%1...").arg(QString(format).toUpper());

        QAction *action = new QAction(text, this);
        action->setData(format);
        connect(action, SIGNAL(triggered()), this, SLOT(save()));
        saveAsActs.append(action);
    }

    printAct = new QAction(tr("&Print..."), this);
    connect(printAct, SIGNAL(triggered()), paintArea, SLOT(print()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    penColorAct = new QAction(tr("&Pen Color..."), this);
    connect(penColorAct, SIGNAL(triggered()), this, SLOT(penColor()));

    penWidthAct = new QAction(tr("Pen &Width..."), this);
    connect(penWidthAct, SIGNAL(triggered()), this, SLOT(penWidth()));

    changeFGColorAct = new QAction(tr("&Change foreground color"), this);
    connect(changeFGColorAct, SIGNAL(triggered()), this, SLOT(changeFGColor()));

    changeBGColorAct = new QAction(tr("&Change background color"), this);
    connect(changeBGColorAct, SIGNAL(triggered()), this, SLOT(changeBGColor()));


    clearScreenAct = new QAction(tr("&Clear Screen"), this);
    clearScreenAct->setShortcut(tr("Ctrl+L"));
    connect(clearScreenAct, SIGNAL(triggered()),
            paintArea, SLOT(clearImage()));

    aboutAct = new QAction(tr("&About"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::createMenus()
{
    saveAsMenu = new QMenu(tr("&Save As"), this);
    foreach (QAction *action, saveAsActs)
        saveAsMenu->addAction(action);

    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);
    fileMenu->addMenu(saveAsMenu);
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = new QMenu(tr("&Edit"), this);
    editMenu->addAction(changeBGColorAct);
    editMenu->addAction(changeFGColorAct);

    viewMenu = new QMenu(tr("&View"), this);

    optionMenu = new QMenu(tr("&Options"), this);
    optionMenu->addAction(penColorAct);
    optionMenu->addAction(penWidthAct);
    optionMenu->addAction(selectToolAct);
    optionMenu->addSeparator();
    optionMenu->addAction(clearScreenAct);

    helpMenu = new QMenu(tr("&Help"), this);
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(editMenu);
    menuBar()->addMenu(viewMenu);
    menuBar()->addMenu(optionMenu);
    menuBar()->addMenu(helpMenu);
}

void MainWindow::createToolBars()
{

    QPixmap openPix = QPixmap("/Users/IMANMK/Documents/Senior/"
                              "Intro\ to\ Software\ Engineering\ \(CS\ 410\)/Homeworks/hw3/Paint/icon/open_icon.bmp");
    //QPixmap openPix("icon/open_icon.bmp");
    QPixmap bgPix("/Users/IMANMK/Documents/Senior/"
                  "Intro\ to\ Software\ Engineering\ \(CS\ 410\)/Homeworks/hw3/Paint/icon/bcolor_icon");
    QPixmap clearAllPix("/Users/IMANMK/Documents/Senior/"
                        "Intro\ to\ Software\ Engineering\ \(CS\ 410\)/Homeworks/hw3/Paint/icon/clearall_icon.bmp");
    QPixmap eraserPix("/Users/IMANMK/Documents/Senior/"
                      "Intro\ to\ Software\ Engineering\ \(CS\ 410\)/Homeworks/hw3/Paint/icon/eraser_icon.bmp");
    QPixmap fgPix("/Users/IMANMK/Documents/Senior/"
                  "Intro\ to\ Software\ Engineering\ \(CS\ 410\)/Homeworks/hw3/Paint/icon/fcolor_icon.bmp");
    QPixmap linePix("/Users/IMANMK/Documents/Senior/"
                    "Intro\ to\ Software\ Engineering\ \(CS\ 410\)/Homeworks/hw3/Paint/icon/line_icon.bmp");
    QPixmap rectPix("/Users/IMANMK/Documents/Senior/"
                    "Intro\ to\ Software\ Engineering\ \(CS\ 410\)/Homeworks/hw3/Paint/icon/rect_icon.bmp");
    QPixmap savePix("/Users/IMANMK/Documents/Senior/"
                    "Intro\ to\ Software\ Engineering\ \(CS\ 410\)/Homeworks/hw3/Paint/icon/save_icon.bmp");
    QPixmap undoPix("/Users/IMANMK/Documents/Senior/"
                    "Intro\ to\ Software\ Engineering\ \(CS\ 410\)/Homeworks/hw3/Paint/icon/undo_icon.bmp");
    QPixmap redoPix("/Users/IMANMK/Documents/Senior/"
                    "Intro\ to\ Software\ Engineering\ \(CS\ 410\)/Homeworks/hw3/Paint/icon/redo_icon.bmp");
    QPixmap penPix("/Users/IMANMK/Documents/Senior/"
                   "Intro\ to\ Software\ Engineering\ \(CS\ 410\)/Homeworks/hw3/Paint/icon/pen_icon.bmp");
    QPixmap newPix("/Users/IMANMK/Documents/Senior/"
                   "Intro\ to\ Software\ Engineering\ \(CS\ 410\)/Homeworks/hw3/Paint/icon/new_icon.bmp");
    QPixmap resizePix("/Users/IMANMK/Documents/Senior/"
                      "Intro\ to\ Software\ Engineering\ \(CS\ 410\)/Homeworks/hw3/Paint/icon/resize_icon.bmp");


    QToolBar *toolbar = addToolBar("Main toolbar");
    QAction *newImageToolbar = toolbar->addAction(QIcon(newPix), "New Image");
    connect(newImageToolbar, SIGNAL(triggered()), paintArea, SLOT(clearImage()));
    QAction *openToolAct = toolbar->addAction(QIcon(openPix), "Open File");
    connect(openToolAct, SIGNAL(triggered()), this, SLOT(open()));
    QAction *saveToolAct = toolbar->addAction(QIcon(savePix), "Save File");
    connect(saveToolAct, SIGNAL(triggered()), this, SLOT(save()));
    toolbar->addAction(QIcon(undoPix), "Undo");
    toolbar->addAction(QIcon(redoPix), "Redo");
    QAction *clearToolAct = toolbar->addAction(QIcon(clearAllPix), "Clear All");
    connect(clearToolAct, SIGNAL(triggered()), paintArea, SLOT(clearImage()));
    toolbar->addAction(QIcon(resizePix), "Resize");
    toolbar->addAction(QIcon(penPix), "Pen");
    toolbar->addAction(QIcon(linePix), "Line");
    toolbar->addAction(QIcon(eraserPix), "Eraser");
    toolbar->addAction(QIcon(rectPix), "Rectangle");
    QAction *fgColorTool = toolbar->addAction(QIcon(fgPix), "Change foreground color");
    connect(fgColorTool, SIGNAL(triggered()), this, SLOT(penColor()));
    QAction *bgColorTool = toolbar->addAction(QIcon(bgPix), "Change background color");
    connect(bgColorTool, SIGNAL(triggered()), this, SLOT(changeBGColor()));


}

bool MainWindow::maybeSave()
{
    if (paintArea->isModified()) {
       QMessageBox::StandardButton ret;
       ret = QMessageBox::warning(this, tr("Paint"),
                          tr("The image has been modified.\n"
                             "Do you want to save your changes?"),
                          QMessageBox::Save | QMessageBox::Discard
                          | QMessageBox::Cancel);
        if (ret == QMessageBox::Save) {
            return saveFile("png");
        } else if (ret == QMessageBox::Cancel) {
            return false;
        }
    }
    return true;
}

bool MainWindow::saveFile(const QByteArray &fileFormat)

{
    QString initialPath = QDir::currentPath() + "/untitled." + fileFormat;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                               initialPath,
                               tr("%1 Files (*.%2);;All Files (*)")
                               .arg(QString::fromLatin1(fileFormat.toUpper()))
                               .arg(QString::fromLatin1(fileFormat)));
    if (fileName.isEmpty()) {
        return false;
    } else {
        return paintArea->saveImage(fileName, fileFormat.constData());
    }
}
