#ifndef __SIGABRT_NOTES__MAINWINDOW__
#define __SIGABRT_NOTES__MAINWINDOW__

#include <memory>
#include <map>
#include <utility>

#include <QWidget>
#include <QGridLayout>
#include <QTextDocument>
#include <QTextEdit>
#include <QString>
#include <QFrame>
#include <QPushButton>
#include <QTextCursor>
#include <QKeySequence>

#include <ui/buttonbay.hpp>
#include <ui/actionbay.hpp>
#include <ui/constants.hpp>
#include <ui/textbox.hpp>

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

        std::unique_ptr<QGridLayout> mainGrid;
        std::unique_ptr<AppUI::TextBox> textBox;
        std::unique_ptr<AppUI::ActionBay> actionBay;

        void connectTextBoxToolbar() {
            connect(actionBay->getButton("bold").get(), &QAction::toggled, textBox.get(), &AppUI::TextBox::boldSelection);
            connect(actionBay->getButton("italics").get(), &QAction::toggled, textBox.get(), &AppUI::TextBox::italicsSelection);
            connect(actionBay->getButton("underline").get(), &QAction::toggled, textBox.get(), &AppUI::TextBox::underlineSelection);
            connect(
                actionBay->getButton("h1").get(), 
                &QAction::toggled, 
                textBox.get(),
                [this](bool isSet) {
                    if (isSet) {
                        actionBay->getButton("h2")->setChecked(false);
                        actionBay->getButton("h3")->setChecked(false);
                        actionBay->getButton("p")->setChecked(false);
                    }
                    textBox->heading1Selection(isSet);
                });
            connect(
                actionBay->getButton("h2").get(), 
                &QAction::toggled, 
                textBox.get(),
                [this](bool isSet) {
                    if (isSet) {
                        actionBay->getButton("h1")->setChecked(false);
                        actionBay->getButton("h3")->setChecked(false);
                        actionBay->getButton("p")->setChecked(false);
                    }
                    textBox->heading2Selection(isSet);
                });
            connect(
                actionBay->getButton("h3").get(), 
                &QAction::toggled, 
                textBox.get(),
                [this](bool isSet) {
                    if (isSet) {
                        actionBay->getButton("h1")->setChecked(false);
                        actionBay->getButton("h2")->setChecked(false);
                        actionBay->getButton("p")->setChecked(false);
                    }
                    textBox->heading3Selection(isSet);
                });
            connect(
                actionBay->getButton("p").get(), 
                &QAction::toggled, 
                textBox.get(),
                [this](bool isSet) {
                    if (isSet) {
                        actionBay->getButton("h1")->setChecked(false);
                        actionBay->getButton("h2")->setChecked(false);
                        actionBay->getButton("h3")->setChecked(false);
                    }
                    textBox->heading3Selection(isSet);
                });
            connect(actionBay->getButton("save").get(), &QAction::triggered, textBox.get(), &AppUI::TextBox::printText);
        }

    public:
        MainWindow(const std::size_t initWidth, const std::size_t initHeight): 
            mainGrid {std::make_unique<QGridLayout>(this)},
            textBox {std::make_unique<AppUI::TextBox>(this)},
            actionBay {std::make_unique<AppUI::ActionBay>(this, toolbar, AppUI::Mode::DARK)} {
                
                connectTextBoxToolbar();

                mainGrid->addWidget(textBox.get(), 0, 0);
                mainGrid->addWidget(actionBay.get(), 1, 0);
                setLayout(mainGrid.get());
                this->setStyleSheet(AppUI::ButtonConstants::MAN_WINDOW_DARK_CSS);
                this->resize(initWidth, initHeight);
            }
    };
}

#endif
