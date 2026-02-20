% a test .m

b= Hilbert(8);
disp(Hilbert(8));

% hilbert函数
function A = Hilbert(n, m, h)
if (nargout > 1) 
    error("only one output\n");
end
if (nargin == 1)
    m = n;
elseif (nargin == 0 || nargin > 2) 
    error("need one or two input\n");
end
for i = 1:n
    for j = 1:m
        A(i, j) = 1 / (i + j - 1);
    end
end
end




