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
    private:
        static const int H1_SIZE = 32;
        static const int H2_SIZE = 26;
        static const int H3_SIZE = 20;
        static const int P_SIZE = 15;
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

        void italicsSelection(bool isSet) {            
            QTextCursor cursor {textCursor()};
            QTextCharFormat bold;
            bold.setFontWeight(isSet ? QFont::StyleItalic : QFont::Normal);
            cursor.mergeCharFormat(bold);
            setFontWeight(isSet ? QFont::Bold : QFont::Normal);
        }
        
        void heading1Selection(bool isSet) {
            QTextCursor cursor {textCursor()};
            cursor.beginEditBlock();
            cursor.movePosition(QTextCursor::StartOfBlock);
            cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);

            QTextCharFormat bold;
            bold.setFontPointSize(isSet ? H1_SIZE : P_SIZE);
            cursor.mergeCharFormat(bold);

            cursor.endEditBlock();
            setFontPointSize(isSet ? H1_SIZE : P_SIZE);
        }
        
        void heading2Selection(bool isSet) {
            QTextCursor cursor {textCursor()};
            cursor.beginEditBlock();
            cursor.movePosition(QTextCursor::StartOfBlock);
            cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);

            QTextCharFormat bold;
            bold.setFontPointSize(isSet ? H2_SIZE : P_SIZE);
            cursor.mergeCharFormat(bold);

            cursor.endEditBlock();
            setFontPointSize(isSet ? H2_SIZE : P_SIZE);
        }

        void heading3Selection(bool isSet) {
            QTextCursor cursor {textCursor()};
            cursor.beginEditBlock();
            cursor.movePosition(QTextCursor::StartOfBlock);
            cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);

            QTextCharFormat bold;
            bold.setFontPointSize(isSet ? H3_SIZE : P_SIZE);
            cursor.mergeCharFormat(bold);

            cursor.endEditBlock();
            setFontPointSize(isSet ? H3_SIZE : P_SIZE);
        }
        
        void printText() {
            std::cout << "Save\n";
            std::cout << this->toHtml().toStdString();
        }
    };
}

#endif
