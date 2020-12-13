#ifndef __SIGABRT_NOTES__MAINWINDOW__
#define __SIGABRT_NOTES__MAINWINDOW__

#include <unordered_map>

#include <QWidget>
#include <QGridLayout>
#include <QTextDocument>
#include <QTextEdit>
#include <QString>
#include <QTextCursor>
#include <QKeySequence>

#include <ui/actionbay.hpp>
#include <ui/constants.hpp>
#include <ui/itemlist.hpp>
#include <ui/wordprocessor.hpp>
#include <ui/notesidebar.hpp>

#include <backend/notesdao.hpp>
#include <backend/models.hpp>

namespace AppUI {
    class MainWindow : public QWidget {
    private:
        const QString CSS_TEMPLATE {"background-color: %1; color: white; padding-left: 0px; margin-left: 0px;"};
        const std::unordered_map<QString, QString> iconMap {
            {"SaveButtonLight", ":/resources/images/save-black-180dp.png"},
            {"SaveButtonDark", ":/resources/images/save-white-180dp.png"},

            {"BoldButtonLight", ":/resources/images/format_bold-black-180dp.png",},
            {"BoldButtonDark", ":/resources/images/format_bold-white-180dp.png",},

            {"ItalicsButtonLight", ":/resources/images/format_italic-black-180dp.png"},
            {"ItalicsButtonDark", ":/resources/images/format_italic-white-180dp.png"},

            {"UnderlineButtonLight", ":/resources/images/format_underlined-black-180dp.png"},
            {"UnderlineButtonDark", ":/resources/images/format_underlined-white-180dp.png"},

            {"H1ButtonLight", ":/resources/images/format_h1-black-180dp.png"},
            {"H1ButtonDark", ":/resources/images/format_h1-white-180dp.png"},

            {"H2ButtonLight", ":/resources/images/format_h2-black-180dp.png"},
            {"H2ButtonDark", ":/resources/images/format_h2-white-180dp.png"},

            {"H3ButtonLight", ":/resources/images/format_h3-black-180dp.png"},
            {"H3ButtonDark", ":/resources/images/format_h3-white-180dp.png"},

            {"PButtonLight", ":/resources/images/format_p-black-180dp.png"},
            {"PButtonDark", ":/resources/images/format_p-white-180dp.png"},
            
            {"NewButtonLight", ":/resources/images/note_add-black-180dp.png"},
            {"NewButtonDark", ":/resources/images/note_add-white-180dp.png"},
            
            {"DeleteButtonLight", ":/resources/images/delete-black-180dp.png"},
            {"DeleteButtonDark", ":/resources/images/delete-white-180dp.png"},
        };
        
        AppBackend::LocalDAO& dao;
        AppUI::Mode mode;
        QGridLayout mainGrid;
        AppUI::WordProcessor wordProcessor;
        AppUI::NoteSidebar noteList;

        QString getCss() const noexcept;
        void connectTextBoxToolbar() noexcept;
        AppBackend::Note newNote() const noexcept;
        
    public:
        MainWindow(
            const std::size_t initWidth,
            const std::size_t initHeight,
            AppBackend::LocalDAO& dao,
            const AppUI::Mode& mode,
            const QString& accent);
    };
}

#endif
