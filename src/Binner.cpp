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
	textEdit->setFixedWidth(width);

	QMenuBar *menuBar = this->menuBar();

	QMenu *fileMenu = menuBar->addMenu("File");
	QMenu *insertMenu = menuBar->addMenu("Insert");
	QMenu *viewMenu = menuBar->addMenu("View");
	QMenu *helpMenu = menuBar->addMenu("Help");

	QAction *newAction = new QAction("New", this);
	connect(newAction, &QAction::triggered, this, &Binner::newAction);
	newAction->setShortcut(QKeySequence::New);
	fileMenu->addAction(newAction);

	QAction *saveAction = new QAction("Save", this);
	connect(saveAction, &QAction::triggered, this, &Binner::saveFile);
	fileMenu->addAction(saveAction);

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
	viewMenu->addAction(wordWrap);

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
	if (filePath == "")
	{
		filePath = selectSaveFile().toStdString();
		if (filePath == "")
		{
			return;
		}
		saveFile();
	}
	else
	{
	}
}


QString Binner::selectSaveFile()
{
	return QFileDialog::getSaveFileName(this);
}
