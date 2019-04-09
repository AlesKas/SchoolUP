(defparameter barberready (make-semaphore 1))
(defparameter customerready (make-semaphore 1))
(defparameter acceschair (make-semaphore 1))
(defvar seats 3)
(defparameter seatsocc 0)

(defun barber ()
  (a-progn
    (progn
      (loop do
            (progn
              (sem-wait customerready)
              (sem-wait acceschair)
              (incf seatsocc)
              (sem-signal barberready)
              (sem-signal acceschair)
              (print "cutting")
              (sleep 2))
        while t))))

(defun customer ()
    (progn
      (sem-wait acceschair)
      (if (> seatsocc 0)
          (progn
            (decf seatsocc)
            (sem-signal customerready)
            (sem-signal acceschair)
            (sem-wait barberready))
        (sem-signal acceschair))))

(defun gethaircut ()
  (barber)
  (wait-to-finish
  (a-dotimes (i 10)
    (customer))))