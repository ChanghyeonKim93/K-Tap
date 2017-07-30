close all;clear all;clc;

%%
rawdata=importdata('analogRead_12_data.csv');

time=rawdata.data(:,1);
ref_pin = rawdata.data(:,2);
raw_pin1=rawdata.data(:,3);

figure();
plot(time,raw_pin1);xlim([0 0.0005]);ylim([-1,4]);xlabel('time [s]');ylabel('voltage [V]');
title('Raw signal - analogRead_resolution 12');

% upper 3.0 : 1, under 0.2 : 0
high_thres=3.0;
low_thres=0.2;
sign_pin1=zeros(length(time),1);

for k=1:length(raw_pin1)
    if(raw_pin1(k) >=high_thres)
        sign_pin1(k) =1;
    elseif(raw_pin1(k)<=low_thres)
        sign_pin1(k) =0;
    end
end

figure();plot(time,sign_pin1,'.');xlim([0 0.0005]);ylim([-0.5,1.5]);title('discretize the raw signal');ylabel('Signal [on/off]');xlabel('time[s]');

%% gradient

for k=1:length(sign_pin1)-1
    grad_sign_pin1(k) = sign_pin1(k+1)-sign_pin1(k);
end
grad_sign_pin1(length(sign_pin1))=grad_sign_pin1(end);

figure();plot(time,grad_sign_pin1);xlim([0 0.0005]);ylim([-2,2]);title('High and low dges');


upEdge_ind   = 1;
downEdge_ind = 1;
for k=1:length(sign_pin1)-1
    if(grad_sign_pin1(k) ==1)
        upEdgeTime(upEdge_ind) = time(k);
        upEdge_ind=upEdge_ind+1;
    end
    if(grad_sign_pin1(k) ==-1)
        downEdgeTime(downEdge_ind) = time(k);
        downEdge_ind=downEdge_ind+1;
    end
end

% compute the time consumption
time_consume_digitalRead=downEdgeTime-upEdgeTime(1:end-1)-2.066628/10^6;
fprintf('time consumption - analogRead_resolution 12_ mean : %f [us], std : %f [us]\n',mean(time_consume_digitalRead)*10^6,std(time_consume_digitalRead)*10^6);


