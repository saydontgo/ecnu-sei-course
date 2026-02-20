% computing the least m that the sum of them is less than 10000

res = 0;
index = 1;
while res <= 10000
    res = res + index;
    index = index + 1;
end

disp([res, index]);
  