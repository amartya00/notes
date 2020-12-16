#ifndef __SIGABRT_NOTES_TEXTBOX__
#define __SIGABRT_NOTES_TEXTBOX__

#include <memory>
#include <ios>
#include <iostream>
#include <optional>

#include <QTextBrowser>

#include <ui/constants.hpp>
#include <backend/notesdao.hpp>
#include <backend/models.hpp>

namespace AppUI {
    class TextBox : public QTextBrowser {
    private:
        static const int H1_SIZE = 32;
        static const int H2_SIZE = 26;
        static const int H3_SIZE = 20;
        static const int P_SIZE = 14;

        AppBackend::LocalDAO& dao;
        std::optional<long> currentNoteId {std::nullopt};
        AppUI::Mode mode;
        QString accent;
        const QString CSS_TEMPLATE {
            "background: %1; "
            "font-size: 15px; "
            "font-family: 'Ubuntu'; "
            "color: %3;"
            "border: 2px solid %2; "
            "border-radius: 3px;"
            "padding: 8px;"
        };

        QString extractTitle() const noexcept;

    public:
        TextBox(QWidget* parent, AppBackend::LocalDAO& dao, const AppUI::Mode& mode, const QString& accent);
        ~TextBox();
        QString getCss() const noexcept;
        void boldSelection(bool isSet) noexcept;
        void italicsSelection(bool isSet) noexcept;
        void underlineSelection(bool isSet) noexcept;
        void heading1Selection(bool isSet) noexcept;
        void heading2Selection(bool isSet) noexcept;
        void heading3Selection(bool isSet) noexcept;
        void pSelection() noexcept;
        void save();
        void refreshContent(const long newNoteId, bool writeBackCurrent);
    };
}

#endif
