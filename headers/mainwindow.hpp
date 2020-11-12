#ifndef __SIGABRT_NOTES__MAINWINDOW__
#define __SIGABRT_NOTES__MAINWINDOW__

#include <memory>
#include <unordered_map>

#include <QWidget>
#include <QGridLayout>
#include <QTextDocument>
#include <QTextEdit>
#include <QString>
#include <QFrame>
#include <QPushButton>
#include <QTextCursor>

#include <buttonbay.hpp>
#include <constants.hpp>
#include <textbox.hpp>

namespace AppUI {
    class MainWindow : public QWidget {
    private:
        const std::size_t initWidth;
        const std::size_t initHeight;
        
        std::unique_ptr<QGridLayout> mainGrid;
        std::unique_ptr<AppUI::TextBox> textBox;
        std::unique_ptr<AppUI::ButtonBay> buttonBay;
        
    public:
        MainWindow(const std::size_t initWidth, const std::size_t initHeight): 
            initWidth {initWidth},
            initHeight {initHeight},
            mainGrid {std::make_unique<QGridLayout>(this)},
            textBox {std::make_unique<AppUI::TextBox>(this)},
            buttonBay {std::make_unique<AppUI::ButtonBay>(
                this,
                std::unordered_map<QString, AppUI::ButtonInfo>{
                    {
                        "save", 
                        {
                            AppUI::ButtonConstants::PLAIN_ROUNDED_CSS,
                            ":/resources/images/save-button.png"
                        }
                    }, 
                    {
                        "bold", 
                        {
                            AppUI::ButtonConstants::PLAIN_ROUNDED_CSS,
                            ":/resources/images/bold-button.png"
                            
                        }
                    }
                }
                
            )} {
                connect(buttonBay->getButton("bold").get(), &QPushButton::clicked, textBox.get(), &AppUI::TextBox::boldSelection);
                mainGrid->addWidget(textBox.get(), 0, 0);
                mainGrid->addLayout(buttonBay.get(), 1, 0);
                setLayout(mainGrid.get());
                this->setStyleSheet(AppUI::ButtonConstants::MAN_WINDOW_DARK_CSS);
                this->resize(initWidth, initHeight);
            }
    };
}

#endif
