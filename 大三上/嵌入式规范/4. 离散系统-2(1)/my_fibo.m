   function a=my_fibo(k)
   % the recursion algorithm
   
   if k==1 | k==2, 
       a=1; 
   else
       a=my_fibo(k-1)+my_fibo(k-2);
   end
   end
