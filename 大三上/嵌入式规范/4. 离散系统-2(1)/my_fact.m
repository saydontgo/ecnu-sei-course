   function k=my_fact(n)
   %factorial function
   
   if nargin~=1, error('Error: Only one input variable accepted'); end
   if nargout>1,error('Error of the number of output');end

   if abs(n-floor(n))>eps | n<0 % judge whether n is a non-negative integer
      error('n should be a non-negative integer');
   end
   if n>1      % if n>1, recursive calls are used
      k=n*my_fact(n-1);
   elseif any([0 1]==n) % 0!=1!=1, the exit of the function
      k=1;
   end
