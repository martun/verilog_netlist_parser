#ifndef TEXT_EDIT_H
#define TEXT_EDIT_H

#include <QTextEdit>

#include <vector>
#include <string>

class TextEdit
    : public QTextEdit
{
    Q_OBJECT;

public:
    TextEdit(QWidget* parent = 0);
    ~TextEdit();

    std::string getLastCommand() const;
    std::vector<std::string> getCommands() const;

    void registerTclCommand();

protected:
    virtual void keyPressEvent(QKeyEvent* e);

signals:
    void commandEntered();

private:
    std::vector<std::string> m_commands;
    QTextCursor m_cursor;
    QString m_currentCommand;
};

#endif // TEXT_EDIT_H 
