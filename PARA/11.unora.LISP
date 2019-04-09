(setf in 0)
(wait-to-finish
 (a-progn
   (dotimes (i 1000)
     (setf in (+ in 1)))
   (dotimes (i 1000)
     (setf in (+ in 1)))))
(print in)