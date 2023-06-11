% 数据绘制
close all
clear all
clc
fp=fopen('datafile.txt','rt');
data=textscan(fp,'%d\t%d\t%f\t%f');
fclose(fp);
N=length(data{1,1})
x=1:N;
x=x';
%当前最优传感器个数
nN=data{1,1};
subplot(2,1,1);
plot(x,nN,'bo');
hold on
%历史最优传感器个数
hN=data{1,2};
plot(x,hN,'r-','LineWidth',3);
legend('当前最优传感器个数','历史最优传感器个数');
ylabel('传感器个数');
xlabel('迭代次数');
hold off;

%当前最优适应度值
nF=data{1,3};
subplot(2,1,2);
plot(x,nF,'bo');
hold on
%历史最优适应度值
hF=data{1,4};
plot(x,hF,'r-','LineWidth',3);
legend('当前最优适应度值','历史最优适应度值');
axis([1,N,1,1.5]);
ylabel('适应度值');
xlabel('迭代次数');
