function [ A ] = mat_add_new( varargin )
%% 定义
%%varargin为一个元胞数组，可接受任意个数的输入参数

%% 语法
%%mat_add(A1,A2,...)
%%A = mat_add(A1,A2,...)

%% 实现
try
    A = varargin{1};
    for i=2:length(varargin)
        A = A + varargin{i};
    end
catch 
    error('???数组大小不一样')
end
end
