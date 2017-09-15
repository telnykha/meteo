function [ object ] = findObject( img )
% Поиск объекта с максимальной полощадью на бинарном изображении. 

[BW1 num]=bwlabel(img,8);

Areas=zeros(num);
Centroid_X=zeros(num);
Centroid_Y=zeros(num);

% % подсчет площади и периметра каждого элемента
feats=regionprops(BW1,'Area','Centroid');
fileID = fopen('out1.txt', 'a+t');
fprintf(fileID, '\n\n');

 for i=1:num; 
      if feats(i).Area>20
           fprintf(fileID, '%d\t%d\t%d\n', feats(i).Area, feats(i).Centroid(1), feats(i).Centroid(2)); 
      else
        %      Centroid_X(i)=feats(i).Centroid(1);
%       Centroid_Y(i)=feats(i).Centroid(2);
 end;
 end;
 fclose(fileID);
 AR =[Areas(1:num)];
 [M_AR, Indices]=max(AR);
 
 C_X=Centroid_X(Indices);
 C_Y=Centroid_Y(Indices);
 
 OBJ =  zeros(3,1);

 OBJ(1) = M_AR;
 OBJ(2) = C_X;
 OBJ(3) = C_Y;
 
 object = OBJ;
end

