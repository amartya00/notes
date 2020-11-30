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
#include <ui/textbox.hpp>
#include <backend/notesdao.hpp>
#include <backend/models.hpp>

QString AppUI::TextBox::extractTitle() const {
    QString text = toPlainText().trimmed();
    if(text == 0) {
        return "Untitled Note";
    } else {
        int firstSentenceLen = text.indexOf('.');
        firstSentenceLen = firstSentenceLen < 0? 51 : firstSentenceLen;
        int firstParaLen = text.indexOf('\n');
        firstParaLen = firstParaLen < 0? 51: firstParaLen;
        int titleLen = firstSentenceLen < firstParaLen ? firstSentenceLen : firstParaLen;
        return (titleLen > 0 && titleLen < 50) ? text.left(titleLen) : text.left(50);
    }
}

AppUI::TextBox::TextBox(QWidget* parent, AppBackend::LocalDAO& dao):
    QTextEdit(parent),
    dao {dao} {
    setAcceptRichText(true);
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    setStyleSheet(AppUI::ButtonConstants::TEXT_EDIT_DARK_BG_CSS);
    setFontPointSize(P_SIZE);
}

void AppUI::TextBox::boldSelection(bool isSet) {            
    QTextCursor cursor {textCursor()};
    QTextCharFormat bold;
    bold.setFontWeight(isSet ? QFont::Bold : QFont::Normal);
    cursor.mergeCharFormat(bold);
    setFontWeight(isSet ? QFont::Bold : QFont::Normal);
}

void AppUI::TextBox::italicsSelection(bool isSet) {            
    QTextCursor cursor {textCursor()};
    QTextCharFormat bold;
    bold.setFontItalic(isSet);
    cursor.mergeCharFormat(bold);
    setFontItalic(isSet);
}
void AppUI::TextBox::underlineSelection(bool isSet) {            
    QTextCursor cursor {textCursor()};
    QTextCharFormat bold;
    bold.setFontUnderline(isSet);
    cursor.mergeCharFormat(bold);
    setFontUnderline(isSet);
}

void AppUI::TextBox::heading1Selection(bool isSet) {
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

void AppUI::TextBox::heading2Selection(bool isSet) {
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

void AppUI::TextBox::heading3Selection(bool isSet) {
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

void AppUI::TextBox::pSelection() {
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

void AppUI::TextBox::save() {
    if (currentNoteId != std::nullopt){
        QString extractedTitle {extractTitle()};
        dao.upsertRecord(
            AppBackend::Note {
                *currentNoteId,
                extractedTitle,
                toHtml()
            }
        );
    }
}

void AppUI::TextBox::refreshContent(const long newNoteId) {
    save();
    currentNoteId = newNoteId;
    std::optional<AppBackend::Note> note {dao.loadRecord(newNoteId)};
    if (note == std::nullopt) {
        throw std::runtime_error("Cannot load note with id " + std::to_string(newNoteId));
    } else {
        setText((*note).body);
        update();
    }
}
