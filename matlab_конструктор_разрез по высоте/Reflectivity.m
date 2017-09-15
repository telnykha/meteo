function [ R ] = Reflectivity(H, ro, fi, theta, dist, az, ev, REF )
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
mint = abs(theta - ev(1,1));
idx  = 1;
for i = 0:10
    if (abs(theta - ev(1,i+1)) < mint)
        mint = abs(theta - ev(1,i+1));
        idx = i+1;
    end
end
idx1 = 1;
if (theta > mint)
    idx1 = idx + 1;
else
    idx1 = idx - 1;
end



if idx1 == 0 || idx1 > 10
    R =0;%ConeReflectivity(ro1,fi, idx, dist, az, REF);
else
    ro1 = ro / cos(3.14*ev(1,idx)/180);
    ro2 = ro / cos(3.14*ev(1,idx1)/180);
    
    R1 = ConeReflectivity(ro1,fi, idx, dist, az, REF);
    R2 = ConeReflectivity(ro2,fi, idx1, dist, az, REF);
    
    R = R1 + (R2-R1)*(theta - ev(1, idx))/(ev(1, idx1) - ev(1, idx));
end

end

