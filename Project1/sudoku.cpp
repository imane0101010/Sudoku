#include "sudoku.h"
#include "ui_sudoku.h"
#include "QGridLayout"
#include <QTextEdit>
#include <QRegularExpressionValidator>
#include <QDebug>
#include <qalgorithms.h>
#include <QTimer>
#include <iostream>
#include <QFileDialog>
#include <QMessageBox>
#include <math.h>
#include <QThread>
Sudoku::Sudoku(QWidget *parent)
    : QMainWindow(parent)

{

    createAction();
    createToolBars();
    createWidgets();
    makeConnections();
    list1.empty();
    list1=list3;

  load_content(currentFile);
  }

Sudoku::~Sudoku()
{
    delete lineEdit;
    delete solve;
    delete save;
    delete reset;
    delete toolbar;

}

void Sudoku::paintEvent(QPaintEvent *e)
{


 Q_UNUSED(e);

 auto painter = new QPainter(this);
 drawGrid(painter);
}

void Sudoku::drawGrid(QPainter *p)
{
  QPen pen;

   // QColor color1 ="#FAD0C9FF";
 QColor color1 ="gray";
      pen.setColor(color1);
      pen.setWidth(8);
      p->setPen(pen);



       QColor color ="gray";
       pen.setColor(color);
        pen.setStyle(Qt::SolidLine);
        pen.setWidth(8);
        p->setPen(pen);
        QRect rect(10,50,930,930);
       p->drawRect(rect);
         pen.setWidth(5);
         p->setPen(pen);
       p->drawLine(13,358,933,358);
       p->drawLine(13,667,933,667);
       p->drawLine(320,50,320,972);
       p->drawLine(627,50,627,972);






    delete p;

}

void Sudoku::createWidgets()
{
QWidget* container = new QWidget;
container->setFixedSize(950,950);
grid = new QGridLayout;
grid->setSpacing(0);
grid->setHorizontalSpacing(0);
grid->setVerticalSpacing(0);
int pos = 0;
for (int i=0; i<9; i++) {
   for (int j=0; j<9; j++) {
       if(list1.at(i).at(j)!=0 ){
         QString str = QString::number(list1.at(i).at(j));
          auto *label = new QLabel(str);
          QFont font = label->font();
          font. setPointSize(35);
          font. setBold(true);
          label->setFont(font);
          label->setAlignment(Qt::AlignCenter);
          label->setStyleSheet("QLabel { background-color : #FAD0C9FF ; color : black; }");
          label->setFixedSize(100,100);
          QString v1= QString::number(i);
          QString v2= QString::number(j);
          v1=v1+v2;
          elements_lab.append(v1);
          v1="";
          labels.append(label);
          grid->addWidget(label, i, j);
          }else {
         lineEdit = new QLineEdit;
       lineEdit->setAlignment(Qt::AlignCenter);
       lineEdit->setFixedSize(100, 100);
       QFont font = lineEdit->font();
       QRegExp re("[1-9]");
       QRegExpValidator *validator = new QRegExpValidator(re, this);
       lineEdit->setValidator(validator);
      font. setPointSize(20);
      lineEdit->setStyleSheet("color: gray");
      lineEdit->setFont(font);
      line.append(lineEdit);
      QString v1= QString::number(i);
      QString v2= QString::number(j);
      v1=v1+v2;
      elements.append(v1);
      v1="";
      grid->addWidget(lineEdit, i, j);
     }
   pos++;
  }
}
    container->setLayout(grid);
    setCentralWidget(container);
    setWindowTitle("Sudoku");
}

void Sudoku::makeConnections()
{
    for(int i =0;i<line.size();i++){     
        connect(line[i], &QLineEdit::textEdited, this, &Sudoku::check);
}
    connect(save,&QAction::triggered,this,&Sudoku::save_slot);
    connect(reset,&QAction::triggered,this,&Sudoku::reset_slot);
    connect(solve,&QAction::triggered,this,&Sudoku::solve_slot);
}

void Sudoku::check()
{
       int a=0;
       int c=0;
      QList<int> listeMat;
      QList<int> liste_mat;
    //Getting the identity of the lineEdit using dynamic_cast
     auto line1  = dynamic_cast<QLineEdit*>(sender());

     for(int  w=0;w<line.size();w++){
         a=0;
          if(line1 == line[w]){
           k=w;
          }

}
       QString s = elements.at(k)[0];
       QString s1 = elements.at(k)[1];
       QList<int> liste;
        QList<int> liste_;
        int i= s.toInt();
       int j = s1.toInt();
         for(int b =0;b<9;b++){
          if(line1->text()!=""){
             if(list1.at(i).at(b)==line1->text().toInt()){
                  for(int v=0;v<qMax(elements_lab.size(),elements.size());v++){
                              if(v<elements_lab.size()){
                      QString s2 = elements_lab.at(v)[0];
                            if(s2.toInt()==i){
                                liste.append(v);
                          }
                              }if(v<elements.size()){

                                  QString s2 = elements.at(v)[0];
                                        if(s2.toInt()==i){
                                            liste_.append(v);
                                      }


                              }
                  }

         }
            if(list1.at(b).at(j)==line1->text().toInt()){

                  for(int v=0;v<qMax(elements_lab.size(),elements.size());v++){
                         if(v<elements_lab.size()){
                      QString s2 = elements_lab.at(v)[1];

                            if(s2.toInt()== j ){
                                liste.append(v);

                            }
                         }
                         if(v<elements.size()){

                         QString s2 = elements.at(v)[1];
                      if(s2.toInt()==j){
                        liste_.append(v);
                          }


                       }

         }
          for(int z=0;z<qMax(liste.size(),liste_.size());z++){
              if(z<liste.size() &&labels[liste[z]]->text() == line1->text()){
                            a =1;

                       labels[liste[z]]->setStyleSheet("color: red");
                        //QThread::msleep(1000);
                    // labels[liste[z]]->setStyleSheet("QLabel { background-color : #FAD0C9FF ; color : black; }");
                }
              if(z<liste_.size() &&line[liste_[z]]->text() == line1->text()){
                  a =1;

                  line[liste_[z]]->setStyleSheet("color: red");
                          c=liste_[z];

                  for(int i=0;i<line.size();i++){
                      if(i!=liste_[z]){
                          QRegExp re("[]");
                          QRegExpValidator *validator = new QRegExpValidator(re, this);
                          line[i]->setValidator(validator);
                      }


                  }


              }
            }
}
         }
          if(a==0){
              list1[i][j]=line1->text().toInt();
          }
           if(line[c]->text()== ""){

               for(int i=0;i<qMax(line.size(),labels.size());i++){
                   if(i<line.size()){
                       QRegExp re("[1-9]");
                       QRegExpValidator *validator = new QRegExpValidator(re, this);
                       line[i]->setValidator(validator);
                       line[i]->setStyleSheet("color : gray");
                   }
                   if(i<labels.size()){
               labels[i]->setStyleSheet("QLabel { background-color : #FAD0C9FF ; color : black; }");



               }


}


            }


}

void Sudoku::save_slot()
{
    auto dialog = new QFileDialog(this);

    saveContent(currentFile);
    QMessageBox msgBox;
    msgBox.setText("The document has been saved.");
    msgBox.exec();
}

void Sudoku::reset_slot()
{
    list1.empty();
    list1=list3;
for(int i=0;i<line.size();i++){
    line[i]->setText("");
}
}

void Sudoku::solve_slot()
{
    list1 = list3;
    if (solveSudoku(list1, 0, 0))
        print(list1);

}

void Sudoku::createAction()
{
      QPixmap reset_icon("/home/hp/build-Project1-Desktop-Debug/reset.png");
    reset = new QAction(reset_icon,"&Reset",this);
     QPixmap save_icon("/home/hp/build-Project1-Desktop-Debug/save.png");
    save = new QAction (save_icon,"&Save",this);
     QPixmap solve_icon("/home/hp/build-Project1-Desktop-Debug/solve.png");
       solve = new QAction(solve_icon,"&Solve",this);

}

void Sudoku::createMenues()
{

}

void Sudoku::createToolBars()
{
    toolbar = addToolBar("Toolbar");
    toolbar->addAction(reset);
    toolbar->addAction(solve);
    toolbar->addAction(save);
}



// Checks whether it will be
// legal to assign num to the
// given row, col
bool Sudoku::is_Safe( QList<QList<int>> &l1, int row, int col, int num)
{

    // Check if we find the same num
    // in the similar row , we
    // return false
    for (int x = 0; x <= 8; x++)
        if (l1[row][x] == num)
            return false;

    // Check if we find the same num in
    // the similar column , we
    // return false
    for (int x = 0; x <= 8; x++)
        if (l1[x][col] == num)
            return false;

    // Check if we find the same num in
    // the particular 3*3 matrix,
    // we return false
    int startRow = row - row % 3,
            startCol = col - col % 3;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (l1[i + startRow][j + startCol] == num)
                return false;

    return true;

/* Takes a partially filled-in grid and attempts
to assign values to all unassigned locations in
such a way to meet the requirements for
Sudoku solution (non-duplication across rows,
columns, and boxes) */
}

bool Sudoku::solveSudoku( QList<QList<int>> &l1,int row,int col)
{

    // Check if we have reached the 8th
    // row and 9th column (0
    // indexed matrix) , we are
    // returning true to avoid
    // further backtracking
    if (row == 8 && col == 9)
        return true;

    // Check if column value  becomes 9 ,
    // we move to next row and
    //  column start from 0
    if (col == 9) {
        row++;
        col = 0;
    }

    // Check if the current position of
    // the grid already contains
    // value >0, we iterate for next column
    if (l1[row][col] > 0)
        return solveSudoku(l1, row, col + 1);

    for (int num = 1; num <= 9; num++)
    {

        // Check if it is safe to place
        // the num (1-9)  in the
        // given row ,col  ->we
        // move to next column

        if (is_Safe(l1, row, col, num))
      {

            /*Assigning the num in
              the current (row,col)
              position of the grid
              and assuming our assigned
              num in the position
              is correct
              */
            l1[row][col] = num;

            //  Checking for next possibility with next
            //  column
            if (solveSudoku(l1, row, col + 1))
                return true;
       }

        // Removing the assigned num ,
        // since our assumption
        // was wrong , and we go for
        // next assumption with
        // diff num value
        l1[row][col] = 0;
    }
    return false;

}

void Sudoku::print( QList<QList<int>> &l1)
{
int k =0;
  for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++){


            if(list3[i][j]==0){
               if(k<line.size()){
              line[k]->setText(QString::number(l1[i][j]));

               k++;
               }else{
                   break;

                 }

           }


    }


}

}

void Sudoku::saveContent(QString filename) const
{

    //Gettign a pointer on the file
    QFile file(filename);
       file.resize(0);
    //Openign the file
    if(file.open(QIODevice::WriteOnly))  //Opening the file in writing mode
    {
        //Initiating a stream using the file
        QTextStream out(&file);

        //loop to save all the content
        for(int i=0; i < 9;i++)
            for(int j=0; j <9; j++)
            {

              //  out << i << ", "<< j << ", " << list1[i][j] << endl;
                out <<list1[i][j] << endl;
            }

    }
    file.close();
}

void Sudoku::load_content(QString filename)
{
     QMessageBox msgBox;
     msgBox.setText("Do you want to resume the part");

     QPushButton *yesButton = msgBox.addButton(tr("Yes"), QMessageBox::ActionRole);
     QPushButton *noButton = msgBox.addButton(tr("No"),QMessageBox::ActionRole);

     msgBox.exec();

     if (msgBox.clickedButton() == yesButton) {

       filename=currentFile;
       QString Alldata;
       QFile importedFile(filename);
       QStringList rowOfData;
       QStringList rowData;
       Alldata.clear();
       rowOfData.clear();
       rowData.clear();
        int k =0;
   if (importedFile.open(QFile::ReadOnly))
   {
        //Reads all data from the importedFile, and stores it as a byte array in AllData.
       Alldata = importedFile.readAll();
       //Split data so as to store it in the list row by row
       rowOfData = Alldata.split("\n");
       //
       importedFile.close();
   }

   for (int x = 0; x < rowOfData.size(); x++)
       for (int y = 0; y < 9; y++)
       {
         if(list3[floor(x/81)][floor(y)]== 0 ){
             if(k<line.size()){
                line[k]->setText(rowOfData[x]);
                  k++;
             }else{
               break;
        }
        }
         }
}
 else if (msgBox.clickedButton() == noButton) {
      reset_slot();
}
}
