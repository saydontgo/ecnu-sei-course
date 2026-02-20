function [s_even,s_odd] = array_add(A)
%求解奇数之和和偶数之和
s_odd=0;
s_even=0;
[r,c]=size(A);
B=reshape(A,1,r*c);%压缩为一维
% disp(B);
for k=B;
   if (rem(k,2)==1)
       s_odd=s_odd+k;
   else
       s_even=s_even+k;
   end
end