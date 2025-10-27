function out = model
%
% GEM_Comsol_Garfield.m
%
% Model exported on Oct 9 2020, 16:19 by COMSOL 5.1.0.234.

import com.comsol.model.*
import com.comsol.model.util.*

model = ModelUtil.create('Model');

model.modelPath('H:\NUMEN\gas tracker');

model.label('GEM_Comsol_Garfield.mph');

model.comments(['Untitled\n\n']);

model.modelNode.create('comp1');

model.file.clear;

model.geom.create('geom1', 3);

model.mesh.create('mesh1', 'geom1');

model.geom('geom1').lengthUnit('mm');
model.geom('geom1').repairTol(1.0E-8);
model.geom('geom1').create('blk1', 'Block');
model.geom('geom1').feature('blk1').set('size', {'0.07*sqrt(3)' '0.07' '2.0'});
model.geom('geom1').feature('blk1').set('pos', {'-0.07' '-0.07' '-1.0'});
model.geom('geom1').create('cone1', 'Cone');
model.geom('geom1').feature('cone1').set('specifytop', 'radius');
model.geom('geom1').feature('cone1').set('h', '0.025');
model.geom('geom1').feature('cone1').set('rtop', '0.07/2');
model.geom('geom1').feature('cone1').set('pos', {'-0.07' '-0.07' '0'});
model.geom('geom1').feature('cone1').set('r', '0.05/2');
model.geom('geom1').create('cone2', 'Cone');
model.geom('geom1').feature('cone2').set('specifytop', 'radius');
model.geom('geom1').feature('cone2').set('h', '0.025');
model.geom('geom1').feature('cone2').set('rtop', '0.05/2');
model.geom('geom1').feature('cone2').set('pos', {'-0.07' '-0.07' '-.025'});
model.geom('geom1').feature('cone2').set('r', '0.07/2');
model.geom('geom1').create('cyl1', 'Cylinder');
model.geom('geom1').feature('cyl1').set('r', '0.08/2');
model.geom('geom1').feature('cyl1').set('pos', {'-0.07' '-0.07' '-0.03'});
model.geom('geom1').feature('cyl1').set('h', '0.005');
model.geom('geom1').create('cyl2', 'Cylinder');
model.geom('geom1').feature('cyl2').set('r', '0.08/2');
model.geom('geom1').feature('cyl2').set('pos', {'-0.07' '-0.07' '0.025'});
model.geom('geom1').feature('cyl2').set('h', '0.005');
model.geom('geom1').create('mov1', 'Move');
model.geom('geom1').feature('mov1').set('keep', true);
model.geom('geom1').feature('mov1').set('displx', '0.07*sqrt(3)');
model.geom('geom1').feature('mov1').set('disply', '0.07');
model.geom('geom1').feature('mov1').selection('input').set({'cone1' 'cone2' 'cyl1' 'cyl2'});
model.geom('geom1').create('blk2', 'Block');
model.geom('geom1').feature('blk2').set('size', {'0.07*sqrt(3)' '0.07' '0.005'});
model.geom('geom1').feature('blk2').set('pos', {'-0.07' '-0.07' '-0.03'});
model.geom('geom1').create('blk3', 'Block');
model.geom('geom1').feature('blk3').set('size', {'0.07*sqrt(3)' '0.07' '0.005'});
model.geom('geom1').feature('blk3').set('pos', {'-0.07' '-0.07' '0.025'});
model.geom('geom1').create('uni5', 'Union');
model.geom('geom1').feature('uni5').set('intbnd', false);
model.geom('geom1').feature('uni5').selection('input').set({'blk2' 'blk3'});
model.geom('geom1').create('uni1', 'Union');
model.geom('geom1').feature('uni1').set('intbnd', false);
model.geom('geom1').feature('uni1').set('repairtol', '1.0E-10');
model.geom('geom1').feature('uni1').selection('input').set({'cone1' 'cone2' 'cyl1' 'cyl2' 'mov1'});
model.geom('geom1').create('dif3', 'Difference');
model.geom('geom1').feature('dif3').set('repairtol', '1.0E-10');
model.geom('geom1').feature('dif3').set('keep', true);
model.geom('geom1').feature('dif3').set('intbnd', false);
model.geom('geom1').feature('dif3').selection('input').set({'uni5'});
model.geom('geom1').feature('dif3').selection('input2').set({'uni1'});
model.geom('geom1').create('del4', 'Delete');
model.geom('geom1').feature('del4').selection('input').init(3);
model.geom('geom1').feature('del4').selection('input').set('uni5(1)', [1 2]);
model.geom('geom1').create('blk8', 'Block');
model.geom('geom1').feature('blk8').set('size', {'0.07*sqrt(3)' '0.07' '0.05'});
model.geom('geom1').feature('blk8').set('pos', {'-0.07' '-0.07' '-0.025'});
model.geom('geom1').create('dif6', 'Difference');
model.geom('geom1').feature('dif6').set('keep', true);
model.geom('geom1').feature('dif6').set('intbnd', false);
model.geom('geom1').feature('dif6').selection('input').set({'blk8'});
model.geom('geom1').feature('dif6').selection('input2').set({'uni1'});
model.geom('geom1').create('del7', 'Delete');
model.geom('geom1').feature('del7').selection('input').init(3);
model.geom('geom1').feature('del7').selection('input').set('blk8(1)', [1]);
model.geom('geom1').create('dif4', 'Difference');
model.geom('geom1').feature('dif4').set('repairtol', '1.0E-10');
model.geom('geom1').feature('dif4').set('keep', true);
model.geom('geom1').feature('dif4').set('intbnd', false);
model.geom('geom1').feature('dif4').selection('input').set({'blk1'});
model.geom('geom1').feature('dif4').selection('input2').set({'dif3(1)'});
model.geom('geom1').create('del11', 'Delete');
model.geom('geom1').feature('del11').selection('input').init;
model.geom('geom1').feature('del11').selection('input').set({'blk1'});
model.geom('geom1').create('int3', 'Intersection');
model.geom('geom1').feature('int3').set('intbnd', false);
model.geom('geom1').feature('int3').set('keep', true);
model.geom('geom1').feature('int3').selection('input').set({'dif4' 'uni1'});
model.geom('geom1').create('del8', 'Delete');
model.geom('geom1').feature('del8').selection('input').init(3);
model.geom('geom1').feature('del8').selection('input').set('uni1(1)', [1 2]);
model.geom('geom1').create('del10', 'Delete');
model.geom('geom1').feature('del10').selection('input').init(3);
model.geom('geom1').feature('del10').selection('input').set('int3(1)', [1 2]);
model.geom('geom1').create('dif7', 'Difference');
model.geom('geom1').feature('dif7').set('keep', true);
model.geom('geom1').feature('dif7').set('intbnd', false);
model.geom('geom1').feature('dif7').selection('input').set({'dif4'});
model.geom('geom1').feature('dif7').selection('input2').set({'dif6'});
model.geom('geom1').create('del6', 'Delete');
model.geom('geom1').feature('del6').selection('input').init(3);
model.geom('geom1').feature('del6').selection('input').set('dif4(1)', [1]);
model.geom('geom1').create('rot1', 'Rotate');
model.geom('geom1').feature('rot1').set('rot', '90');
model.geom('geom1').feature('rot1').selection('input').set({'dif3' 'dif6' 'dif7'});
model.geom('geom1').create('mov2', 'Move');
model.geom('geom1').feature('mov2').set('displx', '-0.07');
model.geom('geom1').feature('mov2').set('disply', '0.07*sqrt(3)/2');
model.geom('geom1').feature('mov2').selection('input').set({'rot1'});
model.geom('geom1').create('mir1', 'Mirror');
model.geom('geom1').feature('mir1').set('axis', {'1' '0' '0'});
model.geom('geom1').feature('mir1').set('pos', {'0' '0' '0'});
model.geom('geom1').feature('mir1').selection('input').set({'mov2'});
model.geom('geom1').feature('fin').set('repairtol', '1.0E-8');
model.geom('geom1').run;

model.variable.create('var1');
model.variable('var1').set('Vdrift', '200');
model.variable('var1').set('Vgem', '300');
model.variable('var1').set('Vind', '200');

model.material.create('mat1', 'Common', 'comp1');
model.material.create('mat2', 'Common', 'comp1');
model.material.create('mat3', 'Common', 'comp1');
model.material('mat1').propertyGroup('def').func.create('eta', 'Piecewise');
model.material('mat1').propertyGroup('def').func.create('Cp', 'Piecewise');
model.material('mat1').propertyGroup('def').func.create('rho', 'Analytic');
model.material('mat1').propertyGroup('def').func.create('k', 'Piecewise');
model.material('mat1').propertyGroup('def').func.create('cs', 'Analytic');
model.material('mat1').propertyGroup.create('RefractiveIndex', 'Refractive index');
model.material('mat2').selection.set([2]);
model.material('mat2').propertyGroup('def').func.create('CTE', 'Piecewise');
model.material('mat3').selection.set([3 4]);
model.material('mat3').propertyGroup.create('linzRes', 'Linearized resistivity');

model.physics.create('es', 'Electrostatics', 'geom1');
model.physics('es').create('pot6', 'ElectricPotential', 2);
model.physics('es').feature('pot6').selection.set([3]);
model.physics('es').create('pot1', 'ElectricPotential', 2);
model.physics('es').feature('pot1').selection.set([11 12 13 23]);
model.physics('es').create('pot2', 'ElectricPotential', 2);
model.physics('es').feature('pot2').selection.set([15 16 17 25]);
model.physics('es').create('pot5', 'ElectricPotential', 2);
model.physics('es').feature('pot5').selection.set([4]);

model.mesh('mesh1').create('ftet1', 'FreeTet');
model.mesh('mesh1').feature('ftet1').create('size1', 'Size');
model.mesh('mesh1').feature('ftet1').create('size2', 'Size');
model.mesh('mesh1').feature('ftet1').feature('size1').selection.geom('geom1', 3);
model.mesh('mesh1').feature('ftet1').feature('size1').selection.set([1]);
model.mesh('mesh1').feature('ftet1').feature('size2').selection.geom('geom1', 3);
model.mesh('mesh1').feature('ftet1').feature('size2').selection.set([2 3 4]);

model.result.table.create('evl3', 'Table');

model.view('view1').set('renderwireframe', true);

model.material('mat1').label('Air');
model.material('mat1').set('family', 'air');
model.material('mat1').propertyGroup('def').func('eta').set('pieces', {'200.0' '1600.0' '-8.38278E-7+8.35717342E-8*T^1-7.69429583E-11*T^2+4.6437266E-14*T^3-1.06585607E-17*T^4'});
model.material('mat1').propertyGroup('def').func('eta').set('arg', 'T');
model.material('mat1').propertyGroup('def').func('Cp').set('pieces', {'200.0' '1600.0' '1047.63657-0.372589265*T^1+9.45304214E-4*T^2-6.02409443E-7*T^3+1.2858961E-10*T^4'});
model.material('mat1').propertyGroup('def').func('Cp').set('arg', 'T');
model.material('mat1').propertyGroup('def').func('rho').set('args', {'pA' 'T'});
model.material('mat1').propertyGroup('def').func('rho').set('expr', 'pA*0.02897/8.314/T');
model.material('mat1').propertyGroup('def').func('rho').set('dermethod', 'manual');
model.material('mat1').propertyGroup('def').func('rho').set('plotargs', {'pA' '0' '1'; 'T' '0' '1'});
model.material('mat1').propertyGroup('def').func('rho').set('argders', {'pA' 'd(pA*0.02897/8.314/T,pA)'; 'T' 'd(pA*0.02897/8.314/T,T)'});
model.material('mat1').propertyGroup('def').func('k').set('pieces', {'200.0' '1600.0' '-0.00227583562+1.15480022E-4*T^1-7.90252856E-8*T^2+4.11702505E-11*T^3-7.43864331E-15*T^4'});
model.material('mat1').propertyGroup('def').func('k').set('arg', 'T');
model.material('mat1').propertyGroup('def').func('cs').set('args', {'T'});
model.material('mat1').propertyGroup('def').func('cs').set('expr', 'sqrt(1.4*287*T)');
model.material('mat1').propertyGroup('def').func('cs').set('dermethod', 'manual');
model.material('mat1').propertyGroup('def').func('cs').set('plotargs', {'T' '0' '1'});
model.material('mat1').propertyGroup('def').func('cs').set('argders', {'T' 'd(sqrt(1.4*287*T),T)'});
model.material('mat1').propertyGroup('def').set('relpermeability', {'1' '0' '0' '0' '1' '0' '0' '0' '1'});
model.material('mat1').propertyGroup('def').set('relpermittivity', {'1' '0' '0' '0' '1' '0' '0' '0' '1'});
model.material('mat1').propertyGroup('def').set('dynamicviscosity', 'eta(T[1/K])[Pa*s]');
model.material('mat1').propertyGroup('def').set('ratioofspecificheat', '1.4');
model.material('mat1').propertyGroup('def').set('electricconductivity', {'0[S/m]' '0' '0' '0' '0[S/m]' '0' '0' '0' '0[S/m]'});
model.material('mat1').propertyGroup('def').set('heatcapacity', 'Cp(T[1/K])[J/(kg*K)]');
model.material('mat1').propertyGroup('def').set('density', 'rho(pA[1/Pa],T[1/K])[kg/m^3]');
model.material('mat1').propertyGroup('def').set('thermalconductivity', {'k(T[1/K])[W/(m*K)]' '0' '0' '0' 'k(T[1/K])[W/(m*K)]' '0' '0' '0' 'k(T[1/K])[W/(m*K)]'});
model.material('mat1').propertyGroup('def').set('soundspeed', 'cs(T[1/K])[m/s]');
model.material('mat1').propertyGroup('def').addInput('temperature');
model.material('mat1').propertyGroup('def').addInput('pressure');
model.material('mat1').propertyGroup('RefractiveIndex').set('n', '');
model.material('mat1').propertyGroup('RefractiveIndex').set('ki', '');
model.material('mat1').propertyGroup('RefractiveIndex').set('n', {'1' '0' '0' '0' '1' '0' '0' '0' '1'});
model.material('mat1').propertyGroup('RefractiveIndex').set('ki', {'0' '0' '0' '0' '0' '0' '0' '0' '0'});
model.material('mat2').label('PCB');
model.material('mat2').propertyGroup('def').func('CTE').set('pieces', {'80.0' '380.0' '9.741443E-6+2.13708E-7*T^1-5.225347E-10*T^2+4.893412E-13*T^3'});
model.material('mat2').propertyGroup('def').func('CTE').set('arg', 'T');
model.material('mat2').propertyGroup('def').set('CTE', 'CTE(T[1/K])[1/K]');
model.material('mat2').propertyGroup('def').set('relpermittivity', {'4' '0' '0' '0' '4' '0' '0' '0' '4'});
model.material('mat2').propertyGroup('def').addInput('temperature');
model.material('mat3').label('Copper');
model.material('mat3').set('family', 'copper');
model.material('mat3').propertyGroup('def').set('relpermeability', {'1' '0' '0' '0' '1' '0' '0' '0' '1'});
model.material('mat3').propertyGroup('def').set('electricconductivity', {'5.998e7[S/m]' '0' '0' '0' '5.998e7[S/m]' '0' '0' '0' '5.998e7[S/m]'});
model.material('mat3').propertyGroup('def').set('heatcapacity', '385[J/(kg*K)]');
model.material('mat3').propertyGroup('def').set('relpermittivity', {'1' '0' '0' '0' '1' '0' '0' '0' '1'});
model.material('mat3').propertyGroup('def').set('emissivity', '0.5');
model.material('mat3').propertyGroup('def').set('density', '8700[kg/m^3]');
model.material('mat3').propertyGroup('def').set('thermalconductivity', {'400[W/(m*K)]' '0' '0' '0' '400[W/(m*K)]' '0' '0' '0' '400[W/(m*K)]'});
model.material('mat3').propertyGroup('linzRes').set('rho0', '');
model.material('mat3').propertyGroup('linzRes').set('alpha', '');
model.material('mat3').propertyGroup('linzRes').set('Tref', '');
model.material('mat3').propertyGroup('linzRes').set('rho0', '1.72e-8[ohm*m]');
model.material('mat3').propertyGroup('linzRes').set('alpha', '3.9e-3[1/K]');
model.material('mat3').propertyGroup('linzRes').set('Tref', '273.15[K]');
model.material('mat3').propertyGroup('linzRes').addInput('temperature');

model.physics('es').feature('pot6').set('V0', '350');
model.physics('es').feature('pot1').set('V0', '150');
model.physics('es').feature('pot2').set('V0', '-150');
model.physics('es').feature('pot5').set('V0', '-200');

model.mesh('mesh1').feature('size').set('hauto', 1);
model.mesh('mesh1').feature('ftet1').feature('size1').set('hauto', 2);
model.mesh('mesh1').feature('ftet1').feature('size2').set('hauto', 9);
model.mesh('mesh1').run;

model.result.table('evl3').label('Evaluation 3D');
model.result.table('evl3').comments('Interactive 3D values');

model.study.create('std1');
model.study('std1').create('stat', 'Stationary');

model.sol.create('sol1');
model.sol('sol1').study('std1');
model.sol('sol1').attach('std1');
model.sol('sol1').create('st1', 'StudyStep');
model.sol('sol1').create('v1', 'Variables');
model.sol('sol1').create('s1', 'Stationary');
model.sol('sol1').feature('s1').create('fc1', 'FullyCoupled');
model.sol('sol1').feature('s1').create('i1', 'Iterative');
model.sol('sol1').feature('s1').feature('i1').create('mg1', 'Multigrid');
model.sol('sol1').feature('s1').feature.remove('fcDef');

model.study('std1').feature('stat').set('initstudyhide', 'on');
model.study('std1').feature('stat').set('initsolhide', 'on');
model.study('std1').feature('stat').set('solnumhide', 'on');
model.study('std1').feature('stat').set('notstudyhide', 'on');
model.study('std1').feature('stat').set('notsolhide', 'on');
model.study('std1').feature('stat').set('notsolnumhide', 'on');

model.result.create('pg1', 'PlotGroup3D');
model.result.create('pg2', 'PlotGroup3D');
model.result('pg1').create('mslc1', 'Multislice');
model.result('pg2').create('str1', 'Streamline');
model.result('pg2').create('surf1', 'Surface');
model.result('pg2').create('slc1', 'Slice');
model.result('pg2').create('str2', 'Streamline');
model.result('pg2').create('surf2', 'Surface');
model.result.export.create('mesh1', 'Mesh');
model.result.export.create('data1', 'Data');

model.sol('sol1').attach('std1');
model.sol('sol1').feature('s1').feature('i1').set('linsolver', 'cg');
model.sol('sol1').feature('s1').feature('i1').feature('mg1').set('prefun', 'amg');
model.sol('sol1').runAll;

model.result('pg1').label('Electric Potential (es)');
model.result('pg1').set('frametype', 'spatial');
model.result('pg2').label('Electric Field');
model.result('pg2').set('frametype', 'spatial');
model.result('pg2').feature('str1').active(false);
model.result('pg2').feature('str1').set('selnumber', '200');
model.result('pg2').feature('surf1').active(false);
model.result('pg2').feature('slc1').active(false);
model.result('pg2').feature('slc1').set('descr', 'Electric field norm');
model.result('pg2').feature('slc1').set('unit', 'V/m');
model.result('pg2').feature('slc1').set('rangecolormax', '700000');
model.result('pg2').feature('slc1').set('rangecolormin', '200');
model.result('pg2').feature('slc1').set('rangecoloractive', 'on');
model.result('pg2').feature('slc1').set('expr', 'es.normE');
model.result('pg2').feature('slc1').set('quickxnumber', '1');
model.result('pg2').feature('surf2').set('descr', 'Electric field norm');
model.result('pg2').feature('surf2').set('unit', 'V/m');
model.result('pg2').feature('surf2').set('colortablesym', true);
model.result('pg2').feature('surf2').set('expr', 'es.normE');
model.result.export('mesh1').set('filename', 'H:\NUMEN\gas tracker\meshfileGarfield2_1_light.mphtxt');
model.result.export('mesh1').set('type3D', 'mphascii');
model.result.export('data1').set('descr', {'Electric potential'});
model.result.export('data1').set('expr', {'V'});
model.result.export('data1').set('filename', 'H:\NUMEN\gas tracker\fieldmapGarfield2_1_light.txt');
model.result.export('data1').set('lagorder', '2');
model.result.export('data1').set('fullprec', false);
model.result.export('data1').set('resolution', 'custom');
model.result.export('data1').set('unit', {'V'});

out = model;
