a = 1;
disp(a);

v = [1 2 3 4];
disp(v(1:3));

mat = [1 2 3; 4 5 6; 7 8 9];
disp(mat);
disp(mat(2, 2));
disp(mat(4));
disp(mat(1,:));

mat2 = [0 1 2; 3 4 5; 6 7 8];
disp(mat * mat2);
disp(mat .* mat2);

%zeros(m, n);
%ones();
%rand();
%randi([rozsah prvku], velikost)
% prazdna matice []

disp(size(mat))
%clc vymaze cmd
%clear smaze promenne
%who seznam promenych
%whos promenne + detaily
%why
M = [1 2 3; 4 5 6];
L = [1 0 0; 0 0 1];
M(M > 3)

vek = [10 : -1 : 1];
vek

a = [1 2 3; 4 5 6; 7 8 9];
matrix = [a a a];
matrix

matrix = randi([1 10], 5);
sum(sum(matrix > 5))

matrix(matrix == 5) = 0
matrix

disp(my_func(-5));

% function [] = nazev(a, b, varargin) varargin{}
% nargin vraci pocet argumentu