function inputVec=bubbleSort(inputVec)
%head-body
num=length(inputVec);
for i=num-1:-1:1
    for j=1:i
        if inputVec(j)>inputVec(j+1)
            temp=inputVec(j);
            inputVec(j)=inputVec(j+1);
            inputVec(j+1)=temp;
        end
    end
end
output=inputVec
return;

           
