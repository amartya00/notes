#ifndef __SIGABRT_NOTES_TEXTBOX__
#define __SIGABRT_NOTES_TEXTBOX__

#include <memory>

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
        
        
    public:
        TextBox(QWidget* parent):
            QTextEdit(parent) {
            setAcceptRichText(true);
            setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
            setStyleSheet(AppUI::ButtonConstants::TEXT_EDIT_DARK_BG_CSS);
        }
        
        void boldSelection() {
            QTextCursor cursor {textCursor()};
            
            QTextCharFormat bold;
            bold.setFontWeight(cursor.charFormat().font().bold() ? QFont::Normal : QFont::Bold);
            cursor.mergeCharFormat(bold);
            
        }
    };
}

#endif
