function [ mess ] = P5( information,shift )
%% 函数可实现信息加密功能
%information表示 加密的信息
%shift表示 加密信息的偏移量
%mess表示 加密后的信息

%% 函数实现
lenShift = length(shift);   %确定shift数组的长度
lenRepShift = length(information);   %确定information的长度
left = mod(lenRepShift,lenShift);    %确定rep后多余的长度
len = floor(lenRepShift/lenShift);   %确定需要重复的次数
repShift = repmat(shift,1,len); %将shift数组重复
repShift = [repShift,shift(1:left)]; %去除shift的多余部分
%将information中每个字符做相应的偏移
temp = double(information);
mess = char(temp + repShift);

end


