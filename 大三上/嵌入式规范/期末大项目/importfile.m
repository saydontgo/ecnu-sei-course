function Untitled = importfile(workbookFile, sheetName, dataLines)
%IMPORTFILE 导入电子表格中的数据
%  UNTITLED = IMPORTFILE(FILE) 读取名为 FILE 的 Microsoft Excel
%  电子表格文件的第一张工作表中的数据。  以表形式返回数据。
%
%  UNTITLED = IMPORTFILE(FILE, SHEET) 从指定的工作表中读取。
%
%  UNTITLED = IMPORTFILE(FILE, SHEET,
%  DATALINES)按指定的行间隔读取指定工作表中的数据。对于不连续的行间隔，请将 DATALINES 指定为正整数标量或 N×2
%  正整数标量数组。
%
%  示例:
%  Untitled = importfile("A:\ecnu\大三上\嵌入式规范\期末大项目\2025年度作业-三机系统\仿真数据.xlsx", "Sheet1", [2, Inf]);
%
%  另请参阅 READTABLE。
%
% 由 MATLAB 于 2026-01-06 17:38:30 自动生成

%% 输入处理

% 如果未指定工作表，则将读取第一张工作表
if nargin == 1 || isempty(sheetName)
    sheetName = 1;
end

% 如果未指定行的起点和终点，则会定义默认值。
if nargin <= 2
    dataLines = [2, Inf];
end

%% 设置导入选项并导入数据
opts = spreadsheetImportOptions("NumVariables", 9);

% 指定工作表和范围
opts.Sheet = sheetName;
opts.DataRange = dataLines(1, :);

% 指定列名称和类型
opts.VariableNames = ["t", "ia", "ib", "ic", "Tlevel", "PClimit", "PC", "FC", "set_val"];
opts.VariableTypes = ["double", "double", "double", "double", "double", "double", "double", "double", "double"];

% 导入数据
Untitled = readtable(workbookFile, opts, "UseExcel", false);

for idx = 2:size(dataLines, 1)
    opts.DataRange = dataLines(idx, :);
    tb = readtable(workbookFile, opts, "UseExcel", false);
    Untitled = [Untitled; tb]; %#ok<AGROW>
end

end