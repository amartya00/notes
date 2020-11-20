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

#include <buttonbay.hpp>
#include <actionbay.hpp>
#include <constants.hpp>
#include <textbox.hpp>

namespace AppUI {
    class MainWindow : public QWidget {
    private:
        const std::vector<std::pair<QString, AppUI::ActionInfo>> toolbar {
            {
                "bold",
                {
                    ":/resources/images/round_format_bold_black_18dp.png",
                    ":/resources/images/round_format_bold_white_18dp.png",
                    true,
                    QKeySequence::Bold
                }
            },
            {
                "italics",
                {
                    ":/resources/images/round_format_italic_black_18dp.png",
                    ":/resources/images/round_format_italic_white_18dp.png",
                    true,
                    QKeySequence::Italic
                }
            },
            {
                "lock",
                {
                    ":/resources/images/round_lock_black_18dp.png",
                    ":/resources/images/round_lock_white_18dp.png",
                    true,
                    std::nullopt
                }
            },
            {
                "save",
                {
                    ":/resources/images/round_save_black_18dp.png",
                    ":/resources/images/round_save_white_18dp.png",
                    false,
                    QKeySequence::Save
                }
            }
        };
        
        std::unique_ptr<QGridLayout> mainGrid;
        std::unique_ptr<AppUI::TextBox> textBox;
        std::unique_ptr<AppUI::ActionBay> actionBay;
        
    public:
        MainWindow(const std::size_t initWidth, const std::size_t initHeight): 
            mainGrid {std::make_unique<QGridLayout>(this)},
            textBox {std::make_unique<AppUI::TextBox>(this)},
            actionBay {std::make_unique<AppUI::ActionBay>(this, toolbar, AppUI::Mode::DARK, AppUI::Colours::PINK)} {
                connect(actionBay->getButton("bold").get(), &QAction::toggled, textBox.get(), &AppUI::TextBox::boldSelection);
                //\connect(buttonBay->getButton("h1").get(), &QPushButton::clicked, textBox.get(), &AppUI::TextBox::heading1Selection);
                //connect(buttonBay->getButton("h2").get(), &QPushButton::clicked, textBox.get(), &AppUI::TextBox::heading2Selection);
                //connect(buttonBay->getButton("save").get(), &QPushButton::clicked, textBox.get(), &AppUI::TextBox::printText);
                //actionBay->getButton("bold")->connect(textBox->boldSelection);
                mainGrid->addWidget(textBox.get(), 0, 0);
                mainGrid->addWidget(actionBay.get(), 1, 0);
                setLayout(mainGrid.get());
                this->setStyleSheet(AppUI::ButtonConstants::MAN_WINDOW_DARK_CSS);
                this->resize(initWidth, initHeight);
            }
    };
}

#endif
