%% SWITCHCASE   Sample switch-case construction.
%
%  Plots the L-shaped membrane with a colormap dependent on the season.
%
%  See also IFELSE.

%% Plot the L-shaped membrane.
figure
membrane
shading interp

%% Determine the date.
D = date;
month = D(4:6); 
day = str2double(D(1:2));
% To test the program, remove the above three lines
% from execution by selecting them and typing Ctrl+R.
% Then make explicit assignments to month and day.
% Return commented lines to execution using Ctrl+T.
% Note that changing the date in the OS may affect 
% the MATLAB license server.

%% Apply a seasonal colormap.
switch month
    
    case{'Jan', 'Feb'}
        colormap(winter)
        title('{\bf It''s winter}')
        
    case{'Mar'}
        switch day
            
            case{21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31}
                colormap(spring)
                title('{\bf It''s spring}')
                
            otherwise
                colormap(winter)
                title('{\bf It''s winter}')
                
        end
        
    case{'Apr', 'May'}
        colormap(spring)
        title('{\bf It''s spring}')
        
    case{'Jun'}
        switch day
            
            case{21, 22, 23, 24, 25, 26, 27, 28, 29, 30}
                colormap(summer)
                title('{\bf It''s summer}')
                
            otherwise
                colormap(spring)
                title('{\bf It''s spring}')
                
        end
     
    case{'Jul', 'Aug'}
        colormap(summer)
        title('{\bf It''s summer}')
        
    case{'Sep'}
        switch day
            
            case{21, 22, 23, 24, 25, 26, 27, 28, 29, 30}
                colormap(autumn)
                title('{\bf It''s autumn}')
                
            otherwise
                colormap(summer)
                title('{\bf It''s summer}')
                
        end
        
    case{'Oct', 'Nov'}
        colormap(autumn)
        title('{\bf It''s autumn}')
        
    case{'Dec'}
        switch day
            
            case{21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31}
                colormap(winter)
                title('{\bf It''s winter}')
                
            otherwise
                colormap(autumn)
                title('{\bf It''s autumn}')
                
        end
        
    otherwise
        disp('Using default membrane colormap')
        
end
