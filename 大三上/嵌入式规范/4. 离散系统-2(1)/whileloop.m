% WHILELOOP Sample WHILE-loop.
%
% Creates an animated plot of the first 12 
% eigenfunctions of the L-shaped membrane.
%
% See also FORLOOP.

n = 1; % The loop variable is assigned outside of the loop.
       % This may be the result of user input or external calculation.
            
figure

while n <= 12 % The keyword "while" is followed by a logical 
              % condition (the "guard") which takes on true/false values.
                      
    membrane(n) % Plot the nth eigenfunction.
    shading interp % Remove grid lines and smooth.
    colormap(autumn) % Assign colors to z-heights.
    title(['{\bf Eigenfunction # }', num2str(n)]) % Add a title 
                                                  % dependent on n.
    pause(1.0) % Set the frame rate
    
    n = n + 1; % The loop variable must be incremented explicitly.
    
end

% Note the repeated eigenvalue at n = 8, 9.
