;;;; ÚLOHA 10.1.
;; Doplnění logických operací OR a NOT do jazyka

[true add "OR" :value true]
[false add "OR" :value {(arg1) arg1}]

[true add "NOT" :value false]
[false add "NOT" :value true]

;;;; ÚLOHA 10.2
;; Doplnit do jazyka zprávu IS-NIHIL

[object add "IS-NIHIL" :value false]
[nihil add "IS-NIHIL" :value true]

;;;; ÚLOHA 10.3
;; Doplnit do jazyka seznamy

[lobby add "PAIR" :value [object clone]]
[pair add "CAR" :value self]
[pair add "CDR" :value self]
[pair add "CONS" :value {(arg1 arg2) [self set-car arg1] [self set-cdr arg2]}]
[lobby add "EMPTY-LIST" :value [pair clone]]

;;;; ÚLOHA 10.4
;; Zpráva IS-LIST

[pair add "IS-LIST" :value {() [[self cdr] is-list]}]
[object add "IS-LIST" :value false]
[nihil add "IS-LIST" :value true]

;;;;; ÚLOHA 10.5
;; Zpráva length

[nihil add "LENGTH" :value {() zero}]
[pair add "LENGTH" :value {() [[[self cdr] length] succ]}]

;;;;; ÚLOHA 10.6
;; Operace se seznamy

[pair add "APPEND" :value {(arg1) [self set-second [[self cdr] append arg1]]}]
[nihil add "APPEND" :value {(arg1) arg1}]

[pair add "FIND" :value {(arg1) [[[self car] equals arg1] if-true arg1 :else [[self cdr] find arg1]]}]
[nihil add "FIND" :value nihil]

[pair add "REMOVE" :value {(arg1) [[[self car] equals arg1] if-true [self cdr] :else [self set-second [[self crd] remove arg1]]]}]
[nihil add "REMOVE" :value nihil]

[pair add "NTH" :value {(arg1) [[arg1 equals 0] if-true [self car] :else [[self cdr] nth [arg1 - 1]]]}]
[nihil add "NTH" :value nihil]

;;;;; ÚLOHA 10.9
;; Operace s esoterickými čísly

[zero add "*" :value zero]
[one add  "*" :value {(arg1) arg1}]
[[one succ] add "*" :value {(arg1) [arg1 + [[[[self name] - 1] esoteric] * arg1]]}]

[zero add "!" :value one]
[one add "!" :value {() [self * [[[[self name] - 1] esoteric] !]]}]

[zero add "^" :value zero]
[one  add "^" :value {(arg1) one}]
[[one succ] add "^" :value {(arg1) [[arg1 equals one]
                                    if-true
                                    self
                                    :else {() [[arg1 equals zero]
                                               if-true
                                               one
                                               :else{() [self * [self ^ [[[arg1 name] - 1] esoteric]]]}]}]}]
;;;;; ÚLOHA 10.10
;; Primitivum error

[object add "ERROR" :value (lambda (self arg1 &key)
                             (declare (ignore arg1))
                             (error self))]
#|
[[true or true] name]
[[true or false] name]
[[false or false] name]
[[true or true] name]
[[true not] name] 
[[false not] name]

[lobby add "PAIR" :value 
       [[pair clone] cons [one succ]
        :arg2 [[pair clone] cons [[one succ] succ]
               :arg2 [[pair clone] cons [[[one succ] succ] succ]
                      :arg2 [empty-list clone]]]]]
|#