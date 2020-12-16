#include <unordered_map>
#include <memory>
#include <vector>
#include <utility>
#include <QString>

#include <ui/wordprocessor.hpp>
#include <ui/models.hpp>
#include <ui/textbox.hpp>
#include <ui/actionbay.hpp>
#include <backend/notesdao.hpp>

using AppBackend::LocalDAO;
using AppUI::WordProcessor;
using AppUI::TextBox;
using AppUI::ActionBay;
using AppUI::ActionInfo;

WordProcessor::WordProcessor(
    QWidget* parent, 
    const std::unordered_map<QString, QString>& buttons,
    LocalDAO& dao,
    const AppUI::Mode mode,
    const QString& accent
    ):
    saveButtonLight {buttons.at("SaveButtonLight")},
    saveButtonDark {buttons.at("SaveButtonDark")},
    
    boldButtonLight {buttons.at("BoldButtonLight")},
    boldButtonDark {buttons.at("BoldButtonDark")},
    
    italicsButtonLight {buttons.at("ItalicsButtonLight")},
    italicsButtonDark {buttons.at("ItalicsButtonDark")},

    underlineButtonLight {buttons.at("UnderlineButtonLight")},
    underlineButtonDark {buttons.at("UnderlineButtonDark")},
    
    h1ButtonLight {buttons.at("H1ButtonLight")},
    h1ButtonDark {buttons.at("H1ButtonDark")},
    
    h2ButtonLight {buttons.at("H2ButtonLight")},
    h2ButtonDark {buttons.at("H2ButtonDark")},
    
    h3ButtonLight {buttons.at("H3ButtonLight")},
    h3ButtonDark {buttons.at("H3ButtonDark")},
    
    pButtonLight {buttons.at("PButtonLight")},
    pButtonDark {buttons.at("PButtonDark")},
    
    textBox {parent, dao, mode, accent},
    actionBay {parent, generateToolbarData(), mode, accent} {
        connectInternl();
        actionBay.getButton("p").setChecked(true);
        addWidget(&textBox);
        addWidget(&actionBay);
}

void WordProcessor::connectInternl() {
    connect(&actionBay.getButton("bold"), &QAction::toggled, &textBox, &AppUI::TextBox::boldSelection);
    connect(&actionBay.getButton("italics"), &QAction::toggled, &textBox, &AppUI::TextBox::italicsSelection);
    connect(&actionBay.getButton("underline"), &QAction::toggled, &textBox, &AppUI::TextBox::underlineSelection);
    connect(
        &actionBay.getButton("h1"), 
        &QAction::toggled, 
        &textBox,
        [this](bool isSet) {
            if (isSet) {
                actionBay.getButton("h2").setChecked(false);
                actionBay.getButton("h3").setChecked(false);
                actionBay.getButton("p").setChecked(false);
            } else {
                actionBay.getButton("p").setChecked(true);
            }
            textBox.heading1Selection(isSet);
        });
    connect(
        &actionBay.getButton("h2"), 
        &QAction::toggled, 
        &textBox,
        [this](bool isSet) {
            if (isSet) {
                actionBay.getButton("h1").setChecked(false);
                actionBay.getButton("h3").setChecked(false);
                actionBay.getButton("p").setChecked(false);
            } else {
                actionBay.getButton("p").setChecked(true);
            }
            textBox.heading2Selection(isSet);
        });
    connect(
        &actionBay.getButton("h3"), 
        &QAction::toggled, 
        &textBox,
        [this](bool isSet) {
            if (isSet) {
                actionBay.getButton("h1").setChecked(false);
                actionBay.getButton("h2").setChecked(false);
                actionBay.getButton("p").setChecked(false);
            } else {
                actionBay.getButton("p").setChecked(true);
            }
            textBox.heading3Selection(isSet);
        });
    connect(
        &actionBay.getButton("p"), 
        &QAction::toggled, 
        &textBox,
        [this](bool isSet) {
            if (isSet) {
                actionBay.getButton("h1").setChecked(false);
                actionBay.getButton("h2").setChecked(false);
                actionBay.getButton("h3").setChecked(false);
            }
            textBox.pSelection();
        });
    connect(
        &actionBay.getButton("save"),
        &QAction::triggered,
        &textBox,
        [this]() {
            textBox.save();
            emit noteSaved();
        });
}

std::vector<std::pair<QString, ActionInfo>> WordProcessor::generateToolbarData() {
    return {
            {
                "bold",
                {
                    boldButtonLight,
                    boldButtonDark,
                    true,
                    QKeySequence::Bold
                }
            },
            {
                "italics",
                {
                    italicsButtonLight,
                    italicsButtonDark,
                    true,
                    QKeySequence::Italic
                }
            },
            {
                "underline",
                {
                    underlineButtonLight,
                    underlineButtonDark,
                    true,
                    QKeySequence::Underline
                }
            },
            {
                "h1",
                {
                    h1ButtonLight,
                    h1ButtonDark,
                    true,
                    std::nullopt
                }
            },
            {
                "h2",
                {
                    h2ButtonLight,
                    h2ButtonDark,
                    true,
                    std::nullopt
                }
            },
            {
                "h3",
                {
                    h3ButtonLight,
                    h3ButtonDark,
                    true,
                    std::nullopt
                }
            },
            {
                "p",
                {
                    pButtonLight,
                    pButtonDark,
                    true,
                    std::nullopt
                }
            },
            {
                "save",
                {
                    saveButtonLight,
                    saveButtonDark,
                    false,
                    QKeySequence::Save
                }
            }
        };
}

const ActionBay& WordProcessor::getToolbar() const noexcept {
    return actionBay;    
}

void WordProcessor::refreshContent(const long noteId, bool writeBackContent) {
    textBox.refreshContent(noteId, writeBackContent);
}
