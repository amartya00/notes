#include <memory>
#include <ios>
#include <iostream>
#include <optional>

#include <QFont>
#include <QWidget>
#include <QTextBrowser>
#include <QTextCursor>
#include <QTextCharFormat>
#include <QSizePolicy>
#include <QToolBar>

#include <ui/constants.hpp>
#include <ui/textbox.hpp>
#include <backend/notesdao.hpp>
#include <backend/models.hpp>

namespace Colors = AppUI::Colours;
using AppUI::Mode;

AppUI::TextBox::TextBox(QWidget* parent, AppBackend::LocalDAO& dao, const AppUI::Mode& mode, const QString& accent):
    QTextBrowser(parent),
    dao {dao},
    mode {mode},
    accent {accent} {
    setAcceptRichText(true);
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    setStyleSheet(getCss());
    setFontPointSize(P_SIZE);
    setTextInteractionFlags(
        textInteractionFlags() |
        Qt::LinksAccessibleByMouse |
        Qt::LinksAccessibleByKeyboard
    );
    setOpenExternalLinks(true);
    setReadOnly(false);
}

AppUI::TextBox::~TextBox() {
    save();
}

QString AppUI::TextBox::getCss() const noexcept {
    switch (mode)
    {
    case AppUI::Mode::DARK:
        return CSS_TEMPLATE.arg(Colours::VERY_DARK_GRAY, accent, Colours::WHITE);
    default:
        return CSS_TEMPLATE.arg(Colours::LIGHT_GRAY, accent, Colours::BLACK);
    } 
}

QString AppUI::TextBox::extractTitle() const noexcept {
    QString text = toPlainText().trimmed();
    if(text == 0) {
        return "Untitled Note";
    } else {
        int firstSentenceLen = text.indexOf('.');
        firstSentenceLen = firstSentenceLen < 0? 51 : firstSentenceLen;
        int firstParaLen = text.indexOf('\n');
        firstParaLen = firstParaLen < 0? 51: firstParaLen;
        int titleLen = firstSentenceLen < firstParaLen ? firstSentenceLen : firstParaLen;
        return (titleLen > 0 && titleLen < 50) ? text.left(titleLen).trimmed() : text.left(50).trimmed();
    }
}

void AppUI::TextBox::boldSelection(bool isSet) noexcept {            
    QTextCursor cursor {textCursor()};
    QTextCharFormat bold;
    bold.setFontWeight(isSet ? QFont::Bold : QFont::Normal);
    cursor.mergeCharFormat(bold);
    setFontWeight(isSet ? QFont::Bold : QFont::Normal);
}

void AppUI::TextBox::italicsSelection(bool isSet) noexcept {            
    QTextCursor cursor {textCursor()};
    QTextCharFormat bold;
    bold.setFontItalic(isSet);
    cursor.mergeCharFormat(bold);
    setFontItalic(isSet);
}
void AppUI::TextBox::underlineSelection(bool isSet) noexcept {            
    QTextCursor cursor {textCursor()};
    QTextCharFormat bold;
    bold.setFontUnderline(isSet);
    cursor.mergeCharFormat(bold);
    setFontUnderline(isSet);
}

void AppUI::TextBox::heading1Selection(bool isSet) noexcept {
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

void AppUI::TextBox::heading2Selection(bool isSet) noexcept {
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

void AppUI::TextBox::heading3Selection(bool isSet) noexcept {
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

void AppUI::TextBox::pSelection() noexcept {
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
                std::nullopt,
                extractedTitle,
                toHtml()
            }
        );
    }
}

void AppUI::TextBox::refreshContent(const long newNoteId, bool writeBackContent) {
    if (writeBackContent) {
        save();
    }
    currentNoteId = newNoteId;
    std::optional<AppBackend::Note> note {dao.loadRecord(newNoteId)};
    if (note == std::nullopt) {
        throw std::runtime_error("Cannot load note with id " + std::to_string(newNoteId));
    } else {
        setText((*note).body);
        update();
    }
}
