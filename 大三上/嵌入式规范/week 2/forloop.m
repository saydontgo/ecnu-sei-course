% FORLOOP Sample FOR-loop.
%
% Creates an animated plot of the first 12 
% eigenfunctions of the L-shaped membrane.
%
% See also WHILELOOP.

figure

for n = 3:2:7 % The keyword "for" is followed by an explicit 
             % assignment of values to a loop parameter.
    sprintf('%d', n)               
    membrane(n)% Plot the nth eigenfunction.
    shading interp % Remove mesh lines from the plot and smooth shading.
    colormap(autumn) % Assign colors to the z-heights.
    title(['{\bf Eigenfunction # }', num2str(n)]) % Add a title 
                                                  % dependent on n.
    pause(1.0) % Set the frame rate.
    
end

% Note the repeated eigenvalue at n = 8, 9.
