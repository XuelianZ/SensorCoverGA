% ���ݻ���
close all
clear all
clc
fp=fopen('datafile.txt','rt');
data=textscan(fp,'%d\t%d\t%f\t%f');
fclose(fp);
N=length(data{1,1})
x=1:N;
x=x';
%��ǰ���Ŵ���������
nN=data{1,1};
subplot(2,1,1);
plot(x,nN,'bo');
hold on
%��ʷ���Ŵ���������
hN=data{1,2};
plot(x,hN,'r-','LineWidth',3);
legend('��ǰ���Ŵ���������','��ʷ���Ŵ���������');
ylabel('����������');
xlabel('��������');
hold off;

%��ǰ������Ӧ��ֵ
nF=data{1,3};
subplot(2,1,2);
plot(x,nF,'bo');
hold on
%��ʷ������Ӧ��ֵ
hF=data{1,4};
plot(x,hF,'r-','LineWidth',3);
legend('��ǰ������Ӧ��ֵ','��ʷ������Ӧ��ֵ');
axis([1,N,1,1.5]);
ylabel('��Ӧ��ֵ');
xlabel('��������');
