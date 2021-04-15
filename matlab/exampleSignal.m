close all; clear all; clc;
N=8;
x=1:N;
x=x';

%% This needs to be done in mote 

for k=0:N-1
    y(k+1)=0;
    for n=0:N-1
     y(k+1)=y(k+1)+x(n+1)*cos(pi/N*(n+0.5)*k);
    end
end


%% In Laptop: take y values from the mote apply scaling then take inverse DCT
y(1)=1/sqrt(N)*y(1);

y(2:end)=sqrt(2/N)*y(2:end);

x_esti=idct(y');

mse(x,x_esti)