## Copyright (C) 2019 Aleš
## 
## This program is free software: you can redistribute it and/or modify it
## under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
## 
## This program is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
## 
## You should have received a copy of the GNU General Public License
## along with this program.  If not, see
## <https://www.gnu.org/licenses/>.

## -*- texinfo -*- 
## @deftypefn {} {@var{retval} =} my_func (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author: Aleš <Aleš@MSI>
## Created: 2019-09-26

function retval = my_func (number)
  retval = number;
  if (number < 0)
    retval = -number;
  endif
endfunction
