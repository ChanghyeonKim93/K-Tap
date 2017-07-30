close all;clear all;clc;

%%
rawdata=importdata('digitalWrite_data.csv');

time=rawdata.data(:,1);
ref_pin = rawdata.data(:,2);
raw_pin1=rawdata.data(:,3);
raw_pin2=rawdata.data(:,4);

figure();
subplot(3,1,1);plot(time,raw_pin1);xlim([0 0.0005]);ylim([-1,4]);
subplot(3,1,2);plot(time,raw_pin2);xlim([0 0.0005]);ylim([-1,4]);

% upper 2.7 : 1, under 0.25 : 0
high_thres=3.0;
low_thres=0.2;
sign_pin1=zeros(length(time),1);
sign_pin2=zeros(length(time),1);

for k=1:length(raw_pin1)
    if(raw_pin1(k) >=high_thres)
        sign_pin1(k) =1;
    elseif(raw_pin1(k)<=low_thres)
        sign_pin1(k) =0;
    end
    if(raw_pin2(k) >=high_thres)
        sign_pin2(k) =1;
    elseif(raw_pin2(k)<=low_thres)
        sign_pin2(k) =0;
    end
end

figure();
subplot(3,1,1);plot(time,sign_pin1,'.');xlim([0 0.0005]);ylim([-2,2]);
subplot(3,1,2);plot(time,sign_pin2,'.');xlim([0 0.0005]);ylim([-2,2]);
subplot(3,1,3);plot(time,sign_pin1);hold on; grid on;plot(time,sign_pin2);xlim([0 0.0005]);ylim([-2,2]);

for k=1:length(sign_pin1)-1
    grad_sign_pin1(k) = sign_pin1(k+1)-sign_pin1(k);
    grad_sign_pin2(k) = sign_pin2(k+1)-sign_pin2(k);
end
grad_sign_pin1(length(sign_pin1))=grad_sign_pin1(end);
grad_sign_pin2(length(sign_pin1))=grad_sign_pin2(end);

figure();
subplot(3,1,1);plot(time,grad_sign_pin1);xlim([0 0.0005]);ylim([-2,2]);
subplot(3,1,2);plot(time,grad_sign_pin2);xlim([0 0.0005]);ylim([-2,2]);
subplot(3,1,3);plot(time,grad_sign_pin1);hold on; grid on;plot(time,grad_sign_pin2);xlim([0 0.0005]);ylim([-2,2]);

%% numbering
ind1=0; ind2=0; ind3=0;
for k=1:length(time)
    if(grad_sign_pin1(k)~=0)
        ind1=ind1+1;
        signal_ind1(ind1)=time(k);
    end
    if(grad_sign_pin2(k)~=0)
        ind2=ind2+1;
        signal_ind2(ind2)=time(k);
    end
end

if(ind1>=ind2)
    ind_temp=ind2;
    signal_ind1(ind1-ind2+end-1)=[];
else
    ind_temp=ind1;
    signal_ind2(ind2-ind1+end-1)=[];
end

time_consume_digitalWrtie=[signal_ind2-signal_ind1];


for k=1:ind_temp-1
    time_consume_loop(k)= signal_ind1(k+1)-signal_ind2(k);
end

fprintf('time consumption - digitalWrite_ mean : %f [us], std : %f [us]\n',mean(time_consume_digitalWrtie)*10^6,std(time_consume_digitalWrtie)*10^6);
fprintf('time consumption - Loop_ mean : %f [us], std : %f [us]\n',mean(time_consume_loop)*10^6,std(time_consume_loop)*10^6);

figure();
% nbins =100;
h = histogram(time_consume_digitalWrtie);

