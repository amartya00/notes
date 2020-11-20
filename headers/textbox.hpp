#ifndef __SIGABRT_NOTES_TEXTBOX__
#define __SIGABRT_NOTES_TEXTBOX__

#include <memory>
#include <ios>
#include <iostream>

#include <QFont>
#include <QWidget>
#include <QTextEdit>
#include <QTextCursor>
#include <QTextCharFormat>
#include <QSizePolicy>
#include <QToolBar>

#include <constants.hpp>

namespace AppUI {
    class TextBox : public QTextEdit {
    public:
        TextBox(QWidget* parent):
            QTextEdit(parent) {
            setAcceptRichText(true);
            setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
            setStyleSheet(AppUI::ButtonConstants::TEXT_EDIT_DARK_BG_CSS);
        }
        
        void boldSelection(bool isSet) {            
            QTextCursor cursor {textCursor()};
            QTextCharFormat bold;
            bold.setFontWeight(isSet ? QFont::Bold : QFont::Normal);
            cursor.mergeCharFormat(bold);
            setFontWeight(isSet ? QFont::Bold : QFont::Normal);
        }
        
        void heading1Selection() {
            QTextCursor cursor {textCursor()};
            cursor.beginEditBlock();
            cursor.movePosition(QTextCursor::StartOfBlock);
            cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
            QString txt {cursor.selectedText()};
            cursor.insertHtml("<h1> " + txt + " </h1>");
            cursor.endEditBlock();
        }
        
        void heading2Selection() {
            QTextCursor cursor {textCursor()};
            cursor.beginEditBlock();
            cursor.movePosition(QTextCursor::StartOfBlock);
            cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
            QString txt {cursor.selectedText()};
            cursor.insertHtml("<h2> " + txt + " </h2>");
            cursor.endEditBlock();
        }
        
        void printText() {
            std::cout << "-------------------------\n";
            std::cout << this->toHtml().toStdString();
            std::cout << "-------------------------\n\n";
        }
    };
}

#endif
