#ifndef HELP_H

#define HELP_H

#include <QWidget>
#include <QPushButton>
#include <QTextBrowser>
#include <QStackedWidget>
#include <QListWidget>

class AppHelp : public QWidget
{
    Q_OBJECT

public:
    explicit AppHelp(QWidget *parent = 0);
    void CreateHelpWindow();

private slots:
    void listWidgetChanged(QListWidgetItem*);

private:
    QListWidget *help_left;
    QTextBrowser *html_content;
};

#endif // HELP_H
