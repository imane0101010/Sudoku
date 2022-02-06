#ifndef SUDOKU_H
#define SUDOKU_H

#include <QMainWindow>
#include <QPainter>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QKeyEvent>
#include <QAction>
#include <QToolBar>
QT_BEGIN_NAMESPACE
//namespace Ui { class Sudoku; }
QT_END_NAMESPACE

class Sudoku : public QMainWindow
{
   // Q_OBJECT

public:
    Sudoku(QWidget *parent = nullptr);
    ~Sudoku();
    void paintEvent(QPaintEvent *event);
    void drawGrid(QPainter * p);
    QList <int> list{0,1,2,0,8,0,7,5,0,0,0,7,5,0,1,4,0,0,0,0,0,7,2,9,0,0,0,0,0,0,0,0,0,0,0,0,6,7,0,4,1,8,0,3,5,0,0,5,0,0,0,1,0,0,9,9,0,0,0,0,0,4,7,0,0,8,0,0,0,6,0,0,7,0,0,0,6,0,0,0,8};
    QList <int> list2{0,1,2,0,8,0,7,5,0,0,0,7,5,0,1,4,0,0,0,0,0,7,2,9,0,0,0,0,0,0,0,0,0,0,0,0,6,7,0,4,1,8,0,3,5,0,0,5,0,0,0,1,0,0,9,6,0,0,0,0,0,4,7,0,0,8,0,0,0,6,0,0,7,0,0,0,6,0,0,0,8};
     QList <int> list4{0,1,2,0,8,0,7,5,0,0,0,7,5,0,1,4,0,0,0,0,0,7,2,9,0,0,0,0,0,0,0,0,0,0,0,0,6,7,0,4,1,8,0,3,5,0,0,5,0,0,0,1,0,0,9,6,0,0,0,0,0,4,7,0,0,8,0,0,0,6,0,0,7,0,0,0,6,0,0,0,8};
    QList<QList<int>> list1{{0,1,2,0,8,0,7,5,0},{0,0,7,5,0,1,4,0,0},{0,0,0,7,2,9,0,0,0},{0,0,0,0,0,0,0,0,0},{6,7,0,4,1,8,0,3,5},{0,0,5,0,0,0,1,0,0},{9,6,0,0,0,0,0,4,7},{0,0,8,0,0,0,6,0,0},{7,0,0,0,6,0,0,0,8}};
    QList<QList<int>> list3{{0,1,2,0,8,0,7,5,0},{0,0,7,5,0,1,4,0,0},{0,0,0,7,2,9,0,0,0},{0,0,0,0,0,0,0,0,0},{6,7,0,4,1,8,0,3,5},{0,0,5,0,0,0,1,0,0},{9,6,0,0,0,0,0,4,7},{0,0,8,0,0,0,6,0,0},{7,0,0,0,6,0,0,0,8}};
    QLineEdit *line1;
    QLabel *label1;
    QGridLayout *grid ;
    void createWidgets();
    void makeConnections();
    QVector<QLineEdit *> line;
    QVector<QLabel *>labels;
    QVector<QString> elements;
    QVector<QString> elements_lab;



     QLineEdit *lineEdit;
    int  k=0;


public slots:
    void check();
    void get_cell(QLineEdit *line);
    void save_slot();
    void reset_slot();
    void solve_slot();

private:

    QAction *reset;
    QAction *solve;
    QAction *save;
    QToolBar *toolbar;
    void createAction();
    void createMenues();
    void createToolBars();
public:
    bool solveSudoku(QList<QList<int>> &list1,int row,int col);
    bool is_Safe(QList<QList<int>> & liste,int row,int col,int num);
     void print(QList<QList<int>>& list1);
     void saveContent(QString filename) const;
     QString currentFile="sudoku.txt";
     void load_content(QString Filename);



};
#endif // SUDOKU_H
