close all;clear all;clc;

%% serial write speed check
rawdata10=importdata('serial_char10_data.csv');
rawdata11=importdata('serial_char11_data.csv');
rawdata12=importdata('serial_char12_data.csv');
rawdata13=importdata('serial_char13_data.csv');
rawdata14=importdata('serial_char14_data.csv');
rawdata15=importdata('serial_char15_data.csv');
rawdata16=importdata('serial_char16_data.csv');

time10=rawdata10.data(:,1); raw_pin10=rawdata10.data(:,3);
time11=rawdata11.data(:,1); raw_pin11=rawdata11.data(:,3);
time12=rawdata12.data(:,1); raw_pin12=rawdata12.data(:,3);
time13=rawdata13.data(:,1); raw_pin13=rawdata13.data(:,3);
time14=rawdata14.data(:,1); raw_pin14=rawdata14.data(:,3);
time15=rawdata15.data(:,1); raw_pin15=rawdata15.data(:,3);
time16=rawdata16.data(:,1); raw_pin16=rawdata16.data(:,3);

figure();
subplot(4,2,1);plot(time10,raw_pin10);ylim([-0.5,4]);xlabel('time [s]');ylabel('voltage [V]');
title('Raw signals - serial_write');
subplot(4,2,2);plot(time11,raw_pin11);ylim([-0.5,4]);xlabel('time [s]');ylabel('voltage [V]');
subplot(4,2,3);plot(time12,raw_pin12);ylim([-0.5,4]);xlabel('time [s]');ylabel('voltage [V]');
subplot(4,2,4);plot(time13,raw_pin13);ylim([-0.5,4]);xlabel('time [s]');ylabel('voltage [V]');
subplot(4,2,5);plot(time14,raw_pin14);ylim([-0.5,4]);xlabel('time [s]');ylabel('voltage [V]');
subplot(4,2,6);plot(time15,raw_pin15);ylim([-0.5,4]);xlabel('time [s]');ylabel('voltage [V]');
subplot(4,2,7);plot(time16,raw_pin16);ylim([-0.5,4]);xlabel('time [s]');ylabel('voltage [V]');


% upper 3.0 : 1, under 0.2 : 0
high_thres=3.0;
low_thres=0.2;
sign_pin10=zeros(length(time10),1);
sign_pin11=zeros(length(time11),1);
sign_pin12=zeros(length(time12),1);
sign_pin13=zeros(length(time13),1);
sign_pin14=zeros(length(time14),1);
sign_pin15=zeros(length(time15),1);
sign_pin16=zeros(length(time16),1);

for k=1:length(raw_pin10)
    if(raw_pin10(k) >=high_thres)
        sign_pin10(k) =1;
    elseif(raw_pin10(k)<=low_thres)
        sign_pin10(k) =0;
    end
end
for k=1:length(raw_pin11)
    if(raw_pin11(k) >=high_thres)
        sign_pin11(k) =1;
    elseif(raw_pin11(k)<=low_thres)
        sign_pin11(k) =0;
    end
end
for k=1:length(raw_pin12)
    if(raw_pin12(k) >=high_thres)
        sign_pin12(k) =1;
    elseif(raw_pin12(k)<=low_thres)
        sign_pin12(k) =0;
    end
end
for k=1:length(raw_pin13)
    if(raw_pin13(k) >=high_thres)
        sign_pin13(k) =1;
    elseif(raw_pin13(k)<=low_thres)
        sign_pin13(k) =0;
    end
end
for k=1:length(raw_pin14)
    if(raw_pin14(k) >=high_thres)
        sign_pin14(k) =1;
    elseif(raw_pin14(k)<=low_thres)
        sign_pin14(k) =0;
    end
end
for k=1:length(raw_pin15)
    if(raw_pin15(k) >=high_thres)
        sign_pin15(k) =1;
    elseif(raw_pin15(k)<=low_thres)
        sign_pin15(k) =0;
    end
end
for k=1:length(raw_pin16)
    if(raw_pin16(k) >=high_thres)
        sign_pin16(k) =1;
    elseif(raw_pin16(k)<=low_thres)
        sign_pin16(k) =0;
    end
end

figure();
subplot(4,2,1);plot(time10,sign_pin10,'.');ylim([-0.5,1.5]);title('discretize the raw signal');ylabel('Signal [on/off]');xlabel('time[s]');
subplot(4,2,2);plot(time11,sign_pin11,'.');ylim([-0.5,1.5]);ylabel('Signal [on/off]');xlabel('time[s]');
subplot(4,2,3);plot(time12,sign_pin12,'.');ylim([-0.5,1.5]);ylabel('Signal [on/off]');xlabel('time[s]');
subplot(4,2,4);plot(time13,sign_pin13,'.');ylim([-0.5,1.5]);ylabel('Signal [on/off]');xlabel('time[s]');
subplot(4,2,5);plot(time14,sign_pin14,'.');ylim([-0.5,1.5]);ylabel('Signal [on/off]');xlabel('time[s]');
subplot(4,2,6);plot(time15,sign_pin15,'.');ylim([-0.5,1.5]);ylabel('Signal [on/off]');xlabel('time[s]');
subplot(4,2,7);plot(time16,sign_pin16,'.');ylim([-0.5,1.5]);ylabel('Signal [on/off]');xlabel('time[s]');

%% gradient

for k=1:length(sign_pin10)-1
    grad_sign_pin10(k) = sign_pin10(k+1)-sign_pin10(k);
end
for k=1:length(sign_pin11)-1
    grad_sign_pin11(k) = sign_pin11(k+1)-sign_pin11(k);
end
for k=1:length(sign_pin12)-1
    grad_sign_pin12(k) = sign_pin12(k+1)-sign_pin12(k);
end
for k=1:length(sign_pin13)-1
    grad_sign_pin13(k) = sign_pin13(k+1)-sign_pin13(k);
end
for k=1:length(sign_pin14)-1
    grad_sign_pin14(k) = sign_pin14(k+1)-sign_pin14(k);
end
for k=1:length(sign_pin15)-1
    grad_sign_pin15(k) = sign_pin15(k+1)-sign_pin15(k);
end
for k=1:length(sign_pin16)-1
    grad_sign_pin16(k) = sign_pin16(k+1)-sign_pin16(k);
end
upTime_10=find(grad_sign_pin10==1);downTime_10=find(grad_sign_pin10==-1);
dt_10=-(time10(upTime_10(1:end-1))-time10(downTime_10(2:end)));
upTime_11=find(grad_sign_pin11==1);downTime_11=find(grad_sign_pin11==-1);
dt_11=-(time11(upTime_11(1:end-1))-time11(downTime_11(2:end)));
upTime_12=find(grad_sign_pin12==1);downTime_12=find(grad_sign_pin12==-1);
dt_12=-(time12(upTime_12(1:end-1))-time12(downTime_12(2:end)));
upTime_13=find(grad_sign_pin13==1);downTime_13=find(grad_sign_pin13==-1);
dt_13=-(time13(upTime_13(1:end-1))-time13(downTime_13(2:end)));
upTime_14=find(grad_sign_pin14==1);downTime_14=find(grad_sign_pin14==-1);
dt_14=-(time14(upTime_14(1:end-1))-time14(downTime_14(2:end)));
upTime_15=find(grad_sign_pin15==1);downTime_15=find(grad_sign_pin15==-1);
dt_15=-(time15(upTime_15(1:end-1))-time15(downTime_15(2:end)));
upTime_16=find(grad_sign_pin16==1);downTime_16=find(grad_sign_pin16==-1);
dt_16=-(time16(upTime_16(1:end-1))-time16(downTime_16(2:end)));



% compute the time consumption
fprintf('time consumption - serial write 10_ mean : %f [us], std : %f [us]\n',mean(dt_10)*10^6,std(dt_10)*10^6);
fprintf('time consumption - serial write 11_ mean : %f [us], std : %f [us]\n',mean(dt_11)*10^6,std(dt_11)*10^6);
fprintf('time consumption - serial write 12_ mean : %f [us], std : %f [us]\n',mean(dt_12)*10^6,std(dt_12)*10^6);
fprintf('time consumption - serial write 13_ mean : %f [us], std : %f [us]\n',mean(dt_13)*10^6,std(dt_13)*10^6);
fprintf('time consumption - serial write 14_ mean : %f [us], std : %f [us]\n',mean(dt_14)*10^6,std(dt_14)*10^6);
fprintf('time consumption - serial write 15_ mean : %f [us], std : %f [us]\n',mean(dt_15)*10^6,std(dt_15)*10^6);
fprintf('time consumption - serial write 16_ mean : %f [us], std : %f [us]\n',mean(dt_16)*10^6,std(dt_16)*10^6);


