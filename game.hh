#ifndef GAME_HH
#define GAME_HH

#include <QDialog>

namespace Ui {
class game;
}

class game : public QDialog
{
    Q_OBJECT

public:
    explicit game(QWidget *parent = nullptr);
    ~game();

private:
    Ui::game *ui;
};

#endif // GAME_HH
