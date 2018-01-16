% ProcessFileNC Преобразование файла NC в бинарное изображение. 
% входные параметры: FileName    - Имя файла 
%                    Elevatioin  - Индекс угла наклона 
% Индекс угла наклона может принимать значение от 1 до 11. 


function [ IMG ] = ProcessFileNC( FileName, ev_ind )

b = ev_ind+1;

ncid1 = netcdf.open(FileName,'NC_WRITE');
varid = netcdf.inqVarID(ncid1,  'azimuthR');

azimuth = double(netcdf.getVar(ncid1, varid));
%[0 b],[360 1]
varid1 = netcdf.inqVarID(ncid1,  'distanceR');
dist = double(netcdf.getVar(ncid1, varid1));
varid_r = netcdf.inqVarID(ncid1,  'Reflectivity');
REF =(double((netcdf.getVar(ncid1, varid_r))-33)*0.5);

varid1 = netcdf.inqVarID(ncid1,  'elevationR');
eval = double(netcdf.getVar(ncid1, varid1));

%[0 0 b], [1832 360 1]
A =  zeros(256,256);

M = max(dist);

k = 360;
m = 1831;
H = 4001 + b*500;

for y = 1:1024
    for x = 1:1024
        
        xx = -M + x*M/512;
        yy = -M + y*M/512;
        
        r = sqrt(xx.^2 + yy.^2);
        
        if r > M
            continue;
        end
        
        fi = atan2d(yy, xx);
        if (fi < 0)
            fi = 360 - abs(fi);
        end 
        
        th = atan2d(H, r);
        
     A(x,y) = Reflectivity(H, r, fi, th, dist, azimuth, eval, REF );              
    end
end


AA = mat2gray(A);
AA=medfilt2(AA);

IMG = AA;
Areas=zeros(num);
Centroid_X=zeros(num);
Centroid_Y=zeros(num);

feats=regionprops(BW1,'Area','Centroid');
fileID = fopen('out1.txt', 'a+t');
fprintf(fileID, '\n\n');
end

