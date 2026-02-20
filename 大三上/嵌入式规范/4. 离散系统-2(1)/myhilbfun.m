function A = myhilb(n, m)
%calculate the Hilbert metrix
%If the number of input is one, then n*n matrix is produced;
%If the number of input is two, then n*m matrix is produced;
%Otherwise the function is error.

%This function is designed by Xue.
if nargout>1,
    error('too many output arguments.'); 
end
if nargin==1,m=n;
elseif nargin==0|nargin>2
    error('wrong number of input arguments.');
end
for i=1:n
    for j=1:m
        A(i,j)=1/(i+j-1);
    end
end

end

