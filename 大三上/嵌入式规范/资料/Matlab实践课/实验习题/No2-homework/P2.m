%clear workspace and command window
clear
clc

%Load the EuropeFertility.mat
load EuropeFertility;
%Load the AfricaFertility-AfricaRates
load AfricaFertility AfricaRates;

%将两个洲的出生率合并
allRates = [EuropeRates;AfricaRates];

%Plot the histogram(hist)of the allRates
%将EuropeRates里的数据按(最大值-最小值)/20划分为十个矩形
%20个矩形高度表示这个区间内数据出现的次数
hist(allRates,20)