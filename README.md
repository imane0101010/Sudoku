# Sudoku

## Overview:

For this final project, I will be gathering almost everything we studied this semester in order to create a functional sudoku game.

## Use Cases:

**A user should be able to close the application.**  
**A user should be able to reset the sudoku table.**  
**A user should be able to get solution of the sudoku game.**  
**A user should be warned in case he violate the rules of the game.**  
**Finally, the numbers entered to the sudoku game must remains in the app in future use in case the user wanted to resume the game.** 

Normally, my app should provide a partially completed grid,which for a well-posed puzzle has a single solution.In this project,I won´t write any program that will generate sudoku numbers due to the lack of time.So I will use only a valid grid that will be stored in a QList that will contain QList of type int.It will contain numbers from 1 to 9 and also the number 0 that will refer to the empty cells.We can change the numbers in the qlist the 

## Graphical Interface

**Actions**
First I will create QActions:
```cpp
    QAction *reset;
    QAction *solve;
    QAction *save;
```    

**ToolBar**
Then,I will create a toolbar.
```cpp
 QToolBar *toolbar;
  ```
**methods** 
Here are the methods that I created to organize the work:
```cpp
  //Method for creating actions
    void createAction();
  //Method for creating toolbar
    void createToolBars();
//Method for creating widgets and layouts and placing them
    void createWidgets();
 //Method for creating connections
    void makeConnections();
  //Method for saving the content of the sudoku game in a file Sudoku.txt
    void saveContent(QString filename) const;
    //Method for loading the content of the file Sudoku.txt and place it in the game
    void load_content(QString Filename);
``` 
Implementation of the method createAction:
```cpp
//creating QActions and adding their corresponding icons
QPixmap reset_icon("/home/hp/build-Project1-Desktop-Debug/reset.png");
reset = new QAction(reset_icon,"&Reset",this);
QPixmap save_icon("/home/hp/build-Project1-Desktop-Debug/save.png");
save = new QAction (save_icon,"&Save",this);
QPixmap solve_icon("/home/hp/build-Project1-Desktop-Debug/solve.png");
 solve = new QAction(solve_icon,"&Solve",this);
```
Implementation of the method createToolBars:
```cpp
//Creating toolbar
toolbar = addToolBar("Toolbar");
//adding actions to the toolbar
toolbar->addAction(reset);
toolbar->addAction(solve);
toolbar->addAction(save);
```
Implementation of the method createWidgets:
```cpp
   //creating a qwidget that will contain the widgets and layouts
   QWidget* container = new QWidget;
    //Fixing the size of the container since i will be using QPainter later
    container->setFixedSize(950,950);
      //creating a gridlayout
      grid = new QGridLayout;
      grid->setSpacing(0);
     grid->setHorizontalSpacing(0);
      grid->setVerticalSpacing(0);
      int pos = 0;
     for (int i=0; i<9; i++) {
      for (int j=0; j<9; j++) {
     //Check if the cell isn´t empty
       if(list1.at(i).at(j)!=0 ){
       //convert the integer stored in list1 to string
         QString str = QString::number(list1.at(i).at(j));
         //create a pointer label
          auto *label = new QLabel(str);
          //create the font
          QFont font = label->font();
          //set the size of the font
          font. setPointSize(35);
          font. setBold(true);
          label->setFont(font);
          //center the text
          label->setAlignment(Qt::AlignCenter);
          //change the color of the background and the text
          label->setStyleSheet("QLabel { background-color : #FAD0C9FF ; color : black; }");
          label->setFixedSize(100,100);
          //convert the index i and j to qstring so as to know the coordinates of each label
          QString v1= QString::number(i);
          QString v2= QString::number(j);
          v1=v1+v2;
          //append the qstring in the qstringlist
          elements_lab.append(v1);
          v1="";
          //append the qlabel in the qlist
          labels.append(label);
          //add qlabel label in the grid layout at (i,j)
          grid->addWidget(label, i, j);
          }else {
          //if the cell is empty we will create a new lineEdit
         lineEdit = new QLineEdit;
         //set a central alignment
         lineEdit->setAlignment(Qt::AlignCenter);
         //set a fixed size
         lineEdit->setFixedSize(100, 100);
          //set a Regular expression so as the user type only numbers from 1 to 9
         QRegExp re("[1-9]");
         QRegExpValidator *validator = new QRegExpValidator(re, this);
         //create font
         QFont font = lineEdit->font();
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
  ```
 Implementation of the method loadContent:
 ```cpp
//Gettign a pointer on the file
QFile file(filename);
file.resize(0);
//Opening the file
if(file.open(QIODevice::WriteOnly))  //Opening the file in writing mode
{
//Initiating a stream using the file
QTextStream out(&file);
//loop to save all the content
for(int i=0; i < 9;i++)
   for(int j=0; j <9; j++)
     {
     out <<list1[i][j] << endl;
      }
     }
     file.close();
```
Implementation of the method SaveContent:
```cpp
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
``


**QPainter** 
I used QPainter to draw sudoku lines.

```cpp
 void paintEvent(QPaintEvent *event);
 void drawGrid(QPainter * p);
 ```
 Implementation of the methods:
 PaintEvent:
 ```cpp
  Q_UNUSED(e);
 auto painter = new QPainter(this);
 drawGrid(painter);
 ```
 drawGrid:
 ```cpp
QPen pen;
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
```

**Connections** 

For the connection part,I proceeded as follows:
First,I connected all the lineEdits using only one slot which is the check slot and then I connected the QActions to their corresponding slots.
```cpp
    for(int i =0;i<line.size();i++){     
        connect(line[i], &QLineEdit::textEdited, this, &Sudoku::check);
}
    connect(save,&QAction::triggered,this,&Sudoku::save_slot);
    connect(reset,&QAction::triggered,this,&Sudoku::reset_slot);
    connect(solve,&QAction::triggered,this,&Sudoku::solve_slot);
  ```
**Slots** 

**Save slot:**
```cpp
    auto dialog = new QFileDialog(this);
    saveContent(currentFile);
    QMessageBox msgBox;
    msgBox.setText("The document has been saved.");
    msgBox.exec();
 ```
 **Reset slot**
 ```cpp
  list1.empty();
    list1=list3;
for(int i=0;i<line.size();i++){
    line[i]->setText("");
}
```
**Check slot**
```cpp
int a=0;
int c=0;
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
}
for(int z=0;z<qMax(liste.size(),liste_.size());z++){
 if(z<liste.size() &&labels[liste[z]]->text() == line1->text()){
     a =1;
labels[liste[z]]->setStyleSheet("color: red");
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
}if(i<labels.size()){
labels[i]->setStyleSheet("QLabel { background-color : #FAD0C9FF ; color : black; }");
}
}
}
```



```
## Backtracking

Backtracking is a general algorithm for finding all (or some) solutions to some computational problems, that incrementally builds candidates to the solutions. As soon as it determines that a candidate cannot possibly lead to a valid complete solution, it abandons this partial candidate and “backtracks’’ (return to the upper level) and reset to the upper level’s state so that the search process can continue to explore the next branch.
To solve the sudoku,We will be using the backtracking algorithm:

Implementation of the method is_Safe:

```cpp
// Check if we find the same num
// in the similar row , we
// return false
for (int x = 0; x <= 8; x++)
 if (l1[row][x] == num)
   return false;
// Check if we find the same num in
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
```
Implementation of the solveSudoku mathod:
```cpp
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
  ```
  Implementation of the print method:
  ```cpp
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
  ```
  
