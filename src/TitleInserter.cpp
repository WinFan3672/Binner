#include <TitleInserter.hpp>
#include <QPushButton>

TitleInserter::TitleInserter(QWidget *parent, QPlainTextEdit *text) : QDialog(parent), textEdit(text)
{
	setWindowTitle("Insert Title");

	central = new QVBoxLayout(this);
	setLayout(central);

	titleBox = new QLineEdit(this);
	central->addWidget(titleBox);

	QPushButton *okayButton = new QPushButton("OK", this);
	okayButton->setDefault(true);
	central->addWidget(okayButton);
	connect(okayButton, &QPushButton::clicked, this, &QDialog::accept);
}

QString TitleInserter::center(QString text, int width)
{
	int spaceWidth = (width - text.length()) / 2;
	std::string spaces(spaceWidth, ' ');
	QString qspaces = QString::fromStdString(spaces);
	return qspaces + text + qspaces + QString("\n");
}

void TitleInserter::accept()
{
	QString text = titleBox->text();
	qDebug() << "Title inserted:" << text;	
	QTextCursor cursor = textEdit->textCursor();
	cursor.insertText(SEPARATOR_NL);
	cursor.insertText(center(text, SEPARATOR_NL.length()));
	cursor.insertText(SEPARATOR_NL);
	QDialog::accept();
}
