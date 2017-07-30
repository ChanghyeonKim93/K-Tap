close all;clear all;clc;

%%
rawdata=importdata('wholeTime_due_data_short.csv');

time_ana=rawdata.data(:,1);
data_ana = rawdata.data(:,2);
time_digit=rawdata.data(:,3);
data_digit=rawdata.data(:,4);

figure();plot(time_ana,data_ana);ylim([-1,6]);xlabel('time [s]');ylabel('voltage [V]');
title('Raw signal - whole loop running time');

figure();plot(time_digit,data_digit,'*');
% upper 3.0 : 1, under 0.2 : 0
high_thres=3.0;
low_thres=0.2;
sign_ana=zeros(length(time_ana),1);

for k=1:length(data_ana)
    if(data_ana(k) >=high_thres)
        sign_ana(k) =1;
    elseif(data_ana(k)<=low_thres)
        sign_ana(k) =0;
    end
end

figure();plot(time_ana,sign_ana,'.');ylim([-0.5,1.5]);title('discretize the raw signal');ylabel('Signal [on/off]');xlabel('time[s]');

%% gradient

for k=1:length(sign_ana)-1
    grad_sign_ana(k) = sign_ana(k+1)-sign_ana(k);
end
grad_sign_ana(length(sign_ana))=grad_sign_ana(end);

figure();plot(time_ana,grad_sign_ana);ylim([-2,2]);title('High and low dges');


upEdge_ind   = 1;
downEdge_ind = 1;
for k=1:length(sign_ana)-1
    if(grad_sign_ana(k) ==1)
        upEdgeTime(upEdge_ind) = time_ana(k);
        upEdge_ind=upEdge_ind+1;
    end
    if(grad_sign_ana(k) ==-1)
        downEdgeTime(downEdge_ind) = time_ana(k);
        downEdge_ind=downEdge_ind+1;
    end
end

% compute the time consumption
time_consume_whole=downEdgeTime-upEdgeTime(1:end-1)-2.066628/10^6;
fprintf('time consumption - whole loop (due) - mean: %f [us], std : %f [us]\n',mean(time_consume_whole)*10^6,std(time_consume_whole)*10^6);


