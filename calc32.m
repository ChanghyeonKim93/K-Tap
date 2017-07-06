close all; clear all;clc;

%% 
a = 600000000;
Num=a;
ind =1;
tic;
while(1)
    Q = floor(Num/32);
    R = mod(Num,32);
    if(Q==0) 
        Arr(ind)=R;
        break;
    end
    Arr(ind)=R;
    ind=ind+1;
    Num=Q;
end
toc
SUM = 0;

for k=1:length(Arr)
    SUM = SUM + Arr(k)*32^(k-1);
end
Arr