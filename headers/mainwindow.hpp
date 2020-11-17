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
        std::unique_ptr<QGridLayout> mainGrid;
        std::unique_ptr<AppUI::TextBox> textBox;
        std::unique_ptr<AppUI::ActionBay> actionBay;
        
    public:
        MainWindow(const std::size_t initWidth, const std::size_t initHeight): 
            mainGrid {std::make_unique<QGridLayout>(this)},
            textBox {std::make_unique<AppUI::TextBox>(this)},
            actionBay {std::make_unique<AppUI::ActionBay>(
                this,
                std::vector<std::pair<QString, AppUI::ActionInfo>>{
                    {
                        "save",
                        {   
                            ":/resources/images/save-button.png",
                            false,
                            std::nullopt
                        }
                    }, 
                    {
                        "bold", 
                        {
                            ":/resources/images/bold-button.png",
                            true,
                            QKeySequence::Bold
                        }
                        
                    }
                }
                
            )} {
                
                connect(actionBay->getButton("bold").get(), &QAction::toggled, textBox.get(), &AppUI::TextBox::boldSelection);
                //connect(buttonBay->getButton("h1").get(), &QPushButton::clicked, textBox.get(), &AppUI::TextBox::heading1Selection);
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
