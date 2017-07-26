#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QMutex* mu, serialThread* myserialthread, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
  mutex=mu;
  thisSerialThread=myserialthread;

    ui->setupUi(this);
    this->connect(this->ui->switchButton,SIGNAL(clicked()),this,SLOT(switchbutton_click()));
    this->connect(this->ui->connectButton,SIGNAL(clicked()),this,SLOT(on_connectButton_clicked()));

  // for realtime plotting
    ui->customPlot->addGraph();//blue line
    ui->customPlot->graph(0)->setPen(QPen(QColor(40,110,255)));
    ui->customPlot->addGraph();//red line
    ui->customPlot->graph(1)->setPen(QPen(QColor(255,110,40)));

    ui->customPlot->xAxis->setLabel("Time [s]");
    ui->customPlot->yAxis->setLabel("Data (fsr / signal)");
    \
    ui->customPlot->axisRect()->setupFullAxesBox();
    ui->customPlot->yAxis->setRange(0.0,5.0);

    //make left and bottom axes transfer their ranges to right and top axes:

    this->connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)),this,SLOT(QCPRange));
    this->connect(ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)),this,SLOT(QCPRange));

    this->connect(&dataTimer, SIGNAL(timeout()),this,SLOT(setRealtimePlot()));
    dataTimer.start(0); // Interval 0 means to refresh as fast as possible. timeout ( start(0) means everytime renew the data)
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::switchbutton_click(){

    if(programOnOff_status==-1){
        experimentalName = ui->nameEdit->text();
        expName=experimentalName.toLocal8Bit().constData();
        if(expName[0]=='p'&& expName[1]=='l' && expName[2] =='e'){
            ui->nameEdit->setText("Please fill it!");
          }
        else{
            programOnOff_status=1;

            std::cout<<expName<<std::endl;
            this->ui->switchButton->setText("Exit");
          }
    }
    else if(programOnOff_status==1){
      programOnOff_status=0;
      std::cout<<"end?"<<std::endl;
      endProgram();
    }
}

void MainWindow::on_connectButton_clicked(){
  std::cout<<"Serial connecting..."<<std::endl;
  serialConnectOn=1;
}

void MainWindow::setEvent(){
}


void MainWindow::endProgram(){
  usleep(1000000);
  std::cout<<"Program end ! will be closed..."<<std::endl;
  usleep(500000);
  qApp->quit();

}

void MainWindow::setRealtimePlot(){
  static QTime time(QTime::currentTime());
  // calculate two new data points:
  double key = time.elapsed(); // time elapsed since start of demo, in seconds
  static double lastPointKey = 0;
  static int vectorStartNum = 0;
  static int vectorFinalNum = 0;
    // add data to lines:
  vectorFinalNum = thisSerialThread->shared_fsr_vec.size()-1;
  if(vectorFinalNum<0) vectorFinalNum=0;
  for(int k=vectorStartNum;k<vectorFinalNum;k++){
      ui->customPlot->graph(0)->addData((double)(thisSerialThread->shared_time_vec[k]/1000000.0),(double)thisSerialThread->shared_signal_vec[k]);
      ui->customPlot->graph(1)->addData((double)(thisSerialThread->shared_time_vec[k]/1000000.0),(double)thisSerialThread->shared_fsr_vec[k]/4096.0*5.0);
    }
  vectorStartNum = vectorFinalNum;

  // make key axis range scroll with the data (at a constant range size of 8):

  if(vectorFinalNum>0){
      ui->customPlot->xAxis->setRange(thisSerialThread->shared_time_vec[vectorFinalNum]/1000000.0-5.0, thisSerialThread->shared_time_vec[vectorFinalNum]/1000000.0);

      if((key-lastPointKey)>10){
          std::cout<<vectorFinalNum<<std::endl;
          std::cout<<thisSerialThread->shared_time_vec[vectorFinalNum]<<std::endl;
          ui->customPlot->xAxis->setRange(thisSerialThread->shared_time_vec[vectorFinalNum]/1000000.0-5.0, thisSerialThread->shared_time_vec[vectorFinalNum]/1000000.0);
          ui->customPlot->replot();
          lastPointKey = key;
        }
      // calculate frames per second:
        static double lastFpsKey;
        static int frameCount;
        ++frameCount;
        if (key-lastFpsKey > 1000) // average fps over 2 seconds
        {
          ui->statusBar->showMessage(
                QString("Plot status : %1 FPS, Total Data points: %2")
                .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
                .arg(ui->customPlot->graph(0)->data()->size()+ui->customPlot->graph(1)->data()->size())
                , 0);
          lastFpsKey = key;
          frameCount = 0;
        }
    }
}

