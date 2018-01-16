function [ R ] = ConeReflectivity( ro, fi, t_idx, dist, az, REF )
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here

r = ro;
k = 360;
m = 1831;

    minr = abs(r - dist(1));
    index_r = 2;
    index_r1 = 2;
    for i = 2:m
        if minr > abs(r - dist(i))
            index_r = i;
            minr = abs(r - dist(i));
        end
    end

    if (abs(r - dist(index_r+1)) >  abs(r - dist(index_r-1)))
        index_r1 = index_r-1;
    else
        index_r1 = index_r+1;
    end

    minfi = abs(fi - az(1,t_idx));
    index_fi1 = 1;
    for j = 1:k
        if minfi > abs(fi - az(j,t_idx))
            index_fi1 = j;
            minfi = abs(fi - az(j,t_idx));
        end
    end

    ifi = index_fi1 + 1;
    if (ifi > 360)
        ifi = 1;
    end   

     if abs(fi - az(index_fi1)) >  abs(fi - az(ifi,t_idx))
        index_fi2 = index_fi1-1;
        if index_fi2 < 1
            index_fi2 = 360;
        end
    else
        index_fi2 = ifi;
     end

 z0= REF(index_r,index_fi1,t_idx);
 z1= REF(index_r1,index_fi1,t_idx);
 z2= REF(index_r,index_fi2,t_idx);
 z3= REF(index_r1,index_fi2,t_idx);


 a1 =   z0 + (z1-z0).*(r - dist(index_r))./(dist(index_r) - dist(index_r1));
 a2 =   z2 + (z3-z2).*(r - dist(index_r))./(dist(index_r) - dist(index_r1));

 dx = r*(cos(3.14*az(index_fi1,t_idx)/180) - cos(3.14*az(index_fi2,t_idx)/180));
 dy = r*(sin(3.14*az(index_fi1,t_idx)/180) - sin(3.14*az(index_fi2,t_idx)/180));

 dr = sqrt(dx^2 + dy^2);

 dx1 = r*(cos(3.14*az(index_fi1,t_idx)/180) - cos(3.14*fi/180));
 dy1 = r*(sin(3.14*az(index_fi1,t_idx)/180) - sin(3.14*fi/180));

 dr1 = sqrt(dx1^2 + dy1^2);

 R = a1 + (a2 - a1)*dr1/dr;

end

