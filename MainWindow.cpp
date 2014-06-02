#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QLayout>
#include <QApplication>
#include <QClipboard>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QPrintDialog>
#include <QPrinter>
#include <QTextCodec>
#include <QTextEdit>
#include <QTextCursor>
#include <QTextDocumentWriter>
#include <QtDebug>
#include <QCloseEvent>
#include <QMessageBox>
#include <QPrintPreviewDialog>
#include <QShortcut>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _brightness = 1.0;

    this->setWindowTitle("Write");
    this->setContentsMargins(-1,0,-1,0);
    this->layout()->setMargin(0);
    this->centralWidget()->layout()->setMargin(0);
    this->centralWidget()->setStyleSheet("QWidget { background-color: black; }");

    connect(new QShortcut(QKeySequence(tr("Ctrl+Q", "Quit")),this),SIGNAL(activated()),this,SLOT(close()));
    connect(new QShortcut(QKeySequence(tr("Ctrl+Shift+F", "Fullscreen")),this),SIGNAL(activated()),this,SLOT(toggleFullscreen()));
    connect(new QShortcut(QKeySequence(tr("Ctrl+Space", "Fullscreen")),this),SIGNAL(activated()),this,SLOT(toggleBlur()));
    connect(new QShortcut(QKeySequence(tr("Esc", "Exit Fullscreen")),this),SIGNAL(activated()),this,SLOT(exitFullscreen()));
    connect(new QShortcut(QKeySequence(tr("Ctrl+O", "Open")),this),SIGNAL(activated()),this,SLOT(openFile()));
    connect(new QShortcut(QKeySequence(tr("Ctrl+S", "Save")),this),SIGNAL(activated()),this,SLOT(saveFile()));
    connect(new QShortcut(QKeySequence(tr("Ctrl+Shift+S", "Save As")),this),SIGNAL(activated()),this,SLOT(saveFileAs()));
    connect(new QShortcut(QKeySequence(tr("Ctrl+N", "New")),this),SIGNAL(activated()),this,SLOT(newFile()));
    connect(new QShortcut(QKeySequence(tr("Ctrl+P", "Print")),this),SIGNAL(activated()),this,SLOT(printFile()));
    connect(new QShortcut(QKeySequence(tr("Ctrl+E", "Export")),this),SIGNAL(activated()),this,SLOT(exportFile()));
    connect(new QShortcut(QKeySequence(tr("Alt+Up", "Increase Brightness")),this),SIGNAL(activated()),this,SLOT(increaseBrightness()));
    connect(new QShortcut(QKeySequence(tr("Alt+Down", "Decrease Brightness")),this),SIGNAL(activated()),this,SLOT(decreaseBrightness()));
    connect(new QShortcut(QKeySequence(tr("F1", "Help")),this),SIGNAL(activated()),this,SLOT(showHelp()));

    showIntro();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::resizeEvent(QResizeEvent *e) {
    if(this->width() < 300) {
	ui->editor->setStyleSheet("QWidget { background-color: red; }");
    }
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if(saveIfModified()) {
	event->accept();
    } else {
	event->ignore();
    }
}






void MainWindow::toggleFullscreen() {
    if(this->isFullScreen())	showNormal();
    else			showFullScreen();
}

void MainWindow::exitFullscreen() {
    if(this->isFullScreen())	showNormal();
}

void MainWindow::toggleBlur() {
    ui->editor->setBlur(!ui->editor->isBlurred());
}





bool MainWindow::loadFile(const QString &f)
{
    if (!QFile::exists(f)) return false;

    QFile file(f);
    if (!file.open(QFile::ReadOnly)) return false;

    QByteArray data = file.readAll();
    QTextCodec *codec = Qt::codecForHtml(data);
    QString str = codec->toUnicode(data);
    if (Qt::mightBeRichText(str)) {
	ui->editor->textEdit()->setHtml(str);
    } else {
	str = QString::fromLocal8Bit(data);
	ui->editor->textEdit()->setPlainText(str);
    }

    setCurrentFileName(f);
    return true;
}

bool MainWindow::saveIfModified()
{
    if (!ui->editor->textEdit()->document()->isModified()) return true;
    if (_fileName.startsWith(QLatin1String(":/"))) return true;

    QMessageBox::StandardButton ret;
    ret = QMessageBox::warning(this, tr("Write"),
			       tr("The document has been modified.\n"
				  "Do you want to save your changes?"),
			       QMessageBox::Save | QMessageBox::Discard
			       | QMessageBox::Cancel);
    if (ret == QMessageBox::Save)	    return saveFile();
    else if (ret == QMessageBox::Cancel)    return false;
    return true;
}

void MainWindow::setCurrentFileName(const QString &fileName)
{
    _fileName = fileName;
    ui->editor->textEdit()->document()->setModified(false);

    QString shownName;
    if (fileName.isEmpty()) shownName = "untitled.txt";
    else		    shownName = QFileInfo(fileName).fileName();

    setWindowTitle(tr("Write - %1").arg(shownName));
    setWindowModified(false);
}







void MainWindow::newFile()
{
    if (saveIfModified()) {
	ui->editor->textEdit()->clear();
	setCurrentFileName(QString());
    }
}

void MainWindow::openFile()
{
    if (saveIfModified()) {
	QString fn = QFileDialog::getOpenFileName(this, tr("Open File..."),QString(), tr("Text Files (*.txt);;All Files (*)"));
	if (!fn.isEmpty()) loadFile(fn);
    }
}

bool MainWindow::saveFile()
{
    if (_fileName.isEmpty())
	return saveFileAs();

    QTextDocumentWriter writer(_fileName);
    bool success = writer.write(ui->editor->textEdit()->document());
    if (success)
	ui->editor->textEdit()->document()->setModified(false);
    return success;
}

bool MainWindow::saveFileAs()
{
    QString fn = QFileDialog::getSaveFileName(this, tr("Save as..."),
					      QString(), tr("Text Files (*.txt);;All Files (*)"));
    if (fn.isEmpty())
	return false;

    setCurrentFileName(fn);
    return saveFile();
}

/*void MainWindow::filePrint()
{
#ifndef QT_NO_PRINTER
    QPrinter printer(QPrinter::HighResolution);
    QPrintDialog *dlg = new QPrintDialog(&printer, this);
    if (textEdit->textCursor().hasSelection())
	dlg->addEnabledOption(QAbstractPrintDialog::PrintSelection);
    dlg->setWindowTitle(tr("Print Document"));
    if (dlg->exec() == QDialog::Accepted) {
	textEdit->print(&printer);
    }
    delete dlg;
#endif
}*/

void MainWindow::printFile()
{
#ifndef QT_NO_PRINTER
    QPrinter printer(QPrinter::HighResolution);
    QPrintPreviewDialog preview(&printer, this);
    connect(&preview, SIGNAL(paintRequested(QPrinter*)), SLOT(printPreview(QPrinter*)));
    preview.exec();
#endif
}

void MainWindow::printPreview(QPrinter *printer)
{
#ifdef QT_NO_PRINTER
    Q_UNUSED(printer);
#else
    ui->editor->textEdit()->print(printer);
#endif
}


void MainWindow::exportFile()
{
#ifndef QT_NO_PRINTER
//! [0]
    QString fileName = QFileDialog::getSaveFileName(this, "Export PDF",
						    QString(), "*.pdf");
    if (!fileName.isEmpty()) {
	if (QFileInfo(fileName).suffix().isEmpty())
	    fileName.append(".pdf");
	QPrinter printer(QPrinter::HighResolution);
	printer.setOutputFormat(QPrinter::PdfFormat);
	printer.setOutputFileName(fileName);
	ui->editor->textEdit()->document()->print(&printer);
    }
//! [0]
#endif
}

void MainWindow::increaseBrightness() {
    _brightness += 0.05;
    if(_brightness > 1.0) _brightness = 1.0;
    ui->editor->setBrightness(_brightness);
}

void MainWindow::decreaseBrightness() {
    _brightness -= 0.05;
    if(_brightness < 0.1) _brightness = 0.1;
    ui->editor->setBrightness(_brightness);
}

void MainWindow::showIntro() {
    loadFile(":/intro.txt");
}

void MainWindow::showHelp() {
    if(saveIfModified()) loadFile(":/help.txt");
}
