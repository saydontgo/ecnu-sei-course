%% IFELSE   Sample if-else construction.
%
%  Plots the L-shaped membrane with a colormap dependent on the season.
%
%  See also SWITCHCASE.

%% Plot the L-shaped membrane.
figure
membrane  %Generates the MATLAB logo
shading interp 

%% Determine the date.
D = date;
month = D(4:6); 
d = str2double(D(1:2)); 
% To test the program, remove the above three lines
% from execution by selecting them and typing Ctrl+R.
% Then make explicit assignments to month and d.
% Return commented lines to execution using Ctrl+T.
% Note that changing the date in the OS may affect 
% the MATLAB license server.

% Convert month string to month number.
Months = ['Jan'; 'Feb'; 'Mar'; 'Apr'; 'May'; 'Jun'; ...
    'Jul'; 'Aug'; 'Sep'; 'Oct'; 'Nov'; 'Dec'];
m = strmatch(month, Months);

%% Determine the season.
win = ((m == 12) && (d >= 21)) || (m == 1) || (m == 2) || ((m == 3) && (d < 21));
spr = ((m == 3) && (d >= 21)) || (m == 4) || (m == 5) || ((m == 6) && (d < 21));
sum = ((m == 6) && (d >= 21)) || (m == 7) || (m == 8) || ((m == 9) && (d < 21));
aut = ((m == 9) && (d >= 21)) || (m == 10) || (m == 11) || ((m == 12) && (d < 21));

%% Apply a seasonal colormap.
if win
    colormap(winter)
    title('{\bf It''s winter}')
elseif spr
    colormap(spring)
    title('{\bf It''s spring}')
elseif sum
    colormap(summer)
    title('{\bf It''s summer}')
elseif aut
    colormap(autumn)
    title('{\bf It''s autumn}')
else
     disp('Using default membrane colormap')
end
