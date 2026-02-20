function a = my_fibo_for( k )
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here

a=[1,1];
for(t=3:k)
    a(t)=a(t-1)+a(t-2);
end

end

