/* Pairs game
 * Description:
 * This program generates the pairs game using QT GUI. The game allows 2
 * players and a variant number of playing cards between 20 and 40. Initially,
 * the program asks players' name and a number of card. If the inserted amount
 * is not valid (No name, same name, wrong amount of cards entered), the
 * message box raises corresponding errors after pressing the start button.
 * If all values are sufficient, the program creates a new dialog, where the
 * number of card buttons that is previously entered, a switch player, reset,
 * and quit button. Each card button has the same figure behind as exactly one
 * other card button, and the player's job is to find those 2 buttons at the
 * same turn. If they are found, the player will be awarded 1 point and won
 * the next turn. The player's points and turn will be updated after pressing
 * the switch player button. The message box also have information about which
 * fruit the players collected. The reset button resets all players' points,
 * shuffles all the cards and starts a new game. Both the main program and the
 * dialog have the quit button, which terminates the program. When all cards
 * are found, the status box tells which player won and his/her points, or
 * it is a draw of the point.
 *
 * Program author
 * Name: Anh Pham
 * Student number: 050357871
 * UserID: skanph
 * E-mail: anh.pham@tuni.fi
 **/

#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "game.hh"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Store player1's name
void MainWindow::on_player1_editingFinished()
{
    player1 = ui->player1->text();
}

// Store player2's name
void MainWindow::on_player2_editingFinished()
{
    player2 = ui->player2->text();
}

// Sotre total number of cards as int value
void MainWindow::on_card_number_editingFinished()
{
    card_number = ui->card_number->text().toInt();
}

// Add and shuffle required pictures using std::random_shuffle
void MainWindow::add_and_shuffle_pictures(){

    // Add 2 same image to the 2 vectors that store picture and name
    for (auto i = 0; i < card_number/2; ++i){
        std::string filename = PREFIX + fruits.at(i) + SUFFIX;
        QPixmap image(QString::fromStdString(filename));
        all_pictures.push_back(image);
        all_pictures.push_back(image);
        all_pictures_name.push_back(fruits.at(i));
        all_pictures_name.push_back(fruits.at(i));
    }
    for (unsigned j = 0 ; j < all_pictures.size(); ++j)
        name_to_picture.insert({all_pictures_name.at(j), all_pictures.at(j)});
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(all_pictures.begin(), all_pictures.end(),g);
    std::shuffle(all_pictures_name.begin(), all_pictures_name.end(),g);
}

// Raise errors or start game when the Start button is clicked
void MainWindow::on_start_button_clicked()
{
    ui->player1->editingFinished();
    ui->player2->editingFinished();
    ui->card_number->editingFinished();

    // Raise necessary errors
    if (player1 == "" or player2 == "")
        ui->text_browser->setText("Players' name is empty.");
    else if (player1 == player2)
        ui->text_browser->setText("Invalid name format. Try again.");

    else if (card_number < 20 or card_number > 40 or card_number % 2 != 0)
        ui->text_browser->setText("Invalid number of cards.\n"
                                 "There should be an even number "
"                                 between 20-40 pairs only.");

    // Assign values and create board
    else{
        ui->text_browser->setText("Game starts.\n"
                                  "It's " + player1 + "'s turn.");
        ui->start_button->setEnabled(false);
        remaining_cards = card_number;
        calculate_factor(row, column);
        init_board(row, column);
    }
}

// Calculate row and column of the button table
void MainWindow::calculate_factor(int &row, int &column){
    for (int i = 1; i*i <= card_number; ++i){
        if (card_number % i == 0)
            row = i;
    }
    column = card_number / row;
}

// Create the board based on number of cards.
// All buttons have the question (not opened) picture.
void MainWindow::init_board(int row, int column){

    //Create new dialog, widget and grid layout in the dialog
    new_game = new game(this);
    QWidget *widget = new QWidget(new_game);
    QGridLayout *grid_layout = new QGridLayout(widget);

    // Create card buttons, add pictures, set size and add to layout
    for (int i = 0; i < row; ++i){
        for (int j = 0; j < column; ++j){
            QPushButton * button = new QPushButton(this);
            button->setFixedSize(MARGIN + PIC_SIZE + MARGIN,
                                 MARGIN + PIC_SIZE + MARGIN);
            button->setIcon(closed_picture);
            button->setIconSize(QSize(PIC_SIZE, PIC_SIZE));
            all_card_buttons.push_back(button);
            grid_layout->addWidget(button,i,j);
            connect(button, &QPushButton::clicked,
                    this, &MainWindow::card_clicked);
        }
    }

    // Create switch player button, set place
    QPushButton *next_player = new QPushButton("Switch player", this);
    grid_layout->addWidget(next_player, 0, column + 1);
    connect(next_player, &QPushButton::clicked,
            this, &MainWindow::next_player_clicked);

    // Show the dialog with required number of
    // buttons and pictures
    add_and_shuffle_pictures();
    new_game->show();

    // Add to the container, used to reveal card's picture
    for(unsigned long k = 0; k < all_card_buttons.size(); k++)
        button_with_pictures.insert({all_card_buttons.at(k),
                                     all_pictures_name.at(k)});

    // Create reset button
    QPushButton *reset_button = new QPushButton("Reset", this);
    grid_layout->addWidget(reset_button, 1, column + 1);
    connect(reset_button, &QPushButton::clicked, this, &MainWindow::reset);

    // Create quit button
    QPushButton *quit_button = new QPushButton("Quit", this);
    grid_layout->addWidget(quit_button, 2, column + 1);
    connect(quit_button, &QPushButton::clicked, this, &MainWindow::close);

    new_game->adjustSize();
}

// Function of the reset button
void MainWindow::reset(){

    // Reset all variables to the initial case
    player1_pts = 0;
    player2_pts = 0;
    in_turn = "";
    turn = 1;
    remaining_cards = card_number;
    cards_opened = 0;
    opened_cards.clear();
    button_with_pictures.clear();

    for (auto &button: all_card_buttons){
        button->setIcon(closed_picture);
        button->setEnabled(true);
    }
    ui->text_browser->setText("Game restarts.\n"
                              "It's " + player1 + "'s turn.");

    // Shuffle pictures again and add back to container
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(all_pictures.begin(), all_pictures.end(),g);
    std::shuffle(all_pictures_name.begin(), all_pictures_name.end(),g);
    for (unsigned long i = 0;i < all_card_buttons.size(); i++)
        button_with_pictures.insert({all_card_buttons.at(i),
                                     all_pictures_name.at(i)});
}

// Function of a card when clicked
void MainWindow::card_clicked(){
    if (cards_opened <= 1) {

        // Flip the card and disable the button
        QPushButton *button = (QPushButton*) sender();
        for (unsigned i = 0; i < all_card_buttons.size(); ++i){
            if (all_card_buttons.at(i) == button){
                button->setIcon
                        (name_to_picture.at(all_pictures_name.at(i)));
                button->setEnabled(false);
            }
        }

        // Add button to container.
        opened_cards.push_back(button);
        cards_opened++;
    }
}

// Function of switch player button
void MainWindow::next_player_clicked(){

    // Add point to player found the pair, update score status
    // Increment turn if pair is not found
    if (cards_opened == 2 and remaining_cards > 0){
        if (button_with_pictures.at(opened_cards.at(0)) ==
                button_with_pictures.at(opened_cards.at(1))){
            pair_found = true;
            remaining_cards -= 2;
            add_point();
            if (turn % 2 == 0)
                player1_pairs.push_back(button_with_pictures.at(opened_cards.at(0)));
            else if (turn % 2 == 1)
                player2_pairs.push_back(button_with_pictures.at(opened_cards.at(0)));
        }
        else
            turn ++;
        update_score();
        close_opened_cards();
    }

    // Announce winner when no cards left.
    if (remaining_cards == 0)
        announce_winner();
}

// Close the cards if pair is found or not
void MainWindow::close_opened_cards(){

    for (auto &cards: opened_cards){
        if (pair_found){
            cards->setIcon(found_picture);
            cards->setEnabled(false);
        }
        else{
            cards->setIcon(closed_picture);
            cards->setEnabled(true);
        }
    }
    opened_cards.clear();

    cards_opened = 0;
    if (pair_found)
        pair_found = false;
}

// Add point to player
void MainWindow::add_point(){
    if (turn % 2 == 0)
        player1_pts += 1;
    else
        player2_pts += 1;
}

// Update players' status after each turn
void MainWindow::update_score(){
    QString player1_stat = player1;
    QString player2_stat = player2;
    player1_stat += " has " + QString::number(player1_pts) + " pairs.";
    player2_stat += " has " + QString::number(player2_pts) + " pairs.";
    if (turn % 2 == 0)
        in_turn = "It's " + player1 + "'s turn.";
    if (turn % 2 == 1)
        in_turn = "It's " + player2 + "'s turn.";
    if (player1_pairs.size() != 0){
        player1_stat += " They are: ";
        for (auto pair = player1_pairs.begin(); pair != player1_pairs.end(); pair++){
            player1_stat += QString::fromStdString(*pair);
            if (pair != player1_pairs.end()-1)
                player1_stat += ", ";
            else
                player1_stat += ".";
        }
    }

    if (player2_pairs.size() != 0){
        player2_stat += " They are: ";
        for (auto pair = player2_pairs.begin(); pair != player2_pairs.end(); pair++){
            player2_stat += QString::fromStdString(*pair);
            if (pair != player2_pairs.end()-1)
                player2_stat += ", ";
            else
                player2_stat += ".";
        }
    }
    ui->text_browser->setText(in_turn + "\n" +
                              player1_stat + "\n" + player2_stat);
}

// Announce winner status. Who win (or draw) and how many points
void MainWindow::announce_winner(){
    if (player1_pts > player2_pts)
        ui->text_browser->setText("Game over. Player " + player1 + " won with "
                                 + QString::number(player1_pts) + " points." );
    else if (player2_pts > player1_pts)
        ui->text_browser->setText("Game over. Player " + player2 + " won with "
                                 + QString::number(player2_pts) + " points." );
    else
        ui->text_browser->setText("Game over. It's a draw. Both players have "
                                 + QString::number(player1_pts) + " points.");
}
