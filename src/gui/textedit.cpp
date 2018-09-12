#include "textedit.h"

#include <QKeyEvent>
#include <QDebug>

TextEdit::TextEdit(QWidget* parent)
    : QTextEdit(parent)
{
    setText(">");
    m_cursor = textCursor();
    m_cursor.movePosition(QTextCursor::End);
    setTextCursor(m_cursor);
}

TextEdit::~TextEdit()
{
}

void TextEdit::registerTclCommand()
{
}

std::string TextEdit::getLastCommand() const
{
    return m_currentCommand.toStdString();
}

std::vector<std::string> TextEdit::getCommands() const
{
    return m_commands;
}

void TextEdit::keyPressEvent(QKeyEvent* e)
{
    if ((e->key() == Qt::Key_Enter) || (e->key() == Qt::Key_Return))
    {
        QString currentText = toPlainText();
        
        // get the last command
        int commandStartInd = currentText.lastIndexOf('>');
        m_currentCommand = currentText.mid(commandStartInd +1).simplified();
        m_commands.push_back(m_currentCommand.toStdString());
        
        setText(currentText + "\n" + ">");
        m_cursor = textCursor();
        m_cursor.movePosition(QTextCursor::End);
        setTextCursor(m_cursor);

        Q_EMIT commandEntered();
    }
    else
    {
        QTextEdit::keyPressEvent(e);
    }
}
