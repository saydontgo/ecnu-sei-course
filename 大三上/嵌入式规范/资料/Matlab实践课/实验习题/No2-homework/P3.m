function [ information ] = P3( mess,shift )

%% 函数可完成加密信息破解工作
%mess表示 加密的信息
%shift表示 加密信息的偏移量
%information表示 破解的信息

%% 函数实现
%将mess中每个字符做相应的偏移
for i=1:length(mess)
    information(i) = char(mess(i)-shift);
end

end

