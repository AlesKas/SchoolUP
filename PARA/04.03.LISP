(defvar pair '())
(defvar zeros 0)
(defvar ones 0)

(defun fce ()
(wait-to-finish
 (let ((isFirst nil)
       (isSecond nil)
       (sended 0)
       (isNulling t))
   (a-progn
     (if isNulling
         (progn
           (setf zeros 0)
           (setf ones 0)
           (setf isNulling nil)))
     (progn
       (setf pair (cons (+ (random 10) 1) (+ 1 (random 10))))
       (setf isFirst t))
     (progn
       (if isFirst
           (if (= (mod (car pair) (cdr pair)) 0)
               (setf sended 1)
             (setf sended 0)))
       (setf isSecond t)
       (setf isFirst nil))
     (progn
       (if isSecond
           (progn
             (if (= sended 1)
               (setf ones (+ ones 1))
             (setf zeros (+ zeros 1)))
           (setf isSecond nil)
           (setf isFirst nil))))))))