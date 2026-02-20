function[dst] = bubbleSort(n, source)
    fprintf("%d %d\n", n, source);
    for i = n:-1:1
        disp(i)
        max = -inf;
        max_index = 0;
        for j = 1:i
            if (max < source(j))
                max = source(j);
                max_index = j;
            end
        end
        tmp = source(i);
        source(i) = max;
        source(max_index) = tmp;
    end
    dst = source;

end