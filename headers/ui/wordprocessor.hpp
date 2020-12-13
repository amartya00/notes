#ifndef __SIGABRT_NOTES_WORD__
#define __SIGABRT_NOTES_WORD__

#include <unordered_map>
#include <memory>
#include <utility>
#include <vector>

#include <QString>
#include <QWidget>
#include <QVBoxLayout>

#include <ui/textbox.hpp>
#include <ui/actionbay.hpp>
#include <ui/constants.hpp>
#include <backend/notesdao.hpp>

namespace AppUI {
    class WordProcessor: public QVBoxLayout {
        Q_OBJECT
    private:
        const QString saveButtonLight;
        const QString saveButtonDark;

        const QString boldButtonLight;
        const QString boldButtonDark;
        
        const QString italicsButtonLight;
        const QString italicsButtonDark;
        
        const QString underlineButtonLight;
        const QString underlineButtonDark;

        const QString h1ButtonLight;
        const QString h1ButtonDark;

        const QString h2ButtonLight;
        const QString h2ButtonDark;

        const QString h3ButtonLight;
        const QString h3ButtonDark;

        const QString pButtonLight;
        const QString pButtonDark;

        AppUI::TextBox textBox;
        AppUI::ActionBay actionBay;

        void connectInternl();
        std::vector<std::pair<QString, AppUI::ActionInfo>> generateToolbarData();

    public:
        WordProcessor(
            QWidget* parent, 
            const std::unordered_map<QString, QString>& buttons, 
            AppBackend::LocalDAO& dao, 
            const AppUI::Mode mode,
            const QString& accent
        );

        const AppUI::ActionBay& getToolbar() const noexcept;
        void refreshContent(const long noteId);
        
    signals:
        void noteSaved();
    };
}

#endif
