#include <iostream>
#include <Binner.hpp>
#include <Globals.hpp>
#include <TitleInserter.hpp>
#include <QFont>
#include <QFontMetrics>
#include <QFileDialog>
#include <QMessageBox>
#include <QMenuBar>
#include <QMenu>
#include <QPlainTextEdit>
#include <QTextEdit>
#include <QFile>

/**
 * Source file for Binner class.
 */

Binner::Binner()
{			
	textEdit = new QPlainTextEdit(this);
	setCentralWidget(textEdit);

	QFont font("Cascadia Mono Light", 12);
	font.setStyleHint(QFont::Monospace);
	textEdit->setFont(font);

	QFontMetrics metrics(font);
	int width = metrics.horizontalAdvance(SEPARATOR) + metrics.horizontalAdvance('=');

	QMenuBar *menuBar = this->menuBar();

	QMenu *fileMenu = menuBar->addMenu("File");
	QMenu *insertMenu = menuBar->addMenu("Insert");
	QMenu *viewMenu = menuBar->addMenu("View");
	QMenu *helpMenu = menuBar->addMenu("Help");

	QAction *newAction = new QAction("New", this);
	connect(newAction, &QAction::triggered, this, &Binner::newAction);
	newAction->setShortcut(QKeySequence::New);
	fileMenu->addAction(newAction);

	QAction *openAction = new QAction("Open", this);
	connect(openAction, &QAction::triggered, this, &Binner::openFile);
	openAction->setShortcut(QKeySequence::Open);
	fileMenu->addAction(openAction);

	QAction *saveAction = new QAction("Save", this);
	connect(saveAction, &QAction::triggered, this, &Binner::saveFile);
	saveAction->setShortcut(QKeySequence::Save);
	fileMenu->addAction(saveAction);

	QAction *saveAs = new QAction("Save As...", this);
	connect(saveAs, &QAction::triggered, this, &Binner::saveFileAs);
	saveAs->setShortcut(QKeySequence::SaveAs);
	fileMenu->addAction(saveAs);

	QAction *quitAction = new QAction("Quit", this);
	connect(quitAction, &QAction::triggered, this, &Binner::close);
	quitAction->setShortcut(QKeySequence::Quit);
	fileMenu->addAction(quitAction);

	QAction *newTitle = new QAction("Title", this);
	connect(newTitle, &QAction::triggered, this, &Binner::insertTitle);
	QKeySequence newTitleSequence(Qt::CTRL | Qt::Key_T);
	newTitle->setShortcut(newTitleSequence);
	insertMenu->addAction(newTitle);

	QAction *insertSep = new QAction("Separator", this);
	connect(insertSep, &QAction::triggered, this, &Binner::insertSeparator);
	QKeySequence insertSepSeq(Qt::CTRL | Qt::Key_E);
	insertSep->setShortcut(insertSepSeq);
	insertMenu->addAction(insertSep);

	wordWrap = new QAction("Toggle Word Wrap", this);
	wordWrap->setCheckable(true);
	wordWrap->setChecked(false);
	connect(wordWrap, &QAction::triggered, this, &Binner::toggleWordWrap);
	/*viewMenu->addAction(wordWrap);*/

	QAction *aboutMenu = new QAction("About Binner...", this);
	connect(aboutMenu, &QAction::triggered, this, &Binner::aboutBinner);
	QKeySequence aboutKey(Qt::Key_F1);
	aboutMenu->setShortcut(aboutKey);
	helpMenu->addAction(aboutMenu);

	resize(width, 600);
}

void Binner::newAction()
{
	std::cout << "New file" << std::endl;
	textEdit->setPlainText("");
}

void Binner::insertTitle()
{
	TitleInserter ti(this, textEdit);
	ti.exec();
}

void Binner::insertSeparator()
{
	QTextCursor cursor = textEdit->textCursor();
	cursor.insertText(SEPARATOR_NL);
}

void Binner::aboutBinner()
{
	std::cout << "About" << std::endl;
	QMessageBox aboutDialog(this);
	aboutDialog.setWindowTitle("About Binner");
	aboutDialog.setText("Binner v0.0.0 (c) 2024 Gordinator, all rights reserved.");
	aboutDialog.exec();
}

void Binner::toggleWordWrap()
{
}

void Binner::saveFile()
{
	std::cout << "Saved file\n";
	if (filePath == "")
	{
		filePath = selectSaveFile();
		if (filePath == "")
		{
			return;
		}
		saveFile();
	}
	else
	{
		QFile file(filePath);
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
			return;
		QTextStream out(&file);
		out << textEdit->toPlainText();
	}
}


QString Binner::selectSaveFile()
{
	return QFileDialog::getSaveFileName(this);
}

void Binner::saveFileAs() 
{
	filePath = selectSaveFile();
	if (filePath == "")
	{
		return;
	}
	saveFile();
}

void Binner::openFile()
{
	std::cout << "Open file\n";
	filePath = selectOpenFile();
	QFile file(filePath);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	QTextStream in(&file);
	textEdit->setPlainText(in.readAll());
}

QString Binner::selectOpenFile()
{
	return QFileDialog::getOpenFileName(this, "Select file to open", "*.txt");
}
