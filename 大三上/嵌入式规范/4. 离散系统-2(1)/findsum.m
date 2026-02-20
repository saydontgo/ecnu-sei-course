function [ m, s ] = findsum(k)
%findsum is used to calculate the sum of n while sum<=k
%   
s=0;m=0;
while(s<=k), m=m+1;s=s+m;end
end

