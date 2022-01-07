/*
 * This header file declare necessary slots, functions, variables
 * and containers for the pairs game. There are private slots, used when
 * a the user clicks buttons or enters names and number. A new dialog
 * for the actual gameplay. Players' name, points is also declared besides
 * the game status. Characteristics for a button with picture is added.
 * Many self-made functions are create for each phase during the game.
 *
 * Program author
 * Name: Anh Pham
 * Student number: 050357871
 * UserID: skanph
 * E-mail: anh.pham@tuni.fi
 * */

#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QString>
#include <game.hh>
#include <QWidget>
#include <QGridLayout>
#include <iostream>
#include <QPixmap>
#include <vector>
#include <string>
#include <map>
#include <QPushButton>
#include <random>
#include <algorithm>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_player2_editingFinished();

    void on_player1_editingFinished();

    void on_card_number_editingFinished();

    void on_start_button_clicked();

    void card_clicked();

    void next_player_clicked();
private:
    Ui::MainWindow *ui;

    // Create a new dialog
    game *new_game;

    // Players' characteristics: Name, turn, points,
    // and their found pairs
    QString player1;
    QString player2;
    QString in_turn;
    int player1_pts = 0;
    int player2_pts = 0;
    std::vector<std::string> player1_pairs;
    std::vector<std::string> player2_pairs;

    // Card's characteristics
    int card_number;
    int row = 0;
    int column = 0;
    int cards_opened = 0;
    int turn = 0;
    int remaining_cards;

    // Pictures' sizes and structures
    const int PIC_SIZE = 50;
    const int MARGIN = 20;
    const std::string PREFIX = ":/";
    const std::string SUFFIX = ".png";
    const std::vector<std::string>
            fruits = {"cherries", "strawberry", "orange", "pear", "apple",
                      "bananas", "tomato", "grapes", "eggplant", "lemon",
                      "mango", "watermelon", "pineapple","mangtosteen",
                      "coconut", "kiwi", "lychee", "starfruit", "cucumber",
                      "sapodilla","jackfruit"};
    QPixmap closed_picture = QString::fromStdString(":/question.png");
    QPixmap found_picture = QString::fromStdString(":/found.png");

    // A bool value to mark if the current player found the pair
    bool pair_found = false;

    // Containers to stores buttons and pictures
    std::vector<QPushButton*> all_card_buttons;
    std::vector<QPushButton*> opened_cards;
    std::vector<QPixmap> all_pictures;
    std::vector<std::string> all_pictures_name;
    std::map<QPushButton*, std::string> button_with_pictures;
    std::map<std::string, QPixmap> name_to_picture;


    // Void functions to perform actions around the game
    void calculate_factor(int& row, int& column);
    void init_board(int row, int column);
    void add_and_shuffle_pictures();
    void update_score();
    void close_opened_cards();
    void add_point();
    void announce_winner();
    void reset();
};
#endif // MAINWINDOW_HH
