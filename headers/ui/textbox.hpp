#ifndef __SIGABRT_NOTES_TEXTBOX__
#define __SIGABRT_NOTES_TEXTBOX__

#include <memory>
#include <ios>
#include <iostream>
#include <optional>

#include <QFont>
#include <QWidget>
#include <QTextEdit>
#include <QTextCursor>
#include <QTextCharFormat>
#include <QSizePolicy>
#include <QToolBar>

#include <ui/constants.hpp>
#include <backend/notesdao.hpp>
#include <backend/models.hpp>

namespace AppUI {
    class TextBox : public QTextEdit {
    private:
        static const int H1_SIZE = 32;
        static const int H2_SIZE = 26;
        static const int H3_SIZE = 20;
        static const int P_SIZE = 15;
        
        AppBackend::LocalDAO& dao;
        long currentNoteId;
        
        QString extractTitle() const {
            QString text = toPlainText().trimmed();
            if(text == 0) {
                return "Untitled Note";
            } else {
                int firstSentenceLen = text.indexOf('.');
                int firstParaLen = text.indexOf('\n');
                int titleLen = firstSentenceLen < firstParaLen ? firstSentenceLen : firstParaLen;
                return (titleLen > 0 && titleLen < 50) ? text.left(titleLen) : text.left(50);
            }
        }

    public:
        TextBox(QWidget* parent, AppBackend::LocalDAO& dao):
            QTextEdit(parent),
            dao {dao} {
            setAcceptRichText(true);
            setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
            setStyleSheet(AppUI::ButtonConstants::TEXT_EDIT_DARK_BG_CSS);
            setFontPointSize(P_SIZE);
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
            bold.setFontItalic(isSet);
            cursor.mergeCharFormat(bold);
            setFontItalic(isSet);
        }
        void underlineSelection(bool isSet) {            
            QTextCursor cursor {textCursor()};
            QTextCharFormat bold;
            bold.setFontUnderline(isSet);
            cursor.mergeCharFormat(bold);
            setFontUnderline(isSet);
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
        
        void pSelection() {
            QTextCursor cursor {textCursor()};
            cursor.beginEditBlock();
            cursor.movePosition(QTextCursor::StartOfBlock);
            cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);

            QTextCharFormat bold;
            bold.setFontPointSize(P_SIZE);
            cursor.mergeCharFormat(bold);

            cursor.endEditBlock();
            setFontPointSize(P_SIZE);
        }
        
        void save() {
            QString extractedTitle {extractTitle()};
            dao.upsertRecord(
                AppBackend::Note {
                    currentNoteId,
                    extractedTitle,
                    toHtml()
                }
            );
        }

        void refreshContent(const long newNoteId) {
            currentNoteId = newNoteId;
            std::optional<AppBackend::Note> note {dao.loadRecord(newNoteId)};
            if (note == std::nullopt) {
                throw std::runtime_error("Cannot load note with id " + std::to_string(newNoteId));
            } else {
                setText((*note).body);
                update();
            }
        }
    };
}

#endif
