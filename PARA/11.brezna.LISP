(defvar coun 0)
(defvar arr (make-array 10 :initial-contents '(t t nil nil nil nil nil t nil t)))
(defun f ()
  (setf coun 0)
  (wait-to-finish
   (a-dotimes (i (/ (length arr) 2))
     (progn
       (make-barrier m)
       (barrier-wait m)
       (if (eql (aref arr i) t)
           (incf coun)))
     (progn
       (make-barrier b)
       (barrier-wait b)
       (if (eql (eref arr (+ i 5)) t)
           (infc coun)))))
  coun)
         

   