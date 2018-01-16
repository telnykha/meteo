FileName = 'KGGW_V03_20120722_000033.nc';

for b = 0:10
    OutFile = sprintf('binary_%i.jpg', b);
    IMG = ProcessFileNC(FileName, b);
    imwrite(IMG, OutFile);
end;