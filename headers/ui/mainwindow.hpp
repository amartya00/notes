#ifndef __SIGABRT_NOTES__MAINWINDOW__
#define __SIGABRT_NOTES__MAINWINDOW__

#include <memory>
#include <map>
#include <utility>
#include <unordered_map>

#include <QWidget>
#include <QGridLayout>
#include <QTextDocument>
#include <QTextEdit>
#include <QString>
#include <QTextCursor>
#include <QKeySequence>

#include <ui/buttonbay.hpp>
#include <ui/actionbay.hpp>
#include <ui/constants.hpp>
#include <ui/textbox.hpp>
#include <ui/itemlist.hpp>

#include <backend/notesdao.hpp>
#include <backend/models.hpp>

namespace AppUI {
    class MainWindow : public QWidget {
    private:
        const std::vector<std::pair<QString, AppUI::ActionInfo>> toolbar {
            {
                "bold",
                {
                    ":/resources/images/format_bold-black-180dp.png",
                    ":/resources/images/format_bold-white-180dp.png",
                    true,
                    QKeySequence::Bold
                }
            },
            {
                "italics",
                {
                    ":/resources/images/format_italic-black-180dp.png",
                    ":/resources/images/format_italic-white-180dp.png",
                    true,
                    QKeySequence::Italic
                }
            },
            {
                "underline",
                {
                    ":/resources/images/format_underlined-black-180dp.png",
                    ":/resources/images/format_underlined-white-180dp.png",
                    true,
                    QKeySequence::Underline
                }
            },
            {
                "h1",
                {
                    ":/resources/images/format_h1-black-180dp.png",
                    ":/resources/images/format_h1-white-180dp.png",
                    true,
                    std::nullopt
                }
            },
            {
                "h2",
                {
                    ":/resources/images/format_h2-black-180dp.png",
                    ":/resources/images/format_h2-white-180dp.png",
                    true,
                    std::nullopt
                }
            },
            {
                "h3",
                {
                    ":/resources/images/format_h3-black-180dp.png",
                    ":/resources/images/format_h3-white-180dp.png",
                    true,
                    std::nullopt
                }
            },
            {
                "p",
                {
                    ":/resources/images/format_p-black-180dp.png",
                    ":/resources/images/format_p-white-180dp.png",
                    true,
                    std::nullopt
                }
            },
            {
                "save",
                {
                    ":/resources/images/save-black-180dp.png",
                    ":/resources/images/save-white-180dp.png",
                    false,
                    QKeySequence::Save
                }
            },
        };
        
        const std::vector<std::pair<QString, AppUI::ActionInfo>> listToolbar {
            {
                "new",
                {
                    ":/resources/images/fnote_add-black-180dp.png",
                    ":/resources/images/note_add-white-180dp.png",
                    false,
                    QKeySequence::New
                }
            },
            {
                "delete",
                {
                    ":/resources/images/delete-black-180dp.png",
                    ":/resources/images/delete-white-180dp.png",
                    false,
                    QKeySequence::Delete
                }
            }
        };
        
        AppBackend::LocalDAO& dao;
        std::unique_ptr<QGridLayout> mainGrid;
        std::unique_ptr<AppUI::TextBox> textBox;
        std::unique_ptr<AppUI::ActionBay> actionBay;
        std::unique_ptr<AppUI::ItemList> noteList;
        std::unique_ptr<AppUI::ActionBay> listActionBay;

        void connectTextBoxToolbar();
        AppBackend::Note newNote() const noexcept;
        AppBackend::Note newNote() noexcept;
        
    public:
        MainWindow(const std::size_t initWidth, const std::size_t initHeight, AppBackend::LocalDAO& dao);
    };
}

#endif
