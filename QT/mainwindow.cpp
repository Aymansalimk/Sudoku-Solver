#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGridLayout>
#include <QMessageBox>
#include <QIntValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createGrid();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createGrid()
{
    QGridLayout *gridLayout = new QGridLayout();

    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            cells[row][col] = new QLineEdit(this);
            cells[row][col]->setFixedSize(35, 35);
            cells[row][col]->setAlignment(Qt::AlignCenter);
            cells[row][col]->setValidator(new QIntValidator(1, 9, this));
            gridLayout->addWidget(cells[row][col], row, col);
        }
    }

    ui->centralwidget->setLayout(gridLayout);
}

bool MainWindow::isPossible(int value, int sudoku[9][9], int row, int col)
{
    for (int i = 0; i < 9; ++i) {
        if (sudoku[row][i] == value || sudoku[i][col] == value) {
            return false;
        }
    }

    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (sudoku[startRow + i][startCol + j] == value) {
                return false;
            }
        }
    }

    return true;
}

bool MainWindow::solve(int sudoku[9][9])
{
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (sudoku[row][col] == 0) {
                for (int value = 1; value <= 9; ++value) {
                    if (isPossible(value, sudoku, row, col)) {
                        sudoku[row][col] = value;
                        if (solve(sudoku)) {
                            return true;
                        } else {
                            sudoku[row][col] = 0;
                        }
                    }
                }
                return false;
            }
        }
    }
    return true;
}

void MainWindow::getSudokuFromGrid(int sudoku[9][9])
{
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            QString text = cells[row][col]->text();
            if (text.isEmpty()) {
                sudoku[row][col] = 0;
            } else {
                sudoku[row][col] = text.toInt();
            }
        }
    }
}

void MainWindow::setGridFromSudoku(int sudoku[9][9])
{
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (sudoku[row][col] != 0) {
                cells[row][col]->setText(QString::number(sudoku[row][col]));
            } else {
                cells[row][col]->clear();
            }
        }
    }
}

void MainWindow::on_solveButton_clicked()
{
    int sudoku[9][9];
    getSudokuFromGrid(sudoku);

    if (solve(sudoku)) {
        setGridFromSudoku(sudoku);
    } else {
        QMessageBox::warning(this, "Error", "No solution exists for the given Sudoku");
    }
}

void MainWindow::on_MainWindow_iconSizeChanged(const QSize &iconSize)
{

}

