#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QMutex* mu, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
  mutex=mu;

    ui->setupUi(this);
    this->connect(this->ui->switchButton,SIGNAL(clicked()),this,SLOT(switchbutton_click()));
    this->connect(this->ui->connectButton,SIGNAL(clicked()),this,SLOT(on_connectButton_clicked()));

  // for realtime plotting
    ui->customPlot->addGraph();//blue line
    ui->customPlot->graph(0)->setPen(QPen(QColor(40,110,255)));
    ui->customPlot->addGraph();//red line
    ui->customPlot->graph(1)->setPen(QPen(QColor(255,110,40)));

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    ui->customPlot->xAxis->setTicker(timeTicker);
    ui->customPlot->axisRect()->setupFullAxesBox();
    ui->customPlot->yAxis->setRange(0.0,5.0);

    //make left and bottom axes transfer their ranges to right and top axes:

    this->connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)),ui->customPlot->xAxis2,SLOT(QCPRange));
    this->connect(ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)),ui->customPlot->yAxis2,SLOT(QCPRange));

    this->connect(&dataTimer, SIGNAL(timeout()),this,SLOT(setRealtimePlot()));
    dataTimer.start(0); // Interval 0 means to refresh as fast as possible. timeout ( start(0) means everytime renew the data)
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::switchbutton_click(){

    if(onOff_status==-1){
        experimentalName = ui->nameEdit->text();
        expName=experimentalName.toLocal8Bit().constData();
        if(expName[0]=='p'&& expName[1]=='l' && expName[2] =='e'){
            ui->nameEdit->setText("please fill it with name!");
          }
        else{
            onOff_status=1;

            std::cout<<expName<<std::endl;
            this->ui->switchButton->setText("Exit");
          }
    }
    else if(onOff_status==1){
      onOff_status=0;
      std::cout<<"end?"<<std::endl;
      //this->ui->lineEdit1->setText("Stop");
      //this->ui->switchButton->setText("Exit");
      endProgram();
    }
}

void MainWindow::on_connectButton_clicked(){
    struct termios newtio;

    fd = open("/dev/ttyACM0",O_RDWR|O_NOCTTY | O_NDELAY );

    cfsetispeed(&newtio, B460800);    // set baud rates
    newtio.c_cflag = B460800| CS8 | CREAD | CLOCAL;
    newtio.c_iflag = IGNPAR;
    newtio.c_oflag = 0;
    newtio.c_lflag = 0;
    tcsetattr(fd, TCSANOW, &newtio); // apply the settings to the port

    //QString temp_port; // for commbBox
    //temp_port = ui->portBox->currentText();

    notRsRead = new QSocketNotifier(fd,QSocketNotifier::Read,this);
    connect(notRsRead,SIGNAL(activated(int)),this,SLOT(setEvent()));
}

void MainWindow::setEvent(){

   // mutex->lock();
    int szRead = read(fd,&shared_data_recv,BUFF_SIZE);
    //std::cout<<"data length : "<<szRead<<std::endl;

    if(szRead>0)  {
        shared_update_count++;
        shared_updated=1;
        shared_data_len = szRead;
      }

      shared_data_recv[szRead] = '\0';
      if(szRead>0){
          ui->textEdit->setText(shared_data_recv);
          ui->textEdit_time->setText(QString("%1").arg(shared_time, 0, 'f', 0));
          ui->textEdit_fsr->setText(QString("%1").arg(shared_fsr, 0, 'f', 0));
          ui->textEdit_sign->setText(QString("%1").arg(shared_signalOnOff, 0, 'f', 0));
          ui->textEdit_seq_num->setText(QString("%1").arg(shared_seq_num,0,'f',0));
        }

  //  mutex->unlock();

   // dataTemp.assign(data_recv);

    //ui->textEdit->insertPlainText(buf_temp);
    //ui->textEdit->moveCursor(QTextCursor::End);


}

void MainWindow::saveData(){
  std::cout<<"save data..."<<std::endl;
  std::fstream dataStream;
  std::stringstream myFileNameStream;
  myFileNameStream<<"../expdata/"<<expName<<"_exp_"<<"_dataLog.txt";
  std::string myFileNameString=myFileNameStream.str();

     dataStream.open(myFileNameString.c_str(),std::fstream::out);

     if(dataStream.is_open()){
       dataStream<<"time,volt(fsr),Stimul"<<std::endl;
       for(int k=0;k<shared_time_vec.size();++k){
         dataStream<<shared_time_vec[k]<<',';
         dataStream<<shared_fsr_vec[k]<<',';
         dataStream<<shared_signal_vec[k]<<std::endl;
       }
     }
     dataStream.close();
  std::cout<<"save done!"<<std::endl;
}

void MainWindow::endProgram(){
  usleep(1000000);
  saveData();
  std::cout<<"program end ! will be closed..."<<std::endl;

  usleep(500000);
  qApp->quit();

}

void MainWindow::setRealtimePlot(){
  static QTime time(QTime::currentTime());
  // calculate two new data points:
  double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
  static double lastPointKey = 0;
  if (key-lastPointKey > 0.002) // at most add point every 2 ms
  {
    // add data to lines:
      // addData(xData,yData)
    ui->customPlot->graph(0)->addData(key, shared_signalOnOff);
    //ui->customPlot->graph(1)->addData(key, shared_fsr/1024.0*3.0);
    ui->customPlot->graph(1)->addData(key, shared_fsr/4096.0*5.0);

    // rescale value (vertical) axis to fit the current data:
    //ui->customPlot->graph(0)->rescaleValueAxis();
    //ui->customPlot->graph(1)->rescaleValueAxis(true);
    lastPointKey = key;
  }
  // make key axis range scroll with the data (at a constant range size of 8):
  ui->customPlot->xAxis->setRange(key, 8, Qt::AlignRight);
  ui->customPlot->replot();

  // calculate frames per second:
  static double lastFpsKey;
  static int frameCount;
  ++frameCount;
  if (key-lastFpsKey > 2) // average fps over 2 seconds
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

