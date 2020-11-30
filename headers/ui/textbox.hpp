#ifndef __SIGABRT_NOTES_TEXTBOX__
#define __SIGABRT_NOTES_TEXTBOX__

#include <memory>
#include <ios>
#include <iostream>
#include <optional>

#include <QTextEdit>

#include <ui/constants.hpp>
#include <backend/notesdao.hpp>
#include <backend/models.hpp>

namespace AppUI {
    class TextBox : public QTextEdit {
    private:
        static const int H1_SIZE = 32;
        static const int H2_SIZE = 26;
        static const int H3_SIZE = 20;
        static const int P_SIZE = 14;

        AppBackend::LocalDAO& dao;
        std::optional<long> currentNoteId {std::nullopt};

        QString extractTitle() const;

    public:
        TextBox(QWidget* parent, AppBackend::LocalDAO& dao);
        ~TextBox();
        void boldSelection(bool isSet);
        void italicsSelection(bool isSet);
        void underlineSelection(bool isSet);
        void heading1Selection(bool isSet);
        void heading2Selection(bool isSet);
        void heading3Selection(bool isSet);
        void pSelection();
        void save();
        void refreshContent(const long newNoteId);
        void resetView();
    };
}

#endif
