function [ A ] = mat_add( varargin )
%% 定义
%%varargin为一个元胞数组，可接受任意个数的输入参数

%% 语法
%%mat_add(A1,A2,...)
%%A = mat_add(A1,A2,...)

%% 实现
    flag = true;
    for k=1:(length(varargin)-1)
        if size(varargin{k}) ~= size(varargin{k+1})
            flag = false;
        end
    end
    if(flag)
    A = varargin{1};
    for i=2:length(varargin)
        A = A + varargin{i};
    end
    
    else
    disp('??? 输入的矩阵大小应该一样');
    disp('??? 错误矩阵不加入运算');
    end
end

