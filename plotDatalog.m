clear all;close all;clc;
%%

dataFileRaw = importdata('abcdef_exp_1_dataLog.txt');

time=dataFileRaw.data(:,1);
volt=dataFileRaw.data(:,2);
stimul=dataFileRaw.data(:,3);
dataFileRaw.data(:,4);

t = (time-time(1))/10^6;
dt = time(2:end)-time(1:end-1);
mean(dt);
figure();
subplot(4,1,1);plot(t,volt,'k','linewidth',2);xlabel('time [s]');ylabel('voltage [V]');grid on; hold on;
subplot(4,1,2);plot(t,stimul/1024*5,'k','linewidth',2);xlabel('time [s]');ylabel('stimulus on/off');grid on; hold on;
subplot(4,1,3);plot(t(1:end-1),dt/1000.0);xlabel('time [s]');ylabel('time [ms]');grid on; hold on;
subplot(4,1,4);plot(t(1:end-1),10^6./dt);xlabel('time [s]');ylabel('Freq [Hz]');grid on; hold on;


figure();
plot(t,stimul*4.5,'r');hold on; grid on;
plot(t,volt/1024*5);legend('stimulation','FSR output');xlabel('time [s]');


figure();
plot(t,volt);