ncid1 = netcdf.open('KGGW_V03_20120722_000033.nc','NC_WRITE');
varid = netcdf.inqVarID(ncid1,  'azimuthR');

azimuth = double(netcdf.getVar(ncid1, varid));
%[0 b],[360 1]
varid1 = netcdf.inqVarID(ncid1,  'distanceV');
varid3 = netcdf.inqVarID(ncid1,  'distanceR_HI');
dist = double(netcdf.getVar(ncid1, varid1));
dist1 = double(netcdf.getVar(ncid1, varid3));