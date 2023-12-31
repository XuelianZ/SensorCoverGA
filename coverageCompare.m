close all
clear all
clc
x =[100,120,150,200,300];
y =[110.172/2,177.325/2,270.431/2,560.094/2,1639.533/2];
z =[10.844/2,14.0/2,18.329/2,33.703/2,92.984/2];
plot(x,y,'b^-','LineWidth',2);
hold on
plot(x,z,'ro-','LineWidth',2);
legend('栅格统计算法','几何覆盖率算法');
ylabel('时间消耗(s)');
xlabel('目标区域边长');