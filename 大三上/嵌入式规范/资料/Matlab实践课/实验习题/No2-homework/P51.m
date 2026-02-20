function [ information ] = P51( mess,shift )

%% 函数可完成加密信息破解工作
%mess表示 加密的信息
%shift表示 加密信息的偏移量
%information表示 破解的信息

%% 函数实现
lenShift = length(shift);   %确定shift数组的长度
lenRepShift = length(mess);   %确定mess的长度
left = mod(lenRepShift,lenShift);    %确定rep后多余的长度
len = floor(lenRepShift/lenShift);   %确定需要重复的次数
repShift = repmat(shift,1,len); %将shift数组重复
repShift = [repShift,shift(1:left)]; %去除repShift的多余部分
%将information中每个字符做相应的偏移
temp = double(mess);
information = char(temp - repShift);

end
